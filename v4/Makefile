GCC := g++ # macOS users need their compiler here
CFLAGS := -std=c++11 -m64

CC := $(GCC) $(CFLAGS)

output := model 

all: main.o Cell.o save.o
	$(CC) -o $(output) main.o Cell.o save.o

main.o: main.cpp
	$(CC) -c main.cpp 

Cell.o: Cell.cpp
	$(CC) -c Cell.cpp
	
save.o: save.cpp
	$(CC) -c save.cpp 
	
clean:
	rm -f *.o $(output)
	
version:
	cp v$(V)/* . 
	make
