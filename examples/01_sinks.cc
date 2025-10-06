#include <uulog.hh>

#include <cassert>
#include <filesystem>
#include <format>
#include <fstream>

static std::ofstream s_logfile;

static void custom_sink(uulog::Level level, const char* file, unsigned long line, const char* message, std::size_t message_size)
{
    if(!s_logfile.is_open()) {
        s_logfile.open("custom_sink.log", std::ios::out | std::ios::app);
        assert(s_logfile.is_open());
    }

    std::filesystem::path filepath(file);
    std::string_view message_view(message, message_size);
    std::string_view level_str(uulog::detail::level_string(level));

    s_logfile << std::format("[{}] {}:{} {}", level_str, filepath.filename().string(), line, message_view) << std::endl;
}

int main(void)
{
    uulog::add_sink(&uulog::builtin::stderr_ansi);

    LOG_INFO("Hello world!");

    uulog::add_sink(&custom_sink);

    LOG_WARNING("this message will also go to custom_sink.log");
    LOG_ERROR("and this one as well!");

    uulog::remove_sink(&uulog::builtin::stderr_ansi);

    LOG_CRITICAL("this message will only go to custom_sink.log");

    return 0;
}
