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

#ifndef TPROCESS_H
#define TPROCESS_H

#include <openssl/ssl.h>
#include <openssl/err.h>

class TProcess
{
   public:
      TProcess();
      ~TProcess();
      void start();
   private:
      void init_openssl(); 
      int create_socket(int port);
      void cleanup_openssl();
      void create_context();
      void configure_context();
      void requestProcess(int client_socket);
      void initClient(int client_socket);
      void closeClient(int client_socket);
      
      int sock;
      static thread_local SSL *ssl;
      SSL_CTX *ctx;
};

#endif // TPROCESS_H
