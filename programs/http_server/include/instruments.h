#ifndef TDEFINES_INSTRUMENTS_H
#define TDEFINES_INSTRUMENTS_H 1

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

namespace _baseitem
{
   const std::string resorcesPath = "../resorces";
   const std::string keyPath = resorcesPath + "/certificates/shc-key.pem";
   const std::string certPath = resorcesPath + "/certificates/shc-cert.pem";
   //const std::string responsePref { "HTTP/2.0 200 OK\nVersion: HTTP/2.0\ncharset=utf-8Content-Length: 88\n\n" };
   const int PORT { 443 };
   
   /*enum typeFile
   {
      html,
      css,
      ico
   };*/
   
   inline std::string createResponse200(std::string message, int size)
   {
      return "HTTP/2.0 200 OK\nVersion: HTTP/2.0\ncharset=utf-8\nContent-Length: " + std::to_string(size) + "\n\n" + message;  
   }
   
   inline std::string createResponse404()
   {
      return "HTTP/2.0 404 OK\nVersion: HTTP/2.0\ncharset=utf-8\n\n";  
   }
     
   struct HttpResponse
   {
      std::string url; 
      std::string sec_fetch_dest;
      std::string host;
   };
   
   inline std::vector<std::string> split(std::string str, std::string delimiter)
   {
      std::vector<std::string> list;
      size_t pos = 0;
      std::string token;
      while ((pos = str.find(delimiter)) != std::string::npos) {
          token = str.substr(0, pos);
          list.push_back(token);
          str.erase(0, pos + delimiter.length());
      }
      list.push_back(str);
      return list;
   };

   inline HttpResponse fileParser(std::string fileText)
   {
       std::vector<std::string> listLines = split(fileText, "\n");
       listLines.resize(14);
       std::string message = listLines.at(0);
       std::string url;
       std::string sec_fetch_dest;
       std::string host;
       if(message.find("POST") != std::string::npos)
       {
          url = message.substr(5, message.length() - 13);
       } else if(message.find("GET") != std::string::npos) {
          url = message.substr(4, message.length() - 13);
       } else { 
          return HttpResponse(); 
       }
       
       for(std::string line : listLines)
       {
          if(line == "avigate")
          {
             break; 
          }
          std::size_t pos = line.find(":"); 
          if(pos == std::string::npos)
          {
             continue; 
          }
          
          std::string lineDataName = line.substr(0, pos ); 
          std::string lineDataInfo = line.substr(pos + 2, line.length()); 
          
          //host;
          if(lineDataName == "Host")
          {
             host = lineDataInfo;  
          } else if(lineDataName == "Sec-Fetch-Dest") {
             sec_fetch_dest = lineDataInfo;  
          }
       }
       url.erase(std::remove_if(url.begin(), url.end(), isspace));
       host.erase(std::remove_if(host.begin(), host.end(), isspace));
       sec_fetch_dest.erase(std::remove_if(sec_fetch_dest.begin(), sec_fetch_dest.end(), isspace));
       
       HttpResponse info;
       info.url = url;
       info.host = host;
       info.sec_fetch_dest = sec_fetch_dest;
       return info;
   };
};

#endif
