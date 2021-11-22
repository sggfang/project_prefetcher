#ifndef __SETPC_HH__
#define __SETPC_HH__

#include <list>

#include "base/types.hh"

class setPC
{
        protected:

        public:
                setPC();
                static std::list<Addr> enqueuePC;
};

#endif
