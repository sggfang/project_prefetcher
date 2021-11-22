all:
	./build/ARM/gem5.opt -d out_fdip configs/spec2k6/run.py -W 10000000 --maxinsts=10000000 --cpu-type=DerivO3CPU --l1d_size=64kB --l1i_size=16kB --caches --l2cache -b gcc --l1i-hwp-type FDIPPrefetcher

