#!/bin/bash

./build/ARM/gem5.opt -d out_tifs_"$1" configs/spec2k6/run.py -W 10000000 --maxinsts=10000000 --cpu-type=DerivO3CPU --l1d_size=64kB --l1i_size="$2"kB --caches --l2cache -b $1 --l1i-hwp-type TIFSPrefetcher

# ./build/ARM/gem5.opt -d out_baseline configs/spec2k6/run.py -W 10000000 --maxinsts=10000000 --cpu-type=DerivO3CPU --l1d_size=64kB --l1i_size="$2"kB --caches --l2cache -b $1 
