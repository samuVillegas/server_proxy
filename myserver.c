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

/* server parameters */
#define SERV_PORT 8080                 /* port */
#define SERV_HOST_ADDR "172.31.17.199" /* IP, only IPV4 support  */
#define BUF_SIZE 100                   /* Buffer rx, tx max size  */
#define BACKLOG 5                      /* Max. client pending connections  */

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
        printf("[SERVER]: ERROR CREATING SOCKET")
    }else{
        printf("[SERVER]: Socket created successful")
    }

    // Bind
    int socket_bind = bind(socket, (struct sockaddr *)sock_address, sizeof(sock_address));
    if(socket_bind != 0){
        printf("[SERVER]: ERROR BIND SOCKET")
    }else{
        printf("[SERVER]: Socket bind 
        excecuted successful")
    }
}