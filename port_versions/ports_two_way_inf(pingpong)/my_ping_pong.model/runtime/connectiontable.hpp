

#ifndef CONNECTION_TABBLE_HPP
#define CONNECTION_TABBLE_HPP

#include <atomic>
#include <map>
#include <mutex>


class IIPort;

class ConnectionTable
{
public:
static int REG_AND_GET_NEXT_ID(IIPort*);
static IIPort* GET_CONNECTED_PORT (int portId);
static void CONNECT_PORTS (int portId1, int portId2);

private:
static std::atomic_int PORT_ID;
static std::mutex MU;
static std::map<int,int> CON_TABLE;
static std::map<int,IIPort*> PORT_TABLE;

};

#endif
