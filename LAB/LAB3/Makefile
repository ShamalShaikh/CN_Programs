
CC = g++
CFLAGS=-g -Wall
#OBJS=shared_memory.o
EXE= P1.exe P2.exe P3.exe P4.exe

all: $(EXE)

%.exe: %.o  $(OBJS) 
	$(CC) $(CFLAGS) $< $(OBJS) -o $@ -pthread

#%.o: %.c %.h
#	$(CC) $(CFLAGS) -c $< -o $@
	
%.o: %.cpp 
	$(CC) $(CFLAGS) -c $< -o $@ -pthread

clean:
	rm -rf *.dSYM *.o $(EXE)
	

