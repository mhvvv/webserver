#ifndef WEBSERVER_COND_H
#define WEBSERVER_COND_H

#include <exception>
#include <pthread.h>
#include <semaphore.h>

class cond {
public:
    cond();
    ~cond();

    bool wait(pthread_mutex_t *);
    bool time_wait(pthread_mutex_t *, struct timespec);
    bool signal();
    bool broadcast();

private:
    pthread_cond_t m_cond;
};


#endif //WEBSERVER_COND_H
