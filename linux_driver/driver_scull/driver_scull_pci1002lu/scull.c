#include <linux/types.h>     
#include <linux/string.h>
#include <asm/io.h>
#include <linux/timer.h>
#include <linux/pci.h>
#include <linux/kthread.h> 
#include <linux/spinlock.h>
#include <uapi/linux/sched/types.h>
#include <linux/sched.h>
#include "scull.h"
#include "baseitem.h"
#include "def.h"
#include "device.h"

#include <asm/delay.h>
/*
 * Representation of scull quantum sets.
 */

int scull_major = 0;
int scull_minor = 0;
int scull_quantum = 4000;
int scull_qset = 1000;
//extern int current_dev;

uint64_t timeout = ONE_MS_IN_NS;

struct task_struct *etx_thread[MAX_DEVICE];
spinlock_t lock[MAX_DEVICE];
struct hrtimer timers[MAX_DEVICE];
uint8_t is_run[MAX_DEVICE];
//struct WriteMessage *message;        
extern int currentDev;
extern struct DeviveInfo value_devices[MAX_DEVICE];
struct scull_dev scull_devices[MAX_DEVICE]; 
struct class *dev_class[MAX_DEVICE];   
int cur_cpu[MAX_DEVICE]; 

//struct timespec time_start; 
//struct timespec time_current; 

//---------------------------------------------------------------------------
int process_pci1002lu(void *args)
{ 
   struct index_info *info = args;
   bool was_frozen;
   
   while(!kthread_freezable_should_stop(&was_frozen)) 
   {
      //printk("TEST process_pci1002lu1 = %d\n", info->index);   
      spin_lock(&lock[info->index]);
      //getnstimeofday(&time_start); 
      process_device(info->index);
      //printk("TEST process_pci1002lu2 = %d\n", info->index);  
      //getnstimeofday(&time_current);
      //printk("TEST process_dd64 = %X\n", time_current.tv_nsec - time_start.tv_nsec); 
   }
   kfree(info);
   return 0;
}
//---------------------------------------------------------------------------
enum hrtimer_restart pci1002lu_unlock(struct hrtimer *timer)
{ 
   for(int i = 0; i < MAX_DEVICE; i++) 
   {
      if(&timers[i] == timer) {
         //getnstimeofday(&time_start); 
         //printk("TEST pci1002lu_unlock = %d\n", i);
         //printk("TEST pci1002lu_unlock1 = %d\n", i);    
         if(spin_is_locked(&lock[i])) { 
            spin_unlock(&lock[i]);
         }
         //printk("TEST pci1002lu_unlock2 = %d\n", i);   
         //getnstimeofday(&time_current);
         //printk("TEST process_dd64 = %X\n", time_current.tv_nsec - time_start.tv_nsec); 
         break;
      }
   }
   hrtimer_forward_now(timer, ns_to_ktime(timeout)); 
   return HRTIMER_RESTART;
}
//---------------------------------------------------------------------------
int scull_release(struct inode *inode, struct file *file)
{
	struct index_info* info = file->private_data;
      
    //printk(KERN_INFO "TEST scull_release = %d\n", info->index ); 
   
	if(info)
	{
		kfree(info);
		info = NULL;
	}

	return 0;
}
//---------------------------------------------------------------------------
int scull_open(struct inode *inode, struct file *file)
{
    struct index_info *info = kzalloc(sizeof(struct index_info), GFP_KERNEL);
    info->index = iminor(inode);
    
    //printk(KERN_INFO "TEST scull_open = %d\n", info->index); 
    
    file->private_data = info;

	return 0;
}
//---------------------------------------------------------------------------
void start(int index)
{
   struct index_info *info = kzalloc(sizeof(struct index_info), GFP_KERNEL);
   //struct sched_param param = { .sched_priority = 1 };
   info->index = index; 
   if(spin_is_locked(&lock[index])) { 
      spin_unlock(&lock[index]);
   }
   etx_thread[index] = kthread_create(&process_pci1002lu, info, "pci1002lu"); 
   if(cur_cpu[index] >= 0) {
      set_user_nice(etx_thread[index], -20);
      kthread_bind(etx_thread[index], cur_cpu[index]);
   }
   wake_up_process(etx_thread[index]);
   //sched_setscheduler(etx_thread[index], SCHED_RR, &param);
   hrtimer_start(&timers[index], ns_to_ktime(timeout), HRTIMER_MODE_ABS);
   is_run[index] = 1;
}
//---------------------------------------------------------------------------
void stop(int index)
{
   kthread_stop(etx_thread[index]);
   hrtimer_cancel(&timers[index]);
   if(spin_is_locked(&lock[index])) { 
      spin_unlock(&lock[index]);
   }
   is_run[index] = 0; 
}
//---------------------------------------------------------------------------
long scull_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
   struct index_info *info;
   //printk(KERN_INFO "TEST1 scull_ioctl1 = %d\n", cmd); 
   //printk(KERN_INFO "TEST2 scull_ioctl2 = %lu\n", arg); 
   
   info = file->private_data;
   //current_dev = info->index;
   //printk(KERN_INFO "TEST3 scull_ioctl1 = %d\n", current_dev); 

   switch(cmd) 
   {
      case PCI1002LU_READY:
      {
         return is_ready(info->index);
      }
      case PCI1002LU_INPUT_TYPE:
      {
         return input_type(info->index);
      }
      case PCI1002LU_SET_GAIN:
      {
         return set_gain(arg, info->index);
      }
      /*case PCI1002LU_GET_CH_VALUE:
      {
         return get_ch(arg);
      }*/
      case PCI1002LU_TIMER_PREIOD:
      {
         printk("TEST1 PCI1002LU_TIMER_PREIOD = %lu\n", arg);  
         if(arg >= MIN_TIMEOUT) {
            timeout = ONE_MKS_IN_NS * arg;   
         }
         break;
      }
      case PCI1002LU_TIMER_START:
      {
         printk("TEST1 PCI1002LU_TIMER_START\n");  
         start(info->index);
         break;
      }
      case PCI1002LU_TIMER_STOP:
      {
         printk("TEST1 PCI1002LU_TIMER_STOP\n");  
         stop(info->index);
         break;
      }
      case PCI1002LU_GET_VALUE:
      {
         if(copy_to_user((void *)arg, &value_devices[info->index], sizeof(struct DeviveInfo))) {
            return -EFAULT;
         } 
         break;
      }
      case PCI1002LU_ENABLE_CH:
      {  
         if(arg < MAX_CH_SIZE) {
            set_enable_ch(info->index, arg);
         }
         break;
      }
      case PCI1002LU_DISABLE_CH:
      {
         if(arg < MAX_CH_SIZE) {
            set_disable_ch(info->index, arg);
         }
         break;
      }
      case PCI1002LU_SET_CPU:
      {
         printk("TEST1 PCI1002LU_SET_CPU index = %d cpu = %lu\n", info->index, arg);   
         cur_cpu[info->index] = arg; 
         break;
      }
      default: 
      {
         return -1; 
      }
   } 
   return 0;
}
//---------------------------------------------------------------------------
struct file_operations scull_fops = {
    .owner          = THIS_MODULE,
    .open           = scull_open,
    .release        = scull_release,
    .unlocked_ioctl = scull_ioctl,
};
//---------------------------------------------------------------------------
int uevent(struct device *dev, struct kobj_uevent_env *env)
{
	add_uevent_var(env, "DEVMODE=%#o", 0666);
	return 0;
}
//---------------------------------------------------------------------------
void scull_setup_cdev(struct scull_dev *dev, int index)
{
   char buffer[100];
   int err, devno;
   sprintf(buffer, "pci1002lu_%d", index);

   devno = MKDEV(scull_major, scull_minor + index);
   cdev_init(&dev->cdev, &scull_fops);
   dev->cdev.owner = THIS_MODULE;
   err = cdev_add(&dev->cdev, devno, 1);

   if (err) {
      printk(KERN_NOTICE "Error %d adding scull%d", err, index);
   }
    
   dev_class[index] = class_create(THIS_MODULE, buffer);
   dev_class[index]->dev_uevent = uevent;
   printk("TEST scull index = %d\n", index); 
   device_create(dev_class[index], NULL, devno, NULL, buffer);
}
//---------------------------------------------------------------------------
void scull_init(void)
{
   uint32_t result;
   dev_t dev = 0;
   
   for(int i = 0; i < MAX_DEVICE; i++)
   {
      value_devices[i].device_size = 0;   
      for(int j = 0; j < MAX_CH_SIZE; j++)
      {
         value_devices[i].values[j] = 0;  
      }
   }
   
   if (scull_major) {
      dev = MKDEV(scull_major, scull_minor);
      result = register_chrdev_region(dev, MAX_DEVICE, "pci1002lu");
   } else {
      result = alloc_chrdev_region(&dev, scull_minor, MAX_DEVICE, "pci1002lu");
      scull_major = MAJOR(dev);
   }
   if (result < 0) {
      printk(KERN_WARNING "scull: can't get major %d\n", scull_major);
   } 
}
//---------------------------------------------------------------------------
void create_new_scull(int index)
{
   scull_devices[index].quantum = scull_quantum;
   scull_devices[index].qset = scull_qset;
   sema_init(&scull_devices[index].sem, 1);
   scull_setup_cdev(&scull_devices[index], index);
   
   spin_lock_init(&lock[index]);
   hrtimer_init(&timers[index], CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
   timers[index].function = &pci1002lu_unlock;
   
   is_run[index] = 0;
   cur_cpu[index] = -1; 
   device_init(index);
}
//---------------------------------------------------------------------------
int scull_trim(struct scull_dev *dev)
{
   struct scull_qset *next, *dptr;
   int qset = dev->qset;   
   int i;
   
   for(dptr = dev->data; dptr; dptr = next) 
   {
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
   dev->size = 0;
   dev->quantum = scull_quantum;
   dev->qset = scull_qset;
   dev->data = NULL;
   return 0;
}
//---------------------------------------------------------------------------
void scull_remove(void) 
{
   int i;
   dev_t devno = MKDEV(scull_major, scull_minor);
   
   for(i = 0; i < currentDev; i++) 
   {
      if(is_run[i] == 1) {
         stop(i); 
      }
      scull_trim(scull_devices + i);
      cdev_del(&scull_devices[i].cdev);
      //device_destroy(dev_class[i], devno);
      class_unregister(dev_class[i]);
      class_destroy(dev_class[i]);
   }
   unregister_chrdev_region(devno, MAX_DEVICE);
}
