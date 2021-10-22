/**
 * \addtogroup ExString 字符串扩展操作
 * \{
 */

#ifndef EX_STRING_H__
#define EX_STRING_H__

/**
 * \brief 判断字符串是否全是一个全数字[0-9].
 *
 * \param s 需要判断的字符串.
 *
 * \return !=0 全是数字组成.
 * \return ==0 字符串中包含非数字字符.
 */
char ExString_IsDigitString(const char *s);

/**
 * \brief 判断指定长度的字符串是否全是一个全数字[0-9].
 *
 * \param s 需要判断的字符串.
 * \param len 字符串长度.
 *
 * \return !=0 全是数字组成.
 * \return ==0 字符串中包含非数字字符.
 */
char ExString_NIsDigitString(const char *s, int len);

/**
 * \brief 判断字符串是否全是一个全16进制数字[0-9a-fA-F]
 *
 * \param s 需要判断的字符串.
 *
 * \return !=0 全是数字组成.
 * \return ==0 字符串中包含非数字字符.
 */
char ExString_IsHexString(const char *s);

/**
 * \brief 判断一个字符串是否为一个IP地址.
 *
 * \param s 需要判断的字符串.
 *
 * \return !=0 是一个IP地址字符串.
 * \return ==0 不是一个IP地址字符串.
 */
unsigned char ExString_IsIPString(const char *s);

/**
 * \brief 字符串转换成整数.
 *
 * \param s 需要转换的字符串.
 *
 * \return 转换结果.
 */
long ExString_Atol(const char *s);

/**
 * \brief 忽略字符串前面的空白字符, 把剩余字符串转换成整数.
 *
 * \param s 需要转换的字符串.
 *
 * \return 转换结果.
 */
long ExString_AtolSkipBankPrefix(const char *s);

/**
 * \brief 字符串转换成整数(10进制), 并返回不能转换的剩余字符地址.
 *
 * \param s 需要转换的字符串.
 * \param [out] left 用于保存不能转换的剩余字符地址.
 *
 * \return 转换结果.
 */
long ExString_StrToLDecade(const char *s, const char **left);

/**
 * \brief 字符串转换成整数(16进制), 并返回不能转换的剩余字符地址.
 *
 * \param s 需要转换的字符串.
 * \param [out] left 用于保存不能转换的剩余字符地址.
 *
 * \return 转换结果.
 */
long ExString_StrToLHex(const char *s, const char **left);

/**
 * \brief 带‘.’版本号的大小比较
 * \details 版本号格式为“x.x.x.x”,长度不同时，只比较相同长度的版本
 *
 * \param version1 版本1字符串
 * \param version2 版本2字符串
 *
 * \return 0:相等 -1：version2 > version1 1:version1 > version2
 */
char ExString_CompareVersionWithDot(const char *version1, const char *version2);



#endif

/** \} */
