/*
 * Copyright 2021 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "tprocess.h"
#include "instruments.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <iostream>
#include <thread>

thread_local SSL *TProcess::ssl = nullptr;
//-----------------------------------------------------------------------------
TProcess::TProcess()
{
    init_openssl();
    create_context();
    configure_context();
    sock = create_socket(8000);
}
//-----------------------------------------------------------------------------
TProcess::~TProcess()
{
    close(sock);
    SSL_CTX_free(ctx);
    cleanup_openssl(); 
}
//-----------------------------------------------------------------------------
void TProcess::initClient(int client_socket)
{
   ssl = SSL_new(ctx);
   SSL_set_fd(ssl, client_socket);
}
//-----------------------------------------------------------------------------
void TProcess::closeClient(int client_socket)
{
   SSL_shutdown(ssl);
   SSL_free(ssl);
   close(client_socket); 
}
//-----------------------------------------------------------------------------
void TProcess::requestProcess(int client_socket)
{
   char buffer[1024]; 
   initClient(client_socket);
   if (SSL_accept(ssl) <= 0) 
   {
       ERR_print_errors_fp(stderr);
   }
   
   //int resultRecv = recv(client_socket, buffer, sizeof(buffer), 0); 
   int resultRecv = SSL_read(ssl, buffer, sizeof(buffer));
   
   if (resultRecv == -1) 
   {
       std::cout << "SocketError1 = " << resultRecv <<  std::endl;
       closeClient(client_socket);
       return;
   } 
   else if(resultRecv == 0)
   {
       std::cout << "Socket close = " << resultRecv <<  std::endl;
       closeClient(client_socket);
       return;
   }
   
   _baseitem::HttpResponse info = _baseitem::fileParser(buffer);
   
   //std::cout << "TEST1 = " << info.host << std::endl;  
   //std::cout << "TEST2 = " << info.sec_fetch_dest << std::endl;
   //std::cout << "TEST3 = " << info.url << std::endl;  
   std::string message;
   if(info.sec_fetch_dest.find("document") != std::string::npos)
   {  
      message = "<head><link rel=\"stylesheet\" href=\"/index.css\"></head><title>Test C++ HTTP Server</title><h1>Test page</h1><p>This is body of the test page...</p><h2>Request headers</h2><pre>" + std::string(buffer) + "</pre>\n<em><small>Test C++ Http Server</small></em>"; 
   } else if(info.sec_fetch_dest.find("image") != std::string::npos) { 
       message = _baseitem::readFile("../resorces/favicon.ico");
   } else if(info.sec_fetch_dest.find("style") != std::string::npos) { 
       message = _baseitem::readFile("../resorces/index.css");
   }
   
   std::string response { _baseitem::createResponse(message) };
   //int resultSend = send(client_socket, hello.c_str(), hello.length(), 0); 
   int resultSend = SSL_write(ssl, response.c_str(), response.length());
   
   if (resultSend == -1) 
   {
       std::cout << "SocketError2 = " << resultSend <<  std::endl;
   } 
   closeClient(client_socket);
}
//-----------------------------------------------------------------------------
void TProcess::start()
{
    while(true)
    {
        struct sockaddr_in addr;
        uint len = sizeof(addr);
        
        int client_socket = accept(sock, (struct sockaddr*)&addr, &len); 
        std::cout << "TEST1 = " << client_socket << std::endl;
        if (client_socket < 0) 
        { 
            perror("Unable to accept");
            exit(EXIT_FAILURE);
        } 
        else 
        {
            std::thread(&TProcess::requestProcess, this, client_socket).detach();
        }
    }  
}
//-----------------------------------------------------------------------------
void TProcess::init_openssl()
{ 
    SSL_load_error_strings();	
    OpenSSL_add_ssl_algorithms();
    
}
//-----------------------------------------------------------------------------
int TProcess::create_socket(int port)
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
//-----------------------------------------------------------------------------
void TProcess::cleanup_openssl()
{
    EVP_cleanup();
}
//-----------------------------------------------------------------------------
void TProcess::create_context()
{
    const SSL_METHOD *method;

    method = TLS_server_method();

    ctx = SSL_CTX_new(method);
    if (!ctx) 
    {
	   perror("Unable to create SSL context");
	   ERR_print_errors_fp(stderr);
	   exit(EXIT_FAILURE);
    }
}
//-----------------------------------------------------------------------------
void TProcess::configure_context()
{
    SSL_CTX_set_ecdh_auto(ctx, 1);

    /* Set the key and cert */
    if (SSL_CTX_use_certificate_file(ctx, _baseitem::certPath.c_str(), SSL_FILETYPE_PEM) <= 0) 
    {
        ERR_print_errors_fp(stderr);
	    exit(EXIT_FAILURE);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, _baseitem::keyPath.c_str(), SSL_FILETYPE_PEM) <= 0 ) 
    {
        ERR_print_errors_fp(stderr);
	    exit(EXIT_FAILURE);
    }
}