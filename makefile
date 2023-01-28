src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src))

all: dijkstra

dijkstra: main.o graph.o minheap.o
	g++ main.o graph.o minheap.o -o dijkstra -Wall

%.o:%.c
	gcc -c $< -Wall

.PHONY: clean all
clean: 
	-rm -rf dijkstra $(obj)
