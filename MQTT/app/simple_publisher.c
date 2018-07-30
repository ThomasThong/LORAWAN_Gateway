
/**
 * @file
 * A simple program to that publishes the current time whenever ENTER is pressed. 
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include <mqtt.h>
#include "templates/posix_sockets.h"

#define MQTTSERVER "m11.cloudmqtt.com"
#define PORT 	   "12234"
#define USER       "esp8266"
#define PASS       "123456789@"
#define TOPIC      "demo"
/**
 * @brief The function that would be called whenever a PUBLISH is received.
 * 
 * @note This function is not used in this example. 
 */
void publish_callback(void** unused, struct mqtt_response_publish *published);

/**
 * @brief The client's refresher. This function triggers back-end routines to 
 *        handle ingress/egress traffic to the broker.
 * 
 * @note All this function needs to do is call \ref __mqtt_recv and 
 *       \ref __mqtt_send every so often. I've picked 100 ms meaning that 
 *       client ingress/egress traffic will be handled every 100 ms.
 */
void* client_refresher(void* client);

/**
 * @brief Safelty closes the \p sockfd and cancels the \p client_daemon before \c exit. 
 */
void exit_example(int status, int sockfd, pthread_t *client_daemon);

/**
 * A simple program to that publishes the current time whenever ENTER is pressed. 
 */
int main() 
{
    /* open the non-blocking TCP socket (connecting to the broker) */
    printf("program start\r\n");
    int sockfd = open_nb_socket(MQTTSERVER, PORT);
    if (sockfd == -1) {
        perror("Failed to open socket: ");
        exit_example(EXIT_FAILURE, sockfd, NULL);
    }
    printf("socket opened\r\n");

    /* setup a client */
    struct mqtt_client client;
    uint8_t sendbuf[2048]; /* sendbuf should be large enough to hold multiple whole mqtt messages */
    uint8_t recvbuf[1024]; /* recvbuf should be large enough any whole mqtt message expected to be received */
    mqtt_init(&client, sockfd, sendbuf, sizeof(sendbuf), recvbuf, sizeof(recvbuf), publish_callback);
    mqtt_connect(&client, "publishing_client", NULL, NULL, 0, USER, PASS, 0, 400);

    /* check that we don't have any errors */
    if (client.error != MQTT_OK) {
        fprintf(stdout, "error: %s\n", mqtt_error_str(client.error));
        exit_example(EXIT_FAILURE, sockfd, NULL);
    }

    /* start a thread to refresh the client (handle egress and ingree client traffic) */
    pthread_t client_daemon;
    if(pthread_create(&client_daemon, NULL, client_refresher, &client)) {
        fprintf(stdout, "Failed to start client daemon.\n");
        exit_example(EXIT_FAILURE, sockfd, NULL);

    }

    /* start publishing the time */
    printf ("enter to send message \r\n");
    while(fgetc(stdin) == '\n') {

        /* print a message */
        char application_message[10];
        snprintf(application_message, sizeof(application_message), "Hello");
        printf("published : \"%s\"\r\n", application_message);

        /* publish the time */
        mqtt_publish(&client, "demo", application_message, strlen(application_message) + 1, MQTT_PUBLISH_QOS_0);

        /* check for errors */
        if (client.error != MQTT_OK) {
            fprintf(stdout, "error: %s\n", mqtt_error_str(client.error));
            exit_example(EXIT_FAILURE, sockfd, &client_daemon);
        }
    }   

    /* disconnect */
    printf("\n disconnecting from %s\n", MQTTSERVER);
    sleep(1);

    /* exit */ 
    exit_example(EXIT_SUCCESS, sockfd, &client_daemon);
}

void exit_example(int status, int sockfd, pthread_t *client_daemon)
{
    if (sockfd != -1) close(sockfd);
    if (client_daemon != NULL) pthread_cancel(*client_daemon);
    exit(status);
}

void publish_callback(void** unused, struct mqtt_response_publish *published) 
{
    /* not used in this example */
}

void* client_refresher(void* client)
{
    while(1) 
    {
        mqtt_sync((struct mqtt_client*) client);
        usleep(100000U);
    }
    return NULL;
}
