#!/bin/sh
sed -i 's/DSCODE/D2p50/g' main_code.f90 
sed -i 's/DSCODE/D2p50/g' makefile
make
sed -i 's/D2p50/DSCODE/g' makefile 
sed -i 's/D2p50/DSCODE/g' main_code.f90 
cp run.sub run_D2p50.sub
sed -i 's/DSCODE/D2p50/g' run_D2p50.sub 
sbatch run_D2p50.sub
##----------------------------------------
sed -i 's/DSCODE/D2p80/g' main_code.f90 
sed -i 's/DSCODE/D2p80/g' makefile
make
sed -i 's/D2p80/DSCODE/g' makefile 
sed -i 's/D2p80/DSCODE/g' main_code.f90 
cp run.sub run_D2p80.sub
sed -i 's/DSCODE/D2p80/g' run_D2p80.sub 
sbatch run_D2p80.sub
##----------------------------------------
sed -i 's/DSCODE/D2p90/g' main_code.f90 
sed -i 's/DSCODE/D2p90/g' makefile
make
sed -i 's/D2p90/DSCODE/g' makefile 
sed -i 's/D2p90/DSCODE/g' main_code.f90 
cp run.sub run_D2p90.sub
sed -i 's/DSCODE/D2p90/g' run_D2p90.sub 
sbatch run_D2p90.sub
##----------------------------------------
sed -i 's/DSCODE/D2p95/g' main_code.f90 
sed -i 's/DSCODE/D2p95/g' makefile
make
sed -i 's/D2p95/DSCODE/g' makefile 
sed -i 's/D2p95/DSCODE/g' main_code.f90 
cp run.sub run_D2p95.sub
sed -i 's/DSCODE/D2p95/g' run_D2p95.sub 
sbatch run_D2p95.sub
##----------------------------------------
sed -i 's/DSCODE/D2p98/g' main_code.f90 
sed -i 's/DSCODE/D2p98/g' makefile
make
sed -i 's/D2p98/DSCODE/g' makefile 
sed -i 's/D2p98/DSCODE/g' main_code.f90 
cp run.sub run_D2p98.sub
sed -i 's/DSCODE/D2p98/g' run_D2p98.sub 
sbatch run_D2p98.sub
##----------------------------------------
sed -i 's/DSCODE/D2p99/g' main_code.f90 
sed -i 's/DSCODE/D2p99/g' makefile
make
sed -i 's/D2p99/DSCODE/g' makefile 
sed -i 's/D2p99/DSCODE/g' main_code.f90 
cp run.sub run_D2p99.sub
sed -i 's/DSCODE/D2p99/g' run_D2p99.sub 
sbatch run_D2p99.sub
##----------------------------------------
sed -i 's/DSCODE/D3p00/g' main_code.f90 
sed -i 's/DSCODE/D3p00/g' makefile
make
sed -i 's/D3p00/DSCODE/g' makefile 
sed -i 's/D3p00/DSCODE/g' main_code.f90 
cp run.sub run_D3p00.sub
sed -i 's/DSCODE/D3p00/g' run_D3p00.sub 
sbatch run_D3p00.sub
##----------------------------------------
