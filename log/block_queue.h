#ifndef WEBSERVER_BLOCK_QUEUE_H
#define WEBSERVER_BLOCK_QUEUE_H

#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <deque>
#include "_mutex.h"
#include "cond.h"

template <typename T>
class block_queue {
public:
    block_queue(int );
//    ~block_queue();

    void clear();
    bool full();
    bool empty();
    bool front(T &);
    bool back(T &);
    int size();
    int max_size();
    bool push(const T & );
    bool pop(T & );
    bool pop(T &, int );  // 增加超时处理 TODO

private:
    _mutex m_mutex;
    cond m_cond;
    std::deque<T> m_array;
    int m_max_size;

};


#endif //WEBSERVER_BLOCK_QUEUE_H
