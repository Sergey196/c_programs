#ifndef DEF_H
#define DEF_H

#define READ_CMD 0
#define WRITE_CMD 1

struct WriteMessage
{
   uint32_t addr;
   uint32_t value;
};

#endif
