#ifndef WEBSERVER_SEM_H
#define WEBSERVER_SEM_H

#include <exception>
#include <pthread.h>
#include <semaphore.h>

class sem {
public:
    sem();
    sem(int );
    ~sem();

    bool wait();
    bool post();

private:
    sem_t m_sem; // 信号量
};


#endif //WEBSERVER_SEM_H
