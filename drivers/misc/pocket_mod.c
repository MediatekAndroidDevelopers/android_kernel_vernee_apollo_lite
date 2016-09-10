/*
 * drivers/misc/pocket_mod.c
 *
 * Copyright (C) 2015, Levin Calado <levincalado@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/workqueue.h>
#include <linux/input.h>
#include <linux/hrtimer.h>
#include <asm-generic/cputime.h>
#include <linux/pocket_mod.h>

extern bool display_off;

unsigned pocket_mod_switch = 1;

int device_is_pocketed(void) {

	if (!(pocket_mod_switch))
		return 0;

	if (display_off) {
                return !ap3xx6_pocket_detection_check();
	}

	return 0;
}

static ssize_t pocket_mod_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%u\n", pocket_mod_switch);
}

static ssize_t pocket_mod_set(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	unsigned int val = 0;

	sscanf(buf, "%u\n", &val);

	if ( ( val == 0 ) || ( val == 1 ) )
		pocket_mod_switch = val;

	return size;
}

static DEVICE_ATTR(pocket_mod_enable, (S_IWUSR|S_IRUGO),
		pocket_mod_show, pocket_mod_set);

static struct attribute *pocket_mod_attributes[] =
{
	&dev_attr_pocket_mod_enable.attr,
	NULL
};

static struct attribute_group pocket_mod_group =
{
	.attrs  = pocket_mod_attributes,
};

#define POCKET_MOD_DECLARED
#ifdef POCKET_MOD_DECLARED
extern struct kobject *pocket_mod_kobj;
#else
struct kobject *pocket_mod_kobj;
EXPORT_SYMBOL_GPL(pocket_mod_kobj);
#endif

static int pocket_mod_init_sysfs(void) {

	int rc = 0;

	struct kobject *pocket_mod_kobj;
	pocket_mod_kobj = kobject_create_and_add("pocket_mod", NULL);

	dev_attr_pocket_mod_enable.attr.name = "enable";

	rc = sysfs_create_group(pocket_mod_kobj,
			&pocket_mod_group);

	if (unlikely(rc < 0))
		pr_err("pocket_mod: sysfs_create_group failed: %d\n", rc);

	return rc;

}

module_init(pocket_mod_init_sysfs);
