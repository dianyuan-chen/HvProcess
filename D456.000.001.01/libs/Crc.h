#ifndef CRC_H_
#define CRC_H_

#include "Std_Types.h"

uint32 Crc_CalculateCRC32(const uint8 *dataPtr, uint16 len, uint32 startVal );
uint16 Crc_CalculateCRC16(	const uint8* dataPtr, uint16 len, uint16 startVal );


#endif /* CRC_H_ */
