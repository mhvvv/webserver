#ifndef WEBSERVER_MYSQL_CONN_POOL_H
#define WEBSERVER_MYSQL_CONN_POOL_H

#include <stdio.h>
#include <list>
#include <mysql/mysql.h>
#include <error.h>
#include <string.h>
#include <iostream>
#include <string>
#include "_mutex.h"
#include "log.h"
#include "sem.h"

class mysql_conn_pool {
public:
    MYSQL* getConnection();
    bool releaseConn(MYSQL *conn);
    int getFreeConnNum();
    void destoryPool();

    static mysql_conn_pool *getInstance();

    void init(std::string url, std::string usr, std::string passwd, std::string dbname,
                                            unsigned port, int maxConn, bool use_log);

private:
    mysql_conn_pool() = default;
    ~mysql_conn_pool();

    int m_max_conn;
    _mutex m_mutex;
    std::list<MYSQL* > m_conn_pool;
    sem m_sem;

    std::string m_url;
    unsigned m_port;
    std::string m_usr;
    std::string m_passwd;
    std::string m_dbname;
    bool m_use_log;
};

class mysql_conn_RAII {
public:
    mysql_conn_RAII(MYSQL **conn, mysql_conn_pool *connPool);
    ~mysql_conn_RAII();

private:
    MYSQL *connRAII;
    mysql_conn_pool *poolRAII;
};




#endif //WEBSERVER_MYSQL_CONN_POOL_H
