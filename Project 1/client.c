/*///////////////////////////////////////////////////////////
*
* FILE:		client.c
* AUTHOR:	Andres
* PROJECT:	CNT 4007 Project 1 - Professor Traynor
* DESCRIPTION:	Network Client Code
*
*////////////////////////////////////////////////////////////

/* Included libraries */

#include <stdio.h>		    /* for printf() and fprintf() */
#include <sys/socket.h>		    /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>		    /* for sockaddr_in and inet_addr() */
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <openssl/evp.h>	    /* for OpenSSL EVP digest libraries/SHA256 */

/* Constants */
#define RCVBUFSIZE 512		    /* The receive buffer size */
#define SNDBUFSIZE 512		    /* The send buffer size */
#define MDLEN 32
#define PORT 8080

/* The main function */
int main(int argc, char *argv[])
{

    int clientSock;		    /* socket descriptor */
    struct sockaddr_in serv_addr;   /* The server address */

    char *studentName;		    /* Your Name */

    char sndBuf[SNDBUFSIZE];	    /* Send Buffer */
    char rcvBuf[RCVBUFSIZE];	    /* Receive Buffer */
    
    int i;			    /* Counter Value */

    /* Get the Student Name from the command line */
    if (argc != 2) 
    {
	printf("Incorrect input format. The correct format is:\n\tnameChanger your_name\n");
	exit(1);
    }
    studentName = argv[1];
    memset(&sndBuf, 0, RCVBUFSIZE);
    memset(&rcvBuf, 0, RCVBUFSIZE);

    /* Create a new TCP socket*/
    /*	    FILL IN	*/
    clientSock = socket(AF_INET, SOCK_STREAM, 0); //maybe change IP
    if(clientSock == -1){
        printf("Socket failed to create");
        close(clientSock);
        exit(0);
    }
    else{
        printf("Socket created :)");
    }
    bzero(&serv_addr, sizeof(serv_addr));

    /* Construct the server address structure */
    /*	    FILL IN	 */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(PORT);


    /* Establish connecction to the server */
    /*	    FILL IN	 */
    if(connect(clientSock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        printf("Connection failed");
        close(clientSock);
        exit(0);
    }
    else{
        printf("Connection established :)");
    }
    
    /* Send the string to the server */
    /*	    FILL IN	 */
    strncpy(sndBuf, studentName, SNDBUFSIZE);  

    send(clientSock, sndBuf, strlen(sndBuf), 0); //maybe add error handling    

    /* Receive and print response from the server */
    /*	    FILL IN	 */
    if(recv(clientSock, rcvBuf, MDLEN, 0) < 0) {
        perror("Receive failed");
        close(clientSock);
        exit(0);
    }

    printf("%s\n", studentName);
    printf("Transformed input is: ");
    for(i = 0; i < MDLEN; i++) printf("%02x", rcvBuf[i]);
    printf("\n");

    close(clientSock);
    return 0;
}
