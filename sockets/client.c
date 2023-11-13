#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

#define LOG_ERR(msg, ...)       printf(msg, ##__VA_ARGS__)
#define LOG_INFO(msg, ...)      printf(msg, ##__VA_ARGS__)

#define PORT            8080
#define BUFF_SIZE       1024

int main(int argc, char **argv)
{
        struct sockaddr_in server_address = {0};
        int client_fd = 0;
        int rc = 0;
        char buff[BUFF_SIZE] = {0};
        char *send_msg = "That is a message from client";
        
        client_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (client_fd < 0) {
                LOG_ERR("Failed to create socket\n");

                return -1;
        }

        LOG_INFO("Client socket created\n");

        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(PORT);

        rc = inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);
        if (0 >= rc) {
                LOG_ERR("Failed to convert IP string to binary representation. "
                        "Error: %s\n", strerror(errno));

                rc = -1;

                goto exit_socket;
        }

        LOG_INFO("Connecting to socket...\n");

        rc = connect(client_fd, (struct sockaddr*)&server_address,
                     sizeof(server_address));
        if (0 > rc) {
                LOG_ERR("Server connection failed. Error: %s\n",
                        strerror(errno));

                rc = -1;

                goto exit_socket;
        }

        send(client_fd, send_msg, strlen(send_msg), 0);
        LOG_INFO("Message to server sent\n");

        read(client_fd, buff, BUFF_SIZE - 1);

        LOG_INFO("\nReply message from server:\n");
        LOG_INFO("-------------------------------\n");
        LOG_INFO("%s\n", buff);
        LOG_INFO("-------------------------------\n");

exit_socket:
        close(client_fd);

        return rc;
}
