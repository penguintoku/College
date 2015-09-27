/**
 * @file server.c
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
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <resolv.h>
#include <sys/socket.h>
#include <openssl/ssl.h>

//Function Prototype
SSL_CTX* initialize_server();
int server_socket(int port);
void ssl_handshake(SSL* ssl);

 /**
  * Since I was writing the code on a Mac, I had to include
  * the pragma which will ignore the warnings given on
  * Mac OS X Version 10.7 and higher.
  */
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

int main(int argc, char *argv[]){

	//Check if valid format
	if(argc != 4){
		printf("\n\nUsage: ./server <certificate> <key> <port number>\n\n");
		exit(1);
	}

	//Initialization
	SSL_CTX *ctx;
	int server;
	char *port;
	SSL_library_init();

	//Get the port from the argument
	port = argv[3];

	//Initialize the OpenSSL (page 1)
	ctx = initialize_server();

	//Load and validate the certificate and key (page 1)
	if(SSL_CTX_use_certificate_file(ctx, argv[1], SSL_FILETYPE_PEM) <= 0){
		printf("\n\nERROR: SSL_CTX_use_certificate_file failed (server.c - main)\n");
		printf("Could not find the certificate file.\n\n");
		exit(1);
	}
	if(SSL_CTX_use_PrivateKey_file(ctx,  argv[2], SSL_FILETYPE_PEM) <= 0){
		printf("\n\nERROR: SSL_CTX_use_PrivateKey_file failed (server.c - main)\n");
		printf("Could not find the private key file or incorrect key.\n\n");
		exit(1);
	}
	if(!SSL_CTX_check_private_key(ctx)){
		printf("\n\nERROR: SSL_CTX_check_private_key failed (server.c -main)\n");
		printf("Private key does not match the public certificate\n\n");
		exit(1);
	}	

	//create server socket
	server = server_socket(atoi(port));	

	//Continue listening
	while(1){
		struct sockaddr_in addr;
		socklen_t addrLen = sizeof(addr);
		SSL *ssl;

		//If client connects
		int client = accept(server, (struct sockaddr*) &addr, &addrLen);
		if(client < 0){
			printf("\n\nERROR: accept() failed (server.c - main).\n\n");
			printf("Couldn't create socket.\n\n");
			exit(1);
		}

		//creates a new SSL structure to hold the data for SSL connection
		ssl = SSL_new(ctx);
		if(ssl == NULL){
			printf("\n\nERROR: SSL_new() failed (server.c - main).\n\n");
			printf("Couldn't create new SSL structure.\n\n");
			exit(1);
		}

		//Sets the file descriptor client as the input/output facility for the SSL (encrypted) side of ssl
		SSL_set_fd(ssl, client);

		//Start talking
		ssl_handshake(ssl);	
	}

	//close and exit
	close(server);	
	SSL_CTX_free(ctx);
	return 0;
}

/**
 *	@brief initialize SSL server and create context
 *  @decription THIS IS NOT MY CODE (from page 1)
 *  @return ctx					The SSL_CTX object
 */
SSL_CTX* initialize_server(){
	SSL_METHOD *method = SSLv3_server_method();
	SSL_CTX *ctx = SSL_CTX_new(method);	
	OpenSSL_add_all_algorithms();	
	SSL_load_error_strings();	

	//check if CTX object is valid
	if(ctx == NULL){
		printf("\n\nERROR: SSL_CTX_new() failed (server.c - initialize_server\n");
		printf("Couldn't create a new SSL_CTX object.\n\n");
		exit(1);
	}
	return ctx;
}

/**
 *	@brief Create server socket
 *  @decription THIS IS NOT MY CODE (from page 2)
 *	@param port[in] 				The port number
 *  @return sd						The socket
 */
int server_socket(int port){
	int sd;
	struct sockaddr_in addr;

	sd = socket(PF_INET, SOCK_STREAM, 0);
	if(sd < 0){
		printf("\n\nERROR: socket() failed (server.c - server_socket).\n\n");
		printf("Couldn't create socket.\n\n");
		exit(1);
	}

	//zero it out
	bzero(&addr, sizeof(addr));

	//the details of the socket
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	//check if port number is available
	if(bind(sd, (struct sockaddr*) &addr, sizeof(addr)) < 0){
		printf("\n\nERROR: bind() failed (server.c - server_socket)\n");
		printf("Couldn't bind socket in that port number: %i\n\n", port);
		close(sd);
		exit(1);
	}
	
	if(listen(sd, 10) < 0){
		printf("\n\nERROR: listen() failed (server.c - server_socket)\n\n");
		close(sd);
		exit(1);
	}
	return sd;
}

/**
 *	@brief SSL servlet (contexts can be shared) 
 *  @decription THIS IS NOT MY CODE (from page 2)
 *	@param *ssl[in] 				Pointer to ssl
 */
void ssl_handshake(SSL* ssl){	
	char buf[1024];
	char reply[1024];
	int client, bytes;
	
	if(SSL_accept(ssl) < 0){
		printf("\n\nERROR: SSL_accept() failed (server.c - ssl_handshake)\n");
	} 
	else{
		bytes = SSL_read(ssl, buf, sizeof(buf));	
		if (bytes > 0){
			buf[bytes] = 0;
			printf("Client: %s\n", buf);
			long check = atol(buf) + 1;
			sprintf(reply, "%ld", check);	
			SSL_write(ssl, reply, strlen(reply));	 
		}
		else{
			printf("\n\nERROR: SSL_read() failed (server.c - ssl_handshake)\n");
			printf("A client has closed.\n\n");
		}
	}
	client = SSL_get_fd(ssl);	
	SSL_free(ssl);	
	close(client);	
}