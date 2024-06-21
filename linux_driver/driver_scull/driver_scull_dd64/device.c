#include <asm/io.h>
#include <asm/delay.h>
#include "device.h"
#include "scull.h"
#include "baseitem.h"
#include "def.h"

extern uint64_t io_port[MAX_DEVICE];
struct DeviveInfo value_devices[MAX_DEVICE];
uint16_t ch_type[MAX_DEVICE][DD64_MAX_CHANELL];
uint8_t is_used_ch[MAX_DEVICE][DD64_MAX_CHANELL];

//---------------------------------------------------------------------------   
uint16_t scull_read_reg(int index, uint16_t addr)
{
   outw(addr, io_port[index] + DIRECT_RA); 
   return inw(io_port[index] + DIRECT_RD);
}
//---------------------------------------------------------------------------
void scull_write_reg(int index, uint16_t addr, uint16_t value)
{
    outw(addr, io_port[index] + DIRECT_RA); 
    outw(value, io_port[index] + DIRECT_RD); 
}
//---------------------------------------------------------------------------   
uint16_t get_version(int index)
{
   return scull_read_reg(index, INDIRECT_RID);
}
//---------------------------------------------------------------------------
void init_dd64(int index)
{
   uint16_t valueRS; 
   scull_write_reg(index, INDIRECT_PROG_RESET, 0xA);
   valueRS = scull_read_reg(index, INDIRECT_RS);
   valueRS |= 0xF;
   scull_write_reg(index, INDIRECT_RS, valueRS);
}
//---------------------------------------------------------------------------
void init_range(int index, uint16_t range_index, uint16_t value)
{ 
   uint16_t res = 0;
   if(value == ADC_SCALE_10_10) {
      res = 0x00 << 4;
   } else if(value == ADC_SCALE_5_5) {
      res = 0x55 << 4;
   } else if(value == ADC_SCALE_2_5_2_5) {
      res = 0xaa << 4;
   } else if(value == ADC_SCALE_0_10) {
      res = 0xff << 4;
   }
    
   if(range_index == DD64_RANDE1_INDEX) {
      scull_write_reg(index, INDIRECT_ADCDATA, res);
      scull_write_reg(index, INDIRECT_ADCCTRL, (0x1 << 5)); //rr1EN  
   } else if(range_index == DD64_RANDE2_INDEX) { 
      scull_write_reg(index, INDIRECT_ADCDATA, res);
      scull_write_reg(index, INDIRECT_ADCCTRL, (0x1 << 4)); //rr2EN
   } else if(range_index == DD64_RANDE3_INDEX) {
      scull_write_reg(index, INDIRECT_ADC2DATA, res);
      scull_write_reg(index, INDIRECT_ADC2CTRL, (0x1 << 5)); //rr1EN
   } else if(range_index == DD64_RANDE4_INDEX) {   
      scull_write_reg(index, INDIRECT_ADC2DATA, res);
      scull_write_reg(index, INDIRECT_ADC2CTRL, (0x1 << 4)); //rr2EN  
   }
}
//---------------------------------------------------------------------------
void set_ch_type(int index, uint16_t ch_num, uint16_t value)
{
   if(ch_num >= DD64_MAX_CHANELL) {
      return; 
   }
   ch_type[index][ch_num] = value;
}
//---------------------------------------------------------------------------
void set_enable_ch(int index, uint16_t ch_num)
{
   is_used_ch[index][ch_num] = 1;
}
//---------------------------------------------------------------------------
void set_disable_ch(int index, uint16_t ch_num)
{
   is_used_ch[index][ch_num] = 0;    
}
//---------------------------------------------------------------------------
uint16_t read_adc_ch(int index, uint16_t ch_num)
{  
   uint16_t res = 0; 
   
   /*if(ch_num >= DD64_MAX_CHANELL) {
      return 0; 
   }*/
   
   if(ch_num < DD64_MAX_CHANELL/2) { 
       //printk("TEST adc1 read_adc_ch = %d\n", ch_num); 
       //printk("TEST adc1 ch_type[current_dev][ch_num] = %d\n", ch_type[current_dev][ch_num]); 
       res = ((ch_num & 7) << 9) | ((ch_type[index][ch_num] & 3) << 7) | 0x9;
       scull_write_reg(index, INDIRECT_ADCDATA, res);
       scull_write_reg(index, INDIRECT_ADCCTRL, (0x1 << 6)); //cr1EN
       
       scull_write_reg(index, INDIRECT_ADCCTRL, (0x1 << 7)); //adEN
       while(scull_read_reg(index, INDIRECT_ADCCST) & (1 << 7)) { udelay(1); }
       res = scull_read_reg(index, INDIRECT_ADCDATA);
   } else if(ch_num >= DD64_MAX_CHANELL/2) {
       //printk("TEST adc2 read_adc_ch = %d\n", ch_num); 
       //printk("TEST adc1 ch_type[current_dev][ch_num] = %d\n", ch_type[current_dev][ch_num]); 
       res = (((ch_num - (DD64_MAX_CHANELL / 2)) & 7) << 9) | ((ch_type[index][ch_num] & 3) << 7) | 0x9;
       scull_write_reg(index, INDIRECT_ADC2DATA, res);
       scull_write_reg(index, INDIRECT_ADC2CTRL, (0x1 << 6)); //cr1EN
       
       scull_write_reg(index, INDIRECT_ADC2CTRL, (0x1 << 7)); //adEN
       while(scull_read_reg(index, INDIRECT_ADC2CST) & (1 << 7)) { udelay(1); }
       res = scull_read_reg(index, INDIRECT_ADC2DATA);
   }
   return res;
}
//---------------------------------------------------------------------------
uint64_t read_dd64_io(int index)
{
   return ((int64_t)scull_read_reg(index, INDIRECT_RDI64_49) << 48) | ((int64_t)scull_read_reg(index, INDIRECT_RDI48_33) << 32) | (scull_read_reg(index, INDIRECT_RDI32_17) << 16) | scull_read_reg(index, INDIRECT_RDI16_1);
}
//---------------------------------------------------------------------------
void process_device(int index)
{
    for(int i = 0; i < DD64_MAX_CHANELL; i++)
    {
       if(is_used_ch[index][i]) {
          value_devices[index].values[i] = read_adc_ch(index, i);  
       } 
       if(ch_type[index][i] == ADC_MODE_4_DIF) {
          i++;  
       } 
    }
    value_devices[index].io_value = read_dd64_io(index);
}
