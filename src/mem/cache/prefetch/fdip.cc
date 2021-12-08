/**
 * @file
 * FDIP Prefetcher template instantiations.
 */

#include "mem/cache/prefetch/fdip.hh"

#include <cassert>
#include <list>

#include "base/intmath.hh"
#include "base/logging.hh"
#include "base/random.hh"
#include "base/trace.hh"
#include "debug/HWPrefetch.hh"
#include "mem/cache/prefetch/associative_set_impl.hh"
#include "mem/cache/prefetch/setPC.hh"
#include "mem/cache/replacement_policies/base.hh"
#include "params/FDIPPrefetcher.hh"

namespace Prefetcher {

FDIP::FDIP(const FDIPPrefetcherParams *p)
  : Queued(p),
  branchPred(nullptr)
{
        branchPred = p->branchPred;
}

/*void
FDIP::setPC(TheISA::PCState &nextPC) {
    enqueuePC = &nextPC;
    printf("btb returned: %lu\n", enqueuePC->pc());
}*/

void
FDIP::calculatePrefetch(const PrefetchInfo &pfi,
                                    std::vector<AddrPriority> &addresses)
{

        if (setPC::instSeq != -1 && setPC::tid != -1) {
                TheISA::PCState nextPC;
                nextPC = setPC::currentPC;
                branchPred->predict(setPC::instPtr, setPC::instSeq,
                        nextPC, setPC::tid);
                // DPRINTF(Prefetcher,
                //             "[tid:%i] [sn:%llu]\n",
                //             setPC::tid, setPC::instSeq);
                addresses.push_back(AddrPriority(nextPC.pc(), 0));

        }
        if (!setPC::enqueuePC.empty()) {
                for (std::list<Addr>::iterator it = setPC::enqueuePC.begin();
                        it!=setPC::enqueuePC.end(); it++) {
                        addresses.push_back(AddrPriority(*it, 0));
                }
                setPC::enqueuePC.clear();
        }
}

} // namespace prefetcher

Prefetcher::FDIP*
FDIPPrefetcherParams::create(){
                return new Prefetcher::FDIP(this);
}
