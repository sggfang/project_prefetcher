#!/bin/bash

# ./build/ARM/gem5.opt -d out_tifs_"$1" configs/spec2k6/run.py -W 10000000 --maxinsts=10000000 --cpu-type=DerivO3CPU --l1d_size=64kB --l1i_size="$2"kB --caches --l2cache -b $1 --l1i-hwp-type TIFSPrefetcher

# ./build/ARM/gem5.opt -d out_baseline_"$1" configs/spec2k6/run.py -W 10000000 --maxinsts=10000000 --cpu-type=DerivO3CPU --l1d_size=64kB --l1i_size="$2"kB --caches --l2cache -b $1 

# bzip2 gcc bwaves mcf milc
benchmark=(bzip2 gcc bwaves mcf milc zeusmp gromacs leslie3d namd gobmk dealII povray calculix hmmer sjeng GemsFDTD libquantum h264ref tonto lbm omnetpp astar wrf sphinx3 xalancbmk specrand_i specrand_f)
size=(4 8 16)

for s in ${size[@]}
do
		for ele in ${benchmark[@]} 
		do
				./build/ARM/gem5.opt -d data_"$s"/out_tifs_"$ele" configs/spec2k6/run.py -W 10000000 --maxinsts=10000000 --cpu-type=DerivO3CPU --l1d_size=64kB --l1i_size="$s"kB --caches --l2cache -b $ele --l1i-hwp-type TIFSPrefetcher

				./build/ARM/gem5.opt -d data_"$s"/out_baseline_"$ele" configs/spec2k6/run.py -W 10000000 --maxinsts=10000000 --cpu-type=DerivO3CPU --l1d_size=64kB --l1i_size="$s"kB --caches --l2cache -b $ele
		done
done

