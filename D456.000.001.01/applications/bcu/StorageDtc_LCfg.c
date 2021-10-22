#include "StorageDtc.h"


/**
 * 必须按升序排列
 */
const uint32 dtc_list[STORAGE_DTC_CODE_NUM] = {
	/**
	 * 测试数据
	 */
    0x01U,
    0x02U,
    0x03U,
    0x04U,
    0x05U,
    0x06U,
    0x07U,
    0x08U,
    0x09U,
    0x0AU,
};

uint16 dtc_last_page_addr_list[STORAGE_DTC_CODE_NUM];

static uint8 dtc_data_cache[512];
static struct StorageCycleContextType dtc_ctx_w = {
    dtc_data_cache,
    {
        0U,0U,0U,0U
    },
    0U,
    0U,
    0U,
    0UL,
    0UL,
};

const struct StorageCycleObjectType StorageDtcObject = {
    STORAGEM_DTC_ID,
    &dtc_ctx_w
};
