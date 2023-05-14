#include "mutex.h"

/*
    int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);

    成功时返回 0，失败时返回 errorno
    mutex : 创建互斥量时传递保存互斥量的变量地址值，销毁时传递需要销毁的互斥量地址
    attr : 传递即将创建的互斥量属性，没有特别需要指定的属性时传递 NULL
*/
mutex::mutex() {
    if(pthread_mutex_init(&m_mutex, NULL) != 0) {
        throw std::exception();
    }
}

mutex::~mutex() {
    if(pthread_mutex_destroy(&m_mutex) != 0) {
        throw std::exception();
    }
}

bool mutex::lock() {
    return pthread_mutex_lock(&m_mutex) == 0;
}

bool mutex::unlock() {
    return pthread_mutex_unlock(&m_mutex) == 0;
}

pthread_mutex_t* mutex::get() {
    return &m_mutex;
}