# Makefile script for uthreads.

CC      =  g++
FLAGS   = -Wall  -g
CFLAGS  = -std=c++14 
LIBS    = -Iinclude
OBJS    = thread.o scheduler.o logger.o

all:    ${OBJS}
        ${CC} ${CFLAGS} ${OBJS} ${LIBS} -ldl -lm src/uthreads.cpp -o uthreads
        -rm *.o

scheduler.o:
        ${CC} ${CFLAGS} ${LIBS}  -c -o scheduler.o src/scheduler.cpp

thread.o:
        ${CC} ${CFLAGS} ${LIBS}  -c -o thread.o src/thread.cpp

logger.o:
        ${CC} ${CFLAGS} ${LIBS}  -c -o logger.o src/logger.cpp

clean:
        rm -vf *.o 
        rm -rf uthreads
