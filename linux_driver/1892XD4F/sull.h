#ifndef SCULL_H
#define SCULL_H

int scull_init(void);
void scull_remove(void);

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

#endif
