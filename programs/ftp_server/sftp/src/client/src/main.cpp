
#include <iostream>

#include <arpa/inet.h> 
#include <unistd.h>
#include <string.h> 
#include <iostream>
#include <fstream>
#include <openssl/ssl.h>
#include "lib_ftp_constants.h"
   
int main() 
{ 
    int s;
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &(addr.sin_addr.s_addr));

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
    }
    
    const SSL_METHOD *method = TLS_client_method(); /* Create new client-method instance */
    SSL_CTX *ctx = SSL_CTX_new(method);
    SSL *ssl = SSL_new(ctx);
    
    SSL_set_fd(ssl, s);
    
    int status = SSL_connect(ssl);
    
    SSL_CTX_set_ecdh_auto(ctx, 1);

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
    
    ////////////////
    
    char buffer[512];

    printf("SSL connection using %s\n", SSL_get_cipher (ssl));
    
    std::ofstream outfile { "2.pdf", std::ios::binary };
    
    _ftp_server::TMessage message;
    message.command = _ftp_server::commandStart;
    strcpy(message.data, "1.pdf");
    SSL_write(ssl, &message, sizeof(_ftp_server::TMessage));
    //send(sock, &message, sizeof(_ftp_server::TMessage), 0);
    
    sleep(1);
    
    message.command = _ftp_server::commandData;
    //send(sock, &message, sizeof(_ftp_server::TMessage), 0);
    SSL_write(ssl, &message, sizeof(_ftp_server::TMessage));
    
    while(true)
    { 
        usleep(100); 
        memset(message.data, 0, sizeof(message.data));
        //int res = recv(sock, &message, sizeof(_ftp_server::TMessage), 0);
        int res = SSL_read(ssl, buffer, sizeof(buffer));
        
        std::cout << "TEST recv = " << res <<  std::endl; 
        
        if(res < 1)
        {
           continue; 
        }
        std::cout << "TEST0 = " << message.command <<  std::endl;  
        if(message.command == _ftp_server::commandData)
        {
           std::cout << "TEST1" <<  std::endl;  
           outfile.write(message.data, sizeof(message.data)); 
           //send(sock, &message, sizeof(_ftp_server::TMessage), 0);
           SSL_write(ssl, &message, sizeof(_ftp_server::TMessage));
        }
        else if(message.command == _ftp_server::commandEnd)
        {
           std::cout << "TEST2" <<  std::endl;    
           //send(sock, &message, sizeof(_ftp_server::TMessage), 0);
           SSL_write(ssl, &message, sizeof(_ftp_server::TMessage));
        }
    }  
    outfile.close();
    
    SSL_free(ssl);
    close(s);
    SSL_CTX_free(ctx);
    
    return 0; 
}
