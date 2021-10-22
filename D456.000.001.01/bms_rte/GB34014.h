#ifndef GB34014_H___
#define GB34014_H___

#if defined(__GNUC__)
#include <stdint.h>
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;
typedef uint8_t Std_ReturnType;
#else
#include "Std_Types.h"
#endif


#define GB34014_DATA_MAGIC 0x789ABC34U
#define GB34014_MAX_SN_LENGTH  27U

typedef struct {
    uint8 year;
    uint8 month;
    uint8 day;
} GB34014_ProductDateType;

/**
 * \brief 获取编号中的生成日期
 * \retval E_OK 解析正确
 * \retval ！=E_OK 解析不正确
 */
Std_ReturnType GB34014_GetProductDate(GB34014_ProductDateType *date, const char *sn);


/**
 * \brief 获取编号中的生成日期
 * \retval !=NULL 生产流水号
 * \retval NULL 解析不正确
 */
const char *GB34014_GetProductSN(const char *sn);

/**
 * \brief 获取电池包的数量
 * \retval 0 没有配置GB34014数据
 * \retval >0 电池包数量
 */
uint16 GB34014_GetPackNum(const void *dat);

/**
 * \brief 获取某一个电池包的编码
 *
 * \param packIndex 需要读取的电池包索引，第一个电池包该值传入0
 * \param sn 用于保存读取到的编码，必须留有26字节的存储空间
 *
 * \retval !=NULL 读取成功, 指向编码字符串
 * \retval NULL 索引超出范围导致读取失败
 */
const char *GB34014_GetPackSN(const void *dat, uint16 packIndex);

/**
 * \brief 获取某个电池包中模组的数量
 * \param packIndex 需要读取的电池包索引，第一个电池包该值传入0
 *
 * \retval 0 索引超出范围
 * \retval >0 模组数量
 */
uint16 GB34014_GetModuleNum(const void *dat, uint16 packIndex);

/**
 * \brief 获取某一个模组的编码
 *
 * \param packIndex 需要读取的电池包索引，第一个电池包该值传入0
 * \param moduleIndex 需要读取的模组索引，第一个模组该值传入0
 * \param sn 用于保存读取到的编码，必须留有26字节的存储空间
 *
 * \retval !=NULL 读取成功, 指向编码字符串
 * \retval NULL 索引超出范围导致读取失败
 */
const char *GB34014_GetModuleSN(const void *dat, uint16 packIndex, uint16 moduleIndex);

/**
 * \brief 获取某个模组中单体的数量
 * \param packIndex 需要读取的电池包索引，第一个电池包该值传入0
 * \param moduleIndex 需要读取的模组索引，第一个模组该值传入0
 *
 * \retval 0 索引超出范围
 * \retval >0 单体数量
 */
uint16 GB34014_GetCellNum(const void *dat, uint16 packIndex, uint16 moduleIndex);

/**
 * \brief 获取某一个单体的编码
 *
 * \param packIndex 需要读取的电池包索引，第一个电池包该值传入0
 * \param moduleIndex 需要读取的模组索引，第一个模组该值传入0
 * \param cellIndex 需要读取的单体索引，第一个单体该值传入0
 * \param sn 用于保存读取到的编码，必须留有26字节的存储空间
 *
 * \retval !=NULL 读取成功, 指向编码字符串
 * \retval NULL 索引超出范围导致读取失败
 */
const char *GB34014_GetCellSN(const void *dat, uint16 packIndex, uint16 moduleIndex, uint16 cellIndex);

/**
 * \brief 获取整个系统模组的总数量
 *
 * \retval 0 没有配置GB34014数据或模组数据
 * \retval >0 模组数量
 */
uint16 GB34014_GetTotoalModuleNum(const void *dat);


/**
 * \brief 获取整个系统单体的数量
 *
 * \retval 0 没有配置GB34014数据、模组数据或单体数据
 * \retval >0 单体数量
 */
uint16 GB34014_GetTotoalCellNum(const void *dat);


#endif