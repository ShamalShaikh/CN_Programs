
CC = g++
CFLAGS=-g -Wall
#OBJS=shared_memory.o
EXE= C1.exe C2.exe C3.exe S.exe

all: $(EXE)

%.exe: %.o $(OBJS)
	$(CC) $(CFLAGS) $< $(OBJS) -o $@

#%.o: %.c %.h
#	$(CC) $(CFLAGS) -c $< -o $@
	
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@	

clean:
	rm -rf *.dSYM *.o $(EXE)
	

