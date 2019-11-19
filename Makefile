CC=gcc
CCFLAGS=-Wall -O2 -pipe -I.
APPNAME=app
LINK=gcc
LINKFLAGS=-lrt
RM=rm

all: drive-serial.o wdl.o
	$(CC) -o $(APPNAME) $(CCFLAGS) drive-serial.o wdl.o $(LINKFLAGS)
drive-serial.o:
	$(CC) -c $(CCFLAGS) drive-serial.c $(LINKFALGS)
wdl.o:
	$(CC) -c $(CCFLAGS) wdl.c $(LINKFLAGS)
clean:
	$(RM) -f *.o
	$(RM) -f $(APPNAME)
