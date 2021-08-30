#!/bin/sh
##-----------------------------------------
sed -i 's/DSCODE/D3p00/g' analysis.py 
python3.7 master_plot.py 
##python3.7 analysis.py 
sed -i 's/D3p00/DSCODE/g' analysis.py 

