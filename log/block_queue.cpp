#include "block_queue.h"

template <typename T>
block_queue<T>::block_queue(int max_size) {
    if (max_size <= 0) {
        throw std::exception();
    }

    m_max_size = max_size;
}

template <typename T>
void block_queue<T>::clear() {
    m_mutex.lock();
    m_array.clear();
    m_mutex.unlock();
}

template <typename T>
bool block_queue<T>::full() {
    m_mutex.lock();
    bool isFull = m_array.size() == m_max_size;
    m_mutex.unlock();
    return isFull;
}

template <typename T>
bool block_queue<T>::empty() {
    m_mutex.lock();
    bool isEmpty = m_array.size() == 0;
    m_mutex.unlock();
    return isEmpty;
}

template <typename T>
bool block_queue<T>::front(T &val) {
    m_mutex.unlock();

    if(m_array.size() == 0) {
        val = nullptr;
        m_mutex.unlock();
        return false;
    }

    val = m_array.front();
    m_mutex.unlock();
    return true;
}

template <typename T>
bool block_queue<T>::back(T &val) {
    m_mutex.unlock();

    if(m_array.size() == 0) {
        val = nullptr;
        m_mutex.unlock();
        return false;
    }

    val = m_array.back();
    m_mutex.unlock();
    return true;
}

template <typename T>
int block_queue<T>::size() {
    int _size;
    m_mutex.lock();
    _size = m_array.size();
    m_mutex.unlock();
    return _size;
}

template <typename T>
int block_queue<T>::max_size() {
    return max_size;
}

template <typename T>
bool block_queue<T>::push(const T &val) {
    m_mutex.lock();
    if(m_array.size() == m_max_size) {
        m_cond.broadcast();
        m_mutex.unlock();
        return false;
    }

    m_array.push_back(val);
    m_cond.broadcast();
    m_mutex.unlock();
}

template <typename T>
bool block_queue<T>::pop(T& item) {
    m_mutex.lock();
    while(m_array.size() <= 0) {
        if(m_cond.wait(m_mutex.get()) != 0) {
            m_mutex.unlock();
            return false;
        }
    }
    item = m_array.front();
    m_array.pop_front();
    m_mutex.unlock();
    return true;
}

//template <typename T>
//bool block_queue<T>::pop(T& item, int ms_timeout) {
//    struct timespec t = {0, 0};
//    struct timeval now = {0, 0};
//    gettimeofday(&now, NULL);
//    m_mutex.lock();
//    if(m_array.size())
//
//
//}





