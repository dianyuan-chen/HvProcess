#include "spi_bus.h"
#include "StorageM.h"
#include "SyncLocks_Cfg.h"

extern const struct SpiNandPlatformType NandFlashPlatformData;
static const struct StorageMDevice nand_device = {
    &NandFlashPlatformData,
    &locks
};

/**
 * 注意:必须保留第一个block用于存储分区信息,此处预留前四个
 */
static const struct StorageMPartitionType partitions[PARTITION_NUM] = {
    {
        STORAGEM_PARTITION_TYPE_FULLCHIP,       /*!< type */
        0U,          /*!< reserved */
        0U,          /*!< first_block */
        0xFFFFU,     /*!< last_block */
    },
    {
        STORAGEM_PARTITION_TYPE_DTC,       /*!< type */
        0U,          /*!< reserved */
        4U,          /*!< first_block */
        63U,         /*!< last_block */
    },
    {
        STORAGEM_PARTITION_TYPE_RECORD,       /*!< type */
        0U,          /*!< reserved */
        64U,         /*!< first_block */
        0xFFFFU,     /*!< last_block */
    },
};

/**
 * \note [128] => 1GBit
 *       [256] => 2GBit
 */
static uint8 bad_block_flags[256];

const struct StorageMConfigType StorageMConfig = {
    &nand_device,
    partitions,
    bad_block_flags
};
