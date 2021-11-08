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

FDIP::FDIP(const StridePrefetcherParams *p)
  : Queued(p),
  enqueuePC(nullptr)
{
}

void
FDIP::setPC(theISA::PCState &nextPC) {
    enqueuePC = &nextPC;
    printf("btb returned: uld\n", enqueuePC->pc())；
}

void
FDIP::calculatePrefetch(const PrefetchInfo &pfi,
                                    std::vector<AddrPriority> &addresses)
{

}
