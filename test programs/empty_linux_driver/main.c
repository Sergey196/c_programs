
#include <linux/init.h>
#include <linux/module.h>
    
static int init(void)
{
    return  0;
}
    
static void exit(void)
{
    return;
}
    
module_init(init);
module_exit(exit); It was originally published on https://www.apriorit.com/ 
