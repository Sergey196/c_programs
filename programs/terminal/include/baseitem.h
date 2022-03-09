#ifndef TDEFINES_BASEITEM_H
#define TDEFINES_BASEITEM_H 1

#include <QString>

const int WIDTH { 1000 };
const int HEIGHT { 1000 };

inline QString getErrorText(int errorCode)
{
   if(errorCode == 0) {
      return "";   
   } else if(errorCode == 1) {
      return "General errors";  
   } else if(errorCode == 2) {
      return "Misuse of shell builtins"; 
   } else if(errorCode == 126) {
      return "Command invoked cannot execute";  
   } else if(errorCode == 127) {
      return "Command not found";
   } else if(errorCode == 128) {
      return "Invalid argument to exit"; 
   } else if(errorCode == 130) {
      return "Script terminated by Control-C"; 
   } else if(errorCode == 255) {
      return "Exit status out of range"; 
   } else if((errorCode > 128) && (errorCode < 255)) {
      return "Fatal error signal " + QString::number(255 - errorCode); 
   } else {
      return QString::number(errorCode);  
   }
}


#endif
