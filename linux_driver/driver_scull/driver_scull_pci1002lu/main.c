#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h> 
#include <linux/pci.h>
#include <linux/ioport.h>
#include "scull.h"
#include "def.h"
#include "baseitem.h"

static struct pci_device_id driver_id_table[] = {
        { PCI_DEVICE(VENDOR_ID, PRODUCT_ID) },
        {0,}
};

MODULE_DEVICE_TABLE(pci, driver_id_table);
int currentDev = 0;
uint64_t io_port[MAX_DEVICE];
uint64_t io_port_legnth[MAX_DEVICE];

int driver_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
   int16_t vendor; 
   int16_t device;
   int8_t revision;
   int16_t command_reg;
   //int32_t phys_addr = 0;
   uint64_t resorce_start;
   uint64_t resorce_end;
   uint64_t resorce_len;
   uint64_t resorce_flags;
   
   if(currentDev >= MAX_DEVICE)
   {
      return -ENODEV;
   }
   
   pci_read_config_word( pdev, PCI_VENDOR_ID, &vendor);
   //printk(" PCI_VENDOR_ID=%x\n", vendor);
   pci_read_config_word( pdev, PCI_DEVICE_ID, &device);
   //printk(" PCI_DEVICE_ID=%x\n", device);
   pci_read_config_byte( pdev, PCI_REVISION_ID, &revision);
   //printk(" PCI_REVISION_ID=%d\n", revision);
   pci_read_config_word(pdev, PCI_COMMAND, &command_reg);
   
   if (command_reg | PCI_COMMAND_MEMORY)
   {
   	  //printk( " Device supports memory access\n" );
   }
   else
   {
   	  //printk( " Device doesn't supports memory access!" );
   }
   
   resorce_start = pci_resource_start(pdev, BAR);
   resorce_end = pci_resource_end(pdev, BAR);
   resorce_len = pci_resource_len(pdev, BAR);
   resorce_flags = pci_resource_flags(pdev, BAR);
   //pci_read_config_dword(pdev, PCI_BASE_ADDRESS_3, &phys_addr);
   //printk("TEST DEVICE_COUNT_RESOURCE = %x\n", phys_addr);
   //phys_addr = pdev->resource[BAR].start;
   //printk("TEST flags = %x\n", resorce_flags);
   //printk("TEST = %x\n", IORESOURCE_IO);
   //printk(" PCI_BASE_ADDRESS_0=%x\n", resorce_start);
   
   if(!request_region(resorce_start, resorce_len, DRIVER_DESC)) {
      return -ENODEV; 
   }
   
   io_port[currentDev] = resorce_start;
   io_port_legnth[currentDev] = resorce_len;
   
   //printk(" Device resource 0: start at %x with length %x\n", resorce_start, resorce_len);

   create_new_scull(currentDev);
   currentDev++;
   return 0;
}

/*void driver_remove(struct pci_dev *pdev)
{
   for(int i = 0; i < currentDev; i++)
   {
      release_region(io_port[i], io_port_legnth[i]); 
   }
   scull_remove();
}*/

static struct pci_driver device_func = {
   .name = DRIVER_NAME,
   .id_table = driver_id_table,
   .probe = driver_probe,
   //.remove = driver_remove
};

int queue_init(void) 
{
   scull_init();  
   return pci_register_driver(&device_func);;
}

void queue_cleanup(void) 
{
   for(int i = 0; i < currentDev; i++)
   {
      release_region(io_port[i], io_port_legnth[i]); 
   }
   scull_remove();
   pci_unregister_driver(&device_func);
}

MODULE_LICENSE("GPL"); 
module_init(queue_init);
module_exit(queue_cleanup);
