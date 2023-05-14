#ifndef WEBSERVER_MUTEX_H
#define WEBSERVER_MUTEX_H

#include <exception>
#include <pthread.h>
#include <semaphore.h>

class mutex {
public:
    mutex();
    ~mutex();

    bool lock();
    bool unlock();
    pthread_mutex_t* get();

private:
    pthread_mutex_t m_mutex;
};


#endif //WEBSERVER_MUTEX_H
