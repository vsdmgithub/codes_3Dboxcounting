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

# TARGET
default: ex

# CLEAN
MKCL=make clean

# COMPILING COMMAND
# ____________________________________________________________________
# To create the executable file count we need the object files
# foo.o, main.o
ex:  foo.o main.o
	$(CC) $(CFLAGS) -o ex foo.o main.o -lm
	$(MKCL)

# CREATE OBJECTS COMMANDS
# ____________________________________________________________________
# To create the object file, we need source and header files
# foo.h, foo.c
foo.o: foo.h foo.c
	$(CC) $(CFLAGS) -c foo.c -lm

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -lm

# CLEANING COMMANDS
# ____________________________________________________________________
# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
clean:
	$(RM) *.o *~
