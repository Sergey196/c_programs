#ifndef TDEFINES_INSTRUMENTS_H
#define TDEFINES_INSTRUMENTS_H 1

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

namespace _baseitem
{
   const std::string keyPath = "../resorces/certificates/shc-key.pem";
   const std::string certPath = "../resorces/certificates/shc-cert.pem";
   const int PORT { 443 };
   
   inline std::string createResponse(std::string message)
   {
      return "HTTP/1.1 200 OK\nVersion: HTTP/1.1\nContent-Type: text/html\ncharset=utf-8\nContent-Length: " + std::to_string(message.length()) + "\n\n" + message;  
   }
   
   inline std::string readFile(std::string file)
   {
      std::string result; 
      std::ifstream imgStream(file);
      std::cout << "TEST readFile = " << file << std::endl; 
      std::string line;
      while(std::getline(imgStream, line)) {
         result += line;
      }
      imgStream.close(); 
      return result;
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
       HttpResponse info;
       std::vector<std::string> listLines = split(fileText, "\n");
       listLines.resize(14);
       std::string message = listLines.at(0);
       if(message.find("POST") != std::string::npos)
       {
          info.url = message.substr(5, message.length() - 13);
       } else if(message.find("GET") != std::string::npos) {
          info.url = message.substr(4, message.length() - 13);
       } else { 
          return info; 
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
          
          std::string lineDataName = line.substr(0, pos); 
          std::string lineDataInfo = line.substr(pos + 2, line.length()); 
          
          //host;
          if(lineDataName == "Host")
          {
             info.host = lineDataInfo;  
          } else if(lineDataName == "Sec-Fetch-Dest") {
             info.sec_fetch_dest = lineDataInfo;  
          }
       }
       return info;
   };
};

#endif
