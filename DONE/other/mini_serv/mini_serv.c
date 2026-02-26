#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <netinet/in.h>

typedef struct s_client {
    int id;
    char *m;
} t_client;

void fatal(void) {
    write(2, "Fatal error\n", 12);
    exit(1);
}

void broadcast(int fd, int max_fd, fd_set write_set, char *m) {
    for (int i = 0; i <= max_fd; i++) {
        if (FD_ISSET(i, &write_set) && i != fd)
            send (i, m, strlen(m), 0);
    }
}

void clean(int max_fd, t_client *cls, fd_set active_set) {
    for (int i = 0; i <= max_fd; i++) {
        if (FD_ISSET(i, &active_set)) {
            FD_CLR(i, &active_set);
            close(i);
        }
        if (cls[i].m)
            free(cls[i].m);
    }
}

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				fatal();
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		fatal();
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}


int main(int ac, char **av) {
    if (ac != 2) {
        write (2, "Wrong number of arguments\n", 26);
        exit(1);
    }
	int sockfd, len, i, max_fd, id;
	struct sockaddr_in servaddr, cli;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) fatal();

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433);
	servaddr.sin_port = htons(atoi(av[1]));

	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) fatal();
	if (listen(sockfd, 10) != 0) fatal();
	
	len = sizeof(cli);
    const int BSIZE = 1024, MSIZE = 64, CSIZE = 16*4096;
    t_client  cls[CSIZE];
    fd_set active_set, read_set, write_set;
    FD_ZERO(&active_set);
    FD_SET(sockfd, &active_set);
    max_fd = sockfd;
    id = 0;

    while (1) {
        read_set = write_set = active_set;
        int active = select(max_fd + 1, &read_set, &write_set, NULL, NULL);
        if (active == -1) {
            clean(max_fd, cls, active_set);
            fatal();
        }

        if (FD_ISSET(sockfd, &read_set)) {
            i = accept(sockfd, (struct sockaddr *)&cli, &len);
            if (i >= 0) {
                cls[i].id = id++;
                cls[i].m = NULL;
                FD_SET(i, &active_set);
                if (i > max_fd) max_fd = i;
                char m[MSIZE];
                bzero(m, MSIZE);
                sprintf(m, "server: client %d just arrived\n", cls[i].id);
                broadcast(i, max_fd, write_set, m);
            }
        }
        else {
            for (i = 0; i <= max_fd; i++) {
                if (FD_ISSET(i, &read_set)) {
                    char buff[BSIZE];
                    bzero(buff, BSIZE);
                    if (recv(i, buff, BSIZE - 1, 0) <= 0) {
                        char m[MSIZE];
                        bzero(m, MSIZE);
                        sprintf(m, "server: client %d just left\n", cls[i].id);
                        broadcast(i, max_fd, write_set, m);
                        FD_CLR(i, &active_set);
                        close(i);
                        if (cls[i].m) {
                            free(cls[i].m);
                            cls[i].m = NULL;
                        }
                    }
                    else {
                        char *line = NULL;
                        cls[i].m = str_join(cls[i].m, buff);
                        while(extract_message(&(cls[i].m), &line)) {
                            char m[MSIZE + strlen(line)];
                            bzero(m, MSIZE + strlen(line));
                            sprintf(m, "client %d: %s", cls[i].id, line);
                            broadcast(i, max_fd, write_set, m);
                            free(line);
                            line = NULL;
                        }
                        if (cls[i].m[0] == '\0') {
                            free(cls[i].m);
                            cls[i].m = NULL;
                        }
                    }
                }
            }
        }
    }
    clean(max_fd, cls, active_set);
    return (0);
}