#include <arpa/inet.h>
#include <math.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <poll.h>
#include "helpers.h"

int findSubscriberByClientId(struct subscriber *subs, char *client_id, int current_pos, int max_pos) {
    if (current_pos > max_pos)
        return -1;
    
    if (strcmp(subs[current_pos].client_id, client_id) == 0)
        return current_pos;
    
    return findSubscriberByClientId(subs, client_id, current_pos + 1, max_pos);
}

int findSubscriberId(struct subscriber *subs, char *client_id, int clients_num) {
    return findSubscriberByClientId(subs, client_id, 0, clients_num);
}

int findTextByInfo(char text[100][51], int current_pos, int max, char info[51]) {
    if (current_pos >= max)
        return -1;
    
    if (strcmp(text[current_pos], info) == 0)
        return current_pos;
    
    return findTextByInfo(text, current_pos + 1, max, info);
}

int findText(char text[100][51], int max, char info[51]) {
    return findTextByInfo(text, 0, max, info);
}

int findSubscribersBySocket_fd(struct subscriber *subs, int clients_num, int i, int current_pos) {
    if (current_pos >= clients_num)
        return -1;

    if (subs[current_pos].socket_fd == i)
        return current_pos;

    return findSubscribersBySocket_fd(subs, clients_num, i, current_pos + 1);
}

int findSubscribers(struct subscriber *subs, int clients_num, int i) {
    return findSubscribersBySocket_fd(subs, clients_num, i, 0);
}

void prepareServerForComm(int tcp, int udp, uint16_t portno) {
    struct sockaddr_in serv_addr;
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = portno;
    serv_addr.sin_family = AF_INET;
    
    // Setam optiunea TCP_NODELAY
    int ret = setsockopt(tcp, IPPROTO_TCP, TCP_NODELAY, &(int){1}, sizeof(int));
    if (ret < 0) {
        perror("setsockopt TCP_NODELAY failed");
        exit(EXIT_FAILURE);
    }

    // Setam optiunea SO_REUSEADDR pentru TCP
    int enable = 1;
    if (setsockopt(tcp, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        perror("setsockopt SO_REUSEADDR failed");

    // Bind TCP socket
    ret = bind(tcp, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr));
    if (ret < 0) {
        perror("bind TCP failed");
        exit(EXIT_FAILURE);
    }

    // Bind UDP socket
    ret = bind(udp, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr));
    if (ret < 0) {
        perror("bind UDP failed");
        exit(EXIT_FAILURE);
    }

    // Listen - TCP socket
    ret = listen(tcp, 5);
    if (ret < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}

void handleExitCommand(struct pollfd poll_fds[], int num_clients, int tcp, int udp, struct subscriber *subs) {
    for (int i = 0; i < num_clients; i++) {
        if (poll_fds[i].revents & POLLIN) {
            close(poll_fds[i].fd);
        }
    }
    close(udp);
    free(subs);
    close(tcp);
    exit(0);
}

void handleUdpMessage(struct udp_message *udp_message, struct subscriber *subs, int clients_num, struct server_message *svmessage) {
    /* Extrage informatiile din mesajul UDP si le pregateste pentru trimiterea catre abonati
    Verifica daca abonatii sunt interesati de acest mesaj si trimite-le mesajul */
    for (int j = 0; j < clients_num; j++) {
        for (int k = 0; k < subs[j].num_subscriptions; k++) {
            if (!strcmp(subs[j].subscriptions[k], udp_message->topic) &&
                !subs[j].is_connected && subs[j].subscription_flags[k]) {
                // Daca abonatul nu este conectat si are optiunea SF activata, adauga mesajul la lista de mesaje pierdute
                subs[j].missed_messages[subs[j].num_missed_messages++] = *udp_message;
                subs[j].num_missed_messages++;
            } else if (subs[j].is_connected && !strcmp(subs[j].subscriptions[k], udp_message->topic)) {
                // Daca abonatul este conectat si este interesat de mesaj, trimite-l
                memcpy(svmessage->topic, udp_message->topic, sizeof(udp_message->topic));
                memcpy(&(svmessage->data_type), &(udp_message->type), sizeof(udp_message->type));
                svmessage->len = sizeof(struct udp_message) - sizeof(udp_message->topic) - sizeof(udp_message->type);
                int n = send(subs[j].socket_fd, svmessage, sizeof(struct server_message), 0);
                DIE(n < 0, "send");
                n = send(subs[j].socket_fd, udp_message->data, svmessage->len, 0);
                DIE(n < 0, "send");
            }
        }
    }
}

void handleUdp(struct pollfd poll_fds[], int udp, struct subscriber *subs, int *clients_num, socklen_t clilen) {
    struct server_message svmessage;
    struct udp_message udp_message;
    ssize_t ret = recvfrom(udp, &udp_message, sizeof(udp_message), 0, (struct sockaddr *)&(svmessage.addr), &clilen);
    DIE(ret < 0, "recvfrom");
    handleUdpMessage(&udp_message, subs, *clients_num, &svmessage);
}

void handleTcpConnection(struct pollfd poll_fds[], int newtcp, struct sockaddr_in *cli_addr, socklen_t clilen, struct subscriber *subs, int *clients_num) {
    char client_id[11];
    int n = recv(newtcp, client_id, 10, 0);
    DIE(n < 0, "recv");

    int subscriber_found = findSubscriberId(subs, client_id, *clients_num);

    if (subscriber_found == -1) {
        printf("New client %s connected from %s:%d\n", client_id,
               inet_ntoa(cli_addr->sin_addr), ntohs(cli_addr->sin_port));
        fflush(stdout);

        poll_fds[*clients_num].fd = newtcp;
        poll_fds[*clients_num].events = POLLIN;
        (*clients_num)++;

        subs[*clients_num].socket_fd = newtcp;
        subs[*clients_num].is_connected = 1;
        strcpy(subs[*clients_num].client_id, client_id);
        subs[*clients_num].num_subscriptions = 0;
    } else {
        if (subs[subscriber_found].is_connected) {
            close(newtcp);
            printf("Client %s already connected.\n", client_id);
            fflush(stdout);
        } else {
            subs[subscriber_found].is_connected = 1;
            printf("New client %s connected from %s:%d\n", client_id,
                   inet_ntoa(cli_addr->sin_addr), ntohs(cli_addr->sin_port));
            fflush(stdout);

            poll_fds[*clients_num].fd = newtcp;
            poll_fds[*clients_num].events = POLLIN;
            (*clients_num)++;
            
            int i = 0;
            while (subs[subscriber_found].num_missed_messages) {
                struct server_message svmessage;
                memcpy(svmessage.topic, subs[subscriber_found].missed_messages[i].topic, TOPIC_SIZE);
                memcpy(&(svmessage.data_type), &(subs[subscriber_found].missed_messages[i].type), TYPE_SIZE);
                svmessage.len = sizeof(struct udp_message) - TOPIC_SIZE - TYPE_SIZE;
                n = send(subs[subscriber_found].socket_fd, &svmessage, sizeof(struct server_message), 0);
                DIE(n < 0, "send");
                n = send(subs[subscriber_found].socket_fd, subs[subscriber_found].missed_messages[i].data, svmessage.len, 0);
                DIE(n < 0, "send");
                i++;
                subs[subscriber_found].num_missed_messages--;
            }
        }
    }
}

void handleSubscriberMessage(struct subscriber_message *message, struct subscriber *subs, int idx) {
    if (!strcmp(message->command, "subscribe")) {
        strcpy(subs[idx].subscriptions[subs[idx].num_subscriptions], message->topic);
        subs[idx].subscription_flags[subs[idx].num_subscriptions++] = message->sf;
    }
    if (!strcmp(message->command, "unsubscribe")) {
        int j = findText(subs[idx].subscriptions, subs[idx].num_subscriptions, message->topic);
        if (j != -1) {
            strcpy(subs[idx].subscriptions[j], subs[idx].subscriptions[subs[idx].num_subscriptions - 1]);
            strcpy(subs[idx].subscriptions[subs[idx].num_subscriptions - 1], "/0");
            subs[idx].subscription_flags[j] = subs[idx].subscription_flags[subs[idx].num_subscriptions - 1];
            subs[idx].subscription_flags[--subs[idx].num_subscriptions] = 0;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s server_port\n", argv[0]);
        exit(0);
    }

    setvbuf(stdout, NULL, _IONBF, BUFSIZ);

    int tcp, udp, portno;
    struct sockaddr_in cli_addr;
    struct subscriber *subs = malloc(1000 * sizeof(struct subscriber));
    int n, ret, clients_num = 0;
    socklen_t clilen = sizeof(cli_addr);

    tcp = socket(AF_INET, SOCK_STREAM, 0);
    DIE(tcp < 0, "socket");

    udp = socket(AF_INET, SOCK_DGRAM, 0);
    DIE(udp < 0, "socket");

    sscanf(argv[1], "%d", &portno);
    DIE(portno == 0, "sscanf");

    prepareServerForComm(tcp, udp, htons(portno));

    struct pollfd poll_fds[32];

    int num_clients = 3;
    poll_fds[0].fd = tcp;
    poll_fds[0].events = POLLIN;

    poll_fds[1].fd = udp;
    poll_fds[1].events = POLLIN;

    poll_fds[2].fd = STDIN_FILENO;
    poll_fds[2].events = POLLIN;
    while (1) {
        ret = poll(poll_fds, num_clients, -1);
        DIE(ret < 0, "poll");

        for (int i = 0; i < num_clients; i++) {
            if (poll_fds[i].revents & POLLIN) {
                if (poll_fds[i].fd == STDIN_FILENO) {
                    char buffer[BUFFLEN];
                    n = read(STDIN_FILENO, buffer, sizeof(buffer));
                    DIE(n < 0, "read");
                    if (!strncmp(buffer, "exit", 4)) {
                        handleExitCommand(poll_fds, num_clients, tcp, udp, subs);
                    }
                } else if (poll_fds[i].fd == udp) {
                    handleUdp(poll_fds, udp, subs, &clients_num, clilen);
                } else if (poll_fds[i].fd == tcp) {
                    int newtcp = accept(tcp, (struct sockaddr *)&cli_addr, &clilen);
                    DIE(newtcp < 0, "accept");
                    handleTcpConnection(poll_fds, newtcp, &cli_addr, clilen, subs, &clients_num);
                } else {
                    struct subscriber_message message;
                    n = recv(poll_fds[i].fd, &message, sizeof(struct subscriber_message), 0);
                    DIE(n < 0, "recv");
                    int idx = findSubscribers(subs, clients_num, poll_fds[i].fd);

                    if (n == 0) {
                        printf("Client %s disconnected.\n", subs[idx].client_id);
                        fflush(stdout);
                        close(poll_fds[i].fd);
                        subs[idx].is_connected = 0;
                    } else {
                        if (n == sizeof(struct subscriber_message)) {
                            handleSubscriberMessage(&message, subs, idx);
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < num_clients; i++) {
        if (poll_fds[i].revents & POLLIN) {
            close(poll_fds[i].fd);
        }
    }

  close(tcp);
  close(udp);
  free(subs);
  return 0;
}
