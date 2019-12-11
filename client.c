#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//20133267 jung daekyeom
#define PORTNUM 9000
int main(void) {
    int sd;
    char buf[256];
    struct sockaddr_in sin;
 
    memset((char *)&sin, '\0', sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORTNUM);
    
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
 
    if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
 
    if(connect(sd, (struct sockaddr *)&sin, sizeof(sin))) {
        perror("connect");
        exit(1);
    }
 
    if(recv(sd, buf, sizeof(buf), 0) == -1) {
        perror("recv");
        exit(1);
    }
 
    printf("*** From Server online *** : %s\n", buf);
 
    strcpy(buf, "Please HTTP Service.");
    if(send(sd, buf, sizeof(buf) + 1, 0) == -1) {
        perror("send");
        exit(1);
    }
 
    close(sd);
    return 0;
}

