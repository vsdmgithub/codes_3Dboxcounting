#!/bin/sh
sed -i 's/DSCODE/D3p00/g' system_variables.c 
sed -i 's/DSCODE/D3p00/g' makefile
make
sed -i 's/D3p00/DSCODE/g' makefile 
sed -i 's/D3p00/DSCODE/g' system_variables.c 
cp run.sub run_D3p00.sub
sed -i 's/DSCODE/D3p00/g' run_D3p00.sub 
sbatch run_D3p00.sub









