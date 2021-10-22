/**
 * \file AppParameterM.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 应用参数管理头文件.
 *
 * * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初版本, 完成讨论部分的定义. | UD00004 | 20170614 |
 */

/**
 * \addtogroup AppParameterM 应用参数管理
 * \{
 */

#ifndef APP_PARAMETERM_H_
#define APP_PARAMETERM_H_

#include "ParameterM.h"
#include "TemperatureM.h"

#define APPPARAMETERM_MEMBER_OF_STRUCT(PTR, MEMBER) (&(PTR)->MEMBER)
#define PARAMETERM_GET_APP_CALIB_PARA_ADDR(PARA) \
    ((uint32)(uint8*)APPPARAMETERM_MEMBER_OF_STRUCT((AppParameterM_CalibParaType*)ParameterM_CurrentCalibParaPtr, PARA))

#define PARAMETERM_GET_APP_DFLASH_CALIB_PARA_ADDR(PARA) \
    ((uint32)(uint8*)APPPARAMETERM_MEMBER_OF_STRUCT((AppParameterM_CalibParaType*)ParameterM_DFlashCalibParaPtr, PARA))

#define PARAMETERM_GET_APP_PFLASH_CALIB_PARA_ADDR(PARA) \
    ((uint32)(uint8*)APPPARAMETERM_MEMBER_OF_STRUCT((AppParameterM_CalibParaType*)ParameterM_PFlashCalibParaPtr, PARA))



/**
 * \brief 应用层标定参数类型定义
 */
typedef struct{
	ParameterM_CalibParaType rtePara; /**< rte层参数 */
    TemperatureM_ConfigType TemperatureMPara; /**< 温度管理参数 */
}AppParameterM_CalibParaType;





#endif

/**
 * \}
 */
