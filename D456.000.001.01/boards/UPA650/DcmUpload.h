#ifndef __DCM_UPLOAD_H__
#define __DCM_UPLOAD_H__


#include "Std_Types.h"


Std_ReturnType DcmUpload_RequestUpload(boolean isInner, uint32 addr, uint16 length);
sint32 DcmUpload_TransferData(uint8 seq, uint8 *data, uint16 size);
Std_ReturnType DcmUpload_ExitTransfer(void);



#endif
