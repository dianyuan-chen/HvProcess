#ifndef CAN_LCFG_H
#define CAN_LCFG_H


extern const uint8 CanUsedControllerNum;
extern const uint8 CanUsedHohNum;

extern const Can_ControllerHwIdType CanControllerRefIdToHwIdMap[CAN_CTRL_MAX];
extern const Can_ControllerRefIdType CanControllerHwIdToRefIdMap[CAN_CTRL_MAX];
extern const Can_HardwareObjectType CanHardwareObject[];
extern const Can_ConfigType CanConfig;
extern const Can_ConfigType CanConfig_TestMode;

#endif
