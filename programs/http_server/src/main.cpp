// Server side C/C++ program to demonstrate Socket programming 
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <iostream>

struct RequestData
{
   std::string SecFetchDest;
   std::string DataValue;
};

void init_openssl()
{ 
    SSL_load_error_strings();	
    OpenSSL_add_ssl_algorithms();
}

int create_socket(int port)
{
    int s;
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &(addr.sin_addr.s_addr));

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) 
    {
	   perror("Unable to create socket");
	   exit(EXIT_FAILURE);
    }

    if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) 
    {
	   perror("Unable to bind");
	   exit(EXIT_FAILURE);
    }

    if (listen(s, 1) < 0) 
    {
	   perror("Unable to listen");
	   exit(EXIT_FAILURE);
    }

    return s;
}

void cleanup_openssl()
{
    EVP_cleanup();
}

SSL_CTX *create_context()
{
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    method = TLS_server_method();

    ctx = SSL_CTX_new(method);
    if (!ctx) 
    {
	   perror("Unable to create SSL context");
	   //ERR_print_errors_fp(stderr);
	   exit(EXIT_FAILURE);
    }

    return ctx;
}

void configure_context(SSL_CTX *ctx)
{
    SSL_CTX_set_ecdh_auto(ctx, 1);

    /* Set the key and cert */
    if (SSL_CTX_use_certificate_file(ctx, "MyCertificate.crt", SSL_FILETYPE_PEM) <= 0) 
    {
        //ERR_print_errors_fp(stderr);
	    exit(EXIT_FAILURE);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, "MyKey.key", SSL_FILETYPE_PEM) <= 0 ) 
    {
        //ERR_print_errors_fp(stderr);
	    exit(EXIT_FAILURE);
    }
}

int main() 
{ 
    int sock;
    SSL_CTX *ctx;

    init_openssl();
    ctx = create_context();
    configure_context(ctx);
    sock = create_socket(8001);
    

    while(true)
    {
        char buffer[1024];
        struct sockaddr_in addr;
        uint len = sizeof(addr);
        SSL *ssl;
        
        int client_socket = accept(sock, (struct sockaddr*)&addr, &len); 
        if (client_socket < 0) 
        { 
            perror("Unable to accept");
            exit(EXIT_FAILURE);
        } 
        
        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, client_socket);
        
        if (SSL_accept(ssl) <= 0) 
        {
            //ERR_print_errors_fp(stderr);
        }
        
        //int resultRecv = recv(client_socket, buffer, sizeof(buffer), 0); 
        int resultRecv = SSL_read(ssl, buffer, sizeof(buffer));
        
        if (resultRecv == -1) 
        {
            std::cout << "SocketError1 = " << resultRecv <<  std::endl;
        } 
        else if(resultRecv == 0)
        {
            std::cout << "Socket close = " << resultRecv <<  std::endl;
        }

        std::cout << buffer << std::endl;
        //////////////////////////////////////
        std::string hello = "HTTP/1.1 200 OK Version: HTTP/1.1 Content-Type: text/html; charset=utf-8 Content-Length: " + std::string(buffer) + "<title>Test C++ HTTP Server</title><h1>Test page</h1><p>This is body of the test page...</p><h2>Request headers</h2><pre>" + std::string(buffer) + "</pre>\n<em><small>Test C++ Http Server</small></em>";

        //int resultSend = send(client_socket, hello.c_str(), hello.length(), 0); 
        int resultSend = SSL_write(ssl, hello.c_str(), hello.length());
        
        if (resultSend == -1) 
        {
            std::cout << "SocketError2 = " << resultSend <<  std::endl;
        } 
        SSL_shutdown(ssl);
        SSL_free(ssl);
        close(client_socket);
    }  
    
    close(sock);
    SSL_CTX_free(ctx);
    cleanup_openssl();
    
    return 0; 
}  
 
void fileParser()
{
    
}
