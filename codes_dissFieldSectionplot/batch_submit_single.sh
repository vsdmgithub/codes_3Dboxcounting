#!/bin/sh
##-----------------------------------------
sed -i 's/DSCODE/D3p00/g' plotDissFieldSection.py
python3.7 plotDissFieldSection.py 
sed -i 's/D3p00/DSCODE/g' plotDissFieldSection.py

