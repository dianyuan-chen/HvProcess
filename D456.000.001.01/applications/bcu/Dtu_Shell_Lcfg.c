#include "SystemConnection.h"
#include "Shell.h"

const char shell_summary_dtustart[] = "Start dtu";
const char shell_help_dtustart[] = "\
  subcommand:\n\
    startdtu Start dtu\n\
";

extern void start_dtu_task_testmode(void);

int shell_func_dtustart(int argc, const char *const *argv);

int shell_func_dtustart(int argc, const char *const *argv) {
    int ret = 0;
    (void)argv;

    if (argc == 1) {
        if (SystemConnection_ConfigInfo.DtuSupport) {
            start_dtu_task_testmode();
        } else {
        }
        ret = 0;
    } else {
        ret = Shell_ArgsError(argv[0]);
    }

    return ret;
}

