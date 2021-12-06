#include "mem/cache/prefetch/setPC.hh"

setPC::setPC()
{
}

std::list<Addr> setPC::enqueuePC;
Addr setPC::currentPC = -1;
