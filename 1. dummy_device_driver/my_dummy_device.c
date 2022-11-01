#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Daler Yuldashev");
MODULE_DESCRIPTION("Simple character device driver.");
MODULE_VERSION("0.01");

#define DEVICE_NAME "my_dummy_device"

/* Prototypes for device functions */
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static int major_num;


/* This structure points to all of the device functions */
static struct file_operations file_ops = {
    .owner = THIS_MODULE,
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release};


/* When a process reads from our device, this gets called. */
static ssize_t device_read(struct file *flip, char *buffer, size_t len, loff_t *offset)
{
    printk(KERN_ALERT "READ operation is not supported.\n");
    return -EINVAL;
}

/* Called when a process tries to write to our device */
static ssize_t device_write(struct file *flip, const char *buffer, size_t len, loff_t *offset)
{
    printk(KERN_ALERT "WRITE is not supported.\n");
    return -EINVAL;
}

/* Called when a process opens our device */
static int device_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Device is opened.\n");
    return 0;
}

/* Called when a process closes our device */
static int device_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Device is released.\n");

    return 0;
}

static int __init my_module_init(void)
{
    
    major_num = register_chrdev(0, DEVICE_NAME, &file_ops);
    if (major_num < 0)
    {
        printk(KERN_ALERT "Could not register device: %d\n", major_num);
        return major_num;
    }
    else
    {
        printk(KERN_INFO "Device is registered, major number %d\n", major_num);
        return 0;
    }
}

static void __exit my_module_exit(void)
{
    unregister_chrdev(major_num, DEVICE_NAME);
    printk(KERN_INFO "Unregister the character device\n");
}
/* Register module functions */
module_init(my_module_init);
module_exit(my_module_exit);
