#ifndef DEF_H
#define DEF_H

#define PCI1002LU_READY         0
#define PCI1002LU_INPUT_TYPE    1
#define PCI1002LU_SET_GAIN      3
#define PCI1002LU_GET_VALUE     4
#define PCI1002LU_TIMER_PREIOD  5
#define PCI1002LU_TIMER_START   6
#define PCI1002LU_TIMER_STOP    7
#define PCI1002LU_ENABLE_CH     8
#define PCI1002LU_DISABLE_CH    9
#define PCI1002LU_SET_CPU       10

#define ADC_SCALE_10_10        0x0
#define ADC_SCALE_5_5          0x1
#define ADC_SCALE_2_5_2_5      0x2
#define ADC_SCALE_1_25_1_25    0x3  

#define MAX_CH_SIZE 32
#define MAX_DEVICE 4

#define ONE_MKS_IN_NS 1000
#define ONE_MS_IN_NS 1000 * ONE_MKS_IN_NS
#define ONE_SEC_IN_NS 1000 * ONE_MS_IN_NS

struct DeviveInfo
{
   uint16_t device_size; 
   uint16_t values[MAX_CH_SIZE];
};

#endif
