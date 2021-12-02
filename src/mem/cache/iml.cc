#include "mem/cache/iml.hh"

std::list<IML::InstructionMissLogEntry> IML::InstructionMissLog;

void
IML::updateInstructionMissLog(Addr addr, bool hit)
{
		auto it = InstructionMissLog.end();
		while(it != InstructionMissLog.begin()){
		if (addr == it->retiredAddress){
					it->hit_from_svb = hit;
		}
		it--;
		}
}

void 
IML::addToInstructionMissLog(Addr addr, bool hit){
		InstructionMissLogEntry entry;
		entry.retiredAddress = addr;
		entry.hit_from_svb = hit;
		InstructionMissLog.push_back(entry);
}
