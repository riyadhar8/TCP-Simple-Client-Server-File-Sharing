#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h> 
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/un.h>
#include<fcntl.h>

#define SA struct sockaddr

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No Port Number specified.\n");
        printf("Server Exiting.\n");
        exit(1);
    }

    int port = atoi(argv[1]);
    printf("Port number: %d\n", port);

    struct sockaddr_in servaddr;
    int sockfd;
    int connectfd;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("----- Error creating a socket.\n");
        exit(2);
    } else {
        printf("----- Socket created successfully.\n");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);       //respond to any client
    servaddr.sin_port = htons(port);

    if (bind(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("----- Could not bind to socket.\n");
        exit(3);
    } else {
        printf("----- Successfully bound.\n");
    }

    if ((listen(sockfd, 1)) < 0) {
        printf("----- Could not listen.\n");
        exit(4);
    } else {
        printf("----- Listening.\n");
    }



    while (1) {
        printf("Waiting for a Client.\n");
        fflush(stdout);

        if ((connectfd = accept(sockfd, (struct sockaddr *)NULL, NULL)) < 0) {
            printf("----- Failed to Connect.\n");
            fflush(stdout);
            continue;
        }

        printf("----- Connected to a Client.\n");
        fflush(stdout);

        
        char recLine[1024];
        memset(recLine, 0, 1024);

        struct sockaddr_in addr;
        socklen_t addr_len;

        if ((read(connectfd, recLine, sizeof(recLine))) < 0){
            printf("----- Failed to receive.\n");
        } else {
            printf("----- File name received.\n");
        }

        fflush(stdout);

        printf("%s\n", recLine);

        FILE *fp = fopen(recLine, "r");
        char *sndLine = NULL;

        if(fp == NULL) {
            printf("----- Could not open file. Sending empty contents.\n");
            sndLine = malloc((2) * sizeof(*sndLine));
            sndLine[0] = '\n';
            sndLine[1] = '\0';
        } else {
            printf("----- File opened. Reading.\n");
            size_t size = 0;

            fseek(fp, 0, SEEK_END);
            size = ftell(fp);
            rewind(fp);

            sndLine = malloc((size + 1) * sizeof(*sndLine));
            fread(sndLine, size, 1, fp);
            sndLine[size] = '\0';
        }

        //printf("1.\n");
        printf("Sending the file contents to the client.\n");

        fflush(stdout);

        if (write(connectfd, sndLine, strlen(sndLine)) < 0) {
            printf("----- Error while Sending to Client.\n");
        } else {
            printf("----- Successfully sent to Client.\n");
        }

        printf("Client has Exited.\n");
        fflush(stdout);
    }

    return 0;
}