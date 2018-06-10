/*
*	a simple kernel module:hello
*	2017.2.25
*
*/


#include <linux/init.h>
#include <linux/module.h>


static int __init hello_init(void)
{
	printk(KERN_ERR "Hello World enter\n");
	return 0;
}



static void __exit hello_exit(void)
{
	printk(KERN_ERR "Hello World exit\n");
}

module_init(hello_init);
module_exit(hello_exit);


MODULE_LICENSE("GPL");








