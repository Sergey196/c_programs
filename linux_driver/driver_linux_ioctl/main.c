#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>   /* printk() */
#include <linux/slab.h>     /* kmalloc() */
#include <linux/fs.h>       /* everything... */
#include <linux/errno.h>    /* error codes */
#include <linux/types.h>    /* size_t */
#include <linux/fcntl.h>    /* O_ACCMODE */
#include <linux/cdev.h>
#include <asm/uaccess.h>    /* copy_*_user */

#define MAX_BUFFER_SIZE 400
#define MAX_MES_SIZE 40

#define ADD_1 0
#define ADD_2 1

char array[MAX_BUFFER_SIZE];
int pos_set = 0;
int pos_get = 0;

int add = 0;


struct scull_qset 
{
    void **data;
    struct scull_qset *next;
};

struct scull_dev 
{
    struct scull_qset *data;  /* Pointer to first quantum set. */
    int quantum;              /* The current quantum size. */
    int qset;                 /* The current array size. */
    unsigned long size;       /* Amount of data stored here. */
    unsigned int access_key;  /* Used by sculluid and scullpriv. */
    struct mutex mutex;       /* Mutual exclusion semaphore. */
    struct cdev cdev;         /* Char device structure. */
};

int scull_major =   0;
int scull_minor =   0;
int scull_quantum = 4000;
int scull_qset = 1000;
struct scull_dev scull_device; 
struct class *dev_class;
//int get_info = 1;

ssize_t scull_read(struct file *filp, char *buf, size_t count, loff_t *offp) 
{
    mutex_lock_interruptible(&scull_device.mutex);
    /*if(pos_get >= pos_set)
    {
       return 0; 
    }*/
    if(pos_get >= 400) {
       pos_get = 0; 
    }
    
    printk(KERN_INFO "\nTEST1 = %d\n", (int)count);
    
    copy_to_user(buf, array + pos_get, MAX_MES_SIZE);
    memset(array + pos_get, 0, MAX_MES_SIZE);
    pos_get = pos_get + MAX_MES_SIZE;
    mutex_unlock(&scull_device.mutex);
    return MAX_MES_SIZE;
}

ssize_t scull_write(struct file *filp,const char *buf, size_t count, loff_t *offp)
{
    printk(KERN_INFO "\nTEST2 = %d\n", (int)count);
    mutex_lock_interruptible(&scull_device.mutex);
    if(count > MAX_MES_SIZE)
    {
       return 0; 
    }
    if(pos_set >= MAX_BUFFER_SIZE) {
       pos_set = 0; 
    }
    
    copy_from_user(array + pos_set, buf, MAX_MES_SIZE);
    pos_set = pos_set + MAX_MES_SIZE;
    mutex_unlock(&scull_device.mutex);
    return count;
}

long scull_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
   printk(KERN_INFO "\nTEST1 add = %d\n", cmd); 
   printk(KERN_INFO "\nTEST2 add = %lu\n", arg); 
   switch(cmd) 
   {
      case ADD_1:
      {
         add = add + 1; 
         break;
      }
      case ADD_2:
      {
         add = add + 2;  
         break;
      }
      default: 
      {
         return 0;
      }
      
      printk(KERN_INFO "\nTEST3 add = %d\n", add);
   } 
   return 0;
}

struct file_operations scull_fops = {
    .owner          = THIS_MODULE,
    .unlocked_ioctl = scull_ioctl,
    .read           = scull_read,
    .write          = scull_write
};

int elvees_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	add_uevent_var(env, "DEVMODE=%#o", 0666);
	return 0;
}

int queue_init(void) 
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

void queue_cleanup(void) 
{
    struct scull_qset *next, *dptr;
    int qset = scull_device.qset;   /* "dev" is not-null */
    int i;    
    for (dptr = scull_device.data; dptr; dptr = next) { /* all the list items */
        if (dptr->data) {
            for (i = 0; i < qset; i++)
                kfree(dptr->data[i]);
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

MODULE_LICENSE("GPL"); 
module_init(queue_init);
module_exit(queue_cleanup);
