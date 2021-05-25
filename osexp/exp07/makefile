head = vmpr.h
srcs = vmpr.cc
objs = vmpr.o
opts = -w -g -c
all:	vmpr
vmpr:	$(objs)
		g++ $(objs) -o vmpr
vmpr.o:	$(srcs) $(head)
		g++ $(opts) $(srcs)
clean:
		rm vmpr *.o