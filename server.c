#include <stdio.h>
#include <string.h>
#include<sys/types.h>
#include <sys/socket.h>
#include<unistd.h>
#include <arpa/inet.h>

int main(void)
{
	int socdec, clsock, cl_size;
    	struct sockaddr_in server_addr, client_addr;
    	char sermsg[500], clmsg[500];
    
    	// Clean buffers:      
   	bzero(sermsg,sizeof(sermsg));
   	bzero(clmsg,sizeof(clmsg));
    
    	// Create socket:
   	socdec = socket(AF_INET, SOCK_STREAM, 0);
    	printf("Socket created successfully\n");
    
    	// Set port and IP:
    	server_addr.sin_family = AF_INET;
    	server_addr.sin_port = htons(1500);
    	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    	// Bind to the set port and IP:
    	bind(socdec ,(struct sockaddr*)&server_addr, sizeof(server_addr));
    	printf("Binding Done\n");
    
    	// Listen for clients:
    	listen(socdec, 10) ;
    	printf("\nListening for incoming connections.....\n");
    
    	// Accept an incoming connection:
    	cl_size = sizeof(client_addr);
    	clsock = accept(socdec, (struct sockaddr*)&client_addr, &cl_size);
   	printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    
    	// Receive client's message:
    	recv(clsock, clmsg, sizeof(clmsg), 0);
    	printf("Msg from client: %s\n", clmsg);
    
    	// Respond to client:
    	strcpy(sermsg, "This is the server's message.");
    
    	send(clsock, sermsg, strlen(sermsg), 0) ;
        
    
    	// Closing the socket:
    	close(clsock);
    	close(socdec);
    
   	 return 0;
}

