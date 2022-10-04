/*standard symbols */
#include <unistd.h>

/* sockets */
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

/* strings / errors*/
#include <errno.h>
#include <stdio.h>
#include <string.h>

/* multithread */
#include <pthread.h>


/* server parameters */
#define SERV_PORT 8080                 /* port */
#define SERV_HOST_ADDR "192.168.0.21" /* IP, only IPV4 support  */
#define BUF_SIZE 100                   /* Buffer rx, tx max size  */
#define BACKLOG 5                      /* Max. client pending connections  */

struct thread_connection{
    pthread_t thid;
    int connection_id;
};

void* fun(void * params){
    struct thread_connection connfd_aux = *(struct thread_connection*)params;
    char *reply = 
		"HTTP/1.1 200 OK\n"
		"Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
		"Server: Apache/2.2.3\n"
		"Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
		"ETag: \"56d-9989200-1132c580\"\n"
		"Content-Type: text/html\n"
		"Content-Length: 15\n"
		"Accept-Ranges: bytes\n"
		"Connection: close\n"
		"\n"
		"sdfkjsdnbfkjbsf";
        
    while(1) {  
                char buff_rx[BUF_SIZE];  
                /* read client message, copy it into buffer */
                int len_rx = read(connfd_aux.connection_id, buff_rx, sizeof(buff_rx));
                if(len_rx == -1){
                    printf("[SERVER]: ERROR READING CLIENT CONTENT");
                }
                /* if length is 0 client socket closed, then exit */
                else if(len_rx == 0) {
                    printf("[SERVER]: client socket closed \n\n");
                    close(connfd_aux.connection_id);
                    break; 
                }else{
                    send(connfd_aux.connection_id,reply, strlen(reply),0);
                    printf("%s", buff_rx);
                }            
    }  
    //pthread_exit(&connfd_aux.connection_id);
}



int main(int argc, char *argv[])
{

    // Create socket address
    struct sockaddr_in sock_address;
    sock_address.sin_family = AF_INET;                        // Set family
    sock_address.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR); // Set internet address
    sock_address.sin_port = htons(SERV_PORT);                 // Set port

    // Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        printf("[SERVER]: ERROR CREATING SOCKET\n");
        return -1;
    }else{
        printf("[SERVER]: Socket created successful\n");
    }

    // Bind
    int socket_bind = bind(sockfd, (struct sockaddr *)&sock_address, sizeof(sock_address));
    if(socket_bind != 0){
        printf("[SERVER]: ERROR SOCKET BIND");
        return -1;
        return -1;
    }else{
        printf("[SERVER]: Socket bind excecuted successful\n");
    }

    //Listen
    int socket_listen = listen(sockfd,BACKLOG);
    if(socket_listen != 0){
        printf("[SERVER]: ERROR LISTENING\n");
        return -1;
    }else{
        printf("[SERVER]: SOCKET LISTENING\n");
    }

    //Conections
    while(1){
        struct sockaddr_in client;
        int len_client = sizeof(client);
        int connfd;

        //Accept connection
        connfd = accept(sockfd, (struct sockaddr *)&client, &len_client); 
        if(connfd<0){
            printf("[SERVER]: ERROR TO CONNECT WITH CLIENT");
            return -1;
        }else{
            pthread_t tid0;
            struct thread_connection thr_conn;
            thr_conn.thid = tid0;
            thr_conn.connection_id = connfd;
            pthread_create(&tid0,NULL,fun,&thr_conn);
        }
    }

}