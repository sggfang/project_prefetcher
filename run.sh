#!/bin/bash

# bzip2 gcc bwaves mcf milc
benchmark=(bzip2 gcc bwaves mcf milc zeusmp gromacs leslie3d namd gobmk dealII povray calculix hmmer sjeng GemsFDTD libquantum h264ref tonto lbm omnetpp astar xalancbmk specrand_i specrand_f)
# benchmark=(leslie3d gromacs GemsFDTD xalancbmk mcf sjeng gcc hmmer calculix astar milc povray tonto gobmk)
size=(4 8 16 64)

for s in ${size[@]}
do
		for ele in ${benchmark[@]} 
		do
				# ./build/ARM/gem5.opt configs/spec2k6/run.py --at-instruction --take-checkpoints=100000 --checkpoint-dir=jump_checkpoint/"$ele" -b $ele --l1d_size=64kB --l1i_size="$s"kB --caches --l2cache --l2_size=8192kB

				# ./build/ARM/gem5.opt -d data_jump_"$s"/out_tifs_"$ele" configs/spec2k6/run.py -r 100000 -W 1000000 -I 1000000 --checkpoint-dir=jump_checkpoint/"$ele" --cpu-type=TimingSimpleCPU --restore-with-cpu=DerivO3CPU --l1d_size=64kB --l1i_size="$s"kB --caches --l2cache --l2_size=8192kB -b $ele --l1i-hwp-type TIFSPrefetcher

				./build/ARM/gem5.opt -d data_mem_"$s"/out_tifs_"$ele" configs/spec2k6/run.py -W 50000000 --maxinsts=1000000000 --cpu-type=DerivO3CPU --l1d_size=64kB --l1i_size="$s"kB --caches --l2cache --l2_size=8192kB -b $ele --l1i-hwp-type TIFSPrefetcher


			./build/ARM/gem5.opt -d data_mem_"$s"/out_stride_"$ele" configs/spec2k6/run.py -W 50000000 --maxinsts=1000000000 --cpu-type=DerivO3CPU --l1d_size=64kB --l1i_size="$s"kB --caches --l2cache --l2_size=8192kB -b $ele --l1i-hwp-type StridePrefetcher

		done
done

