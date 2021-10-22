/**
 * \addtogroup Drivers
 * \{
 * \addtogroup HLSSDriver
 * \{
 */

#ifndef _HSS_CFG_H__
#define _HSS_CFG_H__

#define HLSS_DEV_ERROR_DETECT        STD_OFF

#define HLSS_BCU_DRIVER_NUM          10U
#define HLSS_SINGLE_BMU_DRIVER_NUM   2U
#define HLSS_BMU_DRIVER_NUM         (HLSS_SINGLE_BMU_DRIVER_NUM * BCU_SLAVE_NUM_MAX)

#define HLSS_BCU_HSS1                0U
#define HLSS_BCU_HSS2                1U
#define HLSS_BCU_HSS3                2U
#define HLSS_BCU_HSS4                3U
#define HLSS_BCU_HSS5                4U
#define HLSS_BCU_HSS6                5U
#define HLSS_BCU_HSS7                6U
#define HLSS_BCU_BMU_ENABLE          7U
#define HLSS_BCU_LSS1                8U
#define HLSS_BCU_LSS2                9U

#define HLSS_BMU_HLSS_0(bmu)         (HLSS_BCU_DRIVER_NUM + (bmu * HLSS_SINGLE_BMU_DRIVER_NUM))
#define HLSS_BMU_HLSS_1(bmu)         (HLSS_BCU_DRIVER_NUM + (bmu * HLSS_SINGLE_BMU_DRIVER_NUM) + 1U)

#define HLSS_DRIVER_NUM              (HLSS_BCU_DRIVER_NUM + HLSS_BMU_DRIVER_NUM)

#define HLSS_CHANNEL_NONE                    0xFFU


#define HLSS_VOL_DIAG_ERROR_TIMES        4U
#define HLSS_CUR_DIAG_ERROR_TIMES        20U

#endif
/**
 * \}
 * \}
 */
