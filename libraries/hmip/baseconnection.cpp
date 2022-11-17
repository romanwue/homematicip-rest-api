#include "baseconnection.h"

BaseConnection::BaseConnection()
    : m_restCallRequestCounter(3)
    , m_restCallTimout(6) {
}
