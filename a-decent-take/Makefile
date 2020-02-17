.PHONY: ib clean all

all: clean ib

LIBS=-pthread -lrdmacm -libverbs

CC=gcc
C_FLAGS=-Wall -Werror -O2
C_SRCS=
C_OBJS=$(C_SRCS:.c=.o)

CXX=g++
CXX_FLAGS=-Wall -Werror -O2
CXX_SRCS=main.cc ib.cc
CXX_OBJS=$(CXX_SRCS:.cc=.o)

HEADER_FLAGS=-I.

.c.o:
	$(CC) $(C_FLAGS) $(HEADER_FLAGS) -c -o $@ $<

.cc.o:
	$(CXX) $(CXX_FLAGS) $(HEADER_FLAGS) -c -o $@ $<

ib: $(OBJS) $(CXX_OBJS)
	$(CXX) $(C_FLAGS) $(HEADER_FLAGS) -o $@ $^ $(LIBS)
	
clean:
	rm -rf *.o ib
