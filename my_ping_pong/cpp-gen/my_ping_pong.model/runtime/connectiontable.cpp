#include "connectiontable.hpp"
#include <algorithm>

std::atomic_int ConnectionTable::PORT_ID(0);
std::map<int,int> ConnectionTable::CON_TABLE;
std::map<int,IPort*> ConnectionTable::PORT_TABLE;
std::mutex ConnectionTable::MU;


int ConnectionTable::REG_AND_GET_NEXT_ID(IPort* port)
{
int id = PORT_ID;
++PORT_ID;
std::lock_guard<std::mutex> lock(MU);
PORT_TABLE.insert(std::pair<int,IPort*>(id,port));
return id;
}


IPort * ConnectionTable::GET_CONNECTED_PORT (int portId)
{
int id;
if (CON_TABLE.count(portId) > 0)
{
    id = CON_TABLE[portId];
}
else
{
    id =  std::find_if (CON_TABLE.begin(), CON_TABLE.end(), [portId](std::pair<int,int> p) {return p.second == portId;})->first;
}
return PORT_TABLE[id];
}

void ConnectionTable::CONNECT_PORTS (int portId1, int portId2)
{
std::lock_guard<std::mutex> lock(MU);
CON_TABLE.insert(std::pair<int,int>(portId1,portId2));
}
