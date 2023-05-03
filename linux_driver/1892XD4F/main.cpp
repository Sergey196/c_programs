#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#define INIT_PORT 0
#define SET_SPT 1
#define WRITE_INFO 3
#define READ_PARAMS 4
#define READ_INFO 5
#define STOP 6

#define BUFFER_SIZE 8

struct SptParam
{
   uint8_t ch;
   uint16_t spt;
};

struct Message_Write
{
   uint8_t ch;
   uint8_t size;
   uint32_t buffer[BUFFER_SIZE];
};

struct Message_Read
{
   uint8_t ch;
   uint8_t size;
};

int main()
{
   int hdl = open("/dev/scull", O_RDONLY); 
   if (hdl < 0)
   {
      std::cout << "TEST" << std::endl; 
      return -1;
   }

   int result ;
   int val = 0;
   result = ioctl(hdl, INIT_PORT, val);
   std::cout << "TEST1 = " << result << std::endl;

   SptParam mes1;
   mes1.ch = 0;
   mes1.spt = 10;
   result = ioctl(hdl, SET_SPT, &mes1);
   std::cout << "TEST2 = " << result << std::endl;

   Message_Write mes2;
   mes2.ch = 0;
   mes2.size = BUFFER_SIZE;
   for(int i = 0; i < BUFFER_SIZE; i++)
   {
      mes2.buffer[i] = BUFFER_SIZE - i;
   }
   result = ioctl(hdl, WRITE_INFO, &mes2);
   std::cout << "TEST3 = " << result << std::endl;

   sleep(1);

   Message_Read mes3;
   mes3.ch = 0;
   mes3.size = BUFFER_SIZE;
   result = ioctl(hdl, READ_PARAMS, &mes3);
   std::cout << "TEST3 = " << result << std::endl;

   uint32_t buffer[BUFFER_SIZE];
   result = ioctl(hdl, READ_INFO, buffer);
   std::cout << "TEST4 = " << result << std::endl;
   for(int i = 0; i < BUFFER_SIZE; i++) {
      std::cout << "TEST buffer = " << buffer[i] << std::endl;
   }

   result = ioctl(hdl, STOP, val);
   std::cout << "TEST5 = " << result << std::endl;
   return result;
}
