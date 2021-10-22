/**
 * \addtogroup Shell 简单Shell
 * \{
 */
#ifndef __SHELL_H__
#define __SHELL_H__

/*lint -save */
/*lint -e960 */

/**
 * \brief Shell命令函数类型.
 *
 * \param argc 参数个数.
 * \param argv 参数指针.
 *
 * \return 执行结果.
 */
typedef int(*shell_handler)(int argc, char **argv);

#ifndef SHELL_SUPPORT_HELP
#define SHELL_SUPPORT_HELP 1
#endif

/**
 * \brief Shell命令.
 */
struct shell_command {
    const char *cmd; /**< Shell命令. */
#if SHELL_SUPPORT_HELP
    const char *summary; /**< Shell命令概要描述. */
    const char *help; /**< Shell命令帮助信息. */
#endif
    shell_handler handler; /**< Shell命令处理函数. */
};

#if SHELL_SUPPORT_HELP

/**
 * \brief 声明一个SHELL命令.
 *
 * \param cmd Shell命令
 */
#define SHELL_PROTYPE(cmd)  extern int shell_func_##cmd(int argc, const char * const*argv); extern const char shell_help_##cmd[]; extern const char shell_summary_##cmd[]
SHELL_PROTYPE(help);

#define SHELL_COMMAND(cmd, shell) {cmd, shell_summary_##shell, shell_help_##shell, shell_func_##shell }
#define SHELL_COMMAND_END() {(const char *)0, (const char *)0, (const char *)0, (shell_handler)0}

#else // SHELL_SUPPORT_HELP

#define SHELL_PROTYPE(cmd) extern int shell_func_##cmd(int argc, const char * const*argv);

#define SHELL_COMMAND(cmd, shell) {cmd, shell_func_##shell }
#define SHELL_COMMAND_END() {(const char *)0, (shell_handler)0 }

#endif // SHELL_SUPPORT_HELP

SHELL_PROTYPE(echo);
SHELL_PROTYPE(dmem);
SHELL_PROTYPE(wmem);

/**
 * \brief Shell处理循环.
 *
 * 这个函数可以在一个任务(线程)中执行.
 */
void Shell_Loop(void);

/**
 * \brief 参数错误统一提示.
 *
 * 当命令函数处理时遇到参数错误, 可以使用该函数统一处理.
 *
 * 例如:
 * ```c
 * return Shell_ArgsError(argv[0]);
 * ```
 *
 * \param argv0 输出提示需要的参数.
 * \return 错误码, 可以用于处理函数的返回值.
 */
int Shell_ArgsError(const char *argv0);


/*lint -restore */

#endif

/** \} */