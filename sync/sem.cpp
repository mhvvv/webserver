#include "sem.h"

/*
  int sem_init(sem_t *sem, int pshared, unsigned int value);

  成功时返回 0 ，失败时返回 errorno
  sem : 创建信号量时保存信号量的变量地址值，销毁时传递需要销毁的信号量变量地址值
  pshared : 传递其他值时，创建可由多个进程共享的信号量；传递 0 时，创建只允许 1 个进程内部使用的信号量。需要完成同一进程的线程同步，故为0
  value : 指定创建信号量的初始值
*/
sem::sem() {
    if(sem_init(&m_sem, 0, 0) != 0) {
        throw std::exception();
    }
}

sem::sem(int num) {
    if(sem_init(&m_sem, 0, num) != 0) {
        throw std::exception();
    }
}

sem::~sem() {
    if(sem_destroy(&m_sem) != 0) {
        throw std::exception();
    }
}

bool sem::wait() {
    return sem_wait(&m_sem) == 0;
}

bool sem::post() {
    return sem_post(&m_sem) == 0;
}




