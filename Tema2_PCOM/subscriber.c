#include <arpa/inet.h>
#include <math.h>
#include <netdb.h>
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

#define SIGN(sign, value) ((sign == 1) ? (-value) : (value))

void show_int(int len, char *buff) {
    uint32_t nrint;
    memcpy(&nrint, buff + sizeof(uint8_t), sizeof(uint32_t));
    printf("INT - %d\n", (int)ntohl(nrint));
    fflush(stdout);
}

void show_short_real(int len, char *buff) {
    uint16_t nrshort;
    memcpy(&nrshort, buff, 2);
    printf("SHORT_REAL - %.2f\n", (double)ntohs(nrshort) / 100);
    fflush(stdout);
}

void show_float(int len, char *buff) {
    uint32_t nrfloat;
    uint8_t p;
    memcpy(&p, buff + sizeof(uint32_t) + sizeof(uint8_t), sizeof(uint8_t));
    memcpy(&nrfloat, buff + sizeof(uint8_t), sizeof(uint32_t));
    printf("FLOAT - %.*f\n", p, (double)ntohl(nrfloat) / pow(10, p));
    fflush(stdout);
}

void show_string(int len, char *buff) {
    char text[1501];
    memcpy(text, buff, len);
    text[len] = '\0';
    printf("STRING - %s\n", text);
    fflush(stdout);
}

// Definirea vectorului de pointeri la functii
void (*show_message_functions[])(int, char*) = {
    show_int,
    show_short_real,
    show_float,
    show_string
};

// Functia principala care va apela functia corespunzatoare tipului de mesaj
void show_message(uint8_t type, int len, char *buff) {
    if (type < sizeof(show_message_functions) / sizeof(show_message_functions[0])) {
        show_message_functions[type](len, buff);
    } else {
        printf("Unknown message type\n");
    }
}

// Functie auxiliara pentru tratarea erorilor
void check_error(int condition, const char *message) {
    if (condition) {
        perror(message);
        exit(EXIT_FAILURE);
    }
}

void establishTcpConnWithServer(int tcp, char *argv[]) {
    // Setare TCP_NODELAY
    int nodelay = 1;
    check_error(setsockopt(tcp, IPPROTO_TCP, TCP_NODELAY, &nodelay, sizeof(int)), "nagle");

    // Initializare si conectare la server
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    check_error(inet_aton(argv[2], &serv_addr.sin_addr), "inet_aton");
    serv_addr.sin_port = htons(atoi(argv[3]));

    // Setare SO_REUSEADDR
    int enable = 1;
    setsockopt(tcp, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

    check_error(connect(tcp, (struct sockaddr *)&serv_addr, sizeof(serv_addr)), "connect");

    // Trimitere date catre server
    ssize_t ret = send(tcp, argv[1], strlen(argv[1]), 0);
    check_error(ret < 0, "send");
}

void handleSubscriptionsAndMessages(int tcp) {
    while (1) {
        struct pollfd pfds[MAX_CONNECTIONS];
        int nfds = 0;

        pfds[nfds].fd = STDIN_FILENO;
        pfds[nfds].events = POLLIN;
        nfds++;

        pfds[nfds].fd = tcp;
        pfds[nfds].events = POLLIN;
        nfds++;

        poll(pfds, nfds, -1);

        for (int i = 0; i < nfds; ++i) {
            if (pfds[i].revents & POLLIN) {
                switch (pfds[i].fd) {
                    case STDIN_FILENO: {
                        char buffer[BUFFLEN];
                        memset(buffer, 0, sizeof(buffer));
                        int n = read(STDIN_FILENO, buffer, sizeof(buffer));
                        if (n < 0) {
                            perror("read");
                            exit(EXIT_FAILURE);
                        }

                        struct subscriber_message sms;
                        char cmd[12];
                        int sf;
                        if (sscanf(buffer, "%s %s %d", cmd, sms.topic, &sf) == 3) {
                            sms.sf = sf;
                            if (strcmp(cmd, "exit") == 0) {
                                return;
                            } else if (strcmp(cmd, "subscribe") == 0 && (sms.sf == 0 || sms.sf == 1)) {
                                memcpy(sms.command, cmd, strlen(cmd));
                                n = send(tcp, &sms, sizeof(struct subscriber_message), 0);
                                if (n < 0) {
                                    perror("send");
                                    exit(EXIT_FAILURE);
                                }
                                printf("Subscribed to topic.\n");
                                fflush(stdout);
                            } else if (strcmp(cmd, "unsubscribe") == 0) {
                                memcpy(sms.command, cmd, strlen(cmd));
                                n = send(tcp, &sms, sizeof(struct subscriber_message), 0);
                                if (n < 0) {
                                    perror("send");
                                    exit(EXIT_FAILURE);
                                }
                                printf("Unsubscribed from topic.\n");
                                fflush(stdout);
                            }
                        }
                        break;
                    }
                    default: {
                        int rc;
                        struct server_message svsms;
                        rc = recv(tcp, &svsms, sizeof(struct server_message), 0);
                        if (rc < 0) {
                            perror("recv");
                            exit(EXIT_FAILURE);
                        } else if (rc == 0) {
                            return;
                        }

                        char buff[svsms.len];
                        rc = recv(tcp, buff, svsms.len, 0);
                        if (rc < 0) {
                            perror("recv");
                            exit(EXIT_FAILURE);
                        }

                        printf("%s:%d - %s - ", inet_ntoa(svsms.addr.sin_addr),
                               ntohs(svsms.addr.sin_port), svsms.topic);
                        fflush(stdout);
                        break;
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);

  if (argc < 4) {
    fprintf(stderr, "Usage: %s client_id server_address server_port\n", argv[0]);
    exit(0);
  }

  int tcp = socket(AF_INET, SOCK_STREAM, 0);
  DIE(tcp < 0, "tcp socket");

  establishTcpConnWithServer(tcp, argv);
  handleSubscriptionsAndMessages(tcp);
  close(tcp);
  return 0;
}