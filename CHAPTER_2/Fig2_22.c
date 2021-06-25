#include <linux/init.h>

#include <linux/kernel.h>

#include <linux/module.h>

#include <linux/procfs.h>

#include <asm/uaccess.h>

#define BUFFER_SIZE 128
#define PROC_NAME "hello"
ssizet proc_read(struct file * file, char_user * usrbuf,
  sizet count, lofft * pos);
static struct file_operations proc_ops = {
  .owner = THIS_MODULE,
  .read = proc_read,
};
/* This function is called when the module is loaded. */
int proc_init(void) {
  /* creates the /proc/hello entry */
  proc_create(PROC_NAME, 0666, NULL, & proc_ops);
  return 0;
}
/* This function is called when the module is removed. */
void proc_exit(void) {
  /* removes the /proc/hello entry */
  remove_proc_entry(PROC_NAME, NULL);
}
