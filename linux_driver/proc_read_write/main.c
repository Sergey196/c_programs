#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

#define MAX_BUFFER_SIZE 40

struct k_list {
    struct list_head queue_list;
    char *data;
};

static struct k_list *node;
struct list_head *head;
struct list_head test_head;

int temp,ret;
int new_node=1;

char *msg;

ssize_t pop_queue(struct file *filp, char *buf, size_t count, loff_t *offp ) 
{
    if(list_empty(head)) {
        return 0;
    }

    if(new_node == 1) {
        node=list_first_entry(head, struct k_list, queue_list);
        msg=node->data;
        ret=strlen(msg);
        new_node=0;
    }
    if(count>ret) {
        count=ret;
    }

    ret = ret-count;

    temp=copy_to_user(buf,msg, count);
    printk(KERN_INFO "\n data = %s \n" ,msg);

    if(count==0) {
        list_del(&node->queue_list);
        new_node=1;
    }
    return count;
}

ssize_t push_queue(struct file *filp,const char *buf,size_t count, loff_t *offp)
{
    msg = kmalloc(MAX_BUFFER_SIZE * sizeof(char), GFP_KERNEL);
    copy_from_user(msg, buf, count);

    node = kmalloc(sizeof(struct k_list *), GFP_KERNEL);
    node->data = msg;
    list_add_tail(&node->queue_list, head);
    return count;
}

const struct proc_ops proc_file_fops = {
    .proc_read = pop_queue,
    .proc_write = push_queue,
};

void create_new_proc_entry(void) 
{
    proc_create("scull", 666, NULL, &proc_file_fops);
}


int queue_init(void) {
    create_new_proc_entry();
    head=kmalloc(sizeof(struct list_head *), GFP_KERNEL);
    INIT_LIST_HEAD(head);
    return 0;
}

void queue_cleanup(void) {
    remove_proc_entry("scull", NULL);
}

MODULE_LICENSE("GPL"); 
module_init(queue_init);
module_exit(queue_cleanup);
