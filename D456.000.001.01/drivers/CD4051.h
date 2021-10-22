/**
 * \addtogroup Drivers
 * \{
 * \addtogroup CD4051
 * \{
 */
#ifndef CD4051_H
#define CD4051_H

#include "Dio.h"

/**
 * \brief CD4051硬件连接的配置.
 */
typedef struct {
    Dio_ChannelType enable; /**< 使能的硬件DIO */
    Dio_ChannelType a;
    Dio_ChannelType b;
    Dio_ChannelType c;
} CD4051_HWConfigType;

/**
 * \brief CD4051的通道.
 */
typedef enum {
    CD4051_CHANNEL_0 = 0, /**< 通道0 */
    CD4051_CHANNEL_1 = 1, /**< 通道1 */
    CD4051_CHANNEL_2 = 2, /**< 通道2 */
    CD4051_CHANNEL_3 = 3, /**< 通道3 */
    CD4051_CHANNEL_4 = 4, /**< 通道4 */
    CD4051_CHANNEL_5 = 5, /**< 通道5 */
    CD4051_CHANNEL_6 = 6, /**< 通道6 */
    CD4051_CHANNEL_7 = 7, /**< 通道7 */
    CD4051_CHANNEL_NUM = 8,
    CD4051_CHANNEL_NONE = 0xFF, /**< 不选择任何通道, 禁能芯片 */
} CD4051_ChannelType;

/**
 * \brief 设置CD4051的通道.
 *
 * \param[in] cd4051 CD4051的硬件配置.
 * \param[in] ch 要设置的通道.
 */
void CD4051_SetChannel(const CD4051_HWConfigType *cd4051, CD4051_ChannelType ch);

/**
 * \brief 获取当前CD4051设置的通道.
 *
 * \param[in] cd4051 CD4051的硬件配置.
 * \return 通道.
 */
CD4051_ChannelType CD4051_GetChannel(const CD4051_HWConfigType *cd4051);

#endif
/** \} */
/** \} */