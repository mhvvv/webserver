#ifndef WEBSERVER__MUTEX_H
#define WEBSERVER__MUTEX_H

#include <exception>
#include <pthread.h>
#include <semaphore.h>

class _mutex {
public:
    _mutex();
    ~_mutex();

    bool lock();
    bool unlock();
    pthread_mutex_t* get();

private:
    pthread_mutex_t m_mutex;
};


#endif //WEBSERVER__MUTEX_H
