#include "cond.h"

/*
    int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);

    成功时返回 0，失败时返回 errorno
    cond : 创建互斥量时传递保存条件变量的变量地址值，销毁时传递需要销毁的条件变量地址
    attr : 传递即将创建的互斥量属性，没有特别需要指定的属性时传递 NULL
*/
cond::cond() {
    if(pthread_cond_init(&m_cond, NULL) != 0) {
        throw std::exception();
    }
}

cond::~cond() {
    if(pthread_cond_destroy(&m_cond) != 0) {
        throw std::exception();
    }
}

bool cond::wait(pthread_mutex_t *m_mutex) {
    return pthread_cond_wait(&m_cond, m_mutex) == 0;
}

bool cond::time_wait(pthread_mutex_t *m_mutex, struct timespec t) {
    return pthread_cond_timedwait(&m_cond, m_mutex, &t) == 0;
}

bool cond::signal() {
    return pthread_cond_signal(&m_cond) == 0;
}

bool cond::broadcast() {
    return pthread_cond_broadcast(&m_cond) == 0;
}