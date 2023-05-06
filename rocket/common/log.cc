#include "/home/pjt/WORKSPACE/RPC_Project/rocket/common/log.h"  // 包含自定义日志库的头文件
#include <sys/time.h>                                           // 包含系统时间头文件
#include "/home/pjt/WORKSPACE/RPC_Project/rocket/common/util.h" // 包含自定义工具函数头文件
#include <sstream>                                              // 包含 C++ 标准库中的 stringstream 类头文件
#include <stdio.h>                                              // 包含 C 标准库中的输入输出函数头文件

// 命名空间 rocket
namespace rocket
{

    // 定义静态变量 g_logger，用于全局共享的 Logger 类对象指针
    static Logger *g_logger = NULL;

    // 获取全局共享的 Logger 类对象指针
    Logger *Logger::getGlobalLogger()
    {
        if (g_logger)
        {
            return g_logger;
        }
        Loglevel global_log_level = StringToLoglevel(Config::GetGlobalConfig()->m_log_level);
        g_logger = new Logger(global_log_level);
        return g_logger;
    }

    std::string LoglevelToString(Loglevel level)
    {
        // 根据日志级别 level，返回相应的字符串
        switch (level)
        {
        case Debug:
            return "Debug";
        case Info:
            return "Info";
        case Error:
            return "Error";
        default:
            return "UNKNOWN";
        }
    }

    Loglevel StringToLoglevel(const std::string &log_level)
    {
        // 根据字符串，返回相应的日志等级
        if (log_level == "DEBUG")
            return Debug;
        else if (log_level == "INFO")
            return Info;
        else if (log_level == "ERROR")
            return Error;
        else
            return Unknown;
    }

    // 将 LogEvent 对象转换为字符串
    std::string LogEvent::toString()
    {
        // 获取系统时间，精确到毫秒
        struct timeval now_time;
        gettimeofday(&now_time, nullptr);
        struct tm now_time_t;
        localtime_r(&(now_time.tv_sec), &now_time_t);
        char buf[128];
        strftime(&buf[0], 128, "%y-%m-%d %H:%M:%S", &now_time_t);
        std::string time_str(buf);
        int ms = now_time.tv_usec / 1000;
        time_str = time_str + "." + std::to_string(ms);

        // 获取进程 ID 和线程 ID
        m_pid = getPid();
        m_thread_id = getThreadId();

        // 使用 stringstream 类拼接日志信息
        std::stringstream ss;
        ss << "[" << LoglevelToString(m_level) << "]\t"
           << "[" << time_str << "]\t"
           << "[" << m_pid << ":" << m_thread_id << "]\t"
           << "[" << std::string(__FILE__) << ":" << __LINE__ << "]\t";

        return ss.str(); // 返回日志信息字符串
    }

    // 将日志信息写入缓冲区
    void Logger::pushLog(const std::string &msg)
    {
        m_buffer.push(msg); // 将日志信息加入缓冲区队列
    }

    // 将缓冲区中的日志信息输出到控制台
    void Logger::log()
    {
        while (!m_buffer.empty())
        {                                       // 如果缓冲区不为空
            std::string msg = m_buffer.front(); // 获取队列头部的日志信息
            m_buffer.pop();                     // 弹出队列头部的日志信息
            printf(msg.c_str());                // 输出日志信息到控制台
        }
    }

}
