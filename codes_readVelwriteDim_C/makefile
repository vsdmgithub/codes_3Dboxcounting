# Makefile for box-counting algorithm

# COMPILER
CC = gcc
CF = gfortran

# FLAGS
CFLAGS  = -g -Wall
LM = -lm

# LIBRARY LOCATION
# lb_lc= -Wall -I/home/sugan/fftw/include
LB_LOC= -I/home/coco/fftw/include

# LIBRARY PATH
# lb_fftw=-L/home/sugan/fftw/lib -lfftw3 -lm
LB_PATH=-L/home/coco/fftw/lib -lfftw3 -lm

# FILES
sys_fun =system_functions.c
sys_for =system_readVelocityFortran.f90
prog    =main.c

# OBJECTS
obj=system_functions.o\
		  main.o\

# TARGET
# default: ex

# CLEAN
MKCL=make clean

# RUN
RN=./ex

# COMPILING COMMAND
ex:
	$(CC) $(CFLAGS) $(LB_LOC) -c $(sys_fun) $(LB_PATH)
	$(CC) $(CFLAGS) $(LB_LOC) -c $(prog) $(LB_PATH)
	$(CF) $(LB_LOC) $(obj) $(sys_for) $(LB_PATH) -o ex
	$(RN)

# CLEANING COMMANDS
# ____________________________________________________________________
clean:
	$(RM) *.o *.mod *~
