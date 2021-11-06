/**
 * Copyright (c) 2019 Metempsy Technology Consulting
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

 /**
  * Implementation of the temporal instruction fetch Streaming Prefetcher (STeMS)
  * Reference:
  *    Temporal Instruction Fetch Stream.
  *	Michael Ferdman1 3, Thomas F. Wenisch2,
  *	Anastasia Ailamaki1 3, Babak Falsafi3
  *	 and Andreas Moshovos4
	*	 https://web.eecs.umich.edu/~twenisch/papers/micro08.pdf
	*
  * Notes:
  * - The functionality described in the paper as Streamed Value Buffer (SVB)
  *   is not implemented here, as this is handled by the QueuedPrefetcher class
  */

#ifndef __MEM_CACHE_PREFETCH_TIFS_HH__
#define __MEM_CACHE_PREFETCH_TIFS_HH__

#include <vector>
#include <unordered_map>
#include <string>

#include "base/circular_queue.hh"
#include "base/sat_counter.hh"
#include "mem/cache/prefetch/associative_set.hh"
#include "mem/cache/prefetch/queued.hh"

struct TIFSPrefetcherParams;

namespace Prefetcher {

class TIFS : public Queued
{
  /* data type of instruction miss log entry*/
  struct InstructionMissLogEntry{
		Addr retiredAddress;
		bool hit_from_svb;
  };
	
	CircularQueue<InstructionMissLogEntry> InstructionMissLog;

	void addToInstructionMissLog(Addr addr, bool hit);
	 
	struct IndexTableEntry:public TaggedEntry{
		Addr address;

		IndexTableEntry():TaggedEntry(),address(0){
		
		}

		void invalidate() override{
			TaggedEntry::invalidate();
			address = 0;				
		}	
	};
	
	AssociativeSet<IndexTableEntry> inTable;
	// std::unordered_map<int, INTable> inTables;

	// INTable* findIndexTable(int core_num);
		
  public:
    TIFS(const TIFSPrefetcherParams* p);
    ~TIFS() = default;

    void calculatePrefetch(const PrefetchInfo &pfi,
                           std::vector<AddrPriority> &addresses) override;
};

} // namespace Prefetcher

#endif//__MEM_CACHE_PREFETCH_TIFS_HH__
