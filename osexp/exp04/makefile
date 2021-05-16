hdrs = my_ipc.h
opts = -g -c
c_src = smoker.c my_ipc.c
c_obj = smoker.o my_ipc.o
p_src = producer.c my_ipc.c
p_obj = producer.o my_ipc.o

all:	producer smoker
smoker:	$(c_obj)
			gcc $(c_obj) -o smoker
smoker.o:	$(c_src) $(hdrs)
			gcc $(opts) $(c_src)
producer:	$(p_obj)
			gcc $(p_obj) -o producer
producer.o:	$(p_src) $(hdrs)
			gcc $(opts) $(p_src)
clean:
			rm smoker producer *.o