/**
 * @file
 * @brief Tmp file system
 *
 * @date 12.11.12
 * @author Andrey Gazukin
 */

#include <errno.h>

#include <fs/fs_driver.h>
#include <fs/inode.h>
#include <fs/inode_operation.h>
#include <fs/super_block.h>

#include "ramfs.h"

static int ramfs_create(struct inode *i_new, struct inode *i_dir, int mode) {
	struct ramfs_file_info *fi;

	if (S_ISREG(i_new->i_mode)) {
		fi = ramfs_file_alloc(i_new);
		if (NULL == fi) {
			return -ENOMEM;
		}
		fi->mode = i_new->i_mode;
	}

	return 0;
}

struct inode_operations ramfs_iops;
struct super_block_operations { };
struct super_block_operations ramfs_sbops;
static int ramfs_mount(struct super_block *sb, struct inode *dest) {
	return 0;
}

static struct fsop_desc ramfs_fsop = {
	.mount = ramfs_mount,
	.create_node = ramfs_create,
	.delete_node = ramfs_delete,
	.truncate = ramfs_truncate,
};

static struct fs_driver ramfs_driver = {
	.name    = "ramfs",
	.format = ramfs_format,
	.fill_sb = ramfs_fill_sb,
	.file_op = &ramfs_fops,
	.fsop    = &ramfs_fsop,
};

DECLARE_FILE_SYSTEM_DRIVER(ramfs_driver);
