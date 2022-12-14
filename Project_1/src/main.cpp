#include<iostream>

#include "hv/hmain.h"

#include "log.h"
// short options
static const char options[] = "han:";  //后面加:的话要有参数
// long options
static const option_t long_options[] = {
    {'h', "help",       NO_ARGUMENT},
    {'a', "add",        NO_ARGUMENT},
    {'n', "name",       REQUIRED_ARGUMENT},
};
static const char detail_options[] = R"(
  -h|--help                 Print this information
  -a|--add                  Add info
  -n|--name <name>          Set <name> 
)";
void print_help() {
    printf("Usage: %s [%s]\n", g_main_ctx.program_name, options);
    printf("Options:\n%s\n", detail_options);
}

int main(int argc, char** argv)
{
    int ret = parse_opt_long(argc, argv, long_options, ARRAY_SIZE(long_options));
    // help
    if (ret != 0 || get_arg("h")) {
        print_help();
        return 0;
    }
    Flog::instance()->set_level(LOG_LEVEL_DEBUG);
    FSLOGE("Test Error");
    FSLOGI("Test Info");
    FSLOGD("Test Debug");
    Flog::exitInstance();

    std::cout << "Success!" << std::endl;
    return 0;
}