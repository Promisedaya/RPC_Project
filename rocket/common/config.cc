#include "/home/pjt/WORKSPACE/RPC_Project/rocket/common/config.h"
#include "tinyxml/tinyxml.h"

#define READ_XML_NODE(name, parent)                                               \
    TiXmlElement *name##_node = xml_document->FirstChildElement("#name");         \
    if (!name##_node)                                                             \
    {                                                                             \
        printf("Start rocket server error, failed to read node [%s]\n", "#name"); \
        exit(0);                                                                  \
    }

#define READ_STR_FROM_XML_NODE(name, parent)                                           \
    TiXmlElement *name##_node = parent->FirstChildElement(#name);                      \
    if (!name##_node || !name##_node->GetText())                                       \
    {                                                                                  \
        printf("Start rocket server error, failed to read log level [%s]\n", "#name"); \
        exit(0);                                                                       \
    }                                                                                  \
    std::string log_level = std::string(name##_node->GetText());

namespace rocket
{
    static Config *g_config = NULL;

    Config *Config::GetGlobalConfig()
    {
        return g_config;
    }

    void Config::SetGlobalConfig(const char *xmlfile)
    {
        if (!g_config)
        {
            g_config = new Config(xmlfile);
        }
    }

    Config::Config(const char *xmlfile)
    {
        TiXmlDocument *xml_document = new TiXmlDocument();
        bool rt = xml_document->LoadFile(xmlfile);
        if (!rt)
        {
            printf("Start rocket server error, failed to read config file %s\n", xmlfile);
            exit(0);
        }

        READ_XML_NODE(root, xml_document);
        READ_XML_NODE(log, root_node);

        READ_STR_FROM_XML_NODE(log_level, log_node);

        m_log_level = log_level;

        // TiXmlElement* log_level_node = log_node->FirstChildElement("log_level");
        // if(!log_level_node || !log_level_node->GetText()) {
        //     printf("Start rocket server error, failed to read node %s\n", "log_level");
        //     exit(0);
        // }

        // TiXmlElement* root_node = xml_document->FirstChildElement("root");
        // if(!root_node) {
        //     printf("Start rocket server error, failed to read node %s\n", "root");
        //     exit(0);
        // }

        // TiXmlElement* log_mode = root_node->FirstChildElement("log");
        // if(!log_mode) {
        //     printf("Start rocket server error, failed to read node %s\n", "log");
        //     exit(0);
        // }
    }

}