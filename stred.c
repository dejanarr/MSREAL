#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/string.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#define BUFF_SIZE 20

MODULE_LICENSE("Dual BSD/GPL");

dev_t my_dev_id;
static struct class *my_class;
static struct device *my_device;
static struct cdev *my_cdev;

int stred[BUFF_SIZE];
int pos = 0;
int endRead = 0;

int stred_open(struct inode *pinode, struct file *pfile);
int stred_close(struct inode *pinode, struct file *pfile);
ssize_t stred_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset);
ssize_t stred_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset);

struct file_operations my_fops =
{
	.owner = THIS_MODULE,
	.open = stred_open,
	.read = stred_read,
	.write = stred_write,
	.release = stred_close,
};


int stred_open(struct inode *pinode, struct file *pfile) 
{
		printk(KERN_INFO "Succesfully opened file\n");
		return 0;
}

int stred_close(struct inode *pinode, struct file *pfile) 
{
		printk(KERN_INFO "Succesfully closed file\n");
		return 0;
}

ssize_t stred_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset) 
{
	char buff[120];
	int ret;
	long int len;
	
	if (endRead) {
		endRead = 0;
		printk(KERN_INFO "Succesfully read from file\n");
		return 0;
	}
	
	len = scnprintf(buff, BUFF_SIZE, %s\n", stred);
	ret = copy_from_user(buff, buffer, len);
	
	if (ret) {
		return -EFAULT;
		endRead = 1;
	}
	
	return len;
}


ssize_t stred_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset) 
{
	char buff[120];
	int funkcija[8];
	int str1[BUFF_SIZE];
	int ret;
	int len;

	ret = copy_from_user(buff, buffer, length);
	if(ret)
		return -EFAULT;
	buff[len-1] = '\0';

	ret = sscanf(buff,"%d,%d",&value,&position);

	

	return length;
}

//funkcija string
	if (!strcmp(funkcija, "string")) {
		pos = 0;
		len = strlen(str1);
		
		if (len < 100)
			strncpy(stred, str1, len);
			printk(KERN_INFO "Uneti string je okej!\n");
		else
			printk(KERN_WARNING "Uneti string je predugacak!\n");
		stred[len] = '\0';
	}
	
//funkcija clear
	if (!strcmp(funkcija, "clear")) {
		stred[0] = '\0';
		printk(KERN_INFO "Zavrsena funkcija clear\n");
		
	}	
		
//funkcija shrink
	if (!strcmp(funkcija, "shrink")) {
		int i;
		
		if (stred[len-1] == ' ')
		{
			stred[len-1] = '\0';
		}
		
		if(stred[0] == ' ')
		{
			for(i = 1; i < len; i++) {
				stred[i-1] = stred[i];
			}
		}
		
		printk(KERN_INFO "Funkcija shrink je odradjena!\n");
	}
	
//funkcija append
	if (!strcmp(funckija, "append")) {
		len = strlen(str1);
		if(pos+len >=100) {
			printk(KERN_WARNING "Vec postojeci string sa unetim prevazilazi broj mesta\n");
		}
		else {
			int i;
			for (i=0; i < len; i++)
			{
				stred[pos+i] = str1[i];
			}
			pos+=len;
			stred[pos] = '\0';
		}

		printk(KERN_INFO "Funkcija append je odradjena!\n");

	}
			

/*static int __init stred_init(void)
{
   int ret = 0;
	int i=0;

	//Initialize array
	for (i=0; i<10; i++)
		storage[i] = 0;

   ret = alloc_chrdev_region(&my_dev_id, 0, 1, "stred");
   if (ret){
      printk(KERN_ERR "failed to register char device\n");
      return ret;
   }
   printk(KERN_INFO "char device region allocated\n");

   my_class = class_create(THIS_MODULE, "stred_class");
   if (my_class == NULL){
      printk(KERN_ERR "failed to create class\n");
      goto fail_0;
   }
   printk(KERN_INFO "class created\n");
   
   my_device = device_create(my_class, NULL, my_dev_id, NULL, "stred");
   if (my_device == NULL){
      printk(KERN_ERR "failed to create device\n");
      goto fail_1;
   }
   printk(KERN_INFO "device created\n");

	my_cdev = cdev_alloc();	
	my_cdev->ops = &my_fops;
	my_cdev->owner = THIS_MODULE;
	ret = cdev_add(my_cdev, my_dev_id, 1);
	if (ret)
	{
      printk(KERN_ERR "failed to add cdev\n");
		goto fail_2;
	}
   printk(KERN_INFO "cdev added\n");
   printk(KERN_INFO "Hello world\n");

   return 0;

   fail_2:
      device_destroy(my_class, my_dev_id);
   fail_1:
      class_destroy(my_class);
   fail_0:
      unregister_chrdev_region(my_dev_id, 1);
   return -1;
}

static void __exit stred_exit(void)
{
   cdev_del(my_cdev);
   device_destroy(my_class, my_dev_id);
   class_destroy(my_class);
   unregister_chrdev_region(my_dev_id,1);
   printk(KERN_INFO "Goodbye, cruel world\n");
}


module_init(stred_init);
module_exit(stred_exit);
*/