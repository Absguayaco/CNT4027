/*///////////////////////////////////////////////////////////
*
* FILE:		server.c
* AUTHOR:	Andres Bodero
* PROJECT:	CNT 4007 Project 1 - Professor Traynor
* DESCRIPTION:	Network Server Code
*
*////////////////////////////////////////////////////////////

/*Included libraries*/

#include <stdio.h>	  /* for printf() and fprintf() */
#include <sys/socket.h>	  /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>	  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>	  /* supports all sorts of functionality */
#include <unistd.h>	  /* for close() */
#include <string.h>	  /* support any string ops */
#include <openssl/evp.h>  /* for OpenSSL EVP digest libraries/SHA256 */

#define RCVBUFSIZE 512		/* The receive buffer size */
#define SNDBUFSIZE 512		/* The send buffer size */
#define BUFSIZE 40		/* Your name can be as many as 40 chars*/
#define PORT 9090

//based on https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/

/* The main function */
int main(int argc, char *argv[])
{

    int serverSock;				/* Server Socket */
    int clientSock;				/* Client Socket */
    struct sockaddr_in changeServAddr;		/* Local address */
    struct sockaddr_in changeClntAddr;		/* Client address */
    unsigned short changeServPort;		/* Server port */
    unsigned int clntLen;			/* Length of address data struct */

    char nameBuf[BUFSIZE];			/* Buff to store name from client */
    unsigned char md_value[EVP_MAX_MD_SIZE];	/* Buff to store change result */
    EVP_MD_CTX *mdctx;				/* Digest data structure declaration */
    const EVP_MD *md;				/* Digest data structure declaration */
    int md_len;					/* Digest data structure size tracking */


    /* Create new TCP Socket for incoming requests*/
    /*	    FILL IN	*/
    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else{
        printf("Socket successfully created..\n");
    }
    bzero(&changeServAddr, sizeof(changeServAddr));

    /* Construct local address structure*/
    /*	    FILL IN	*/
    changeServAddr.sin_family = AF_INET;
    changeServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    changeServAddr.sin_port = htons(PORT);
    
    /* Bind to local address structure */
    /*	    FILL IN	*/
     if ((bind(serverSock, (struct sockaddr *)&changeServAddr, sizeof(changeServAddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 

    /* Listen for incoming connections */
    /*	    FILL IN	*/
     if ((listen(serverSock, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 

    /* Loop server forever*/
    while(1)
    {

      /* Accept incoming connection */
      /*	FILL IN	    */
      clntLen = sizeof(changeClntAddr);  
      clientSock = accept(serverSock, (struct sockaddr *)&changeClntAddr, &clntLen);
      if (clientSock < 0) {
        printf("server acccept failed...\n");
        exit(0);
      }
    

      /* Extract Your Name from the packet, store in nameBuf */
      /*	FILL IN	    */
      int recvLen = recv(clientSock, nameBuf, BUFSIZE-1, 0);


      /* Run this and return the final value in md_value to client */
      /* Takes the client name and changes it */
      /* Students should NOT touch this code */
        OpenSSL_add_all_digests();
        md = EVP_get_digestbyname("SHA256");
        mdctx = EVP_MD_CTX_create();
        EVP_DigestInit_ex(mdctx, md, NULL);
        EVP_DigestUpdate(mdctx, nameBuf, strlen(nameBuf));
        EVP_DigestFinal_ex(mdctx, md_value, &md_len);
        EVP_MD_CTX_destroy(mdctx);

      /* Return md_value to client */
      /*	FILL IN	    */
        if (send(clientSock, md_value, md_len, 0) != md_len) {
                    printf("Failed to send data to client\n");
                } else {
                    printf("Sent to client\n");
                }
                close(clientSock);
    }
close(serverSock);
return 0;
}
