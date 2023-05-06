#ifndef ROCKET_COMMON_LOG_H
#define ROCKET_COMMON_LOG_H

#include <string>
#include <queue>
#include <memory>
#include "/home/pjt/WORKSPACE/RPC_Project/rocket/common/config.h"

namespace rocket
{

    // 可变参数模板函数，用于格式化字符串
    template <typename... Args>
    std::string formatString(const char *str, Args &&...args)
    {
        // 使用 snprintf 计算格式化后的字符串长度
        int size = snprintf(nullptr, 0, str, args...);
        // 创建一个空字符串
        std::string result;
        // 如果字符串长度大于 0
        if (size > 0)
        {
            // 将字符串缓冲区大小设为长度 + 1，加 1 是为了容纳结尾的空字符
            result.resize(size);
            // 使用 snprintf 将格式化后的字符串输出到缓冲区中
            snprintf(&result[0], size + 1, str, args...);
        }
        // 返回格式化后的字符串
        return result;
    }

    // 定义宏 DEBUGLOG，用于将日志信息写入缓冲区，并输出到控制台
    #define DEBUGLOG(str, ...) \
        if(rocket::Logger::getGlobalLogger()->getLoglevel() <= rocket::Debug) \
        { \
            rocket::Logger::getGlobalLogger()->pushLog((new rocket::LogEvent(rocket::Loglevel::Debug))->toString() + rocket::formatString(str, ##__VA_ARGS__) + "\n"); \
            rocket::Logger::getGlobalLogger()->log(); \ 
        } \
           

    #define INFOLOG(str, ...) \
        if(rocket::Logger::getGlobalLogger()->getLoglevel() <= rocket::Info) \
        { \
            rocket::Logger::getGlobalLogger()->pushLog((new rocket::LogEvent(rocket::Loglevel::Info))->toString() + rocket::formatString(str, ##__VA_ARGS__) + "\n"); \
            rocket::Logger::getGlobalLogger()->log();  \ 
        } \

    #define ERRORLOG(str, ...) \
        if(rocket::Logger::getGlobalLogger()->getLoglevel() <= rocket::Error) \
        { \
            rocket::Logger::getGlobalLogger()->pushLog((new rocket::LogEvent(rocket::Loglevel::Error))->toString() + rocket::formatString(str, ##__VA_ARGS__) + "\n"); \
            rocket::Logger::getGlobalLogger()->log(); \ 
        } \                                                         

    // 定义一个枚举类型，表示日志级别
    enum Loglevel
    {
        Unknown = 0,
        Debug = 1, // 调试信息
        Info = 2,  // 信息
        Error = 3  // 错误
    };

    // 定义一个日志器类，包含将日志信息保存至队列以及将队列中的日志信息输出到控制台的函数
    class Logger
    {
    public:
        // 定义智能指针类型
        typedef std::shared_ptr<Logger> s_ptr;

        Logger(Loglevel level) : m_set_level(level) {}

        // 将一条日志信息压入队列
        void pushLog(const std::string &msg);

        // 将队列中的所有日志信息输出到控制台
        void log();

        Loglevel getLoglevel() const {
            return m_set_level;
        }

        // 获取全局日志器
        static Logger *getGlobalLogger();

    private:
        Loglevel m_set_level;             // 设置的日志级别
        std::queue<std::string> m_buffer; // 日志信息队列
    };

    // 将日志级别枚举转换成字符串
    std::string LoglevelToString(Loglevel level);
    Loglevel StringToLoglevel(const std::string &log_level);

    // 定义一个日志事件类，包含一个日志级别和一些辅助信息
    class LogEvent
    {
    public:
        // 构造函数，需要一个日志级别作为参数
        LogEvent(Loglevel level) : m_level(level) {}

        // 获取文件名
        std::string getFileName()
        {
            return m_file_name;
        }

        // 获取日志级别
        Loglevel getLoglevel() const
        {
            return m_level;
        }

        // 将日志事件转换成字符串
        std::string toString();

    private:
        std::string m_file_name; // 文件名
        std::string m_file_line; // 行号
        int m_pid;               // 进程号
        int m_thread_id;         // 线程号

        Loglevel m_level;       // 日志级别
        Logger::s_ptr m_logger; // 日志器
    };

}

#endif