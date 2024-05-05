#ifndef _HELPERS_H
#define _HELPERS_H 1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/in.h>

#define MAX_CONNECTIONS 32
#define TOPIC_SIZE 50
#define TYPE_SIZE 1
#define BUFFLEN 256


#define DIE(assertion, call_description)                                       \
  do {                                                                         \
    if (assertion) {                                                           \
      fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__);                       \
      perror(call_description);                                                \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)


struct subscriber_message {
	char command[20];
	char topic[51];
	uint8_t sf;
	
};

struct udp_message {
	char topic[TOPIC_SIZE];
	uint8_t type;
	char data[1500];
};

struct server_message {
	int len;
	struct sockaddr_in addr;
	char topic[51];
	uint8_t data_type;
};

struct subscriber {
    char client_id[11];
    char subscriptions[100][51];
    int num_subscriptions;
    int socket_fd;
    uint8_t is_connected;
    int subscription_flags[100];
    int num_missed_messages;
    struct udp_message missed_messages[100];
};

#endif
