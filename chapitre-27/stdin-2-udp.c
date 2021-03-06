// ------------------------------------------------------------------
// stdin-2-udp.c
// Fichier d'exemple du livre "Developpement Systeme sous Linux"
// (C) 2000-2019 - Christophe BLAESS <christophe@blaess.fr>
// https://www.blaess.fr/christophe/
// ------------------------------------------------------------------

#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <sys/socket.h>

#define BUFFER_SIZE  1024


int parse_args(int argc, char * argv[], int server, struct addrinfo **result);

int main (int argc, char * argv[])
{
	int    sock;
	char   buffer[BUFFER_SIZE];
	int    bytes;
	struct addrinfo *results;
	
	if (parse_args(argc, argv, 0, &results) < 0)
		exit(EXIT_FAILURE);

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	while (1) {
		if ((bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE)) == 0)
			break;
		if (bytes < 0) {
			perror("read");
			break;
		}
		sendto(sock, buffer, bytes, 0, results->ai_addr, results->ai_addrlen);
	}
	return 0;
}


int parse_args(int argc, char * argv[], int server, struct addrinfo **results)
{
	char * option_list = "a:p:h";
	int    option;
	int    err;	
	char * host  = "localhost";
	char * port = "2000";

	struct addrinfo  hints;

	while ((option = getopt(argc, argv, option_list)) != -1) {
		switch (option) {
			case 'a' :
				host  = optarg;
				break;
			case 'p' :
				port = optarg;
				break;
			case 'h' :
				fprintf(stderr, "Syntaxe : %s [-a adresse] [-p port] \n",
						argv[0]);
				return -1;
			default	: 
				break;
		}
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	if (server)
		hints.ai_flags = AI_PASSIVE;
	if ((err = getaddrinfo(host, port, &hints, results)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
		return -1;
	}

	return 0;
}

