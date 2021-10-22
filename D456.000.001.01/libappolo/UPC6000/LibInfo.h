/*
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * Generate by template render, DONOT edit it
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */

/**
 * \file AppInfo.h
 * \copyright UDAN Co.,Ltd.
 * \note
 *     本文件(AppInfo.h)由 cmake 使用模板 AppInfo.h.in 文件自动生成
 *     请勿手动编辑本文件,相关修改请移至 AppInfo.h.in 文件内
 *
 * \par 修改历史
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * |:------:|:---------|:------:|:--------:|
 * | 0.1 | 按文档定义的软件标识 | UD0010 | 20170106 |
 */

#ifndef __LIBINFO_H__
#define __LIBINFO_H__

#include "BootInfo.h"


#define FWVERSION_MAJOR                   3
#define FWVERSION_MINOR                   0
#define FWVERSION_REVISION                5
#define FWVERSION_BUILD                   1
#define LIB_INFO_FWVERSION                "3.0.5.1"

/**
 * 以下宏定义由cmake自动生成,不需要手动修改
 */
#define LIB_INFO_SOURCE_COMMIT_ID        "dbd0da289dd8d2d2b312a6fa172dd9530e1ea56d"
#define LIB_INFO_CONFIG_COMMIT_ID        "dbd0da289dd8d2d2b312a6fa172dd9530e1ea56d"
#define LIB_INFO_BUILD_TIME              "20201119174536"

#define LIB_INFO_BUILD_DATE_Y            2020
#define LIB_INFO_BUILD_DATE_M            11
#define LIB_INFO_BUILD_DATE_D            19

#define LIB_INFO_BUILD_TIME_H            17
#define LIB_INFO_BUILD_TIME_M            45
#define LIB_INFO_BUILD_TIME_S            36

#pragma push
#pragma CONST_SEG __GPAGE_SEG APP_INFO
extern const Boot_AppInfoTagType AppInfoTag;
extern boolean AppInfo_IsTestVersion(void);
#pragma pop
#endif
