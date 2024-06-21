#ifndef DEVICE_H
#define DEVICE_H

#include <linux/types.h> 

#define TIMER_1                   0 
#define TIMER_2                   0x4 
#define TIMER_3                   0x8 
#define CONTROL_8254              0xC 
#define ANALOG_INPUT_CH_CONTOL    0x10 
#define STATUS                    0x10 
#define ANALOG_INPUT_GAIN_CONTOL  0x14 
#define GENERAL_CONTROL           0x18 
#define A_D_SOFTWARE              0x1C 
#define CLEAR                     0x1C 
#define DIJITAL_OUTPUT            0x20 
#define DIJITAL_INPUT             0x20 
#define A_D_DATA                  0x30 

#define PCI_1002_LU_ID            200 

uint32_t set_gain(uint8_t gain, int index);
uint8_t is_ready(int index);
uint8_t input_type(int index);
void process_device(int index);
void device_init(int index);
void set_enable_ch(int index, uint16_t ch_num);
void set_disable_ch(int index, uint16_t ch_num);

#endif 
