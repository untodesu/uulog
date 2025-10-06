#include <uulog.hh>

int main(void)
{
    uulog::add_sink(&uulog::builtin::stderr_ansi);

    LOG_DEBUG("Hello world");
    LOG_INFO("Hello world");
    LOG_WARNING("Hello world");
    LOG_ERROR("Hello world");
    LOG_CRITICAL("Hello world");

    return 0;
}
