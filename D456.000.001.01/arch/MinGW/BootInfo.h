#ifndef _APPINFO_H_
#define _APPINFO_H_

#include "Std_Types.h"

#define APP_INFO_FLAG_0         (0x123ABCF0UL)
#define APP_INFO_FLAG_1         (0x456DE789UL)
#define APP_TAG_VERSION         (0)

#define BOOT_ResetVectorSource_RST  0x01u
#define BOOT_ResetVectorSource_CMF  0x02u
#define BOOT_ResetVectorSource_COP  0x03u

#define Boot_PflashAddr_LogicToPhy(addr)  (0x400000UL + 16UL*1024UL*((addr)>>16) + ((addr) & 0xFFFF) - 0x8000UL)

#define Boot_AppInfoTagA_ADDR             (0xE7BC00u)
#define Boot_AppInfoTagB_ADDR             (0xEFBC00u)
#define Boot_RunFlagTag_ADDR              (0x3FF8u)
#define BOOT_EXP100_FBL_DRIVER_ADDR       (0x3A00u)
#define BOOT_EXP100_FBL_DRIVER_MAX_SIZE   (0x05f8u)
#define BOOT_EXP100_FBL_TAG_VERSION       (0x01u)

#define Boot_FlagUnbeliveableApp 0xFF
#define Boot_FlagRequestRunFBL   0x01
#define Boot_FlagRequestRunApp   0x02

#define Boot_FWBootloadAddrSpace 0x00
#define Boot_FWCopyAAddrSpace    0x01
#define Boot_FWCopyBAddrSpace    0x02

typedef struct {
    uint32 ValidFlag[2];
    uint32 TagVersion;
    char FWID[16];
    char BurnID[16];
    char SourceCommitId[40];
    char ConfigCommitId[40];
    char BuildTime[20];
    char FWName[20];
    char FWVersion[10];
    char SupplierName[10];
    uint32 CompatibleHW;
    void (*Entry)(void);
    uint8 FWAddrSpace;
    char ReleaseName[64];
} Boot_AppInfoTagType;

typedef struct {
    uint32 TagVersion;
    char BuildTime[20];
    char BootName[20];
    char BootVersion[10];
    char HWName[20];
    char HWVersion[10];
} Boot_FBLInfoTagType;

typedef struct {
    uint8 TagVersion;
    uint8 ResetVectorSource;
    uint8 Flag;
    uint8 ExtFlag;
    uint8 Reserved[4];
} Boot_RunFlagsTagType;

typedef uint8 FlashDriverReturnType;
#define FLASH_DRIVER_OK   0
#define FLASH_DRIVER_ERR  1

typedef struct {
    uint8 TagVersion;
    uint8 ValidFlag;
    FlashDriverReturnType (*__near Init)(uint32 oscFreq); //<! 初始化FLASH控制器.
    FlashDriverReturnType (*__near Erase)(uint32 eraseAddr, uint16 eraseSize); //<! 擦除FLASH.
    FlashDriverReturnType (*__near Write)(uint32 writeAddr, const uint8 *__far pSrcDataAddr, uint16 writeSize); //<! 写入数据.
    FlashDriverReturnType (*__near Read)(uint32 readAddr, uint8 *__far pDestDataAddr, uint16 readSize); //<! 读取数据
    FlashDriverReturnType (*__near DFlashPartion)(uint16 dfpart, uint16 erpart); //!< DFLASH分区.
} Boot_FlashDriverTagType;

extern const Boot_FlashDriverTagType *__near const BootFlashDriverPtr;
extern const Boot_RunFlagsTagType * __near const BootRunFlagPtr;

#define Boot_FlashDriverIsValid() (BootFlashDriverPtr->ValidFlag != 0x00)


void Boot_ResetToApp(uint8 extFlag);
void Boot_ResetToFBL(void);
void Boot_SetFlashDriverFlag(boolean valid);
void Boot_ResetToFBLDefaultSession(void);


#endif
