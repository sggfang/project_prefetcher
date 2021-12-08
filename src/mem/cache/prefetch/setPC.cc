#include "mem/cache/prefetch/setPC.hh"

setPC::setPC()
{
}

std::list<Addr> setPC::enqueuePC;
// Addr setPC::currentPC = -1;
TheISA::PCState setPC::currentPC;
StaticInstPtr setPC::instPtr;
InstSeqNum setPC::instSeq = -1;
ThreadID setPC::tid = -1;
