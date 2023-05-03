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

#define MAX_BUFFER_SIZE 40

struct k_list 
{
    struct list_head queue_list;
    char *data;
    size_t size;
};

struct k_list *node;
struct list_head *head;

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
static struct scull_dev scull_device; 

ssize_t scull_read(struct file *filp, char *buf, size_t count, loff_t *offp) 
{
    printk(KERN_INFO "\nTEST1 = %d\n", (int)count);
    mutex_lock_interruptible(&scull_device.mutex);
    if(list_empty(head)) {
        mutex_unlock(&scull_device.mutex);
        return 0;
    }
    
    node = list_first_entry(head, struct k_list, queue_list);
    copy_to_user(buf, node->data, node->size);
    list_del(&node->queue_list);
    kfree(node->data);
    kfree(node);
    mutex_unlock(&scull_device.mutex);
    return node->size;
}

ssize_t scull_write(struct file *filp,const char *buf, size_t count, loff_t *offp)
{
    printk(KERN_INFO "\nTEST2 = %d\n", (int)count);
    mutex_lock_interruptible(&scull_device.mutex);
    node = kmalloc(sizeof(struct k_list *), GFP_KERNEL);
    node->data = kmalloc(MAX_BUFFER_SIZE * sizeof(char), GFP_KERNEL);
    node->size = count;
    copy_from_user(node->data, buf, count);
    list_add_tail(&node->queue_list, head);
    mutex_unlock(&scull_device.mutex);
    return count;
}

struct file_operations scull_fops = {
    .owner =    THIS_MODULE,
    .read =     scull_read,
    .write =    scull_write
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
    struct class *dev_class;
    
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
    cdev_add(&scull_device.cdev, dev_scull, 1);
    if (result) {
        printk(KERN_NOTICE "Error adding scull\n");
    } else {
        printk(KERN_INFO "scull add success\n");
    }
    mutex_init(&scull_device.mutex);
    device_create(dev_class, NULL, dev_scull, NULL, "scull");
    
    head = kmalloc(sizeof(struct list_head *), GFP_KERNEL);
    INIT_LIST_HEAD(head);
    
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
    
    cdev_del(&scull_device.cdev);
}

MODULE_LICENSE("GPL"); 
module_init(queue_init);
module_exit(queue_cleanup);
