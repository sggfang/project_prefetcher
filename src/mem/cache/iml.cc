#include "mem/cache/iml.hh"

std::list<IML::InstructionMissLogEntry> IML::InstructionMissLog;

void
IML::updateInstructionMissLog(Addr addr, bool hit)
{
		auto it = InstructionMissLog.end();
		int temp_num = iml_size;
		while(it != InstructionMissLog.begin() && temp_num!=0){
				if (addr == it->retiredAddress){
						it->hit_from_svb = hit;
						break;
				}
				it--;
				temp_num--;
		}
}

void 
IML::addToInstructionMissLog(Addr addr, bool hit){
		InstructionMissLogEntry entry;
		entry.retiredAddress = addr;
		entry.hit_from_svb = hit;
		InstructionMissLog.push_back(entry);
}
