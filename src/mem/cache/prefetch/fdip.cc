/**
 * @file
 * FDIP Prefetcher template instantiations.
 */

#include "mem/cache/prefetch/fdip.hh"

#include <cassert>

#include "base/intmath.hh"
#include "base/logging.hh"
#include "base/random.hh"
#include "base/trace.hh"
#include "debug/HWPrefetch.hh"
#include "mem/cache/prefetch/associative_set_impl.hh"
#include "mem/cache/replacement_policies/base.hh"
#include "params/FDIPPrefetcher.hh"

namespace Prefetcher {

FDIP::FDIP(const FDIPPrefetcherParams *p)
  : Queued(p)
  //enqueuePC(nullptr)
{
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
	if (setPC::enqueuePC != -1) {
		addresses.push_back(AddrPriority(setPC::enqueuePC, 0));
		setPC::enqueuePC = -1;
	}	
}

} // namespace prefetcher

Prefetcher::FDIP* 
FDIPPrefetcherParams::create(){
		return new Prefetcher::FDIP(this);
}
