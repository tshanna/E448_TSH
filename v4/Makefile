GCC := g++ # macOS users need their compiler here

output := model 

all: main.o Cell.o save.o
	$(GCC) -o $(output) main.o Cell.o save.o

main.o: main.cpp
	$(GCC) -c main.cpp 

Cell.o: Cell.cpp
	$(GCC) -c Cell.cpp
	
save.o: save.cpp
	$(GCC) -c save.cpp 
	
clean:
	rm -f *.o $(output)
	
version:
	cp v$(V)/* . 
	make
