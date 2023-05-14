#ifndef WEBSERVER_LOG_H
#define WEBSERVER_LOG_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <stdarg.h>
#include <pthread.h>
#include "block_queue.h"

class Log {
public:
    // 单例模式 - 懒汉模式,  C++11以后，由编译器保证线程安全
    static Log *get_instance();
    static void *flush_log_thread(void *);

    /**
     *
     * @param file_name 日志 路径/文件名
     * @param use_log 是否启用日至
     * @param log_buf_size 日至缓冲区大小
     * @param split_lines 最大行数
     * @param max_queue_size 最长日志条队列
     * @return
     */
    bool init(const char *file_name, bool use_log, int log_buf_size = 8192,
                int split_lines = 5000000, int max_queue_size = 0);

    void write_log(int level, const char *format, ...);

    void flush(void);

private:
    Log();
    virtual ~Log();
    void *async_write_log();

    char dir_name[128]; //路径名
    char log_name[128]; //log文件名
    int m_split_lines;  //日志最大行数
    int m_log_buf_size; //日志缓冲区大小
    long long m_count;  //日志行数记录
    int m_today;        //因为按天分类,记录当前时间是那一天
    FILE *m_fp;         //打开log的文件指针
    char *m_buf;
    block_queue<std::string> *m_log_queue; //阻塞队列
    bool m_is_async;                  //是否同步标志位
    pthread_t p_id;

    _mutex m_mutex;
    int m_use_log; //开启日志

};

Log *Log::get_instance() {
    static Log instance;
    return &instance;
}

void *Log::flush_log_thread(void *args) {
    Log::get_instance()->async_write_log();
}


#define LOG_DEBUG(format, ...) if(m_use_log) {Log::get_instance()->write_log(0, format, ##__VA_ARGS__); Log::get_instance()->flush();}
#define LOG_INFO(format, ...) if(m_use_log) {Log::get_instance()->write_log(1, format, ##__VA_ARGS__); Log::get_instance()->flush();}
#define LOG_WARN(format, ...) if(m_use_log) {Log::get_instance()->write_log(2, format, ##__VA_ARGS__); Log::get_instance()->flush();}
#define LOG_ERROR(format, ...) if(m_use_log) {Log::get_instance()->write_log(3, format, ##__VA_ARGS__); Log::get_instance()->flush();}


#endif //WEBSERVER_LOG_H
