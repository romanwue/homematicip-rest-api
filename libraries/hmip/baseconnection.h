#ifndef BASECONNECTION_H
#define BASECONNECTION_H

#include <string>

class BaseConnection {
public:
    BaseConnection();

private:
    std::string m_auth_token;
    std::string m_clientauth_token;
    std::string m_urlREST;
    std::string m_urlWebSocket;
    uint32_t m_restCallRequestCounter;
    uint32_t m_restCallTimout;
};

#endif // BASECONNECTION_H
