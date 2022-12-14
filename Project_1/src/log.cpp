#include "log.h"

SINGLETON_IMPL(Flog)

Flog::Flog()
{
    m_log = logger_create();
    logger_set_remain_days(m_log, -1);
    logger_set_file(m_log, "/var/log/project/project1.log");
    logger_set_max_filesize_by_str(m_log, "1G");
    logger_print(m_log, LOG_LEVEL_INFO, "==========project1 start==========\n");

}

Flog::~Flog()
{
    logger_print(m_log, LOG_LEVEL_INFO, "==========project1 end==========\n\n");
    if(m_log)
    {
        logger_destroy(m_log);
        m_log = nullptr;
    }
}