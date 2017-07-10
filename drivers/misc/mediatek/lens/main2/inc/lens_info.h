/*
 * Copyright (C) 2015 MediaTek Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef _MAIN_LENS_H

#define _MAIN_LENS_H

#include <linux/ioctl.h>

#define MAX_NUM_OF_LENS 32

#define AF_MAGIC 'A'

/* AFDRV_XXXX be the same as AF_DRVNAME in (*af).c */
#define AFDRV_BU6424AF "BU6424AF"
#define AFDRV_DW9714A "DW9714A"

/* Structures */
typedef struct {
/* current position */
	u32 u4CurrentPosition;
/* macro position */
	u32 u4MacroPosition;
/* Infinity position */
	u32 u4InfPosition;
/* Motor Status */
	bool bIsMotorMoving;
/* Motor Open? */
	bool bIsMotorOpen;
/* Support SR? */
	bool bIsSupportSR;
} stAF_MotorInfo;

/* Structures */
typedef struct {
/* macro position */
	u32 u4MacroPos;
/* Infinity position */
	u32 u4InfPos;
} stAF_MotorCalPos;

/* Structures */
typedef struct {
	u8 uMotorName[32];
} stAF_MotorName;

/* Structures */
typedef struct {
	u32 u4CmdID;
	u32 u4Param;
} stAF_MotorCmd;

/* Structures */
typedef struct {
	u8 uEnable;
	u8 uDrvName[32];
	void (*pAF_SetI2Cclient)(struct i2c_client *pstAF_I2Cclient, spinlock_t *pAF_SpinLock, int *pAF_Opened);
	long (*pAF_Ioctl)(struct file *a_pstFile, unsigned int a_u4Command, unsigned long a_u4Param);
	int (*pAF_Release)(struct inode *a_pstInode, struct file *a_pstFile);
} stAF_DrvList;


/* Control commnad */
/* S means "set through a ptr" */
/* T means "tell by a arg value" */
/* G means "get by a ptr" */
/* Q means "get by return a value" */
/* X means "switch G and S atomically" */
/* H means "switch T and Q atomically" */
#define AFIOC_G_MOTORINFO _IOR(AF_MAGIC, 0, stAF_MotorInfo)

#define AFIOC_T_MOVETO _IOW(AF_MAGIC, 1, u32)

#define AFIOC_T_SETINFPOS _IOW(AF_MAGIC, 2, u32)

#define AFIOC_T_SETMACROPOS _IOW(AF_MAGIC, 3, u32)

#define AFIOC_G_MOTORCALPOS _IOR(AF_MAGIC, 4, stAF_MotorCalPos)

#define AFIOC_S_SETPARA _IOW(AF_MAGIC, 5, stAF_MotorCmd)

#define AFIOC_S_SETDRVNAME _IOW(AF_MAGIC, 10, stAF_MotorName)

#endif
