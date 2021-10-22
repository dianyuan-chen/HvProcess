#ifndef PRE_INCLUDE_H
#define PRE_INCLUDE_H

/*lint -e537 */
/*lint +rw(inline) */
/*lint -esym(950, inline) */
/*lint -e621 */
/*lint -e708 */
/*lint -e717 */
/*lint -e749 */
/*lint -e750 */
/*lint -e754 */
/*lint -e826 */
/*lint -e830 */
/*lint -e835 */

/* misra-c 2004 */
/*lint -e829 */ /* rule 20.9 */
/*lint -e923 */ /* rule 11.3(建议) */
/*lint -e926 */ /* rule 11.4(建议) */
/*lint -e927 */ /* rule 11.4(建议) */
/*lint -e928 */ /* rule 11.4(建议) */
/*lint -e929 */ /* rule 11.4(建议) */
/*lint -e950 */ /* rule 2.2 */
/*lint -e961 */ /* rule 19.7(建议) */
/*lint -e970 */ /* rule 6.3(建议) */

#include <hidef.h>
#include <stddef.h>

#define SYS_OSC_FREQ  8000000



#ifdef __HC12__
#pragma MESSAGE DISABLE C12056 /*SP debug info incorrect because of optimization or inline assembler*/
#pragma MESSAGE DISABLE C4001 /*Condition always FALSE*/
#pragma MESSAGE DISABLE C12053 /*Stack-pointer change not in debugging-information*/
#endif

#ifdef __XGATE__
#define inline
#endif


#ifdef __LARGE__
#pragma DATA_SEG __GPAGE_SEG PAGED_RAM
#endif

#pragma CONST_SEG DEFAULT

#endif
