#ifndef _K_NODEWATCHDOG_H_
#define _K_NODEWATCHDOG_H_

//#define VSCODE_DEFINES

#ifdef VSCODE_DEFINES
#if defined(__GNUC__)
typedef __kernel_loff_t		loff_t;
#endif

/*
 * The following typedefs are also protected by individual ifdefs for
 * historical reasons:
 */
#ifndef _SIZE_T
#define _SIZE_T
typedef __kernel_size_t		size_t;
#endif

#ifndef _SSIZE_T
#define _SSIZE_T
typedef __kernel_ssize_t	ssize_t;
#endif

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
typedef __kernel_ptrdiff_t	ptrdiff_t;
#endif

#ifndef _CLOCK_T
#define _CLOCK_T
typedef __kernel_clock_t	clock_t;
#endif

#ifndef _CADDR_T
#define _CADDR_T
typedef __kernel_caddr_t	caddr_t;
#endif

/* bsd */
typedef unsigned char		u_char;
typedef unsigned short		u_short;
typedef unsigned int		u_int;
typedef unsigned long		u_long;

/* sysv */
typedef unsigned char		unchar;
typedef unsigned short		ushort;
typedef unsigned int		uint;
typedef unsigned long		ulong;

#ifndef __BIT_TYPES_DEFINED__
#define __BIT_TYPES_DEFINED__

typedef u8			u_int8_t;
typedef s8			int8_t;
typedef u16			u_int16_t;
typedef s16			int16_t;
typedef u32			u_int32_t;
typedef s32			int32_t;

#endif /* !(__BIT_TYPES_DEFINED__) */

typedef u8			uint8_t;
typedef u16			uint16_t;
typedef u32			uint32_t;

#if defined(__GNUC__)
typedef u64			uint64_t;
typedef u64			u_int64_t;
typedef s64			int64_t;
#endif

struct file_operations {
	struct module *owner;
	loff_t (*llseek) (struct file *, loff_t, int);
	ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
	ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
	ssize_t (*read_iter) (struct kiocb *, struct iov_iter *);
	ssize_t (*write_iter) (struct kiocb *, struct iov_iter *);
	int (*iopoll)(struct kiocb *kiocb, bool spin);
	int (*iterate) (struct file *, struct dir_context *);
	int (*iterate_shared) (struct file *, struct dir_context *);
	__poll_t (*poll) (struct file *, struct poll_table_struct *);
	long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
	long (*compat_ioctl) (struct file *, unsigned int, unsigned long);
	int (*mmap) (struct file *, struct vm_area_struct *);
	unsigned long mmap_supported_flags;
	int (*open) (struct inode *, struct file *);
	int (*flush) (struct file *, fl_owner_t id);
	int (*release) (struct inode *, struct file *);
	int (*fsync) (struct file *, loff_t, loff_t, int datasync);
	int (*fasync) (int, struct file *, int);
	int (*lock) (struct file *, int, struct file_lock *);
	ssize_t (*sendpage) (struct file *, struct page *, int, size_t, loff_t *, int);
	unsigned long (*get_unmapped_area)(struct file *, unsigned long, unsigned long, unsigned long, unsigned long);
	int (*check_flags)(int);
	int (*flock) (struct file *, int, struct file_lock *);
	ssize_t (*splice_write)(struct pipe_inode_info *, struct file *, loff_t *, size_t, unsigned int);
	ssize_t (*splice_read)(struct file *, loff_t *, struct pipe_inode_info *, size_t, unsigned int);
	int (*setlease)(struct file *, long, struct file_lock **, void **);
	long (*fallocate)(struct file *file, int mode, loff_t offset,
			  loff_t len);
	void (*show_fdinfo)(struct seq_file *m, struct file *f);
#ifndef CONFIG_MMU
	unsigned (*mmap_capabilities)(struct file *);
#endif
	ssize_t (*copy_file_range)(struct file *, loff_t, struct file *,
			loff_t, size_t, unsigned int);
	loff_t (*remap_file_range)(struct file *file_in, loff_t pos_in,
				   struct file *file_out, loff_t pos_out,
				   loff_t len, unsigned int remap_flags);
	int (*fadvise)(struct file *, loff_t, loff_t, int);
} __randomize_layout;
#endif

typedef unsigned int opcode_t;
typedef unsigned int procflag_t;

/* general return codes */
#define EXIT_SUCCESS                0
#define EXIT_FAILURE                1

/* number base(s) */
#define BASE_DECIMAL                10
#define BASE_HEXADECIMAL            16


/* God-Mode (SIGNAL_UNKILLABLE) */
#define SIGNAL_UNKILLABLE   		0x00000040              /* SIGNAL_UNKILLABLE */
#define FLAG_DEFAULT	    		0x00000000              /* flag reset to force-clear SIGNAL_UNKILLABLE */


#define TASK_INVALID				0xFFFFFFFF				/* If task_struct == NULL, return UINT_MAX, so we won't confuse the erroneous operation with actual signal flag */ 


/* --- Character Device --- */

/* character device status (semaphore) identifiers */
#define DEV_STATUS_ERROR            2       				/* status == error            */
#define DEV_STATUS_INITIALIZED      1       				/* status == initialized (OK) */
#define DEV_STATUS_UNINITIALIZED    0       				/* status == not initialized  */

/* character device operations */
#define CDEV_UNREGISTER_ONLY        2              			/* used for unregistering chrdev only */
#define CDEV_DESTROY_CLASS_ONLY     1              			/* used to specify if unregisted_device() should only destroy the class itself  */
#define CDEV_DESTROY_DEVICE_ONLY    0              			/* used to specify if unregister_device() should only destroy the chrdev itself */

/* character device constants */
#define DATA_MAX                    96              		/* max size of data copied from user */
#define CDEV_NAME                   "gmdDevuce"     		/* cdev name */
#define CDEV_CLASS_NAME             "gmdev"         		/* cdev class name */

/* init() exit codes */
#define ECDEV                       256            			/* unable to spawn chardev */
#define ESCNR                       257            			/* unable to deploy heavy-duty scanners */

/* godMode cdev com opcodes */
#define GMDEV_ENABLE_GOD			1
#define GMDEV_DISABLE_GOD			0


#endif