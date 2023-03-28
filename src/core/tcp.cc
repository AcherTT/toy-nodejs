#include <ev.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>

#define SERVER_PORT 9000

static void signal_cb(EV_P_ ev_signal *w, int revents)
{
    ev_break(EV_A_ EVBREAK_ALL);
}

static void read_cb(EV_P_ ev_io *w, int revents)
{
    char buf[1024];
    int nread;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    nread = recvfrom(w->fd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &client_len);
    if (nread < 0)
    {
        perror("recvfrom");
        return;
    }

    printf("Received %d bytes from %s:%d\n", nread, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    sendto(w->fd, "Welcome to my server!\n", strlen("Welcome to my server!\n"), 0, (struct sockaddr *)&client_addr, client_len);
}

int main()
{
    struct sockaddr_in server_addr;
    int sock_fd;

    // Create a socket
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind");
        exit(1);
    }

    struct ev_loop *loop = ev_default_loop(0);

    // Set up an ev_io watcher to receive data
    ev_io io_watcher;
    ev_io_init(&io_watcher, read_cb, sock_fd, EV_READ);
    ev_io_start(loop, &io_watcher);

    // Set up an ev_signal watcher to handle SIGINT
    ev_signal signal_watcher;
    ev_signal_init(&signal_watcher, signal_cb, SIGINT);
    ev_signal_start(loop, &signal_watcher);

    // Start the event loop
    ev_loop(loop, 0);

    // Clean up
    close(sock_fd);
    return 0;
}
