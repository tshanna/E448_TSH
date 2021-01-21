GCC := g++ # macOS users need their compiler here

output := model 

all: main.o Cell.o 
	$(GCC) -o $(output) main.o Cell.o

main.o: main.cpp
	$(GCC) -c main.cpp 

Cell.o: Cell.cpp
	$(GCC) -c Cell.cpp
	
clean:
	rm -f *.o $(output)