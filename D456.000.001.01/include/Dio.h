/**
 * \addtogroup autosar
 * \{
 * \addtogroup DIO DIO驱动
 * \{
 */

#ifndef DIO_H_
#define DIO_H_

#include "Std_Types.h"
#include "Dio_Types.h"
#include "Dio_Cfg.h"

typedef uint8 Dio_LevelType;

Dio_LevelType Dio_ReadChannel(Dio_ChannelType channelId);
void Dio_WriteChannel(Dio_ChannelType channelId, Dio_LevelType level);
Dio_LevelType Dio_FlipChannel(Dio_ChannelType channelId);
Dio_PortLevelType Dio_ReadPort(Dio_PortType portId);
void Dio_WritePort(Dio_PortType portId, Dio_PortLevelType level);
Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType *channelGroupIdPtr );
void Dio_WriteChannelGroup(const Dio_ChannelGroupType *channelGroupIdPtr, Dio_PortLevelType level);

#endif /*DIO_H_*/

/**
 * \}
 * \}
 */
