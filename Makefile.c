#######################################################################
# Homework Assignment 5, for EECS 22, Fall 2017
#
# Author: Tim Schmidt
# Date: 11/09/2017
#
# Makefile: Makefile for HW 5
#
#######################################################################

# Variables
CC = gcc
DEBUG = -g -DDEBUG
CFLAGS = -ansi -Wall -std=c99 -c
LFLAGS = -ansi -Wall

# Default target
all: MovieLab

######################### Generate object files #######################
# Target for MovieLab.o
MovieLab.o: MovieLab.c FileIO.h DIPs.h Image.h ImageList.h Movie.h Constants.h
        $(CC) $(CFLAGS) MovieLab.c -o MovieLab.o

# Target for FileIO.o
FileIO.o: FileIO.c FileIO.h Image.h
        $(CC) $(CFLAGS) FileIO.c -o FileIO.o

# Target for DIPs.o
DIPs.o: DIPs.c DIPs.h Image.h
        $(CC) $(CFLAGS) DIPs.c -o DIPs.o

# Target for Image.o
Image.o: Image.c Image.h
        $(CC) $(CFLAGS) Image.c -o Image.o

# Target for ImageList.o
ImageList.o: ImageList.c ImageList.h Image.h
        $(CC) $(CFLAGS) ImageList.c -o ImageList.o

# Target for Movie.o
Movie.o: Movie.c Movie.h Image.h ImageList.h
        $(CC) $(CFLAGS) Movie.c -o Movie.o

######################### Generate the executable #####################
# Target for MovieLab
MovieLab: MovieLab.o FileIO.o DIPs.o Image.o Movie.o ImageList.o
        $(CC) $(LFLAGS) -lm MovieLab.o FileIO.o DIPs.o Image.o ImageList.o Movie.o -o MovieLab

###############################  others  ##############################
# Target for clean-up
clean:
        rm -f *.o
        rm -f out.yuv
        rm -f MovieLab

