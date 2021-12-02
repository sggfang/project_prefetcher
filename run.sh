#!/bin/bash

# ./build/ARM/gem5.opt -d out_tifs_"$1" configs/spec2k6/run.py -W 10000000 --maxinsts=10000000 --cpu-type=DerivO3CPU --l1d_size=64kB --l1i_size="$2"kB --caches --l2cache -b $1 --l1i-hwp-type TIFSPrefetcher

# ./build/ARM/gem5.opt -d out_baseline_"$1" configs/spec2k6/run.py -W 10000000 --maxinsts=10000000 --cpu-type=DerivO3CPU --l1d_size=64kB --l1i_size="$2"kB --caches --l2cache -b $1 

benchmark=(bzip2 gcc bwaves gamess mcf milc zeusmp gromacs cactusADM leslie3d namd gobmk dealII soplex povray calculix hmmer sjeng GemsFDTD libquantum h264ref tonto lbm omnetpp astar wrf sphinx3 xalancbmk specrand_i specrand_f)
counter=6

 for ele in ${benchmark[@]} 
 do
	#	./build/ARM/gem5.opt -d data/out_tifs_"$ele" configs/spec2k6/run.py -W 10000000 --maxinsts=10000000 --cpu-type=DerivO3CPU --l1d_size=64kB --l1i_size="$1"kB --caches --l2cache -b $ele --l1i-hwp-type TIFSPrefetcher

		./build/ARM/gem5.opt -d data/out_baseline_"$ele" configs/spec2k6/run.py -W 10000000 --maxinsts=10000000 --cpu-type=DerivO3CPU --l1d_size=64kB --l1i_size="$1"kB --caches --l2cache -b $ele
		counter=`expr $counter - 1`
		echo $counter
		if [ "$counter" == 0 ]; then
				break
		fi
done


