#ifndef _JAJKO_H_
#define _JAJKO_H_

#define DEVICE_NAME "jajko"
#define CLASS_NAME "jajko"
#define BUFFER_SIZE 32

static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

#endif