#ifndef DEVICE_H
#define DEVICE_H

#include <linux/types.h> 

#define DIRECT_RI      0x8
#define DIRECT_TIMER   0xA
#define DIRECT_RA      0xC
#define DIRECT_RD      0xE

#define INDIRECT_RID            0x0
#define INDIRECT_RS             0x1

#define INDIRECT_RDO8_1         0x8
#define INDIRECT_RDO16_9        0x9
#define INDIRECT_RDO24_17       0xA
#define INDIRECT_RDO32_25       0xB
#define INDIRECT_RDO40_33       0xC
#define INDIRECT_RDO48_41       0xD
#define INDIRECT_RDO56_49       0xE
#define INDIRECT_RDO64_57       0xF

#define INDIRECT_RDI16_1        0x9
#define INDIRECT_RDI32_17       0xB
#define INDIRECT_RDI48_33       0xD
#define INDIRECT_RDI64_49       0xF

#define INDIRECT_IMASK_8_1      0x18
#define INDIRECT_IMASK_16_9     0x19
#define INDIRECT_IMASK_24_17    0x1A
#define INDIRECT_IMASK_32_25    0x1B
#define INDIRECT_IMASK_40_33    0x1C
#define INDIRECT_IMASK_48_41    0x1D
#define INDIRECT_IMASK_56_49    0x1E
#define INDIRECT_IMASK_64_57    0x1F

#define INDIRECT_RIF_16_1       0x29
#define INDIRECT_RIF_32_17      0x2B
#define INDIRECT_RIF_48_33      0x2D
#define INDIRECT_RIF_64_49      0x2F

#define INDIRECT_TIMERCMP       0x02
#define INDIRECT_TIMERDIV       0x12

#define INDIRECT_PROG_RESET     0x75

#define INDIRECT_IOCFG1_16_1    0x78
#define INDIRECT_IOCFG1_32_17   0x79
#define INDIRECT_IOCFG1_48_33   0x7A
#define INDIRECT_IOCFG1_64_49   0x7B
#define INDIRECT_IOCFG2_16_1    0x7C
#define INDIRECT_IOCFG2_32_17   0x7D
#define INDIRECT_IOCFG2_48_33   0x7E
#define INDIRECT_IOCFG2_64_49   0x7F

#define INDIRECT_ADCCFG         0x21
#define INDIRECT_ADCDATA        0x06
#define INDIRECT_ADCCTRL        0x07
#define INDIRECT_ADCCST         0x07
#define INDIRECT_ADC2DATA       0x10
#define INDIRECT_ADC2CTRL       0x11
#define INDIRECT_ADC2CST        0x11

#define ADC_SCALE_10_10         0x0
#define ADC_SCALE_5_5           0x1
#define ADC_SCALE_2_5_2_5       0x2
#define ADC_SCALE_0_10          0x3

#define ADC_MODE_8_IN           0x0
#define ADC_MODE_4_PSEUDO_DIF   0x1
#define ADC_MODE_4_DIF          0x2
#define ADC_MODE_7_PSEUDO_DIF   0x3

uint16_t get_version(int index);
void init_dd64(int index);
void init_range(int index, uint16_t range_index, uint16_t value);
void set_ch_type(int index, uint16_t ch_num, uint16_t value);
void set_enable_ch(int index, uint16_t ch_num);
void set_disable_ch(int index, uint16_t ch_num);
void process_device(int index);

#endif 
