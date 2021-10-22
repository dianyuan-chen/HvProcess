/**
 * \addtogroup Drivers
 * \{
 * \addtogroup HLSSDriver
 * \{
 */

#ifndef _HSS_CFG_H__
#define _HSS_CFG_H__

#include "App_Cfg.h"

#define HLSS_DEV_ERROR_DETECT        STD_ON

#define HLSS_BCU_DRIVER_NUM          10
#define HLSS_SINGLE_BMU_DRIVER_NUM   2
#define HLSS_BMU_DRIVER_NUM         (HLSS_SINGLE_BMU_DRIVER_NUM * BCU_SLAVE_NUM_MAX)

#define HLSS_BCU_HSS1                0
#define HLSS_BCU_HSS2                1
#define HLSS_BCU_HSS3                2
#define HLSS_BCU_HSS4                3
#define HLSS_BCU_HSS5                4
#define HLSS_BCU_HSS6                5
#define HLSS_BCU_HSS7                6
#define HLSS_BCU_BMU_ENABLE          7
#define HLSS_BCU_LSS1                9
#define HLSS_BCU_LSS2                10

#define HLSS_BMU_HLSS_0(bmu)         (HLSS_BCU_DRIVER_NUM + (bmu * HLSS_SINGLE_BMU_DRIVER_NUM))
#define HLSS_BMU_HLSS_1(bmu)         (HLSS_BCU_DRIVER_NUM + (bmu * HLSS_SINGLE_BMU_DRIVER_NUM) + 1)

#define HLSS_DRIVER_NUM              (HLSS_BCU_DRIVER_NUM + HLSS_BMU_DRIVER_NUM)

#define HLSS_CHANNEL_NONE                    0xFF

#endif
/**
 * \}
 * \}
 */
