/**
 * @file client.c
 * @brief SSL connection 
 * @section Description
 * 
 * Assignment 4 of CS458: Introduction to Computer Security
 * Before starting, read the README
 * 
 * @author Tokumaru Yahashi
 */


//Dependencies
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <ctype.h>

//Function Prototype 
SSL_CTX* initialize_client();
int client_socket(const char *hostname, int port);
int only_digit(const char *s);


/**
  * Since I was writing the code on a Mac, I had to include
  * the pragma which will ignore the warnings given on
  * Mac OS X Version 10.7 and higher.
  */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

int main(int argc, char *argv[]){

	//Check if valid format
	if(argc != 3){
		printf("\n\nUsage: ./client <hostname> <port number>\n\n");
		exit(1);
	}

	//Initialize
	SSL_CTX *ctx;
	int server;
	SSL *ssl;
	char buf[1024];
	int bytes;
	char *hostname;
	char *port;
	SSL_library_init();

	//Get hostname and port number from argument
	hostname = argv[1];
	port = argv[2];

	//Continue loop
	while(1){
		ctx = initialize_client();
		server = client_socket(hostname, atoi(port));
		ssl = SSL_new(ctx);		
		SSL_set_fd(ssl, server);	
		if(SSL_connect(ssl) == -1){
			printf("\n\nERROR: SSL_connect failed (client.c - main)\n\n");
			exit(1);
		} 
		else{
			long x;
			char buf[1024];
			char temp[1024];
			int flag = 1;
			int valid;
			do{
				printf("\nInput number: ");
				scanf("%s", temp);
				valid = only_digit(temp);
				if(valid != 1){
					printf("\nERROR: Contains non-digit.\n");
					printf("Must only contain digits and '-' for negative number at the begining.\n");
				}
				else{
					flag = 0;
					x = atol(temp);
					if(x > 9223372036854775806){
						printf("ERROR: Number is to big, it will overflow.\n");
						flag = 1;
					}
					if(x < -9223372036854775807){
						printf("ERROR: Number is to small, it will underflow.\n");
						flag = 1;
					}
				}
			}while(flag);
			sprintf(buf, "%ld", x);
			SSL_write(ssl, buf, strlen(buf));	
			bytes = SSL_read(ssl, buf, sizeof(buf));	
			buf[bytes] = 0;
			printf("Server: %s\n", buf);
			if(atol(buf) == x + 1){
				printf("Correct\n");
			}
			else{
				printf("Incorrect\n");
			}
			SSL_free(ssl);
		}
		close(server);	 
		SSL_CTX_free(ctx);	
	}
}

/**
 *	@brief initialize SSL client and create context
 *  @decription THIS IS NOT MY CODE (from page 2)
 *  @return ctx					The SSL_CTX object
 */
SSL_CTX* initialize_client(){
	SSL_METHOD* method = SSLv3_client_method();	
	SSL_CTX* ctx = SSL_CTX_new(method);	
	OpenSSL_add_all_algorithms();	
	SSL_load_error_strings();

	//check if CTX object is valid
	if(ctx == NULL){
		printf("\n\nERROR: SSL_new() failed (client.c - initialize_client)\n");
		printf("Couldn't create new SSL structure.\n\n");
		exit(1);
	}
	return ctx;
}

/**
 *	@brief Create client socket and connect to server
 *  @decription THIS IS NOT MY CODE (from page 3)
 *  @param *hostname				Pointer to the hostname
 *	@param port[in] 				The port number
 *  @return sd						The socket
 */
int client_socket(const char *hostname, int port){
	int sd;
	struct hostent *host;
	struct sockaddr_in addr;

	//validate the host name from argument
	if((host = gethostbyname(hostname)) == NULL){
		printf("\n\nERROR: gethostbyname() failed (client.c - client_socket\n");
		printf("Incorrect hostname.\n\n");
		exit(1);
	}

	//Initialize the socket
	sd = socket(PF_INET, SOCK_STREAM, 0);
	if(socket < 0){
		printf("\n\nERROR: socket() failed (client.c - client_socket)\n");
		printf("Couldn't create socket.\n\n");
		exit(1);
	}
	//zero it out
	bzero(&addr, sizeof(addr));

	//the details of the socket
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = *(long*)(host->h_addr);

	//connect to the server
	if(connect(sd, (struct sockaddr*) &addr, sizeof(addr)) < 0){
		printf("\n\nERROR: connect() failed (client.c - client_socket)\n");
		printf("Could not connect to server due to time out or doesn't exist.\n\n");
		close(sd);
		exit(1);
	}
	return sd;
}

/**
 *	@brief checks if the value is valid
 *  @decription THIS IS NOT MY CODE (from internet)
 *	@param *s[in] 					The string from user input
 *  @return valid					1 or 0 if string is valid
 */
int only_digit(const char *s){

	int valid = 1;
	const char *ptr = strchr(s, '-');
	int index = 0;

	while(*s){
		if(ptr){
			index = ptr - s + 1;
			if(index == 0){
				valid = 1;
			}
		}
		if(isdigit(*s++) == 0){
			valid = 0;
		}
    }
	return valid;
}