
#ifndef __BUFFER_H_
#define __BUFFER_H_

#include "Std_Types.h"

/**********************************************
 *
 * set or get data
 *
 ***********************************************/
extern inline uint32 Buffer_GetBTUint32(const uint8 *buffer, uint16 index);
extern inline uint32 Buffer_GetBTUint24(const uint8 *buffer, uint16 index);
extern inline uint16 Buffer_GetBTUint16(const uint8 *buffer, uint16 index);
extern inline uint8  Buffer_GetBTUint8 (const uint8 *buffer, uint16 index);
extern inline uint32 Buffer_GetLTUint32(const uint8 *buffer, uint16 index);
extern inline uint32 Buffer_GetLTUint24(const uint8 *buffer, uint16 index);
extern inline uint16 Buffer_GetLTUint16(const uint8 *buffer, uint16 index);
extern inline uint8  Buffer_GetLTUint8 (const uint8 *buffer, uint16 index);

extern inline void Buffer_SetBTUint32(uint8 *buffer, uint16 index, uint32 value);
extern inline void Buffer_SetBTUint24(uint8 *buffer, uint16 index, uint32 value);
extern inline void Buffer_SetBTUint16(uint8 *buffer, uint16 index, uint16 value);
extern inline void Buffer_SetBTUint8 (uint8 *buffer, uint16 index, uint8 value);
extern inline void Buffer_SetLTUint32(uint8 *buffer, uint16 index, uint32 value);
extern inline void Buffer_SetLTUint24(uint8 *buffer, uint16 index, uint32 value);
extern inline void Buffer_SetLTUint16(uint8 *buffer, uint16 index, uint16 value);
extern inline void Buffer_SetLTUint8 (uint8 *buffer, uint16 index, uint8 value);

/**********************************************
 *
 * read or write data and the position is moved
 *
 ***********************************************/
extern inline uint32 Buffer_ReadBTUint32(const uint8* buffer, uint16 *index);
extern inline uint32 Buffer_ReadBTUint24(const uint8* buffer, uint16 *index);
extern inline uint16 Buffer_ReadBTUint16(const uint8* buffer, uint16 *index);
extern inline uint8  Buffer_ReadBTUint8 (const uint8* buffer, uint16 *index);
extern inline uint32 Buffer_ReadLTUint32(const uint8* buffer, uint16 *index);
extern inline uint32 Buffer_ReadLTUint24(const uint8* buffer, uint16 *index);
extern inline uint16 Buffer_ReadLTUint16(const uint8* buffer, uint16 *index);
extern inline uint8  Buffer_ReadLTUint8 (const uint8* buffer, uint16 *index);


extern inline uint32 Buffer_ReadBTUint32WithSize(const uint8* buffer, uint16 *index, uint16 size);
extern inline uint32 Buffer_ReadBTUint24WithSize(const uint8* buffer, uint16 *index, uint16 size);
extern inline uint16 Buffer_ReadBTUint16WithSize(const uint8* buffer, uint16 *index, uint16 size);
extern inline uint8  Buffer_ReadBTUint8WithSize (const uint8* buffer, uint16 *index, uint16 size);
extern inline uint32 Buffer_ReadLTUint32WithSize(const uint8* buffer, uint16 *index, uint16 size);
extern inline uint32 Buffer_ReadLTUint24WithSize(const uint8* buffer, uint16 *index, uint16 size);
extern inline uint16 Buffer_ReadLTUint16WithSize(const uint8* buffer, uint16 *index, uint16 size);
extern inline uint8  Buffer_ReadLTUint8WithSize (const uint8* buffer, uint16 *index, uint16 size);

extern inline void Buffer_WriteBTUint32(uint8* buffer, uint16 *index, uint32 value);
extern inline void Buffer_WriteBTUint24(uint8* buffer, uint16 *index, uint32 value);
extern inline void Buffer_WriteBTUint16(uint8* buffer, uint16 *index, uint16 value);
extern inline void Buffer_WriteBTUint8(uint8* buffer, uint16 *index, uint8 value);
extern inline void Buffer_WriteLTUint32(uint8* buffer, uint16 *index, uint32 value);
extern inline void Buffer_WriteLTUint24(uint8* buffer, uint16 *index, uint32 value);
extern inline void Buffer_WriteLTUint16(uint8* buffer, uint16 *index, uint16 value);
extern inline void Buffer_WriteLTUint8(uint8* buffer, uint16 *index, uint8 value);

extern inline void Buffer_WriteBTUint32WithSize(uint8* buffer, uint16 *index, uint32 value, uint16 size);
extern inline void Buffer_WriteBTUint24WithSize(uint8* buffer, uint16 *index, uint32 value, uint16 size);
extern inline void Buffer_WriteBTUint16WithSize(uint8* buffer, uint16 *index, uint16 value, uint16 size);
extern inline void Buffer_WriteBTUint8WithSize (uint8* buffer, uint16 *index, uint8 value, uint16 size);
extern inline void Buffer_WriteLTUint32WithSize(uint8* buffer, uint16 *index, uint32 value, uint16 size);
extern inline void Buffer_WriteLTUint24WithSize(uint8* buffer, uint16 *index, uint32 value, uint16 size);
extern inline void Buffer_WriteLTUint16WithSize(uint8* buffer, uint16 *index, uint16 value, uint16 size);
extern inline void Buffer_WriteLTUint8WithSize (uint8* buffer, uint16 *index, uint8 value, uint16 size);



#endif
