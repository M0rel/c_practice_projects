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
        struct sockaddr_in address = {0};
        int socket_fd = 0;
        int connect_socket_fd = 0;
        int opt = 1;
        int rc = 0;
        char buff[BUFF_SIZE] = {0};
        socklen_t addrlen = sizeof(address);
        char *reply_msg = "Message received";
        
        socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (-1 == socket_fd) {
                LOG_ERR("Failed to create socket\n");

                return -1;
        }

        LOG_INFO("Socket created\n");

        rc = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        if (0 != rc) {
                LOG_ERR("Failed to change socket options. Error: %s\n",
                        strerror(errno));

                rc = -1;

                goto exit_socket;
        }

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);

        rc = bind(socket_fd, (struct sockaddr *)&address, sizeof(address));
        if (0 != rc) {
                LOG_ERR("Failed to bind socket. Error: %s\n", strerror(errno));

                rc = -1;

                goto exit_socket;
        }

        rc = listen(socket_fd, 1);
        if (0 != rc) {
                LOG_ERR("Failed to set socket in listen mode. Error: %s\n",
                        strerror(errno));

                rc = -1;

                goto exit_socket;
        }

        LOG_INFO("Waiting for connections...\n");

        connect_socket_fd = accept(socket_fd, (struct sockaddr*)&address,
                  &addrlen);
        if (0 > connect_socket_fd) {
                LOG_ERR("Failed to process accept. Error: %s\n",
                        strerror(errno));

                rc = -1;

                goto exit_socket;
        }

        LOG_INFO("Client with id %d connected\n", connect_socket_fd);

        read(connect_socket_fd, buff, BUFF_SIZE - 1);

        LOG_INFO("\nReceived message:\n");
        LOG_INFO("-------------------------------\n");
        LOG_INFO("%s\n", buff);
        LOG_INFO("-------------------------------\n\n");

        send(connect_socket_fd, reply_msg, strlen(reply_msg), 0);
        LOG_INFO("Reply message sent\n");

        close(connect_socket_fd);

exit_socket:
        close(socket_fd);

        return rc;
}
