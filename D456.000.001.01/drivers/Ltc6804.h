/**
 * \file Ltc6804.h
 * \copyright UDAN Co.,Ltd.
 *
 * \note 当前接口用于 Ltc6804-1 型号, 采用菊花链连接.兼容Ltc6811-1
 */

/**
 * \addtogroup Drivers
 * \{
 * \addtogroup Ltc6804 Ltc6804驱动
 * \{
 */
#ifndef __Ltc6804_H__
#define __Ltc6804_H__

#include "Std_Types.h"
#include "spi_bus.h"
#include "Ltc6804_Cfg.h"

#if defined(__HC08__) || defined(__HC12__)     /*!< HC08 & HCS08 */
#pragma MESSAGE DISABLE C1106 /* WARNING C1106: Non-standard bitfield type */
#endif

#define LTC6804_CV_GROUP_NUM    4U
#define LTC6804_AV_GROUP_NUM    2U

#define LTC6804_MAX_CV_NUM      12U
#define LTC6804_MAX_AV_NUM      5U

/**
 * 清寄存器命令
 */
#define LTC6804_CMD_CLRCELL     0x711U
#define LTC6804_CMD_CLRAUX      0x712U
#define LTC6804_CMD_CLRSTAT     0x713U
#define LTC6804_CMD_DIAGN       0x715U

#define LTC_MV_TO_100uV(v)    (((uint16)v) * 10UL)
#define LTC_ITMP_TO_100uV(t)     (75UL * (((uint16)t) + 273UL))

#define LTC6804_CRC16_REMAINDER 16U

struct Ltc6804RegType {
    uint8 R[6];
};

struct Ltc6804CFG {
    uint8 CFGR0;
    uint8 CFGR1;
    uint8 CFGR2;
    uint8 CFGR3;
    uint8 CFGR4;
    uint8 CFGR5;
};

struct Ltc6804CVxVal {
    uint16 voltage[sizeof(struct Ltc6804RegType) / sizeof(uint16)];     /*!< 电池电压采集值, 分辨率为 100uV每bit */
};

struct Ltc6804AVxVal {
    uint16 voltage[sizeof(struct Ltc6804RegType) / sizeof(uint16)];     /*!< 辅助电压采集值, 分辨率为 100uV每bit */
};

struct Ltc6804CellVoltage {
    uint16 voltage[LTC6804_MAX_CV_NUM];
};

struct Ltc6804AuxVoltage {
    uint16 voltage[LTC6804_MAX_AV_NUM];
    uint16 ref;                             /*!< 参考电压 */
};

struct Ltc6804STxVal {
    uint16 soc;             /*!< 总电压采集值, 分辨率为 2mV每bit */
    uint16 itmp;            /*!< 片内温感电压采集值 */
    uint16 va;              /*!< 模拟参考电压采集值 */
    uint16 vd;              /*!< 数字参考电压采集值 */
    struct {
        uint8 value;
#if 0
        struct {
            uint16 THSD    : 1;  /*!< 热停机故障标记位 */
            uint16 MUXFAIL : 1;  /*!< 多路器故障标记位 */
            uint16         : 1;
            uint16         : 1;
            uint16 REV     : 4;  /*!< 芯片版本号 */
        } bits;
#endif
    } misc;
};

/**
 * \brief Ltc6804设备对象
 */
struct Ltc6804 {
    const uint8 flags; /*!< 初始化参数,描述SPI特性,请参考 \link spi_bus.h \endlink 中SPI_FLAG_xxx相关宏定义 */
    const struct spi_bus *bus;    /*!< SPI设备对象 */
};

/**
 * \brief Ltc6804初始化
 *
 * \param Ltc6804 设备对象
 */
void Ltc6804_Init(const struct Ltc6804 *dev);

/**
 * \brief Ltc6804按指定remainder计算校验值
 *
 * \param start_remainder 指定起始remainder
 * \param data 待校验数据指针
 * \param len 数据长度
 *
 * \return 校验值
 */
uint16 Ltc6804_CalcCheckNum(uint16 start_remainder, const uint8 *data, uint16 len);

/**
 * \brief 读配置参数
 *
 * \param Ltc6804 设备对象
 * \param Ltc6804CFG 配置数据指针
 * \param count 设备数量
 * \retval 0: 表示全部正常
 * \retval !0: 使用位图表示对应设备通信失败
 */
uint16 Ltc6804_1_ReadCfg(const struct Ltc6804 *dev, struct Ltc6804CFG *cfg, uint8 count);

/**
 * \brief 写配置参数
 *
 * \param Ltc6804 设备对象
 * \param Ltc6804CFG 配置数据指针
 * \param count 设备数量
 * \note  菊花链连接方式,写配置应该使用倒序,即最先发送的配置数据是给离MCU最远的6804的
 */
void Ltc6804_1_WriteCfg(const struct Ltc6804 *dev, struct Ltc6804CFG const *cfg, uint8 count);

/**
 * \brief 发送命令
 *
 * \param Ltc6804 设备对象
 * \param cmd 命令字
 * \note 菊花链方式时始终是以广播的形式发送命令,不需要指定数量
 */
void Ltc6804_1_SendCmd(const struct Ltc6804 *dev, uint16 cmd);

/**
 * \brief      发送命令,并检查命令执行结果
 *
 * \param[in]  dev    设备对象
 * \param[in]  cmd    命令字
 * \param[in]  retry  重试次数
 *
 * \retval     0: 表示成功
 * \retval    !0: 表示失败
 * \note      向设备发采集命令,并查询状态,如果设备忙,则表明设备已经接收到命令了,以此判断命令的执行结果
 *            本函数适用于耗时的采集命令
 */
uint8 Ltc6804_1_SendCmdEx(const struct Ltc6804 *dev, uint16 cmd, uint8 retry);

/**
 * \brief 获取电池单元采集值(按分组方式)
 *
 * \param Ltc6804 设备对象
 * \param gid 电池采集值组(0~3)
 * \param Ltc6804CVxVal 缓冲区
 * \param count 设备数量
 * \retval 0: 表示全部正常
 * \retval !0: 使用位图表示对应设备通信失败
 */
uint16 Ltc6804_1_GetCellVoltageWithGroup(const struct Ltc6804 *dev, uint8 gid, struct Ltc6804CVxVal *buf, uint8 count);

/**
 * \brief 获取电池单元电压采集值(按模块方式)
 *
 * \param Ltc6804 设备对象
 * \param Ltc6804CellVoltage 缓冲区
 * \param Ltc6804CVxVal 用于临时存放寄存器组数据的缓存区
 * \param count 模块数量
 * \retval 0: 表示全部正常
 * \retval !0: 使用位图表示对应的设备通信失败(同一个模块内任一寄存器组失败均计为失败)
 */
uint16 Ltc6804_1_GetCellVoltage(const struct Ltc6804 *dev, struct Ltc6804CellVoltage *cell, struct Ltc6804CVxVal *val, uint8 count);
/**
 * \brief 获取辅助电压采集值(按分组方式)
 *
 * \param Ltc6804 设备对象
 * \param gid 电压采集值组(0~1)
 * \param Ltc6804AVxVal 缓冲区
 * \param count 设备数量
 * \retval 0: 表示全部正常
 * \retval !0: 使用位图表示对应设备通信失败
 */
uint16 Ltc6804_1_GetAuxiliaryWithGroup(const struct Ltc6804 *dev, uint8 gid, struct Ltc6804AVxVal *buf, uint8 count);

/**
 * \brief 获取辅助电压采集值(按模块方式)
 *
 * \param Ltc6804 设备对象
 * \param Ltc6804AuxVoltage 缓冲区
 * \param Ltc6804AVxVal 用于临时存放寄存器组数据的缓存区
 * \param count 模块数量
 * \retval 0: 表示全部正常
 * \retval !0: 使用位图表示对应的设备通信失败(同一个模块内任一寄存器组失败均计为失败)
 */
uint16 Ltc6804_1_GetAuxiliaryVoltage(const struct Ltc6804 *dev, struct Ltc6804AuxVoltage *aux, struct Ltc6804AVxVal *val, uint8 count);

/**
 * \brief 获取状态信息
 *
 * \param Ltc6804 设备对象
 * \param Ltc6804STxVal 状态信息指针
 * \param count 设备数量
 * \retval 0: 表示全部正常
 * \retval !0: 使用位图表示对应设备通信失败
 */
uint16 Ltc6804_1_GetStatusVoltage(const struct Ltc6804 *dev, struct Ltc6804STxVal *buf, uint8 count);

/**
 * \brief 启动指定通道电池电压采集
 *
 * \param Ltc6804 设备对象
 * \param channel 通道号 [0 ~ 11]
 * \retval 0: 表示正常
 * \retval !0: 表示失败
 */
uint8 Ltc6804_1_StartChannel(const struct Ltc6804 *dev, uint8 channel);

/**
 * \brief 启动电池电压采集
 * \details 默认采集所有通道,7kHz采样率时需要2.3ms
 *
 * \param ltc6804 设备对象
 * \retval 0: 表示正常
 * \retval !0: 表示失败
 */
uint8 Ltc6804_1_StartAdcv(const struct Ltc6804 *dev);

/**
 * \brief 启动电池电压开路检查
 *
 * \param Ltc6804 设备对象
 * \param pullup True表示上拉电流,反之为下拉电流
 * \retval 0: 表示正常
 * \retval !0: 表示失败
 */
uint8 Ltc6804_1_StartAdow(const struct Ltc6804 *dev, boolean pullup);

/**
 * \brief 启动辅助电压采集
 * \details 默认采集所有通道,7kHz采样率需要2.3ms
 *
 * \param ltc6804 设备对象
 * \retval 0: 表示正常
 * \retval !0: 表示失败
 */
uint8 Ltc6804_1_StartAux(const struct Ltc6804 *dev);

/**
 * \brief 启动状态采集
 * \details 默认采集所有状态电压值,7kHz采样率需要1.6ms
 *
 * \param ltc6804 设备对象
 * \retval 0: 表示正常
 * \retval !0: 表示失败
 */
uint8 Ltc6804_1_StartStatus(const struct Ltc6804 *dev);

/**
 * \brief 启动所有电压采集
 * \details 包含 12 路电池电压以及 GPIO1 和 GPIO2
 *
 * \param ltc6804 设备对象
 * \retval 0: 表示正常
 * \retval !0: 表示失败
 */
uint8 Ltc6804_1_StartAll(const struct Ltc6804 *dev);

/**
 * \brief      等待采集完成
 *
 * \param[in]  dev        设备对象
 * \param[in]  ms         最大等待时间
 * \param[in]  sleep_1ms  延时1ms的回调函数
 *
 * \retval 0:  等待超时
 * \retval !0  转换完成
 */
uint8 Ltc6804_WaitAdc(const struct Ltc6804 *dev, uint8 ms, void (*sleep_1ms)(void));

/**
 * 将12bit压缩的数据解压为16bit形式
 * \param dat: 压缩的数据指针
 * \param len: 压缩的数据长度
 * \param buf: 解压的结果缓冲区指针
 * \param size: 结果缓冲区大小
 * \return: 返回解压后的数量
 * \note: {0xBC, 0xFA, 0xDE} => {0xABC, 0xDEF}
 * \note 长度不足时丢弃不完整的数据
 */
uint16 ltc_12_to_16(const uint8 *dat, uint16 len, uint16 *buf, uint16 size);

/**
 * 将16bit的数据转换为12bit形式
 * \param dat 待压缩的数据指针
 * \param len 待压缩的数据长度
 * \param buf 压缩缓冲区
 * \param size 缓冲区大小
 * \return 压缩后的长度
 * \note {0xABC, 0xDEF} => {0xBC, 0xFA, 0xDE}
 * \note 长度不足时补0
 */
uint16 ltc_16_to_12(const uint16 *dat, uint16 len, uint8 *buf, uint16 size);

/**
 * \brief 从配置数据中获取均衡标记
 * \param Ltc6804CFG 配置数据指针
 * \return 返回均衡标记
 */
uint16 Ltc6804_GetBalanceFlags(const struct Ltc6804CFG *cfg);

/**
 * \brief 将均衡标记写入配置数据
 * \param Ltc6804CFG 配置数据指针
 * \param flags 均衡标记
 */
void Ltc6804_SetBalanceFlags(struct Ltc6804CFG *cfg, uint16 flags);

uint8 Ltc6804_GetGpioFlags(const struct Ltc6804CFG *cfg);

void Ltc6804_SetGpioFlags(struct Ltc6804CFG *cfg, uint8 flags);

#endif

/**
 * \}
 * \}
 */