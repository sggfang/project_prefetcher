#ifndef __IML_HH__
#define __IML_HH__
#define iml_size 1024

#include <list>
#include "base/circular_queue.hh"
#include "base/types.hh"

class IML{
public:
IML(){}

struct InstructionMissLogEntry{
				Addr retiredAddress;
				bool hit_from_svb;
};

static std::list<InstructionMissLogEntry> InstructionMissLog;

static void updateInstructionMissLog(Addr addr, bool hit);

static void addToInstructionMissLog(Addr addr, bool hit);

};


#endif
