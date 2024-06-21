#ifndef DEF_H
#define DEF_H

#define DD64_INIT 0
//#define DD64_RREAD_IO 1
#define DD64_INIT_RANGE 3
#define DD64_INIT_CHANEL 4
//#define DD64_READ_ADC_CH 5
#define DD64_GET_VERSION 5
#define DD64_TIMER_PREIOD  6
#define DD64_TIMER_START   7
#define DD64_TIMER_STOP    8
#define DD64_ENABLE_CH     9
#define DD64_DISABLE_CH    10
#define DD64_GET_VALUE     11
#define DD64_SET_CPU       12

#define DD64_RANDE1_INDEX 0
#define DD64_RANDE2_INDEX 1
#define DD64_RANDE3_INDEX 2
#define DD64_RANDE4_INDEX 3

#define ADC_SCALE_10_10         0x0
#define ADC_SCALE_5_5           0x1
#define ADC_SCALE_2_5_2_5       0x2
#define ADC_SCALE_0_10          0x3

#define ADC_MODE_8_IN           0x0
#define ADC_MODE_4_PSEUDO_DIF   0x1
#define ADC_MODE_4_DIF          0x2
#define ADC_MODE_7_PSEUDO_DIF   0x3

#define DD64_MAX_CHANELL   16
#define MAX_DEVICE 4

#define ONE_MKS_IN_NS 1000
#define ONE_MS_IN_NS 1000 * ONE_MKS_IN_NS
#define ONE_SEC_IN_NS 1000 * ONE_MS_IN_NS

struct WriteMessage
{
   uint16_t index;
   uint16_t value;
};

struct DeviveInfo
{
   uint16_t values[DD64_MAX_CHANELL];
   uint64_t io_value;
};

#endif
