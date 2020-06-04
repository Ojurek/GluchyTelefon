#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#include "jajko.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RS");
MODULE_DESCRIPTION("Linux Kernel Module over chrdev.");
MODULE_VERSION("1.0");

static int majorNumber;
static char message[BUFFER_SIZE] = {0};
static size_t message_len;
static struct class *jajkoCharClass = NULL;
static struct device *jajkoCharDevice = NULL;

static struct file_operations fops = {
    .read = dev_read,
    .write = dev_write,
};

static int __init jajko_init(void)
{
    printk(KERN_INFO "JAJKO: Initializing JAJKO LKM!\n");

    // Try to dynamically allocate a major number for the device
    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    if (majorNumber < 0)
    {
        printk(KERN_ALERT "JAJKO: Failed to register a major number\n");
        return majorNumber;
    }
    printk(KERN_INFO "JAJKO: Registered correctly with major number %d\n", majorNumber);

    // Register the device class
    jajkoCharClass = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(jajkoCharClass))
    {
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "JAJKO: Failed to register device class\n");
        return PTR_ERR(jajkoCharClass);
    }
    printk(KERN_INFO "JAJKO: device class registered correctly\n");

    // Register the device driver
    jajkoCharDevice = device_create(jajkoCharClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    if (IS_ERR(jajkoCharDevice))
    {
        class_destroy(jajkoCharClass);
        unregister_chrdev(majorNumber, DEVICE_NAME);
        printk(KERN_ALERT "JAJKO: Failed to create the device\n");
        return PTR_ERR(jajkoCharDevice);
    }
    printk(KERN_INFO "JAJKO: device class created correctly\n");

    return 0;
}

static void __exit jajko_exit(void)
{
    device_destroy(jajkoCharClass, MKDEV(majorNumber, 0));
    class_unregister(jajkoCharClass);
    class_destroy(jajkoCharClass);
    unregister_chrdev(majorNumber, DEVICE_NAME);
    printk(KERN_INFO "JAJKO: Shutting down JAJKO LKM!\n");
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
	if (message_len<len){
		return 0;
	}
	copy_to_user(buffer, message, len);
	message_len-=len;
	return len;
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset)
{
	if (len>BUFFER_SIZE){
		return 0;
	}
	copy_from_user(message, buffer, len);
	message_len=len;	
	return len;
}

module_init(jajko_init);
module_exit(jajko_exit);
