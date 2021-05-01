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

void modify(char *arr, int len) {
    arr[2] = 'C';
    arr[3] = 'l';
    arr[4] = 'i';
    arr[5] = 'e';
    arr[6] = 'n';
    arr[7] = 't';
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Please enter both the IP Address and the Port Number.\n");
        printf("Client Exiting.\n");
        exit(1);
    }

    printf("Client Entering.\n");

    char *ip = argv[1];
    printf("IP Address of Server: %s\n", ip);

    int port = atoi(argv[2]);
    printf("Port Number of Server: %d\n", port);

    struct sockaddr_in servaddr;
    int sockfd;
    int connectfd;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("----- Error in creating a Socket.\n");
        exit(2);
    } else {
        printf("----- Socket created successfully.\n");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr(ip);

    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        printf("----- Failed to Connect.\n");
        exit(3);
    } else {
        printf("----- Connected to Server.\n");
    }

    char sndLine[1024];
    memset(sndLine, 0, 1024);
    
    printf("Enter the name of the file: ");
    fgets(sndLine, 1024, stdin);

    for(int i=0; i<1024; i++) {
        if (sndLine[i]=='\n') {
            sndLine[i] = '\0';
            break;
        }
    }

    //printf("%s", sndLine);

    if (write(sockfd, sndLine, strlen(sndLine)) < 0) {
        printf("----- Error while Sending to Server.\n");
        exit(4);
    } else {
        printf("----- Successfully sent to Server. Waiting for response.\n");
    }

    char recLine[1024];
    memset(recLine, 0, 1024);

    if (read(sockfd, recLine, 1024) < 1) {
        printf("----- Error in Receiving from Server.\n");
        exit(5);
    } else {
        printf("----- Contents of file received. Storing.\n");
    }

    //change `./Server/input.txt` to `./Client/input.txt`
    modify(sndLine, strlen(sndLine));

    FILE *fp = fopen(sndLine, "w");
    int error = fputs(recLine, fp);
    if (error == EOF) {
        printf("----- Error in writing to file.\n");
    }
    fclose(fp);

    printf("Client Exiting! Bye.\n");

    return 0;

}