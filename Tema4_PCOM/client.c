#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>
#include "parson.h"
#include "requests.h"
#include "helpers.h"

#define SERVER_IP           "34.246.184.49"
#define SERVER_PORT          8080
#define INCORRECT_REQUEST   "400"
#define UNAUTHORIZED        "401"
#define ACCESS_DENIED       "403"
#define PAGE_NOT_FOUND      "404"

int is_numeric_string(const char *str, int index) {
    if (str[index] == '\0') {
        return 1;
    } else if (!isdigit(str[index])) {
        return 0;
    }

    return is_numeric_string(str, index + 1);
}

int is_numeric(const char *str) {
    return is_numeric_string(str, 0);
}


void register_user(int *sockfd, char **request_message, char **server_response, char **response_code,
                    char ***cookies, int *cookies_count) {
    char *input_username = calloc(64, sizeof(char));
    printf("username=");
    fgets(input_username, 64, stdin);
    size_t pos = 0;
    while (input_username[pos] != '\0' && input_username[pos] != '\n') {
        pos++;
    }
    input_username[pos] = '\0';

    char *input_password = calloc(64, sizeof(char));
    printf("password=");
    fgets(input_password, 64, stdin);
    pos = 0;
    while (input_password[pos] != '\0' && input_password[pos] != '\n') {
        pos++;
    }
    input_password[pos] = '\0';

    int contains_spaces = 0;
    for (int i = 0; input_username[i] != '\0'; i++) {
        if (isspace(input_username[i])) {
            contains_spaces = 1;
            break;
        }
    }
    for (int i = 0; input_password[i] != '\0'; i++) {
        if (isspace(input_password[i])) {
            contains_spaces = 1;
            break;
        }
    }

    if (contains_spaces) {
        printf("ERROR: Username must not contain spaces!\n\n");
        return;
    }

    JSON_Value *json_payload_value = json_value_init_object();
    JSON_Object *json_payload_object = json_value_get_object(json_payload_value);
    json_object_set_string(json_payload_object, "username", input_username);
    json_object_set_string(json_payload_object, "password", input_password);
    char *json_payload_string = json_serialize_to_string_pretty(json_payload_value);

    *request_message = compute_post_request(SERVER_IP, "/api/v1/tema/auth/register", "application/json", json_payload_string, NULL, NULL, 0);

    json_free_serialized_string(json_payload_string);
    json_value_free(json_payload_value);

    *sockfd = open_connection(SERVER_IP, SERVER_PORT, AF_INET, SOCK_STREAM, 0);
    send_to_server(*sockfd, *request_message);
    *server_response = receive_from_server(*sockfd);

    *response_code = calloc(3, sizeof(char));
    memccpy(*response_code, strchr(*server_response, ' ') + 1, ' ', 3);

    if (strncmp(*response_code, INCORRECT_REQUEST, 3) == 0) {
        printf("ERROR %s - The username %s is already in use!\n\n", *response_code, input_username);
    } else {
        printf("Registration successful for username %s!\n\n", input_username);
    }

    free(input_username);
    free(input_password);
}

void login_user(int *sockfd, char **request_message, char **server_response, char **response_code,
                char ***cookies, int *cookies_count) {
    char *input_username = calloc(64, sizeof(char));
    printf("username=");
    fgets(input_username, 64, stdin);
    size_t pos = 0;
    while (input_username[pos] != '\0' && input_username[pos] != '\n') {
        pos++;
    }
    input_username[pos] = '\0';

    char *input_password = calloc(64, sizeof(char));
    printf("password=");
    fgets(input_password, 64, stdin);
    pos = 0;
    while (input_password[pos] != '\0' && input_password[pos] != '\n') {
        pos++;
    }
    input_password[pos] = '\0';

    int contains_spaces = 0;
    for (int i = 0; input_username[i] != '\0'; i++) {
        if (isspace(input_username[i])) {
            contains_spaces = 1;
            break;
        }
    }
    for (int i = 0; input_password[i] != '\0'; i++) {
        if (isspace(input_password[i])) {
            contains_spaces = 1;
            break;
        }
    }

    if (contains_spaces) {
        printf("ERROR: Password must not contain spaces!\n\n");
        return;
    }

    JSON_Value *json_payload_value = json_value_init_object();
    JSON_Object *json_payload_object = json_value_get_object(json_payload_value);
    json_object_set_string(json_payload_object, "username", input_username);
    json_object_set_string(json_payload_object, "password", input_password);
    char *json_payload_string = json_serialize_to_string_pretty(json_payload_value);

    *request_message = compute_post_request(SERVER_IP, "/api/v1/tema/auth/login", "application/json", json_payload_string, NULL, NULL, 0);

    json_free_serialized_string(json_payload_string);
    json_value_free(json_payload_value);

    *sockfd = open_connection(SERVER_IP, SERVER_PORT, AF_INET, SOCK_STREAM, 0);
    send_to_server(*sockfd, *request_message);
    *server_response = receive_from_server(*sockfd);

    *response_code = calloc(3, sizeof(char));
    memccpy(*response_code, strchr(*server_response, ' ') + 1, ' ', 3);

    if (strncmp(*response_code, INCORRECT_REQUEST, 3) == 0) {
        printf("ERROR %s - Incorrect credentials for username %s!\n\n", *response_code, input_username);
    } else {
        (*cookies) = (char **)calloc(1, sizeof(char *));
        if ((*cookies) == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        (*cookies)[0] = (char *)calloc(LINELEN, sizeof(char));
        if ((*cookies)[0] == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        char *cookie_start = strstr(*server_response, "Set-Cookie: ");
        if (cookie_start != NULL) {
            cookie_start += strlen("Set-Cookie: ");
            char *cookie_end = strchr(cookie_start, ';');
            if (cookie_end != NULL) {
                size_t cookie_length = cookie_end - cookie_start;
                strncpy((*cookies)[0], cookie_start, cookie_length);
                (*cookies)[0][cookie_length] = '\0';
            }
        }

        (*cookies_count)++;

        printf("Logged in successfully as %s!\n\n", input_username);
    }

    free(input_username);
    free(input_password);
}

void check_library_access(int *sockfd, char **request_message, char **server_response, char **response_code,
                    char **authorization_token, char **received_cookies, int cookies_count) {
    if (*authorization_token) {
        printf("ERROR: You currently hold library admission!\n\n");
        return;
    }

    *request_message = compute_get_request(SERVER_IP, "/api/v1/tema/library/access", NULL, NULL, received_cookies, cookies_count);
    
    *sockfd = open_connection(SERVER_IP, SERVER_PORT, AF_INET, SOCK_STREAM, 0);
    send_to_server(*sockfd, *request_message);
    
    *server_response = receive_from_server(*sockfd);

    *response_code = (char *)malloc(4 * sizeof(char));
    if (*response_code == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    char *space_ptr = strchr(*server_response, ' ');
    if (space_ptr != NULL) {
        strncpy(*response_code, space_ptr + 1, 3);
        (*response_code)[3] = '\0';
    }

    if (strncmp(*response_code, UNAUTHORIZED, 3) == 0) {
        printf("ERROR %s - You are currently not logged in!\n\n", *response_code);
    } else {
        JSON_Value *json_value = json_parse_string(strchr(*server_response, '{'));
        if (json_value != NULL) {
            JSON_Object *json_object = json_value_get_object(json_value);
            const char *token_str = json_object_get_string(json_object, "token");
            if (token_str != NULL) {
                int token_len = strlen(token_str);
                *authorization_token = (char *)calloc(token_len + 1, sizeof(char));
                strncpy(*authorization_token, token_str, token_len);
                (*authorization_token)[token_len] = '\0';
                printf("Access to the library has been authorized!\n\n");
            }
            json_value_free(json_value);
        }
    }
}

void display_books(char *server_response) {
    char *books_start = strchr(server_response, '[');
    if (books_start != NULL && strncmp(books_start, "[]", 2) == 0) {
        printf("Your book list is empty!\n\n");
    } else {
        JSON_Value *json_value = json_parse_string(books_start);
        if (json_value != NULL) {
            JSON_Array *books = json_value_get_array(json_value);
            for (int i = 0; i < json_array_get_count(books); i++) {
                JSON_Object *book = json_array_get_object(books, i);
                printf("\nid=%d\n", (int)json_object_get_number(book, "id"));
                printf("title=%s\n", json_object_get_string(book, "title"));
            }
            printf("\n");
            json_value_free(json_value);
        }
    }
}

void get_books(int *sockfd, char **request_message, char **server_response, char **response_code, char *authorization_token) {
    *request_message = compute_get_request(SERVER_IP, "/api/v1/tema/library/books", NULL, authorization_token, NULL, 0);
    
    *sockfd = open_connection(SERVER_IP, SERVER_PORT, AF_INET, SOCK_STREAM, 0);
    send_to_server(*sockfd, *request_message);
    
    *server_response = receive_from_server(*sockfd);
    *response_code = (char *)malloc(4 * sizeof(char));
    if (*response_code == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    char *space_ptr = strchr(*server_response, ' ');
    if (space_ptr != NULL) {
        strncpy(*response_code, space_ptr + 1, 3);
        (*response_code)[3] = '\0';
    }

    if (strncmp(*response_code, ACCESS_DENIED, 3) == 0) {
        printf("ERROR %s - You are not permitted to access the library!\n\n", *response_code);
    } else {
        display_books(*server_response);
    }
}

void display_book_details(char *server_response) {
    JSON_Value *json_value = json_parse_string(strchr(server_response, '{'));
    if (json_value != NULL) {
        JSON_Object *book = json_value_get_object(json_value);

        printf("\nid=%d\n", (int)json_object_get_number(book, "id"));
        printf("title=%s\n", json_object_get_string(book, "title"));
        printf("author=%s\n", json_object_get_string(book, "author"));
        printf("publisher=%s\n", json_object_get_string(book, "publisher"));
        printf("genre=%s\n", json_object_get_string(book, "genre"));
        printf("page_count=%d\n\n", (int)json_object_get_number(book, "page_count"));

        json_value_free(json_value);
    }
}

void get_book(int *sockfd, char **request_message, char **server_response,
              char **response_code, char *authorization_token) {
    char *book_id = (char *)malloc(16 * sizeof(char));
    if (book_id == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    printf("id=");
    fgets(book_id, 16, stdin);
    char *newline_ptr = strchr(book_id, '\n');
    if (newline_ptr != NULL) {
        *newline_ptr = '\0';
    }

    if (!is_numeric(book_id)) {
        printf("ERROR: Input a number that meets the criteria!\n\n");
        free(book_id);
        return;
    }

    char *url = (char *)malloc(LINELEN * sizeof(char));
    if (url == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    sprintf(url, "/api/v1/tema/library/books/%s", book_id);
    
    *request_message = compute_get_request(SERVER_IP, url, NULL, authorization_token, NULL, 0);
    
    *sockfd = open_connection(SERVER_IP, SERVER_PORT, AF_INET, SOCK_STREAM, 0);
    send_to_server(*sockfd, *request_message);
    *server_response = receive_from_server(*sockfd);

    *response_code = (char *)malloc(4 * sizeof(char));
    if (*response_code == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    memccpy(*response_code, strchr(*server_response, ' ') + 1, ' ', 3);

    if (strncmp(*response_code, ACCESS_DENIED, 3) == 0) {
        printf("ERROR %s - Access not allowed!\n\n", *response_code);
    } else if (strncmp(*response_code, PAGE_NOT_FOUND, 3) == 0) {
        printf("ERROR %s - Book with ID %s was not found!\n\n", *response_code, book_id);

    } else {
        display_book_details(*server_response);
    }

    free(url);
    free(book_id);
}

void delete_book(int *sockfd, char **request_message, char **server_response,
                 char **response_code, char *authorization_token) {
    char *book_id = (char *)malloc(16 * sizeof(char));
    if (book_id == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    printf("id=");
    fgets(book_id, 16, stdin);
    char *newline_ptr = strchr(book_id, '\n');
    if (newline_ptr != NULL) {
        *newline_ptr = '\0';
    }

    if (!is_numeric(book_id)) {
        printf("ERROR: Input a number that meets the criteria!\n\n");
        free(book_id);
        return;
    }

    char *url = (char *)malloc(LINELEN * sizeof(char));
    if (url == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    sprintf(url, "/api/v1/tema/library/books/%s", book_id);
    
    *request_message = compute_delete_request(SERVER_IP, url, NULL, authorization_token, NULL, 0);
    
    *sockfd = open_connection(SERVER_IP, SERVER_PORT, AF_INET, SOCK_STREAM, 0);
    send_to_server(*sockfd, *request_message);
    *server_response = receive_from_server(*sockfd);

    *response_code = (char *)malloc(4 * sizeof(char));
    if (*response_code == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    memccpy(*response_code, strchr(*server_response, ' ') + 1, ' ', 3);

    if (strncmp(*response_code, ACCESS_DENIED, 3) == 0) {
        printf("ERROR %s - Access not allowed!\n\n", *response_code);
    } else if (strncmp(*response_code, PAGE_NOT_FOUND, 3) == 0) {
        printf("ERROR %s - Book with ID %s was not found!\n\n", *response_code, book_id);

    } else {
        printf("The book with ID %s has been successfully deleted!\n\n", book_id);
    }

    free(url);
    free(book_id);
}


char *read_input(const char *prompt, size_t max_len) {
    char *input = (char *)malloc(max_len * sizeof(char));
    if (input == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    printf("%s", prompt);
    fgets(input, max_len, stdin);

    char *newline_ptr = strchr(input, '\n');
    if (newline_ptr != NULL) {
        *newline_ptr = '\0';
    }

    return input;
}

void add_new_book(int *sockfd, char **request_message, char **server_response, char **response_code, char *authorization_token) {
    char *title = read_input("title=", 128);
    char *author = read_input("author=", 128);
    char *publisher = read_input("publisher=", 128);
    char *genre = read_input("genre=", 128);
    char *page_count = read_input("page_count=", 16);

    if (!strlen(title) || !strlen(author) || !strlen(publisher) || !strlen(genre) || !strlen(page_count) || !is_numeric(page_count)) {
        if (!is_numeric(page_count)) {
            printf("ERROR: Input a number that meets the criteria!\n\n");
        } else {
            printf("ERROR: Please fill in all book fields!\n\n");
        }
        free(title);
        free(author);
        free(publisher);
        free(genre);
        free(page_count);
        return;
    }

    JSON_Value *json_value = json_value_init_object();
    JSON_Object *json_object = json_value_get_object(json_value);

    json_object_set_string(json_object, "title", title);
    json_object_set_string(json_object, "author", author);
    json_object_set_string(json_object, "publisher", publisher);
    json_object_set_string(json_object, "genre", genre);
    json_object_set_number(json_object, "page_count", atoi(page_count));
    char *json_payload = json_serialize_to_string_pretty(json_value);

    *request_message = compute_post_request(SERVER_IP, "/api/v1/tema/library/books", "application/json", json_payload, authorization_token, NULL, 0);
    *sockfd = open_connection(SERVER_IP, SERVER_PORT, AF_INET, SOCK_STREAM, 0);
    send_to_server(*sockfd, *request_message);
    *server_response = receive_from_server(*sockfd);
    json_free_serialized_string(json_payload);
    json_value_free(json_value);

    *response_code = calloc(3, sizeof(char *));
    memccpy(*response_code, strchr(*server_response, ' ') + 1, ' ', 3);

    if (strncmp(*response_code, ACCESS_DENIED, 3) == 0) {
        printf("ERROR %s - Access not allowed!\n\n", *response_code);
    } else {
        printf("Book added!\n\n");
    }

    free(title);
    free(author);
    free(publisher);
    free(genre);
    free(page_count);
}

void logout(int *sockfd, char **request_message, char **server_response, char **response_code,
            char **authorization_token, char ***received_cookies, int *cookies_count) {
    *request_message = compute_get_request(SERVER_IP, "/api/v1/tema/auth/logout", NULL, NULL, *received_cookies, *cookies_count);
    *sockfd = open_connection(SERVER_IP, SERVER_PORT, AF_INET, SOCK_STREAM, 0);
    send_to_server(*sockfd, *request_message);
    *server_response = receive_from_server(*sockfd);

    *response_code = (char *)malloc(4 * sizeof(char));
    if (*response_code == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    memccpy(*response_code, strchr(*server_response, ' ') + 1, ' ', 3);

    if (strncmp(*response_code, INCORRECT_REQUEST, 3) == 0) {
        printf("ERROR %s - You are currently not logged in!\n\n", *response_code);
    } else {
        free(*authorization_token);
        *authorization_token = NULL;
        free((*received_cookies)[0]);
        free(*received_cookies);
        *received_cookies = NULL;
        *cookies_count = 0;
        printf("You have been successfully logged out!\n\n");
    }
}

int main(int argc, char *argv[]) {
    char **user_cookies = NULL;
    char *authorization_token = NULL;
    int cookies_count = 0;

    char *user_input = calloc(32, sizeof(char));
    while (fgets(user_input, 32, stdin) && strcmp(user_input, "exit\n") != 0) {
        int command_executed = 0;
        int sockfd = 0;
        char *request_message = NULL;
        char *server_response = NULL;
        char *response_code = NULL;

        if (strcmp(user_input, "register\n") == 0) {
            register_user(&sockfd, &request_message, &server_response, &response_code, &user_cookies, &cookies_count);
            command_executed++;
        } else if (strcmp(user_input, "login\n") == 0) {
            login_user(&sockfd, &request_message, &server_response, &response_code, &user_cookies, &cookies_count);
            command_executed++;
        } else if (strcmp(user_input, "enter_library\n") == 0) {
            check_library_access(&sockfd, &request_message, &server_response, &response_code, &authorization_token, user_cookies, cookies_count);
            command_executed++;
        } else if (strcmp(user_input, "get_books\n") == 0) {
            get_books(&sockfd, &request_message, &server_response, &response_code, authorization_token);
            command_executed++;
        } else if (strcmp(user_input, "get_book\n") == 0) {
            get_book(&sockfd, &request_message, &server_response, &response_code, authorization_token);
            command_executed++;
        } else if (strcmp(user_input, "add_book\n") == 0) {
            add_new_book(&sockfd, &request_message, &server_response, &response_code, authorization_token);
            command_executed++;
        } else if (strcmp(user_input, "delete_book\n") == 0) {
            delete_book(&sockfd, &request_message, &server_response, &response_code, authorization_token);
            command_executed++;
        } else if (strcmp(user_input, "logout\n") == 0) {
            logout(&sockfd, &request_message, &server_response, &response_code, &authorization_token, &user_cookies, &cookies_count);
            command_executed++;
        } else if (!command_executed) {
            printf("Unknown command\n");
        } else if (sockfd) {
            free(request_message);
            free(server_response);
            free(response_code);
            close(sockfd);
        }
    }

    free(user_input);
    return 0;
}