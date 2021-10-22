#ifndef PRINTF_STDARG
#define PRINTF_STDARG

/*lint -save */
/*lint -e960 */

int printf(const char *format, ...);
int sprintf(char *out, const char *format, ...);
int snprintf(char *buf, unsigned int count, const char *format, ...);


/*lint -restore */


#endif

