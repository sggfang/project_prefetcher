# Run the program  
1. build the program  
```
scons-3 -j 4 ./build/ARM/gem5.opt  
```  
2. run all benchmarks. The data will be placed on current directory.  
```
sh run.sh
```

# Modification of code  
./SimPoint.3.2  
simpoint directory  

./configs/common/Caches.py: 57, 70, 74  
Set the parameters of icache and L2 cache.  

./data*  
All folders started with data are our simulated results.  

./src/mem/AbstractMemory.py: 49  
Set the memory to 3GB  

./src/mem/SimpleMemory.py: 46, 50  
Set the memory bandwidth and access latency  

./src/mem/packet.hh: 322-323  
Add flag to indicate the block is from SVB. This may be used for prefetcher latter.  

./src/mem/cache/Sconscript: 41  

./src/mem/cache/base.cc: 370  
Add blocks to IML when hitting in SVB

./src/mem/cache/base.hh: 1237-1238  
set the address in IML to true when hitting in icache.  

./src/mem/cache/iml.hh iml.cc  
IML data structure used for TIFS  

./src/mem/cache/prefetch/Prefetcher.py: 168, class TIFSPrefetcher
Set the entry number of StridePrefetcher to 32  
Init TIFS prefetcher  

./src/mem/cache/prefetch/Sconscript: 49  

./src/mem/cache/prefetch/base.cc base.hh: Base::PrefetchInfo::PrefetchInfo, Base::probeNotify  

./src/mem/cache/prefetch/queue.cc queue.hh: Queued::checkInQueue  

./src/mem/cache/prefetch/tifs.cc tifs.hh
TIFS prefetcher  
