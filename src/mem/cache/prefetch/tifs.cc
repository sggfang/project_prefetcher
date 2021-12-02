/*
 * Copyright (c) 2018 Inria
 * Copyright (c) 2012-2013, 2015 ARM Limited
 * All rights reserved
 *
 * The license below extends only to copyright in the software and shall
 * not be construed as granting a license to any other intellectual
 * property including but not limited to intellectual property relating
 * to a hardware implementation of the functionality of the software
 * licensed hereunder.  You may use the software subject to the license
 * terms below provided that you ensure that this notice is replicated
 * unmodified and in its entirety in all distributions of the software,
 * modified or unmodified, in source code or in binary form.
 *
 * Copyright (c) 2005 The Regents of The University of Michigan
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

#include "mem/cache/prefetch/tifs.hh"

#include <cassert>
#include <assert.h>

#include "base/intmath.hh"
#include "base/logging.hh"
#include "base/random.hh"
#include "base/trace.hh"
#include "debug/HWPrefetch.hh"
#include "mem/cache/prefetch/associative_set_impl.hh"
#include "mem/cache/replacement_policies/base.hh"
#include "params/TIFSPrefetcher.hh"

namespace Prefetcher {

TIFS::TIFS(const TIFSPrefetcherParams *p)
  : Queued(p),
	// InstructionMissLog(p->InstructionMiss_entries),
	inTable(p->inTable_entries, 
					p->inTable_assoc,
					p->inTable_indexing_policy, 
					p->inTable_replacement_policy,
					IndexTableEntry())
{
}
/*
void 
TIFS::addToInstructionMissLog(Addr addr, bool hit){
		InstructionMissLogEntry entry;
		entry.retiredAddress = addr;
		entry.hit_from_svb = hit;
		InstructionMissLog.push_back(entry);
}

void
TIFS::updateInstructionMissLog(Addr addr, bool hit){
		auto it = InstructionMissLog.end();
		while(it != InstructionMissLog.begin()){
				if (addr == it->retiredAddress){
						it->hit_from_svb = hit;
				}
				it--;
		}
}
*/
void
TIFS::calculatePrefetch(const PrefetchInfo &pfi,
                        std::vector<AddrPriority> &addresses)
{
    if (!pfi.hasPC()) {
        DPRINTF(HWPrefetch, "Ignoring request with no PC.\n");
        return;
    }

    // Get required packet info
    Addr pf_addr = pfi.getPaddr();
    Addr pc = pfi.getPC();
    bool is_secure = pfi.isSecure();

    // Search for entry in the index table
    IndexTableEntry *entry = inTable.findEntry(pf_addr, is_secure);

		if (entry == nullptr) {
				entry = inTable.findVictim(pf_addr);
				if (entry == nullptr){
						printf("entry cannot be nullptr\n");
						assert(false);
				}
				inTable.insertEntry(pf_addr, is_secure,entry);
				entry->address = pf_addr; 
				entry->pc = pc;

				IML::addToInstructionMissLog(pf_addr, false);
    }

    if (true) {
        inTable.accessEntry(entry);
				bool hit_in_log = false;
				auto it = IML::InstructionMissLog.end();
				while (it != IML::InstructionMissLog.begin()){
						it--;
						if (it->retiredAddress == pf_addr){
								addresses.push_back(AddrPriority(pf_addr, 0));
								it++;
								hit_in_log = true;
								break;
						}
				}
				int counter = 1024;
				do{ 
						if (!hit_in_log || !it->hit_from_svb) break;
						addresses.push_back(AddrPriority(it->retiredAddress, 0));
						it++;
						counter--;
				}
				//while(counter!=0);
				while(it != IML::InstructionMissLog.end() && counter!=0);
		}
		// if (addresses.size() != 1) printf("prefetched addr size %lu\n", addresses.size()); 
}

} // namespace Prefetcher

Prefetcher::TIFS* 
TIFSPrefetcherParams::create(){
	return new Prefetcher::TIFS(this);
}
