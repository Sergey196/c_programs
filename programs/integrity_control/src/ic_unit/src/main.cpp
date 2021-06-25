#include <iostream>
#include "hashgenerator.h"
#include "lib_integrity_constants.h"
#include <vector>

class Data
{
   public:
     int a;
     int b;
};


int main() 
{
   Data *data1 = new Data();
   data1->a = 10;
   data1->b = 20;
   
   Data *data2 = new Data();
   data2->a = 30;
   data2->b = 40;
   
   std::vector<std::string> vec { "./test1.so", "./test2.so", "./test3.so", "./test4.so", "./test5.so", "./test6.so", "./test7.so", "./test8.so", "./test9.so", "./test10.so" };
   //std::vector<_integrity_control::ObjectInfo> vec { _integrity_control::ObjectInfo { sizeof(Data), data1}, _integrity_control::ObjectInfo { sizeof(Data), data2} };
   std::cout << "TEST result = " << _integrity_control::HashGenerator::calcHash(vec, _integrity_control::crc8) << std::endl;
}
