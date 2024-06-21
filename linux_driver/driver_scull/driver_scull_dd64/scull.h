#ifndef SCULL_H
#define SCULL_H

#include <linux/cdev.h>
#include <linux/fs.h>    

struct scull_qset {
	void **data;
	struct scull_qset *next;
};

struct scull_dev {
	struct scull_qset *data;  /* Pointer to first quantum set */
	int quantum;              /* the current quantum size */
	int qset;                 /* the current array size */
	unsigned long size;       /* amount of data stored here */
	struct semaphore sem;     /* mutual exclusion semaphore     */
	struct cdev cdev;	  /* Char device structure		*/
};

struct index_info
{
   int index;
};

void scull_init(void);
void scull_remove(void);
void create_new_scull(int index);

#endif
