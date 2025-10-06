#include <uulog/uulog.hh>

int main(void)
{
    uulog::add_sink(&uulog::builtin::stderr_ansi);

    LOG_INFO("Hello world!");

    return 0;
}
