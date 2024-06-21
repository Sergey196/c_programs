#include <asm/io.h>
#include <asm/delay.h>
#include "device.h"
#include "scull.h"
#include "baseitem.h"
#include "def.h"

//#include <linux/time.h>

extern uint64_t io_port[MAX_DEVICE];
struct DeviveInfo value_devices[MAX_DEVICE];
uint8_t is_used[MAX_DEVICE][MAX_CH_SIZE];

void device_init(int index)
{
   value_devices[index].device_size = input_type(index) ? MAX_CH_SIZE : MAX_CH_SIZE/2;
}
//---------------------------------------------------------------------------
uint8_t is_ready(int index)
{
   return inw(io_port[index] + STATUS) & 0x1;
}
//---------------------------------------------------------------------------
uint8_t input_type(int index)
{
   return (inw(io_port[index] + STATUS) & 0x2) >> 1;   
}
//---------------------------------------------------------------------------
uint32_t p1002_delay(uint16_t wDownCount, int index)
{
    uint16_t h, l;
    int count;

    wDownCount &= 0x7fff;
    if(wDownCount < 1) { wDownCount = 1; }
    /* Clock in=4M --> count 4000 = 1 ms ,count 1 = 0.25 us */

    l = wDownCount & 0xff;
    wDownCount = wDownCount / 256;
    h = wDownCount & 0xff;

    outw(0xB0, io_port[index] + 3 * 4);
    outw(l, io_port[index] + 3 * 4);
    outw(h, io_port[index] + 3 * 4);

    outw(0x80, io_port[index] + 3 * 4);

    l = inw(io_port[index] + 2 * 4);
    h = inw(io_port[index] + 2 * 4);

    for(count = 32767;count > 0; count--)
    {
        outw(0x80, io_port[index] + 12);
        l = inw(io_port[index] + 8);
        h = inw(io_port[index] + 8);
        if (h >= 0x80) { return 0; }
    }
    return -1;
}
//---------------------------------------------------------------------------
uint32_t set_gain(uint8_t gain, int index)
{
   outw(0, io_port[index] + GENERAL_CONTROL);
   //outw(index_ch, io_port[current_dev] + ANALOG_INPUT_CH_CONTOL);
   outw(gain, io_port[index] + ANALOG_INPUT_GAIN_CONTOL); 
   return p1002_delay(23, index);
}
//---------------------------------------------------------------------------
uint16_t get_ch(int index_ch, int index)
{
   uint16_t result = 0; 
   //printk("TEST index_ch = %d\n", io_port[index]); 
   outw(index_ch, io_port[index] + ANALOG_INPUT_CH_CONTOL);
   for(int i = 1; i <= 2; i++)
   {
      outw(1, io_port[index] + CLEAR);
      while(true)
      {
         if(((inw(io_port[index] + STATUS)) & 0x1) == 1) { break; }// check A/D busy?
         udelay(1);
      }
   
      result = (inw(io_port[index] + A_D_DATA)) & 0x0fff;
   }
   //printk("TEST result = %d\n", result); 
   return result;
} 
//---------------------------------------------------------------------------
void set_enable_ch(int index, uint16_t ch_num)
{
   is_used[index][ch_num] = 1;
}
//---------------------------------------------------------------------------
void set_disable_ch(int index, uint16_t ch_num)
{
   is_used[index][ch_num] = 0;  
}
//---------------------------------------------------------------------------
void process_device(int index)
{
   //printk("TEST io_port = %x\n", io_port[index]); 
   //struct timespec time_start; 
   //struct timespec time_current; 
   //getnstimeofday(&time_start);
   for(int i = 0; i < value_devices[index].device_size; i++) 
   {
      if(is_used[index][i]) {
         value_devices[index].values[i] = get_ch(i, index);  
      } 
   }
   //getnstimeofday(&time_current);
   //printk("TEST io_port = %X\n", time_current.tv_nsec - time_start.tv_nsec); 
}
