/**
 * \file Diagnosis.h
 * \copyright UDAN Co.,Ltd. *
 *
 * \brief 诊断处理头文件.
 *
 * 这里详细说明.
 *
 * \par 修订历史:
 * | 版本号 | 修订日志 | 修改人 | 修订时间 |
 * | :--- | :--- | :--- | :--- |
 * | 0.1 | 初始版本, 完成讨论部分的定义. | UD0005 | 20161201 |
 */

/**
 * \addtogroup Diagnosis 诊断
 * \{
 */

#ifndef DIAGNOSIS_H_
#define DIAGNOSIS_H_

#include "Std_Types.h"
#include "App_Types.h"
#include "Diagnosis_Cfg.h"
#include "list.h"
#include "Async_Looper.h"
#include "Async_Event.h"

#if (!defined(DIAGNOSIS_SUPPORT_LEVEL))|| (DIAGNOSIS_SUPPORT_LEVEL < 3U || DIAGNOSIS_SUPPORT_LEVEL > 4U)
#error "DIAGNOSIS_SUPPORT_LEVEL must define as 3 or 4"
#endif

/**
 * \brief 支持异步定时的最大个数
 */
#define DIAGNOSIS_ASYNC_EVENT_NUM_MAX       20U
/**
 * \brief 缓存大小定义
 */
#define DIAGNOSIS_LOOPER_CMD_BUFF_SIZE      100U
/**
 * \brief 诊断任务堆栈大小
 */
#define DIAGNOSIS_TASK_STK_SIZE             400U


#define DIAGNOSIS_START_DIAG_CYCLE          100U

#define DIAGNOSIS_COND_ASYNC_EVENT_CYCLE    100U
#define DIAGNOSIS_COND_ASYNC_TRIGGER_CANCLE 1U

#define DIAGNOSIS_LEVEL_FIRST_MASK      (1U)
#define DIAGNOSIS_LEVEL_SECOND_MASK     ((uint8)((uint8)1U << 1))
#define DIAGNOSIS_LEVEL_THIRD_MASK      ((uint8)((uint8)1U << 2))
#define DIAGNOSIS_LEVEL_FOURTH_MASK     ((uint8)((uint8)1U << 3))
#define DIAGNOSIS_LEVEL_ALL_MASK        (0x0FU)

/**
 * \brief 诊断条件掩码定义
 */
#define DIAGNOSIS_CONDITION_DC_CHG_MASK (1U)
#define DIAGNOSIS_CONDITION_AC_CHG_MASK ((uint8)((uint8)1U << 1))
#define DIAGNOSIS_CONDITION_DCHG_MASK   ((uint8)((uint8)1U << 2))
#define DIAGNOSIS_CONDITION_CHG_MASK    (DIAGNOSIS_CONDITION_DC_CHG_MASK | DIAGNOSIS_CONDITION_AC_CHG_MASK)
#define DIAGNOSIS_CONDITION_ALL_MASK    (0xFFU)

/**
 * \brief 诊断项当前状态获取函数指针类型定义
 */
typedef uint16 (*Diagnosis_GetParaValue)(void);


/**
 * \brief 诊断等级.
 */
typedef uint8 Diagnosis_LevelType;
#define DIAGNOSIS_LEVEL_NONE   0U /**< 无报警发生 */
#define DIAGNOSIS_LEVEL_FIRST  1U /**< 一级报警 */
#define DIAGNOSIS_LEVEL_SECOND 2U /**< 二级报警 */
#define DIAGNOSIS_LEVEL_THIRD  3U /**< 三级报警 */
#define DIAGNOSIS_LEVEL_FOURTH 4U /**< 四级报警 */

/**
 * \brief 诊断事件.
 */
typedef enum {
    DIAGNOSIS_EVENT_DEASSERT, /**< 诊断报警释放 */
    DIAGNOSIS_EVENT_ASSERT, /**< 诊断报警触发 */
} Diagnosis_EventType;

typedef struct {
    uint32 timestamp;
    uint8 state;
} Diagnosis_LevelInnerDataType;

/**
 * \brief 启动诊断状态类型定义
 */
typedef enum{
    DIAGNOSIS_START_DIAG_STATE_WAITING, /**< 等待诊断 */
    DIAGNOSIS_START_DIAG_STATE_NORMAL, /**< 启动诊断正常 */
    DIAGNOSIS_START_DIAG_STATE_FAULT, /**< 启动诊断故障 */
}Diagnosis_StartDiagStateType;

/**
 * 各等级状态类型定义
 */
typedef struct {
    Diagnosis_LevelInnerDataType status[DIAGNOSIS_SUPPORT_LEVEL];
}Diagnosis_LevelsStatusType;

/**
 * \brief 诊断事件关注的等级位标识; 诊断使能的等级标志位.
 */
typedef uint8 Diagnosis_LevelMaskType;

/**
 * \brief 诊断关注的条件标识位，不满足条件时诊断模块不诊断或仅释放诊断
 */
typedef uint8 Diagnosis_ConditionMaskType;

/**
 * \brief 数据物理量单一等级的诊断标准.
 */
typedef struct {
    uint16 triggerThreshold; /**< 触发阈值 */
    uint16 releaseThreshold; /**< 释放阈值 */
    uint16 triggerConfirmTime; /**< 触发确认时间 */
    uint16 releaseConfirmTime; /**< 释放确认时间 */
} Diagnosis_LevelParaType;

/**
 * \brief 数据物理量的诊断标准.
 */
typedef struct {
    Diagnosis_LevelParaType levelPara[DIAGNOSIS_SUPPORT_LEVEL]; /**< 诊断配置 */
} Diagnosis_ParaType;

typedef struct{
    Diagnosis_ParaType para[DIAGNOSIS_CALIB_ITEM_NUM];
}Diagnosis_AllItemParaType;

/**
 * \brief 诊断类型类型定义
 */
typedef enum{
    DIAGNOSIS_TYPE_HIGH_EXTREME, /**< 高极值诊断 */
    DIAGNOSIS_TYPE_LOW_EXTREME, /**< 低极值诊断 */
}Diagnosis_DiagnosisTypeType;

/**
 * \brief 诊断事件回调函数.
 * \note 当某个诊断的某个等级的状态发生变化时, 如果注册了事件关注, 那么被注册回调函数会被调用,
 * 参考\link Diagnosis_EventConfigType \endlink, \link Diagnosis_RegisterEventCbk \endlink, \link Diagnosis_UnregisterEventCbk \endlink.
 *
 *
 * \param item 诊断条目.
 * \param level 诊断等级, 状态发生变化的哪个等级.
 * \param event 诊断事件, \link Diagnosis_EventType \endlink.
 */
typedef void (*Diagnosis_StatusChangeCbkType)(Diagnosis_ItemType item, Diagnosis_LevelType level, Diagnosis_EventType event);

/**
 * \brief 诊断实时数据有效性检查函数
 * \details 如果检查为无效，将不进行诊断触发条件检查，但允许诊断释放
 *
 * \param data 待检查数据
 * \return 0-无效 非0-有效
 */
typedef uint8 (*Diagnosis_DataIsValid)(uint16 data);

/**
 * \brief 获取单等级报警故障参数函数类型定义
 * \details 获取触发值、释放值、触发延时、释放延时
 *
 * \param level 报警等级, 0-一级报警 1-二级报警...
 * \param para 参数缓存指针
 */
typedef void (*Diagnosis_LevelParaGetFuncType)(uint8 level, Diagnosis_LevelParaType *para);

typedef uint8 Diagnosis_EventMaskType;
#define DIAGNOSIS_EVENT_MASK_NONE      0U /**< 无报警发生 */
#define DIAGNOSIS_EVENT_MASK_ASSERT    1U /**< 报警触发 */
#define DIAGNOSIS_EVENT_MASK_DEASSERT  2U /**< 报警释放 */

/**
 * \brief 诊断事件回调函数项类型
 */
typedef struct {
    Diagnosis_EventMaskType eventMask;  /**< 关心的事件 */
    Diagnosis_LevelMaskType levelMask; /**< 关心的级别 */
    Diagnosis_StatusChangeCbkType cbk; /**< 回调函数 */
} Diagnosis_DefaultEventCbkItemType;


/**
 * \brief 一个数据的物理量诊断条目的相关数据类型
 */
typedef struct {
    uint16 cycle; /**< 更新周期 */
    Diagnosis_ConditionMaskType conditionFlag; /**< 诊断条件标识 */
    Diagnosis_LevelMaskType enableFlag; /**< 诊断使能标记*/
    Diagnosis_DiagnosisTypeType diagnosisType; /**< 诊断类型 */
    Diagnosis_LevelsStatusType *status; /**< 各等级状态指针 */
    const Diagnosis_GetParaValue getDataFunc; /**< 获取诊断项状态值函数指针 */
    const Diagnosis_DataIsValid DataIsvalidFunc; /**< 数据是否有效函数指针 */
    Diagnosis_LevelParaGetFuncType levelParaGetFunc; /**< 报警参数获取函数 */
    uint8 defaultEventCbkNum;
    const Diagnosis_DefaultEventCbkItemType *defaultEvent; /**< 默认事件链表头 */
} Diagnosis_DiagInfoType;

/**
 * \brief 系统启动诊断是否允许函数类型
 */
typedef uint8 (*Diagnosis_StartDiagIsAllowFunc)(void);

/**
 * \brief 系统启动诊断项类型定义
 */
typedef struct{
    uint32 timeout; /**< 自检超时时间 */
    Diagnosis_LevelMaskType enableFlag; /**< 诊断使能标记*/
    Diagnosis_StartDiagIsAllowFunc IsAllowFunc; /**< 启动诊断是否允许诊断回调函数 */
    uint8 defaultEventCbkNum;
    const Diagnosis_DefaultEventCbkItemType *defaultEvent; /**< 默认事件链表头 */
}Diagnosis_StartDiagInfoType;

/**
 * \brief 一个数据的物理量诊断条目相关数据链表项类型
 */
typedef struct {
    struct list_head list; //!< 双向链表表头
    Diagnosis_ItemType diagnosis; /**< 诊断项 */
    struct list_head userEventHead; /**< 用户注册事件，用于链接事件项 Diagnosis_EventCbkItemType */
    const Diagnosis_DiagInfoType *info; /**< 诊断条目相关数据 */
    Diagnosis_StartDiagStateType startDiagState; /**< 启动诊断状态 */
    const Diagnosis_StartDiagInfoType *startDiagInfo; /**< 启动诊断相关烦气 */
    const Diagnosis_ParaType *config; /**< 诊断配置参数 */
}Diagnosis_DiagInfoItemType;

/**
 * \brief 诊断事件回调函数项类型
 */
typedef struct {
    struct list_head list; //!< 双向链表表头.用于链接诊断事件项
    Diagnosis_LevelMaskType mask; /**< 关心的级别 */
    Diagnosis_StatusChangeCbkType cbk; /**< 回调函数 */
}Diagnosis_EventCbkItemType;


/**
 * \brief 诊断模块异步定时事件类型
 */
typedef struct {
    Async_EventType event; /**< 异步事件 */
    struct list_head head; //!< 双向链表表头.用于链接诊断项 Diagnosis_DiagInfoItemType
}Diagnosis_AsyncEventItemType;

/**
 * \brief 诊断模块内部参数类型定义
 */
typedef struct{
    uint8 start; /**< 启动标志 */
    Async_EventType Event; /**< 诊断事件 */
    Diagnosis_LevelParaType LevelParaTemp; /**< 等级参数 */
}Diagnosis_InnerDataType;

typedef boolean (*Diagnosis_CondCheck)(void);
typedef void (*Diagnosis_Action)(void);

typedef struct{
    Async_EventType event; /**< 异步事件 */
    Diagnosis_ItemType diagItem; /**< 诊断项 */
    Diagnosis_LevelMaskType enableFlag; /**< 诊断使能标记*/
    uint32 decCounter; /**< 计时 */
    Diagnosis_CondCheck condFunc; /**< 条件检查函数 */
    Diagnosis_Action actionFunc; /**< 动作函数 */
}Diagnosis_CondAsyncEventType;

extern const Diagnosis_DiagInfoType Diagnosis_DiagInfoItem[DIAGNOSIS_ITEM_DEFAULT_NUM];
extern const Diagnosis_DiagInfoType Diagnosis_DiagInfoConfig[];
extern const Diagnosis_StartDiagInfoType Diagnosis_StartDiagInfo[];
extern const Diagnosis_ParaType Diagnosis_ChgSckTmpHTDiagConfig[];

/**
 * \brief 诊断模块初始化
 *
 * \param DiagnosisParaPtr 诊断依赖配置参数指针
 * \param pri 任务优先级
 */
void Diagnosis_Init(const Diagnosis_AllItemParaType* DiagnosisParaPtr, uint8 pri);

/**
 * \brief 设置可标定诊断配置参数指针
 * \details 用于模式切换时更新配置参数
 *
 * \param ptr 配置参数指针
 */
void Diagnosis_CalibParaConfigPtrSet(const Diagnosis_AllItemParaType * ptr);

/**
 * \brief 诊断项初始化
 * \details 初始化诊断项的链表、配置、及参数指针
 *
 * \param DiagInfoItem 初始化诊断项指针
 * \param item 诊断项
 * \param info 诊断项状态信息
 * \param config 诊断项依赖配置
 * \return E_OK:初始化成功 E_NOT_OK:初始化失败
 */
Std_ReturnType Diagnosis_DiagInfoItemInit(
    Diagnosis_DiagInfoItemType *DiagInfoItem,
    Diagnosis_ItemType item,
    const Diagnosis_DiagInfoType *info,
    const Diagnosis_ParaType *config
);

/**
 * \brief 获取诊断项指定等级已经触发的时间
 *
 * \param item 诊断项编号
 * \param level 诊断等级
 * \return 已经触发的时间
 */
uint32 Diagnosis_GetItemPreTriggerTime(Diagnosis_ItemType item, uint8 level);

/**
 * \brief 诊断项注册
 * \details 注册新诊断项，如果异步定时事件中已经存在同周期的异步事件，将新诊断项直接关联到此异步事件，如果没有同周期异步事件，创建新异步事件来注册诊断项
 *
 * \param Diagnosis 待注册诊断项指针
 * \return E_OK:注册成功 E_NOT_OK:注册失败
 */
Std_ReturnType Diagnosis_RegisterDiagnosis(Diagnosis_DiagInfoItemType *Diagnosis);

/**
 * \brief 获取所有诊断条目的诊断结果.
 *
 * \param buf 结果存放的缓冲.
 * \param bufItemSize 缓冲大小(以\link Diagnosis_LevelType \endlink的大小为单位).
 */
void Diagnosis_GetAllItemLevel(Diagnosis_LevelType *buf, uint16 bufItemSize);


/**
 * \brief 获取所有诊断条目的诊断结果.
 *
 * \param buf 结果存放的缓冲, 按照故障Index的顺序存放.
 * \param bufSize 缓冲大小(以\link Diagnosis_LevelType \endlink的大小为单位).
 */
void Diagnosis_GetAllLevelByIndex(Diagnosis_LevelType *buf, uint16 bufSize);


/**
 * \brief 获取从当前报警诊断项开始的的下一个正在报警的诊断项
 *
 * \param currentItem 起始诊断项
 * \return 正在报警的下一诊断项，返回DIAGNOSIS_ITEM_INVALID_INDEX表示无正在报警项
 */
Diagnosis_ItemType Diagnosis_GetNextAlarmingItem(Diagnosis_ItemType startItem);

/**
 * \brief 查找已注册的诊断项
 * \details 通过诊断项编号在已注册的诊断项链表中查找对应编号的诊断项，并返回该诊断项的info指针
 *
 * \param item 诊断项编号
 * \return 诊断项info指针
 */
Diagnosis_DiagInfoItemType* Diagnosis_SearchInfoItem(Diagnosis_ItemType item);

/**
 * \brief 注册诊断事件
 * \details 根据诊断项编号注册对应的诊断事件
 *
 * \param item 诊断项编号
 * \param event 诊断事件
 *
 * \return E_OK: 注册成功 E_NOT_OK: 注册失败
 */
Std_ReturnType Diagnosis_RegisterEvent(Diagnosis_ItemType item, Diagnosis_EventCbkItemType *event);

/**
 * \brief 注销诊断事件
 * \details 根据诊断项编号注销对应的诊断事件
 *
 * \param item 诊断项编号
 * \param event 诊断事件
 *
 * \return E_OK: 注销成功 E_NOT_OK: 注销失败
 */
Std_ReturnType Diagnosis_UnRegisterEvent(Diagnosis_ItemType item, Diagnosis_EventCbkItemType *event);

/**
 * \brief 获取诊断当前状态
 *
 * \param item 诊断项编号
 * \return 诊断状态 参见\link Diagnosis_LevelType \endlink
 */
Diagnosis_LevelType Diagnosis_GetLevel(Diagnosis_ItemType item);

/**
 * \brief 上电自检是否完成全部初次检测
 * \return TRUE-完成 FALSE-未完成
 */
uint8 Diagnosis_StartDiagIsFinish(void);

/**
 * \brief 上电自检是否全部正常
 * \return TRUE-正常 FALSE-不正常
 */
uint8 Diagnosis_StartDiagIsAllNormal(void);

/**
 * \brief 初始化故障诊断条件延时异步事件
 *
 * \param Event 条件延时异步事件
 * \param delay 延时
 * \param diagItem 诊断项
 * \param enableFlag 诊断等级
 * \return E_OK: 成功 E_NOT_OK: 失败
 */
Std_ReturnType Diagnosis_CondAsyncEventInit(Diagnosis_CondAsyncEventType *Event,
    uint32 delay,
    Diagnosis_ItemType diagItem,
    Diagnosis_LevelMaskType enableFlag);

/**
 * \brief 故障诊断条件延时异步事件注册
 *
 * \param Event 诊断条件延时异步事件
 * \param CondFunc 条件函数指针
 * \param ActionFunc 动作函数指针
 * \return E_OK: 注册成功 E_NOT_OK: 注册失败
 */
Std_ReturnType Diagnosis_CondAsyncEventRegister(
    Diagnosis_CondAsyncEventType *Event,
    Diagnosis_CondCheck CondFunc,
    Diagnosis_Action ActionFunc);

/**
 * \brief 故障诊断条件延时异步事件注销
 *
 * \param Event 诊断条件延时异步事件
 * \return E_OK: 注销成功 E_NOT_OK: 注销失败
 */
Std_ReturnType Diagnosis_CondAsyncEventCancle(Diagnosis_CondAsyncEventType *Event);

/**
 * \brief 获取当前最高报警等级
 * \return 最高报警等级
 */
Diagnosis_LevelType Diagnosis_GetDiagLevelMax(void);

/**
 * \brief 获取所有报警的数量，不区分报警等级
 *
 * \return 报警数量
 */
uint16 Diagnosis_GetAllAlarmNum(void);

/**
 * \brief 获取指定报警等级的报警数量
 *
 * \return 报警数量
 */
uint16 Diagnosis_GetAlarmNumWithLevel(Diagnosis_LevelType level);

/**
 * \brief 将诊断项编号转换为连续数组使用的索引号
 *
 * \param item 诊断项编号
 * \return 索引号
 */
uint8 Diagnosis_ItemToIndex(Diagnosis_ItemType item);

/**
 * \brief 将索引号转换为诊断项编号
 *
 * \param index 索引号
 * \return 诊断项编号
 */
Diagnosis_ItemType Diagnosis_IndexToItem(uint8 index);

/**
 * \brief 获取诊断项配置参数值
 * \details 根据实际诊断配置，从系统参数、标定参数或者用户自定义参数函数中获取禁止充电诊断项配置参数值
 *
 * \param diagnosis 诊断项
 * \param level 报警等级 0-一级 1-二级 2-三级 3-四级
 * \param offset 0-触发阈值 1-释放阈值 2-触发延时 3-释放延时
 * \return 指定配置参数值
 */
uint16 Diagnosis_GetDiagnosisPara(Diagnosis_ItemType diagnosis, uint8 level, uint8 offset);



#endif

/** \} */
