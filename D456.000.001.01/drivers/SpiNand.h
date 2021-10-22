#ifndef _spi_nand_H__
#define _spi_nand_H__

#include <stdio.h>
#include "Std_Types.h"

/**
 * \brief  附加区域布局,此处定义两组,第一组用于存储扇区ID
 */
struct NandOobFreeType {
    struct {
        uint8 offset; /*!< 附加数据偏移量(需要确保第一个附加数据受ECC保护) */
        uint8 length; /*!< 附加数据长度 */
    } dat[2];
};

struct NandPageLayoutType {
    uint16 sector_size;         /*!< 扇区空间大小 */
    uint16 sector_count;        /*!< 扇区数量 */
    const struct NandOobFreeType *oobfree;  /*!< 附加数据存储区布局 */
};

struct NandInfoType {
    uint32 id;
    uint16 id_bytes;
    uint16 bytes_per_page;
    uint16 bytes_per_spare;
    uint16 pages_per_block;
    uint16 blocks_per_chip;
    const struct NandPageLayoutType *page_layout;
    const char *part_num;
};

struct SpiNandContextType {
    uint8 cs_index;
    uint8 spi_init_flag;
    const struct NandInfoType *chipinfo;
#ifdef __MINGW32__
    uint8 *buffer;
#endif
};

struct SpiNandPlatformType {
    void *private_data;
    const struct spi_bus *bus;
};

#define OOBFREE_DAT_OFFSET(page,index,segment)    (page->oobfree[index].dat[segment].offset)
#define OOBFREE_DAT_LENGTH(page,index,segment)    (page->oobfree[index].dat[segment].length)
#define SECTOR_COUNT_IN_PAGE(page)                (page->sector_count)
#define SECTOR_SIZE_IN_PAGE(page)                 (page->sector_size)

int SpiNand_Init(const struct SpiNandPlatformType *platform);
void SpiNand_DeInit(const struct SpiNandPlatformType *platform);
int SpiNand_ReadPage(const struct SpiNandPlatformType *platform, uint32 page_addr);
int SpiNand_WritePage(const struct SpiNandPlatformType *platform, uint32 page_addr);
int SpiNand_Erase(const struct SpiNandPlatformType *platform, uint32 page_addr);
sint32 SpiNand_ReadPageData(const struct SpiNandPlatformType *platform, uint16 offset, uint8 *buffer, uint16 size);
sint32 SpiNand_WritePageData(const struct SpiNandPlatformType *platform, uint16 offset, const uint8 *buffer, uint16 size);
const void *SpiNand_GetChipInfo(const struct SpiNandPlatformType *platform);

int SpiNand_ReadReg(const struct SpiNandPlatformType *platform, uint8 addr, uint8 *pdata);
int SpiNand_WriteReg(const struct SpiNandPlatformType *platform, uint8 addr, uint8 data);

#endif
