#include <uulog.hh>

#include <cassert>
#include <filesystem>
#include <format>
#include <fstream>

// Yummy C++20 templated argument abuse
// Passing string literals as template arguments

template<std::size_t Count>
class StringLiteral final {
public:
    constexpr StringLiteral(const char (&str)[Count])
    {
        std::copy_n(str, Count, value);
    }

    constexpr operator const char*() const
    {
        return value;
    }

    char value[Count];
};

template<uulog::Level LevelValue, StringLiteral Filename>
static void filtered_file_sink(uulog::Level level, const char* file, unsigned long line, const char* message, std::size_t message_size)
{
    static std::ofstream s_logfile;

    if(!s_logfile.is_open()) {
        s_logfile.open(Filename, std::ios::out | std::ios::app);
        assert(s_logfile.is_open());
    }

    if(level == LevelValue) {
        std::filesystem::path filepath(file);
        std::string_view message_view(message, message_size);
        std::string_view level_str(uulog::detail::level_string(level));

        s_logfile << std::format("[{}] {}:{} {}", level_str, filepath.filename().string(), line, message_view) << std::endl;
    }
}

int main(int argc, char** argv)
{
    uulog::add_sink(&uulog::builtin::stderr_ansi);
    uulog::add_sink(&filtered_file_sink<uulog::Level::Warning, "warnings.log">);
    uulog::add_sink(&filtered_file_sink<uulog::Level::Error, "errors.log">);
    uulog::add_sink(&filtered_file_sink<uulog::Level::Critical, "critical.log">);

    LOG_INFO("Hello world!");

    LOG_WARNING("this message will go to warnings.log");
    LOG_ERROR("this message will go to errors.log");
    LOG_CRITICAL("this message will go to critical.log");

    return 0;
}
