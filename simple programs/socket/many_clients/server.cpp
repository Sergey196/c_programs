//Example code: A simple server side code, which echos back the received message.
//Handle multiple socket connections with select and fd_set on Linux 
#include <stdio.h> 
#include <string.h>   //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>   //close 
#include <arpa/inet.h>    //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 
#include <iostream>
#include <vector>
#include <algorithm>
     
#define PORT 8888 
     
int main(int argc , char *argv[])  
{  
    int opt = true;  
    int master_socket , new_socket;  
    int max_sd;  
    struct sockaddr_in address;  
    std::vector<int> clients;
         
    char buffer[1025];  //data buffer of 1K 
         
    //set of socket descriptors 
    fd_set readfds;  
         
    //create a master socket 
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
    {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }  
     
    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this 
    /*if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0 )  
    {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    }  */
     
    //type of socket created 
    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = INADDR_ANY;  
    address.sin_port = htons( PORT );  
         
    //bind the socket to localhost port 8888 
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
    {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  
    printf("Listener on port %d \n", PORT);  
         
    //try to specify maximum of 3 pending connections for the master socket 
    if (listen(master_socket, 3) < 0)  
    {  
        perror("listen");  
        exit(EXIT_FAILURE);  
    }  
         
    //accept the incoming connection 
    int addrlen = sizeof(address);  
    puts("Waiting for connections ...");  
         
    while(true)  
    {  
        for(int sock : clients)
        {  
            std::cout << "TEST sock = " << sock << std::endl; 
        }
        //clear the socket set 
        FD_ZERO(&readfds);  
     
        //add master socket to set 
        FD_SET(master_socket, &readfds);  
        FD_SET(STDIN_FILENO, &readfds);
        max_sd = master_socket;  
             
        //add child sockets to set 
        for(int sd : clients)
        {  
                 
            //if valid socket descriptor then add to read list 
            if(sd > 0)  
                FD_SET( sd , &readfds);  
                 
            //highest file descriptor number, need it for the select function 
            if(sd > max_sd)  
                max_sd = sd;  
        }  
     
        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely 
        int activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
       
        if ((activity < 0) && (errno!=EINTR))  
        {  
            printf("select error");  
        }  
            
        //If something happened on the master socket , 
        //then its an incoming connection 
        if (FD_ISSET(master_socket, &readfds))  
        {  
            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)  
            {  
                perror("accept");  
                exit(EXIT_FAILURE);  
            }  
             
            //inform user of socket number - used in send and receive commands 
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs (address.sin_port));  
           
            //a message 
            char message[] = "HELLO from server";  
            //send new connection greeting message 
            if( send(new_socket, message, strlen(message), 0) != strlen(message) )  
            {  
                perror("send");  
            }  
                 
            puts("Welcome message sent successfully");  
                 
            clients.push_back(new_socket);
            printf("Adding to list of sockets as %d\n" , new_socket);  
        }  
             
        //else its some IO operation on some other socket
        //for(int &sock : clients)
        for(auto it = clients.begin();it != clients.end();)
        {  
            if (FD_ISSET(*it , &readfds))  
            {  
                //Check if it was for closing , and also read the 
                //incoming message 
                memset(buffer, 0, sizeof(buffer));
                int valread = recv(*it, buffer, 1024, 0);
                if (valread == 0)  
                {  
                    //Somebody disconnected , get his details and print 
                    getpeername(*it , (struct sockaddr*)&address , (socklen_t*)&addrlen);  
                    printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
                         
                    //Close the socket and mark as 0 in list for reuse 
                    close(*it); 
                    it = clients.erase(it);
                    //sock = -1;
                }  
                     
                //Echo back the message that came in 
                else 
                {  
                    std::cout << "TEST read = " << buffer << std::endl; 
                    char message[] = "TEST message from server";  
                    if(send(*it, message, strlen(message), 0) != strlen(message))  
                    {  
                       perror("send");  
                    } 
                    it++;
                    //set the string terminating NULL byte on the end 
                    //of the data read 
                    //send(sd , buffer , strlen(buffer) , 0 );  
                } 
            }  
            else
            {
               it++;  
            }
        }  
        sleep(1);
    }  
         
    return 0;  
}  
