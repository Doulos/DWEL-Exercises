/*
 * "Hello, world!" minimal kernel module - /dev version
 * This exercise is based on code written by: 
 * Valerie Henson <val@nmt.edu>
 *
 * Fill in the blanks to create a Linux kernel module
 *
 * Basic kernel module which creates an entry in /dev/.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
/*????*/

/*
 * hello_read is the function called when a process calls read() on
 * /dev/hello.  It writes "Hello, world!" to the buffer passed in the
 * read() call.
 */

static ssize_t hello_read(struct file * file, char * buf, 
			  size_t count, loff_t *ppos)
{
	char *hello_str = "Hello, world!\n";
	int len = strlen(hello_str); /* Don't include the null byte. */
	/*
	 * We only support reading the whole string at once.
	 */
	if (count < len)
		return -EINVAL;
	/*
	 * If file position is non-zero, then assume the string has
	 * been read and indicate there is no more data to be read.
	 */
	if (*ppos != 0)
		return 0;
	/*
	 * Besides copying the string to the user provided buffer,
	 * this function also checks that the user has permission to
	 * write to the buffer, that it is mapped, etc.
	 */
	if (copy_to_user(buf, hello_str, len))
		return -EINVAL;
	/*
	 * Tell the user how much data we wrote.
	 */
	*ppos = len;

	return len;
}

/*
 * The only file operation we care about is read.
 */

static const struct file_operations hello_fops = {
	.owner		= THIS_MODULE,
	.read		= hello_read,
};

static struct miscdevice hello_dev = {
	/*
	 * We don't care what minor number we end up with, so tell the
	 * kernel to just pick one.
	 */
	MISC_DYNAMIC_MINOR,
	/*
	 * Name ourselves /dev/hello.
	 */
	"hello",
	/*
	 * What functions to call when a program performs file
	 * operations on the device.
	 */
	&hello_fops
};

/*
 * Code for Module init function
 * static int %keyword function call(void)%
 */
{
	int ret;

	/*
	 * Create the "hello" device in the /sys/class/misc directory.
	 * Udev will automatically create the /dev/hello device using
	 * the default rules.
	 */
	ret = misc_register(&hello_dev);
	if (ret)
		printk(KERN_ERR
		       "Unable to register \"Hello, world!\" misc device\n");
	else
		printk(KERN_INFO "%s\n", __func__);

	return ret;
}
/* End of init function */


/*
 * Code for Module exit function
 * static void %keyword function call(void)%
 */
{
	printk(KERN_INFO "Bye Bye\n");
	misc_deregister(&hello_dev);
}
/* End of exit function */


/* ???? */
/* ???? */

