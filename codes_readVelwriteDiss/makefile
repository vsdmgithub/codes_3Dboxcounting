# MAKEFILE FOR DISSIPATION FIELD CALC.

# COMPILER
cc=gfortran

# LIBRARY LOCATION
lb_lc= -I/home/ssray/3D_NS_Decimated_Multifractal_Analysis/Analysis/opt/fftw/3.3.8/include

#
# LIBRARY FILE
lb_fftw=-L/home/ssray/3D_NS_Decimated_Multifractal_Analysis/Analysis/opt/fftw/3.3.8/lib -lfftw3 -lm

# PROGRAM
program=main_code.f90

# MODULES
timer_mod          =system_timer.f90
fft_mod            =system_fftw_adv.f90
constants_mod      =system_constants.f90
auxilaries_mod     =system_auxilaries.f90
basicvariables_mod =system_basicvariables.f90
main_mod           =system_readVelwriteDiss.f90

# OBJECTS
obj=system_timer.o\
	system_fftw_adv.o\
	system_constants.o\
	system_auxilaries.o\
	system_basicvariables.o\
	system_readVelwriteDiss.o\

# EXECUTABLE
run=./ex_DSCODE

# CLEAN COMMANDS
rmex=rm ex

mkcl=make cl
#----------------------------end-------

# MAKEFILE
# ---------------------------start-----
ex:$(ob)
	$(cc) $(lb_lc) -c $(fft_mod) $(lb_fftw)
	$(cc) -c $(timer_mod)
	$(cc) -c $(constants_mod)
	$(cc) -c $(auxilaries_mod)
	$(cc) -c $(basicvariables_mod)
	$(cc) -c $(main_mod)

	$(cc) $(lb_lc) $(program) $(obj) $(lb_fftw) -o ex_DSCODE
	$(mkcl)
	# $(run)

#----------------------------end-------

# CLEANING
# ---------------------------start-----
clean:
	rm ex
	clear
cl:
	rm *.mod
	rm *.o
	rm *.err
	rm *.out	
#----------------------------end-------
