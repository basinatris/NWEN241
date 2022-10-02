#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(){
    printf("Starting server...\n");
    
    int port = 23456;
    
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sock_fd < 0) {
        printf("Error creating socket\n"); 
        
        return -1;
    }
    
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    
    printf("Binding to socket\n");
    
    int bind_c = bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    if (bind_c < 0){
        printf("Bind failed\n");
        
        return -1;
    }
    
    
    printf("Socket created and bound\n");
    
    printf("Listening for new client requests...\n");
    
    int listen_c = listen(sock_fd, SOMAXCONN);
    
    if (listen_c < 0)
        return -1;
    
    
    struct sockaddr client_addr;
    int client_addrl = sizeof(client_addr);
    int client_fd = accept(sock_fd, (struct sockaddr*)&client_addr, (socklen_t*)&client_addrl);
    
    if(client_fd < 0) 
        return -1;
    
    
    printf("Client accepted\n");
    
    
    
    char incoming[100]; 
    memset(incoming, '\0', 100);
    
    ssize_t receive = recv(client_fd, incoming, 100, 0); 
    
    if (receive < 0){
        printf("Error receiving message from client\n");
        close(client_fd);
        return -1;
    }
    else if (receive == 0){
        printf("Client socket closed.\n");
        return -1;
    }
    
    char reverse[strlen(incoming)];
    memset(reverse, '\0', strlen(incoming));
    //printf("%s", incoming);
    
    for (int i = strlen(incoming) - 1; i >= 0; i--){
        int idx = abs(i - (strlen(incoming) - 1));
        //printf("%d, %d\n", i, idx);
        reverse[idx] = incoming[i];
    }
    reverse[strlen(reverse)] = '\n';
    //printf("%s", reverse);
    
    
    ssize_t sent = send(client_fd, reverse, sizeof(reverse), 0);

    if (sent < 0){
        printf("Error sending message to client; Closing\n");
        
        close(client_fd);
        
        return -1;
    }
    
    exit(0);
}
