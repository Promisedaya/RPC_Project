#ifndef ROCKET_COMMON_CONFIG_H
#define ROCKET_COMMON_CONFIG_H
#include <string>
#include <map>

namespace rocket
{
    class Config
    {
    public:
        Config(const char *xmlFile);

    public:
        static Config *GetGlobalConfig();
        static void SetGlobalConfig(const char *m_xmlFile);

    public:
        std::string m_log_level;
        const char *m_xmlFile;
    };

}

#endif