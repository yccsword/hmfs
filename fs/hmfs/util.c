#include <linux/kallsyms.h>
#include "util.h"
#include "hmfs.h"

pte_t * (*hmfs_get_locked_pte) (struct mm_struct *, unsigned long, 
				spinlock_t **);

/* 
 * FIXME: Any good idea to call the function which is not exported
 * by macro EXPORT_SYMBOL
 */
/**
 * 将函数hmfs_get_locked_pte地址值设为内核函数__get_locked_pte的地址
 * 成功则返回0
 * 否则返回并打印错误信息
 */
int init_util_function(void)
{
	unsigned long sym_addr = 0;

	sym_addr = kallsyms_lookup_name("__get_locked_pte");
	if (!sym_addr)
		goto fail;
	hmfs_get_locked_pte = 
			(pte_t * (*) (struct mm_struct *, unsigned long, spinlock_t **))sym_addr;

	return 0;
fail:
	printk(KERN_INFO"[HMFS]: Fail to get all needed function\n");
	return -EPERM; 
}
