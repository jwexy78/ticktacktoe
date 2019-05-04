CC=g++
CFLAGS=-std=c++11
DEPS=$(wildcard *.cpp *.h)

SHAREDLIBSROOT=../sharedlibs

include $(SHAREDLIBSROOT)/catch/rules.mk
include $(SHAREDLIBSROOT)/hasmethod/rules.mk

all: main.out test.out

main.out: $(DEPS)
	$(CC) $(CFLAGS) $(IFLAGS) main.cpp -o $@

test.out: $(DEPS)
	$(CC) $(CFLAGS) $(IFLAGS) test.cpp -o $@

