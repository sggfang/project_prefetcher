#ifndef __SETPC_HH__
#define __SETPC_HH__

#include <list>

#include "arch/decoder.hh"
#include "arch/utility.hh"
#include "base/statistics.hh"
#include "base/types.hh"
#include "config/the_isa.hh"
#include "cpu/pc_event.hh"
#include "cpu/pred/bpred_unit.hh"
#include "cpu/timebuf.hh"
#include "cpu/translation.hh"
#include "enums/FetchPolicy.hh"
#include "mem/packet.hh"
#include "mem/port.hh"
#include "sim/eventq.hh"
#include "sim/probe/probe.hh"

class setPC
{
        protected:

        public:
                setPC();
                static std::list<Addr> enqueuePC;
                // static Addr currentPC;
                static TheISA::PCState currentPC;
                static StaticInstPtr instPtr;
                static InstSeqNum instSeq;
                static ThreadID tid;
};

#endif
