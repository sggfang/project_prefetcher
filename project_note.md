# How to use checkpoint on DerivO3CPU?  

*Create checkpoint at 10000 instruction*  
./build/ARM/gem5.opt configs/spec2k6/run.py --maxinsts=250000 --cpu-type=DerivO3CPU --l1d_size=64kB --l1i_size=16kB --caches --l2cache --checkpoint-dir=./checkpoints --at-instruction --take-checkpoints=10000 -b gcc  
  
*Restore from checkpoint*  
./build/ARM/gem5.opt configs/spec2k6/run.py -b gcc --at-instruction -r 10000 -I 10000 --l1d_size=64kB --l1i_size=16kB --caches --l2cache --checkpoint-dir=./checkpoints  

*Reference*    
https://www.gem5.org/documentation/general_docs/checkpoints/  
https://gem5-users.gem5.narkive.com/F0rkgfb8/question-on-creating-restoring-checkpoint-for-a-specific-number-of-instructions  
https://www.cnblogs.com/lcchuguo/p/4634147.html  

