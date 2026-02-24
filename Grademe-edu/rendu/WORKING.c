#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <netinet/in.h>

typedef struct	s_client {
	int id;
	char *m;
}	t_client;

void	fatal() {
	write(2, "Fatal error\n", 12);
	exit(1);
}

void broadcast(int fd, int maxfd, fd_set write_set, char *m) {
	for (int i = 0; i <= maxfd; i++) {
		if (FD_ISSET(i, &write_set) && i != fd)
			if (send(i, m, strlen(m), 0) == -1)
				fatal();
	}
}

void clean(int maxfd, t_client *cls, fd_set active_set) {
	for (int i = 0; i <= maxfd; i++) {
		if (FD_ISSET(i, &active_set)) {
			FD_CLR(i, &active_set);
			close(i);
		}
		if (cls[i].m)
			free (cls[i].m);
	}
}

int extract(char **buf, char **msg) {
	char *new;
	int i = 0;

	*msg = 0;
	if (*buf == 0)
		return 0;
	while ((*buf)[i]) {
		if ((*buf)[i] == '\n') {
			new = calloc(1, sizeof(*new) * (strlen(*buf + i + 1) + 1));
			if (!new)
				fatal();
			strcpy(new, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = new;
			return 1;
		}
		i++;
	}
	return 0;
}

char *strjoin(char *buf, char *add) {
	char *new;
	int len;
	
	if (!buf)
		len = 0;
	else
		len = strlen(buf);
	new = malloc(sizeof(*new) * (len + strlen(add) + 1));
	if (!new)
		fatal();
	new[0] = 0;
	if (buf)
		strcat(new, buf);
	free(buf);
	strcat(new, add);
	return (new);
}

int main(int ac, char **av) {
	if (ac != 2) {
		write(2, "Wrong number of arguments\n", 26);
		return 1;
	}
	int sockfd, connfd, maxfd, id;
	unsigned int len;
	struct sockaddr_in servaddr, cli;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) fatal();
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433);
	servaddr.sin_port = htons(atoi(av[1]));

	if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) fatal();
	if (listen(sockfd, 10) != 0) fatal();
	
	len = sizeof(cli);
	int BSIZE = 1024, MSIZE = 64, CSIZE = 16*4096;
	t_client cls[CSIZE];
	fd_set active_set, read_set, write_set;
	FD_ZERO(&active_set);
	FD_SET(sockfd, &active_set);
	maxfd = sockfd;
	id = 0;

	while (1) {
		read_set = write_set = active_set;
		if (select(maxfd + 1, &read_set, &write_set, NULL, NULL) == -1) {
			clean(maxfd, cls, active_set);
			fatal();
		}

		if (FD_ISSET(sockfd, &read_set)) {
			connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
			if (connfd >= 0) {
				cls[connfd].id = id++;
				cls[connfd].m = NULL;
				FD_SET(connfd, &active_set);
				if (connfd > maxfd) maxfd = connfd;
				
				char m[MSIZE];
				bzero(m, MSIZE);
				sprintf(m, "server: client %d just arrived\n", cls[connfd].id);
				broadcast(connfd, maxfd, write_set, m);
			}
		}
		else {
			for (connfd = 0; connfd <= maxfd; connfd++) {
				printf("here\n");
				if (FD_ISSET(connfd, &read_set)) {
					char buf[BSIZE];
					bzero(buf, BSIZE);
					if (recv(connfd, buf, BSIZE - 1, 0) <= 0) {
						char m[MSIZE];
						bzero(m, MSIZE);
						sprintf(m, "server: client %d just left\n", cls[connfd].id);
						broadcast(connfd, maxfd, write_set, m);
						FD_CLR(connfd, &active_set);
						close(connfd);
						if (cls[connfd].m) {
							free (cls[connfd].m);
							cls[connfd].m = NULL;
						}
					}
					else {
						char *line = NULL;
						cls[connfd].m = strjoin(cls[connfd].m, buf);
						while (extract(&(cls[connfd].m), &line)) {
							char m[MSIZE + strlen(line)];
							bzero(m, MSIZE + strlen(line));
							sprintf(m, "client %d : %s", cls[connfd].id, line);
							broadcast(connfd, maxfd, write_set, m);
							free(line);
							line = NULL;
						}
						if (cls[connfd].m[0]) {
							free(cls[connfd].m);
							cls[connfd].m = NULL;
						}
					}
				}
			}
		}
	}
	clean(maxfd, cls, active_set);
	return 0;
}