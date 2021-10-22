#ifndef BRIDGE_INSU_H
#define BRIDGE_INSU_H

#include "Std_Types.h"
#include "Dio.h"
#include "BridgeInsu_Cfg.h"
#include "Async_Looper.h"
#include "Adc.h"

#define BRIDGEINSU_INVALID_RESISTANCE       0xFFFFU
#define BRIDGEINSU_RESISTANCE_MAX           0xFFFEU

#define BRIDGEINSU_MODE_OFF                 0U
#define BRIDGEINSU_MODE_WITH_MOS            1U
#define BRIDGEINSU_MODE_WITHOUT_MOS         2U



typedef struct {
    uint32 detectInterval;
    uint8 maxWaitSampleTimes;
    Dio_ChannelType posSwitchCtrl;
    Dio_ChannelType negSwitchCtrl;
    boolean isDoHighTurnOnSwitch;
    uint16 totalResistor;
    float (*PGAControl)(uint8 *withMos);
    uint16 diffAbs;
    uint16 diffPercentFactorToTotal;
} BridgeInsu_ConfigType;


#ifndef BRIDGEINSU_LCFG_H__
#define BRIDGEINSU_LCFG_H__

#include "BridgeInsu.h"
extern const BridgeInsu_ConfigType BridgeInsuConfigData;

extern const BridgeInsu_ConfigType BridgeInsuConfigData_A650 ;
extern const BridgeInsu_ConfigType BridgeInsuConfigData_A652 ;

#endif


void BridgeInsu_Init(Async_LooperType *looper, const BridgeInsu_ConfigType *cfgData);

#define BRIDGEINSU_MOS_BY_VOL 0U   /**< 根据电压自动使用平衡桥或非平衡桥 */
#define BRIDGEINSU_MOS_ALWAYS_ON 1U /**< 使用平衡桥，一直保持MOS处于闭合状态 */
#define BRIDGEINSU_MOS_ON_WHEN_DETECT 2U  /**<  使用平衡桥，只有在检测时MOS处于闭合状态，2次检测之间断开MOS */
void BridgeInsu_Start(uint8 mos_op);
void BridgeInsu_Stop(void);
uint16 BridgeInsu_GetPositive(void);
uint16 BridgeInsu_GetNegative(void);
boolean BridgeInsu_IsCalculated(void);
void dump_insu(void);

#endif
