#include <linux/slab.h>  
#include <linux/fs.h>   
#include <linux/errno.h>    
#include <linux/types.h>    
#include <linux/fcntl.h>    
#include <linux/cdev.h>
#include <linux/pci.h>
#include "sull.h"
#include "main.h"
#include "elvees_mcb03_regs.h"
#include "elvees_mcb03_bits.h"


#define DPRAM_HALF 0x20000
#define SWIC_RESET 0x00000079
#define SWIC_START 0x00000101

extern struct driver_addr *drv_priv;

uint32_t buffer[BUFFER_SIZE];

//uint32_t id_dev = 0;
int result;

uint8_t cur_read_ch = 0;
uint8_t cur_read_size = 0;


struct scull_qset 
{
    void **data;
    struct scull_qset *next;
};

struct scull_dev 
{
    struct scull_qset *data; 
    int quantum;             
    int qset;                
    unsigned long size;      
    unsigned int access_key; 
    struct mutex mutex;      
    struct cdev cdev;        
};

int scull_major =   0;
int scull_minor =   0;
int scull_quantum = 4000;
int scull_qset = 1000;
struct scull_dev scull_device; 
struct class *dev_class;
//int get_info = 1;

uint32_t mcb_read_reg(uint32_t addr)
{
	return ioread32(drv_priv->hwmem + addr);
}

void mcb_write_reg(uint32_t addr, uint32_t value)
{
	iowrite32(value, drv_priv->hwmem + addr);
}

void clean_dma(int port)
{
   uint32_t mode; 
   mcb_write_reg(MCB_SWIC_STATUS(port), 0x00000000);
   mcb_write_reg(MCB_SWIC_RX_DATA_IR(port), MCB_DPRAM_BASE(0) + DPRAM_HALF);
   //Обнуляем всё 

   mode = mcb_read_reg (MCB_SWIC_MODE_CR (port));
   mode &= ~ (MC_SWIC_AutoStart | MC_SWIC_LinkStart);
   mode |= MC_SWIC_LinkDisabled;
   mcb_write_reg (MCB_SWIC_MODE_CR (port), mode);

   mcb_write_reg (MCB_SWIC_RX_DESC_RUN (port), 0);
   mcb_write_reg (MCB_SWIC_RX_DATA_RUN (port), 0);
   mcb_write_reg (MCB_SWIC_TX_DESC_RUN (port), 0);
   mcb_write_reg (MCB_SWIC_TX_DATA_RUN (port), 0);

   mode |= MC_SWIC_SWCORE_RST;
   //mode |= MC_SWIC_DS_RST;
   mcb_write_reg (MCB_SWIC_MODE_CR (port), mode);

   mcb_read_reg (MCB_SWIC_RX_DESC_CSR (port));
   mcb_read_reg (MCB_SWIC_RX_DATA_CSR (port));
   mcb_read_reg (MCB_SWIC_TX_DESC_CSR (port));
   mcb_read_reg (MCB_SWIC_TX_DATA_CSR (port));

   mode &= ~MC_SWIC_SWCORE_RST;
   //mode &= ~MC_SWIC_DS_RST;
   mcb_write_reg (MCB_SWIC_MODE_CR (port), mode);

   mcb_write_reg (MCB_SWIC_RX_DESC_CP (port), 0);
   mcb_write_reg (MCB_SWIC_RX_DATA_CP (port), 0);
   mcb_write_reg (MCB_SWIC_TX_DESC_CP (port), 0);
   mcb_write_reg (MCB_SWIC_TX_DATA_CP (port), 0);

   mcb_write_reg (MCB_SWIC_RX_DESC_IR (port), 0);
   mcb_write_reg (MCB_SWIC_RX_DATA_IR (port), 0);
   mcb_write_reg (MCB_SWIC_TX_DESC_IR (port), 0);
   mcb_write_reg (MCB_SWIC_TX_DATA_IR (port), 0);

   mcb_write_reg (MCB_SWIC_RX_DESC_CSR (port), 0);
   mcb_write_reg (MCB_SWIC_RX_DATA_CSR (port), 0);
   mcb_write_reg (MCB_SWIC_TX_DESC_CSR (port), 0);
   mcb_write_reg (MCB_SWIC_TX_DATA_CSR (port), 0);
}

void init_hw(int chan)
{
   if(chan > 3)
   {
      return;
   }

   clean_dma(chan);

   mcb_write_reg(MCB_SWIC_MODE_CR(chan), SWIC_RESET); //Сброс SWIC
   mcb_write_reg(MCB_SWIC_MODE_CR(chan), SWIC_START); //Запуск соеденения
   //MCB_SWIC_TX_SPEED Регистр управления скоростью передачи
   //MC_SWIC_PLL_TX_EN разрешение PLL_TX_SWIC
   //MC_SWIC_LVDS_EN Управление работой приемопередатчиков LVDS SWIC:
   //MC_SWIC_TX_SPEED_PRM Определяет скорость передачи данных при установке соединения (врежиме авто установки скорости). Должен быть записан код 0x02
   mcb_write_reg(MCB_SWIC_TX_SPEED(chan), MC_SWIC_PLL_TX_EN | MC_SWIC_LVDS_EN | MC_SWIC_TX_SPEED_PRM(2));
   //MCB_SWIC_MODE_CR Регистр управления режимом работы
   //MC_SWIC_LinkStart Установка LinkStart для блока Link interface
   //MC_SWIC_AutoStart Установка Autostart для блока Link interface
   //MC_SWIC_WORK_TYPE  Тип режима работы
   mcb_write_reg(MCB_SWIC_MODE_CR(chan), MC_SWIC_LinkStart | MC_SWIC_AutoStart | MC_SWIC_WORK_TYPE);
}

void set_spt(int spd, int chan)
{
    printk(KERN_INFO "\nTEST set_spt chan = %d\n", chan); 
    printk(KERN_INFO "\nTEST set_spt spd = %d\n", spd); 
    if((chan > 3) || (spd > 400))
    {
       return;
    }
    mcb_write_reg(MCB_SWIC_TX_SPEED(chan), MC_SWIC_PLL_TX_EN | MC_SWIC_LVDS_EN | MC_SWIC_TX_SPEED_PRM(spd/5));
}

void clearTx(void)
{
    uint32_t addr = MCB_DPRAM_BASE(0) + DPRAM_HALF;
    int i;
    for(i = 0; i < BUFFER_SIZE + 2; i++) {
        mcb_write_reg(addr, 0);
        addr += 4;
    }
}

void clearRx(void)
{
    uint32_t addr = MCB_DPRAM_BASE(0);
    int i;
    for(i = 0; i < BUFFER_SIZE + 2; i++) {
        mcb_write_reg(addr, 0);
        addr += 4;
    }
}

void writeMessage(struct Message_Write *mes)
{
    int i;
    uint32_t addr;
    printk(KERN_INFO "\nTEST write size = %d\n", mes->size); 
    printk(KERN_INFO "\nTEST write ch = %d\n", mes->ch); 
    if((mes->ch > 3) || (mes->size > BUFFER_SIZE))
    {
       return;
    }

    clearTx();

    addr = MCB_DPRAM_BASE(0) + DPRAM_HALF + 8;
    for(i = 0; i < mes->size; i++)	{
        mcb_write_reg(addr, mes->buffer[i]);
        printk(KERN_INFO "\nTEST write = %d\n", mes->buffer[i]); 
        addr += 4;
    }

    //Передача количества байт (начало всегда одинаковое 0xA)
    mcb_write_reg(MCB_DPRAM_BASE(0) + DPRAM_HALF, 0xA0000000 | (mes->size * 4));

    // packet transfer
    mcb_write_reg(MCB_SWIC_TX_DESC_IR(mes->ch), MCB_DPRAM_BASE(0) + DPRAM_HALF);
    mcb_write_reg(MCB_SWIC_TX_DATA_IR(mes->ch), MCB_DPRAM_BASE(0) + DPRAM_HALF + 8);

    mcb_write_reg(MCB_SWIC_TX_DESC_CSR(mes->ch), MC_DMA_CSR_WCX(0));
    mcb_write_reg(MCB_SWIC_TX_DATA_CSR(mes->ch), MC_DMA_CSR_WCX(mes->size / 2 - 1));

    mcb_write_reg(MCB_SWIC_TX_DATA_RUN(mes->ch), 1);
    mcb_write_reg(MCB_SWIC_TX_DESC_RUN(mes->ch), 1);
}

int readMessage(uint32_t *buffer)
{
   uint32_t desc;
   uint32_t addr;
   int i;
   clearRx();
   
   mcb_write_reg(MCB_DPRAM_BASE(0), 0xA0000000);
   
   mcb_write_reg(MCB_SWIC_RX_DESC_IR(cur_read_ch), MCB_DPRAM_BASE(0));
   mcb_write_reg(MCB_SWIC_RX_DATA_IR(cur_read_ch), MCB_DPRAM_BASE(0) + 8);
   
   mcb_write_reg(MCB_SWIC_RX_DESC_CSR(cur_read_ch), MC_DMA_CSR_WCX(0)); //Обнуляем счётчик слов
   mcb_write_reg(MCB_SWIC_RX_DATA_CSR(cur_read_ch), MC_DMA_CSR_WCX(cur_read_size / 2 - 1));
   
   mcb_write_reg(MCB_SWIC_RX_DATA_RUN(cur_read_ch), 1);
   mcb_write_reg(MCB_SWIC_RX_DESC_RUN(cur_read_ch), 1);
   
   desc = mcb_read_reg(MCB_DPRAM_BASE(0)) & 0xFFFFFFF;
   printk(KERN_INFO "\nTEST read desc = %d\n", desc); 
   if(!desc) {
      return desc;  
   }
   
   addr = MCB_DPRAM_BASE(0) + 8;
   for (i = 0; i < cur_read_size; ++i) {
       buffer[i] = mcb_read_reg(addr);
       printk(KERN_INFO "\nTEST read add = %d\n", buffer[i]); 
       addr += 4;
   }
   return desc;
}


long scull_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
   printk(KERN_INFO "\nTEST1 scull_ioctl1 = %d\n", cmd); 
   printk(KERN_INFO "\nTEST2 scull_ioctl2 = %lu\n", arg); 

   switch(cmd) 
   {
      case INIT_PORT:
      {
         init_hw(arg); 
         result = 0;
         break;
      }
      case SET_SPT:
      {
         struct SptParam *mes = kmalloc(sizeof(struct SptParam), GFP_DMA);
         if (copy_from_user(mes, (void *)arg, sizeof(struct SptParam))) {
            return -EFAULT;
         }
         set_spt(mes->spt, mes->ch);
         kfree(mes);
         result = 0;
         break;
      }
      case WRITE_INFO:
      {
         struct Message_Write *mes = kmalloc(sizeof(struct Message_Write), GFP_DMA); 
         if(copy_from_user(mes, (void *)arg, sizeof(struct Message_Write))) {
             return -EFAULT;
         }
         writeMessage(mes);
         result = 0;
         break;
      }
      case READ_PARAMS:
      {
         struct Message_Read *mes = kmalloc(sizeof(struct Message_Read), GFP_DMA); 
         if(copy_from_user(mes, (void *)arg, sizeof(struct Message_Read))) {
             return -EFAULT;
         }
         cur_read_ch = mes->ch;
         cur_read_size = mes->size;
         kfree(mes);
         result = 0;
         break;
      }
      case READ_INFO:
      {
         result = readMessage(buffer);
         if(copy_to_user((void **)arg, buffer, sizeof(buffer))) {
             return -EFAULT;
         }
         break;
      }
      case STOP:
      {
         clean_dma(arg); 
         result = 0;
         break;
      }
      default: 
      {
         result = 0; 
         break;
      }
   } 
   return result;
}

struct file_operations scull_fops = {
    .owner          = THIS_MODULE,
    .unlocked_ioctl = scull_ioctl,
};

int elvees_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	add_uevent_var(env, "DEVMODE=%#o", 0666);
	return 0;
}

int scull_init(void) 
{
    int result;
    dev_t dev_scull = 0;
    
    scull_major = MAJOR(dev_scull);
    result = alloc_chrdev_region(&dev_scull, scull_minor, 1, "scull");

    if (result < 0) {
        printk(KERN_WARNING "scull: can't get major %d\n", scull_major);
        return result;
    } else {
        printk(KERN_INFO "scull: get major %d success\n", scull_major);
    }        
    
    dev_class = class_create(THIS_MODULE, "scull");
    dev_class->dev_uevent = elvees_uevent;
    cdev_init(&scull_device.cdev, &scull_fops);
    scull_device.cdev.owner = THIS_MODULE;
    scull_device.cdev.ops = &scull_fops;
    scull_device.quantum = scull_quantum;
    scull_device.qset = scull_qset;
    cdev_add(&scull_device.cdev, dev_scull, 1);
    if (result) {
        printk(KERN_NOTICE "Error adding scull\n");
    } else {
        printk(KERN_INFO "scull add success\n");
    }
    mutex_init(&scull_device.mutex);
    device_create(dev_class, NULL, dev_scull, NULL, "scull");
    
    return result;
}

void scull_remove(void) 
{
    struct scull_qset *next, *dptr;
    int qset = scull_device.qset;   /* "dev" is not-null */
    int i;    
    for (dptr = scull_device.data; dptr; dptr = next) { /* all the list items */
        if (dptr->data) {
            for (i = 0; i < qset; i++)
            {
                kfree(dptr->data[i]);
            }
            kfree(dptr->data);
            dptr->data = NULL;
        }
        next = dptr->next;
        kfree(dptr);
    }
    scull_device.size = 0;
    scull_device.data = NULL;
    scull_device.quantum = scull_quantum;
    scull_device.qset = scull_qset;
    
    cdev_del(&scull_device.cdev);
    device_destroy(dev_class, MKDEV(scull_major, scull_minor));
	unregister_chrdev_region(MKDEV(scull_major, scull_minor), MINORMASK);
	class_unregister(dev_class);
	class_destroy(dev_class);
}
