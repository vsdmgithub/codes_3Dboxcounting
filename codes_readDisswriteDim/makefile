# ____________________________________________________________________
# 	TYPING 'MAKE' OR 'MAKE EX' WILL CREATE THE EXECUTABLE FILE.
# ____________________________________________________________________

# DEFINE SOME MAKEFILE VARIABLES FOR THE COMPILER AND COMPILER FLAGS
# TO USE MAKEFILE VARIABLES LATER IN THE MAKEFILE: $()
# ____________________________________________________________________
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings

# COMPILER
CC = gcc

# FLAGS
CFLAGS  = -g -Wall
LM = -lm

# TARGET
default: ex

# CLEAN
MKCL=make clean

# RUN
RN=./ex_DSCODE

# COMPILING COMMAND
# ____________________________________________________________________
# To create the executable file count we need the object files
# system_variables.o, main.o
ex:  system_variables.o main.o
	$(CC) $(CFLAGS) -o ex_DSCODE system_variables.o main.o $(LM)
	$(MKCL)
	#$(RN)

# CREATE OBJECTS COMMANDS
# ____________________________________________________________________
# To create the object file, we need source and header files
# system_variables.h, system_variables.c
system_variables.o: system_variables.h system_variables.c
	$(CC) $(CFLAGS) -c system_variables.c $(LM)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LM)

# CLEANING COMMANDS
# ____________________________________________________________________
# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
clean:
	$(RM) *.o *~
