#ifndef LOG_H
#define LOG_H

#include "hv/hlog.h"
#include "hv/singleton.h"
#include "sys/syscall.h"

class Flog
{
    SINGLETON_DECL(Flog);
private:
    logger_t* m_log = nullptr;

public:
    Flog();
    ~Flog();
    logger_t* logger(){return m_log;}
    void set_level(int level){logger_set_level(m_log, level);}

};

#define FSLOGE(fmt, ...) if(Flog::instance()->logger()) logger_print(Flog::instance()->logger(), LOG_LEVEL_ERROR, "%ld " fmt " [%s:%d:%s]\n", syscall(SYS_gettid), ## __VA_ARGS__, __FILENAME__, __LINE__, __FUNCTION__)
#define FSLOGI(fmt, ...) if(Flog::instance()->logger()) logger_print(Flog::instance()->logger(), LOG_LEVEL_INFO,  "%ld " fmt " [%s:%d:%s]\n", syscall(SYS_gettid), ## __VA_ARGS__, __FILENAME__, __LINE__, __FUNCTION__)
#define FSLOGD(fmt, ...) if(Flog::instance()->logger()) logger_print(Flog::instance()->logger(), LOG_LEVEL_DEBUG, "%ld " fmt " [%s:%d:%s]\n", syscall(SYS_gettid), ## __VA_ARGS__, __FILENAME__, __LINE__, __FUNCTION__)

#endif