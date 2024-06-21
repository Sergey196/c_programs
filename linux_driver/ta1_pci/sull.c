#include <linux/slab.h>  
#include <linux/fs.h>   
#include <linux/errno.h>    
#include <linux/types.h>    
#include <linux/fcntl.h>    
#include <linux/cdev.h>
#include <linux/pci.h>
#include <linux/uaccess.h>

#include "sull.h"
#include "main.h"
#include "baseitem.h"
#include "def.h"

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

int scull_min =   0;
int scull_max =   4;
int scull_quantum = 4000;
int scull_qset = 1000;

int scull_major[MAX_DEVICE];

extern struct driver_addr *drv_priv[MAX_DEVICE];
//struct WriteMessage *message;        
extern int currentDev;
struct scull_dev scull_device[MAX_DEVICE]; 
struct class *dev_class;   

struct scull_info
{
   int index;
};

uint32_t scull_read_reg(int index, uint32_t addr)
{
   int rssult = ioread32(drv_priv[index]->hwmem + addr);
   printk(KERN_INFO "TEST1 scull_read_reg = %d\n", index); 
   printk(KERN_INFO "TEST2 scull_read_reg = %d\n", drv_priv[index]->hwmem); 
   printk(KERN_INFO "TEST3 scull_read_reg = %d\n", rssult); 
	return rssult;
}

void scull_write_reg(int index, uint32_t addr, uint32_t value)
{
   printk(KERN_INFO "TEST1 scull_write_reg = %d\n", index); 
   printk(KERN_INFO "TEST2 scull_write_reg = %x\n", addr); 
   printk(KERN_INFO "TEST3 scull_write_reg = %d\n", value); 
	iowrite32(value, drv_priv[index]->hwmem + addr);
}

int scull_release(struct inode *inode, struct file *file)
{
	struct scull_info* info = file->private_data;
      
    printk(KERN_INFO "TEST scull_release = %d\n", info->index ); 
   
	if(info)
	{
		kfree(info);
		info = NULL;
	}

	return 0;
}

int scull_open(struct inode *inode, struct file *file)
{
    struct scull_info *info = kzalloc(sizeof(struct scull_info), GFP_KERNEL);
    info->index = iminor(inode);
    
    printk(KERN_INFO "TEST scull_open = %d\n", info->index); 
    
    file->private_data = info;

	return 0;
}

long scull_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
   struct scull_info *info;
   printk(KERN_INFO "TEST1 scull_ioctl1 = %d\n", cmd); 
   printk(KERN_INFO "TEST2 scull_ioctl2 = %lu\n", arg); 
   
   info = file->private_data;
   
   printk(KERN_INFO "TEST3 scull_ioctl3 = %d\n", info->index); 

   switch(cmd) 
   {
      case READ_CMD:
      {
         return scull_read_reg(info->index, arg);
      }
      case WRITE_CMD:
      {
         struct WriteMessage *message = kzalloc(sizeof(struct WriteMessage), GFP_KERNEL);
         if(copy_from_user(message, (void *)arg, sizeof(struct WriteMessage))) {
             return -EFAULT;
         }
         scull_write_reg(info->index, message->addr, message->value);
         kfree(message);
         break;
      }
      default: 
      {
         break;
      }
   } 
   return 0;
}

struct file_operations scull_fops = {
    .owner          = THIS_MODULE,
    .open           = scull_open,
    .release        = scull_release,
    .unlocked_ioctl = scull_ioctl,
};

int uevent(struct device *dev, struct kobj_uevent_env *env)
{
	add_uevent_var(env, "DEVMODE=%#o", 0666);
	return 0;
}

void create_new_scull(int index)
{
   int result = 0;
   dev_t dev_scull = 0;
   printk(KERN_INFO "TEST1 create_new_scull = %d\n", index); 
   
   if (index) {
       dev_scull = MKDEV(scull_major[index], scull_min);
       result = register_chrdev_region(dev_scull, scull_max, "ta1_pci");
   } else {
       result = alloc_chrdev_region(&dev_scull, scull_min, scull_max, "ta1_pci");
       scull_major[index] = MAJOR(dev_scull);
   }

   if (result < 0) {
       printk(KERN_WARNING "TEST scull: can't get major %d\n", scull_major[index]);
       return;
   } else {
       printk(KERN_INFO "TEST scull: get major %d success\n", scull_major[index]);
   } 
   
   if(!dev_class) {
      dev_class = class_create(THIS_MODULE, "ta1_pci");
      dev_class->dev_uevent = uevent;
   }
   
   cdev_init(&scull_device[index].cdev, &scull_fops);
   scull_device[index].cdev.owner = THIS_MODULE;
   scull_device[index].cdev.ops = &scull_fops;
   scull_device[index].quantum = scull_quantum;
   scull_device[index].qset = scull_qset;
   mutex_init(&scull_device[index].mutex);
   cdev_add(&scull_device[index].cdev, dev_scull, 1);
   device_create(dev_class, NULL, dev_scull, NULL, "ta1_pci_%d", index);
}

void scull_remove(void) 
{
   printk(KERN_INFO "scull: cleanup start %d\n", currentDev);
   for (int i = 0; i < currentDev; i++) {
      dev_t dev_scull = MKDEV(scull_major[i], i);   
      cdev_del(&scull_device[i].cdev);
      unregister_chrdev_region(dev_scull, scull_min);
      device_destroy(dev_class, dev_scull);
   }    
   if(dev_class) {
      class_unregister(dev_class);
      class_destroy(dev_class);
   }
   printk(KERN_INFO "scull: cleanup success\n");
}
