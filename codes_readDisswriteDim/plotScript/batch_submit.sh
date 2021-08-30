#!/bin/sh
##-----------------------------------------
sed -i 's/DSCODE/D2p00/g' analysis.py 
python3.7 master_plot.py 
sed -i 's/D2p00/DSCODE/g' analysis.py 
##-----------------------------------------
sed -i 's/DSCODE/D2p20/g' analysis.py 
python3.7 master_plot.py 
sed -i 's/D2p20/DSCODE/g' analysis.py 
##-----------------------------------------
sed -i 's/DSCODE/D2p50/g' analysis.py 
python3.7 master_plot.py 
sed -i 's/D2p50/DSCODE/g' analysis.py 
##-----------------------------------------
sed -i 's/DSCODE/D2p80/g' analysis.py 
python3.7 master_plot.py 
sed -i 's/D2p80/DSCODE/g' analysis.py 
##-----------------------------------------
sed -i 's/DSCODE/D2p90/g' analysis.py 
python3.7 master_plot.py 
sed -i 's/D2p90/DSCODE/g' analysis.py 
##-----------------------------------------
sed -i 's/DSCODE/D2p95/g' analysis.py 
python3.7 master_plot.py 
sed -i 's/D2p95/DSCODE/g' analysis.py 
##-----------------------------------------
sed -i 's/DSCODE/D2p98/g' analysis.py 
python3.7 master_plot.py 
sed -i 's/D2p98/DSCODE/g' analysis.py 
##-----------------------------------------
sed -i 's/DSCODE/D2p99/g' analysis.py 
python3.7 master_plot.py 
sed -i 's/D2p99/DSCODE/g' analysis.py 
##-----------------------------------------
sed -i 's/DSCODE/D3p00/g' analysis.py 
python3.7 master_plot.py 
sed -i 's/D3p00/DSCODE/g' analysis.py 

