#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h> 
#include <linux/pci.h>
#include "sull.h"
#include "main.h"

#define VENDOR_ID 0x2001
#define PRODUCT_ID 0x680c
#define DRIVER_DESC   "MCB-03PEM-PCI"

static struct pci_device_id driver_id_table[] = {{ PCI_DEVICE(VENDOR_ID, PRODUCT_ID) },{ 0,}};
MODULE_DEVICE_TABLE(pci, driver_id_table);

struct driver_addr *drv_priv;

static int driver_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	int16_t vendor; 
    int16_t device;
    int8_t revision;
    int16_t command_reg;
    int32_t phys_addr = 0;
    int bar; 
    int err;
    unsigned long mmio_start;
    unsigned long mmio_len;
    
	pci_read_config_word( pdev, PCI_VENDOR_ID, &vendor);
	printk(" PCI_VENDOR_ID=%x\n", vendor);
	pci_read_config_word( pdev, PCI_DEVICE_ID, &device);
	printk(" PCI_DEVICE_ID=%x\n", device);
	pci_read_config_byte( pdev, PCI_REVISION_ID, &revision);
	printk(" PCI_REVISION_ID=%d\n", revision);

	pci_read_config_word(pdev, PCI_COMMAND, &command_reg);

	if (command_reg | PCI_COMMAND_MEMORY)
	{
		printk( " Device supports memory access\n" );
	}
	else
	{
		printk( " Device doesn't supports memory access!" );
	}
	
	pci_read_config_dword(pdev, PCI_BASE_ADDRESS_0, &phys_addr);
	phys_addr = pdev->resource[0].start;
	printk(" PCI_BASE_ADDRESS_0=%x\n", phys_addr);

	bar = pci_select_bars(pdev, IORESOURCE_MEM_64);

	printk(" Device availale MEM BAR are 0x%x\n", bar);

	err = pci_enable_device_mem(pdev);

	if (err)
	{
		printk(" Failed to enable device memory, err: %i\n", err);
		return err;
	}

	err = pci_request_region(pdev, bar, DRIVER_DESC);

	if (err) {
		pci_disable_device(pdev);
		return err;
	}

	mmio_start = pci_resource_start(pdev, 0);
	mmio_len   = pci_resource_len(pdev, 0);

	printk(" Device resource 0: start at 0x%lx with length %lu\n", mmio_start, mmio_len);

	drv_priv = kzalloc(sizeof(struct driver_addr), GFP_KERNEL);

	if (!drv_priv) {
		return -ENOMEM;
	}

	drv_priv->hwmem = ioremap(mmio_start, mmio_len);

	if (!drv_priv->hwmem) {
		return -EIO;
	}
    
    printk(" Device mapped resource 0x%lx to 0x%p\n", mmio_start, drv_priv->hwmem);
	return 0;
}

void driver_remove(struct pci_dev *pdev)
{
    iounmap(drv_priv->hwmem);
    kfree(drv_priv);
}

static struct pci_driver device_func = {
	.name = "elvees_mcb_pe_rb056",
	.id_table = driver_id_table,
	.probe = driver_probe,
 	.remove = driver_remove
};

int queue_init(void) 
{
    scull_init();
    return pci_register_driver(&device_func);;
}

void queue_cleanup(void) 
{
   scull_remove(); 
}

MODULE_LICENSE("GPL"); 
module_init(queue_init);
module_exit(queue_cleanup);
