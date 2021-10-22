/**
 * \addtogroup DigitalInput 数字输入
 * \{
 */
#ifndef DIGITALINPUT_H
#define DIGITALINPUT_H

#include "Std_Types.h"
#include "Dio.h"
#include "DigitalInput_Cfg.h"

typedef uint8 DigitalInput_ChannelType;

/**
 * \brief 作为开关输入的数字输入通道读取到的状态.
 */
typedef enum {
    DIGITALINPUT_SW_OFF, /**< 外部开关断开 */
    DIGITALINPUT_SW_ON, /**< 外部开关闭合 */
} DigitalInput_SwState;

/**
 * \brief 电平输入状态类型定义
 */
typedef struct{
  Dio_LevelType Level; /**< 电平状态 */
  uint16 frequency; /**< 频率 */
  uint16 duty; /**< 占空比 */
}DigitalInput_DinStatusType;


void DigitalInput_Init(void);

/**
 * \brief 读取一个数字输入量的电平输入状态.
 *
 * \param channel 需要读取的通道.
 *
 * \return 读取到的外部输入电平.
 *
 * \dot
digraph {
  edge [fontname="Simsun",arrowhead=none];
  node [fontname="Simsun"];
  fontname="Simsun";
  label="需要返回A点的电平状态";
  rankdir=LR;
  subgraph cluster0 {
    color=lightgrey;
    label="BMS";
    style=filled;
    预处理电路 [shape=box,style=filled,color=white];
    处理器 [shape=box,style=filled,color=white];
    预处理电路 -> 处理器 [arrowhead=tee,color=black];
  }
  输入 [shape=point];
  输入->预处理电路[label="A"];
}
 * \enddot
 *
 * \note 读取到的值必须是外部输入的电平值, 依据内部电路可能与读到的IO值反向.
 */
Dio_LevelType DigitalInput_GetDinLevel(DigitalInput_ChannelType channel);

/**
 * \brief 读取外部开关量输入的状态.
 *
 * \param channel 需要读取的通道.
 *
 * \return 读取到的外部开关输入状态.
 *
 * \note 读取到的状态值必须外部开关的状态, 依据内部电路可能与读到的IO值不同.
 */
DigitalInput_SwState DigitalInput_GetSwitchState(DigitalInput_ChannelType channel);

#endif

/** \} */