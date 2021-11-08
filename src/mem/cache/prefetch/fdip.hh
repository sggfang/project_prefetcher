/**
 * @file
 * Describes a FDIP prefetcher.
 */

#ifndef __MEM_CACHE_PREFETCH_FDIP_HH__
#define __MEM_CACHE_PREFETCH_FDIP_HH__

#include <string>
#include <unordered_map>
#include <vector>

#include "base/sat_counter.hh"
#include "base/types.hh"
#include "mem/cache/prefetch/associative_set.hh"
#include "mem/cache/prefetch/queued.hh"
#include "mem/cache/replacement_policies/replaceable_entry.hh"
#include "mem/cache/tags/indexing_policies/set_associative.hh"
#include "mem/packet.hh"

class BaseIndexingPolicy;
class BaseReplacementPolicy;
struct FDIPPrefetcherParams;

namespace Prefetcher {

class FDIP : public Queued
{
  protected:

  public:
    FDIP(const FDIPPrefetcherParams *p);

    theISA::PCState* enqueuePC;

    void setPC(theISA::PCState &nextPC);

    void calculatePrefetch(const PrefetchInfo &pfi,
                           std::vector<AddrPriority> &addresses) override;
};

} // namespace Prefetcher

#endif // __MEM_CACHE_PREFETCH_FDIP_HH__