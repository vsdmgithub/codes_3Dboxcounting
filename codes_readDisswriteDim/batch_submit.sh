#!/bin/sh
##-----------------------------------------
sed -i 's/DSCODE/D2p00/g' system_variables.c 
sed -i 's/DSCODE/D2p00/g' makefile
make
sed -i 's/D2p00/DSCODE/g' makefile 
sed -i 's/D2p00/DSCODE/g' system_variables.c 
cp run.sub run_D2p00.sub
sed -i 's/DSCODE/D2p00/g' run_D2p00.sub 
sbatch run_D2p00.sub
##-----------------------------------------
sed -i 's/DSCODE/D2p20/g' system_variables.c 
sed -i 's/DSCODE/D2p20/g' makefile
make
sed -i 's/D2p20/DSCODE/g' makefile 
sed -i 's/D2p20/DSCODE/g' system_variables.c 
cp run.sub run_D2p20.sub
sed -i 's/DSCODE/D2p20/g' run_D2p20.sub 
sbatch run_D2p20.sub
##-----------------------------------------
sed -i 's/DSCODE/D2p50/g' system_variables.c 
sed -i 's/DSCODE/D2p50/g' makefile
make
sed -i 's/D2p50/DSCODE/g' makefile 
sed -i 's/D2p50/DSCODE/g' system_variables.c 
cp run.sub run_D2p50.sub
sed -i 's/DSCODE/D2p50/g' run_D2p50.sub 
sbatch run_D2p50.sub
##-----------------------------------------
sed -i 's/DSCODE/D2p80/g' system_variables.c 
sed -i 's/DSCODE/D2p80/g' makefile
make
sed -i 's/D2p80/DSCODE/g' makefile 
sed -i 's/D2p80/DSCODE/g' system_variables.c 
cp run.sub run_D2p80.sub
sed -i 's/DSCODE/D2p80/g' run_D2p80.sub 
sbatch run_D2p80.sub
##-----------------------------------------
sed -i 's/DSCODE/D2p90/g' system_variables.c 
sed -i 's/DSCODE/D2p90/g' makefile
make
sed -i 's/D2p90/DSCODE/g' makefile 
sed -i 's/D2p90/DSCODE/g' system_variables.c 
cp run.sub run_D2p90.sub
sed -i 's/DSCODE/D2p90/g' run_D2p90.sub 
sbatch run_D2p90.sub
##-----------------------------------------
sed -i 's/DSCODE/D2p95/g' system_variables.c 
sed -i 's/DSCODE/D2p95/g' makefile
make
sed -i 's/D2p95/DSCODE/g' makefile 
sed -i 's/D2p95/DSCODE/g' system_variables.c 
cp run.sub run_D2p95.sub
sed -i 's/DSCODE/D2p95/g' run_D2p95.sub 
sbatch run_D2p95.sub
##-----------------------------------------
sed -i 's/DSCODE/D2p98/g' system_variables.c 
sed -i 's/DSCODE/D2p98/g' makefile
make
sed -i 's/D2p98/DSCODE/g' makefile 
sed -i 's/D2p98/DSCODE/g' system_variables.c 
cp run.sub run_D2p98.sub
sed -i 's/DSCODE/D2p98/g' run_D2p98.sub 
sbatch run_D2p98.sub
##-----------------------------------------
sed -i 's/DSCODE/D2p99/g' system_variables.c 
sed -i 's/DSCODE/D2p99/g' makefile
make
sed -i 's/D2p99/DSCODE/g' makefile 
sed -i 's/D2p99/DSCODE/g' system_variables.c 
cp run.sub run_D2p99.sub
sed -i 's/DSCODE/D2p99/g' run_D2p99.sub 
sbatch run_D2p99.sub
##-----------------------------------------
sed -i 's/DSCODE/D3p00/g' system_variables.c 
sed -i 's/DSCODE/D3p00/g' makefile
make
sed -i 's/D3p00/DSCODE/g' makefile 
sed -i 's/D3p00/DSCODE/g' system_variables.c 
cp run.sub run_D3p00.sub
sed -i 's/DSCODE/D3p00/g' run_D3p00.sub 
sbatch run_D3p00.sub









