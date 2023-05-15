#include "mysql_conn_pool.h"

mysql_conn_pool * mysql_conn_pool::getInstance() {
    static mysql_conn_pool connPool;
    return &connPool;
}

void mysql_conn_pool::init(std::string url, std::string usr, std::string passwd, std::string dbname, unsigned port,
                           int maxConn, bool use_log) {
    m_url = url;
    m_usr = usr;
    m_passwd = passwd;
    m_dbname = dbname;
    m_port = port;
    m_max_conn = maxConn;
    m_use_log = use_log;

    for(int i = 0; i < m_max_conn; ++i) {
        MYSQL *conn = nullptr;
        conn = mysql_init(conn);
        if(!conn) {
            LOG_ERROR("MySQL Error");
            throw std::exception();
        }
        conn = mysql_real_connect(conn, m_url.c_str(), usr.c_str(), passwd.c_str(),
                                  dbname.c_str(), m_port, nullptr, 0);
        if(!conn) {
            LOG_ERROR("MySQL Error");
            throw std::exception();
        }

        m_conn_pool.push_back(conn);
    }

    m_sem = sem(m_max_conn);
}

MYSQL *mysql_conn_pool::getConnection() {
    MYSQL *conn = nullptr;

//    if(m_conn_pool.size() == 0)
//        return nullptr;

    m_sem.wait();
    m_mutex.lock();
    conn = m_conn_pool.front();
    m_conn_pool.pop_front();

    m_mutex.unlock();
    return conn;
}

bool mysql_conn_pool::releaseConn(MYSQL *conn) {
    if(!conn) return false;

    m_mutex.lock();
    m_conn_pool.push_back(conn);
    m_mutex.unlock();
    m_sem.post();
    return true;
}

void mysql_conn_pool::destoryPool() {
    m_mutex.lock();
    for(auto iter = m_conn_pool.begin(); iter != m_conn_pool.end(); ++iter)
        mysql_close(*iter);
    m_conn_pool.clear();
    m_mutex.unlock();
}

int mysql_conn_pool::getFreeConnNum() {
    m_mutex.lock();
    unsigned _size = m_conn_pool.size();
    m_mutex.unlock();
    return _size;
}

mysql_conn_pool::~mysql_conn_pool() {
    destoryPool();
}

mysql_conn_RAII::mysql_conn_RAII(MYSQL **conn, mysql_conn_pool *connPool) {
    *conn = connPool->getConnection();
    connRAII = *conn;
    poolRAII = connPool;
}

mysql_conn_RAII::~mysql_conn_RAII() {
    poolRAII->releaseConn(connRAII);
}