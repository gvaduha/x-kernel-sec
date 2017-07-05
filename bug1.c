
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>

void (*my_funptr)(void);

ssize_t bug1_write(struct file *file, const char *buf, size_t len, loff_t *shi)
{
	my_funptr();
	return -1;
}

int init_module(void)
{
	static struct file_operations fops = { .owner = THIS_MODULE, .write = bug1_write };
	
	printk(KERN_INFO "Bug1 loaded\n");
	
	proc_create("bug1", 0666, 0, &fops);

	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Bug1 unloaded\n");
}
