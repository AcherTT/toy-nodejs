#include <ev.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void file_read_cb(struct ev_loop *loop, struct ev_io *watcher, int revents)
{
    char buf[1024];
    int bytes_read = read(watcher->fd, buf, sizeof(buf));
    if (bytes_read < 0)
    {
        perror("read error");
        ev_break(loop, EVBREAK_ALL);
        return;
    }
    if (bytes_read == 0)
    {
        // end of file
        ev_io_stop(loop, watcher);
        ev_break(loop, EVBREAK_ALL);
        return;
    }
    printf("%.*s", bytes_read, buf);
}

// int main(int argc, char **argv)
// {
//     if (argc < 2)
//     {
//         fprintf(stderr, "Usage: %s FILE\n", argv[0]);
//         return 1;
//     }

//     const char *filename = argv[1];
//     int fd = open(filename, O_RDONLY);
//     if (fd < 0)
//     {
//         perror("open error");
//         return 1;
//     }

//     struct ev_loop *loop = ev_default_loop(0);
//     struct ev_io io_watcher;
//     ev_io_init(&io_watcher, file_read_cb, fd, EV_READ);
//     ev_io_start(loop, &io_watcher);

//     ev_run(loop, 0);

//     return 0;
// }
