/*
myled.c
This is Device driver to handle 4 LEDs for Raspberry Pi.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>

#define COUNT_LED 4

MODULE_AUTHOR("MasakazuTamura");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;

static volatile u32 *gpio_base = NULL;
static int led_port[] = {25, 24, 23, 22};

static int calc = 0;

static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos)
{
	char c;
	if(copy_from_user(&c, buf, sizeof(char))){
		return -EFAULT;
	}

	if(c < 0x30){
		return -1;
	}else if(c < 0x3A){
		//0 to 9
		calc += (int)c - 48;
	}else if(c < 0x41){
		return -1;
	}else if(c < 0x47){
		//A to F
		//10 to 15
		calc += (int)c - 55;
	}else if(c < 0x61){
		return -1;
	}else if(c < 0x67){
		//a to f
		//10 to 15
		calc += (int)c - 97;
	}else{
		return -1;
	}

	calc %= 16;

	if(!(calc & 8)){
		gpio_base[10] = 1 << led_port[0];
	}else{
		gpio_base[7] = 1 << led_port[0];
	}
	if(!(calc & 4)){
		gpio_base[10] = 1 << led_port[1];
	}else{
		gpio_base[7] = 1 << led_port[1];
	}
	if(!(calc & 2)){
		gpio_base[10] = 1 << led_port[2];
	}else{
		gpio_base[7] = 1 << led_port[2];
	}
	if(!(calc & 1)){
		gpio_base[10] = 1 << led_port[3];
	}else{
		gpio_base[7] = 1 << led_port[3];
	}

	//printk(KERN_INFO "led_write is called\n");

	return 1;
}

/*
static ssize_t sushi_read(struct file* filp, char* buf, size_t count, loff_t* pos)
{
	int size = 0;
	char sushi[] = {0xF0, 0x9F, 0x8D, 0xA3, 0x0A};
	if(copy_to_user(buf + size, (const char *)sushi, sizeof(sushi))){
		printk(KERN_INFO "sushi: copy_to_use failed\n");
		return -EFAULT;
	}
	size += sizeof(sushi);

	return size;
}
*/

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.write = led_write
	//.read = sushi_read
};

static int __init init_mod(void)
{
	int retval, i;
	//0x3f200000: base address, 0xA0: region to map
	gpio_base = ioremap_nocache(0x3f200000, 0xA0);

	for(i = 0; i < COUNT_LED; i++){
		const u32 led = led_port[i];
		const u32 index = led / 10;			//GPFSEL2
		const u32 shift = (led % 10) * 3;	//15bit
		const u32 mask = ~(0x7 << shift);	//1111 1111 1111 1100 0111 1111 1111 1111
		gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);	//001: outpit flag
		//1111 1111 1111 1100 1111 1111 1111 1111
	}

	retval = alloc_chrdev_region(&dev, 0, 1, "myled");
	if(retval < 0){
		printk(KERN_ERR "alloc_chrdev_region failed.\n");
		return retval;
	}
	printk(KERN_INFO "%s is loaded. major:%d\n", __FILE__, MAJOR(dev));

	cdev_init(&cdv, &led_fops);
	retval = cdev_add(&cdv, dev, 1);
	if(retval < 0){
		printk(KERN_ERR "cdev_add failed. major:%d, minor:%d", MAJOR(dev), MINOR(dev));
		return retval;
	}

	cls = class_create(THIS_MODULE, "myled");
	if(IS_ERR(cls)){
		printk(KERN_ERR "class_create failed.");
		return PTR_ERR(cls);
	}
	device_create(cls, NULL, dev, NULL, "myled%d", MINOR(dev));

	return 0;
}

static void __exit cleanup_mod(void)
{
	cdev_del(&cdv);
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "%s is unloaded. major:%d\n", __FILE__, MAJOR(dev));
}

module_init(init_mod);
module_exit(cleanup_mod);
