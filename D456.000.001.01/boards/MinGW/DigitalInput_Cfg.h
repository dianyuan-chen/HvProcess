#ifndef DIGITALINPUT_CFG_H
#define DIGITALINPUT_CFG_H


#define DIGITALINPUT_DEV_ERROR_DETECT           STD_ON

/**
 * \brief 数字输入类型
 */
#define DIGITALINPUT_TYPE_LEVEL                 0
#define DIGITALINPUT_TYPE_SWITCH                1

/**
 * \brief 数字输入通道
 */
#define DIGITALINPUT_BCU_SW_NUM                 2
#define DIGITALINPUT_BCU_DIN_NUM                2

#define DIGITALINPUT_SINGLE_BMU_SW_NUM          0
#define DIGITALINPUT_BMU_SW_NUM                 (DIGITALINPUT_SINGLE_BMU_SW_NUM * BCU_SLAVE_NUM_MAX)

#define DIGITALINPUT_SINGLE_BMU_DIN_NUM         1
#define DIGITALINPUT_BMU_DIN_NUM                (DIGITALINPUT_SINGLE_BMU_DIN_NUM * BCU_SLAVE_NUM_MAX)


#define DIGITALINPUT_BCU_DIN1                   0
#define DIGITALINPUT_BCU_DIN2                   1

#define DIGITALINPUT_BCU_SW1                    0
#define DIGITALINPUT_BCU_SW2                    1

#if DIGITALINPUT_SINGLE_BMU_DIN_NUM != 1
#define DIGITALINPUT_BMU_DIN_1(bmu)             ((DIGITALINPUT_BCU_DIN_NUM + (bmu * DIGITALINPUT_SINGLE_BMU_DIN_NUM)))
#else
#define DIGITALINPUT_BMU_DIN_1(bmu)             (DIGITALINPUT_BCU_DIN_NUM + (bmu))
#endif

#if DIGITALINPUT_SINGLE_BMU_SW_NUM != 1
#define DIGITALINPUT_BMU_SW_1(bmu)              ((DIGITALINPUT_BCU_SW_NUM + (bmu * DIGITALINPUT_SINGLE_BMU_SW_NUM)))
#else
#define DIGITALINPUT_BMU_SW_1(bmu)              ((DIGITALINPUT_BCU_SW_NUM + bmu))
#endif

#define DIGITALINPUT_SW_NUM                     (DIGITALINPUT_BCU_SW_NUM + DIGITALINPUT_BMU_SW_NUM)
#define DIGITALINPUT_DIN_NUM                    (DIGITALINPUT_BCU_DIN_NUM + DIGITALINPUT_BMU_DIN_NUM)



#endif