/**
 * \addtogroup Drivers
 * \{
 * \addtogroup HEF4052
 * \{
 */
#ifndef HEF4052_H
#define HEF4052_H

#include "Dio.h"

/**
 * \brief HEF4052硬件连接的配置.
 */
typedef struct {
    Dio_ChannelType enable;
    Dio_ChannelType s1;
    Dio_ChannelType s2;
} HEF4052_HWConfigType;

/**
 * \brief HEF4052的通道.
 */
typedef enum {
    HEF4052_CHANNEL_0 = 0, /**< 选择通道1 */
    HEF4052_CHANNEL_1 = 1, /**< 选择通道2 */
    HEF4052_CHANNEL_2 = 2, /**< 选择通道3 */
    HEF4052_CHANNEL_3 = 3, /**< 选择通道4 */
    HEF4052_CHANNEL_NONE = 0xFFu, /**< 不选择任何通道, 禁能芯片 */
} HEF4052_ChannelType;

/**
 * \brief 设置HEF4052的通道.
 *
 * \param[in] hef4052 HEF4052的硬件配置.
 * \param[in] ch 要设置的通道.
 */
void HEF4052_SetChannel(const HEF4052_HWConfigType *hef4052, HEF4052_ChannelType ch);

/**
 * \brief 获取当前HEF4052设置的通道.
 *
 * \param[in] hef4052 HEF4052的硬件配置.
 * \return 通道.
 */
HEF4052_ChannelType HEF4052_GetChannel(const HEF4052_HWConfigType *hef4052);

#endif
/** \} */
/** \} */