#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>
#define PORT 8080

int main(){
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char* hello = "Hello from Client\n"; //Can I make this a CPP string?
    //strcpy(hello, "hello from client\n");
    char buffer[1024] = {0}; // difference between this and {\0}?
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\nsocket creation failure");
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
        printf("\nInvalid address / address not supported");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        printf("\nConnection failed\n");
        return -1;
    }
    char val[32];
    while (fgets(val, 32, stdin)){
        //printf("%s", val);
        send(sock, val, strlen(val), 0);
        valread = read(sock, buffer, 1024);
    }
    //printf("%s\n", buffer);
    
    return 0;
}
