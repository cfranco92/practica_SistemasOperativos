
ejecutable: ctrlsis.o ctrleval.o evaluador.o
	g++ -g -o ctrlsis ctrlsis.o
	g++ -g -o ctrleval ctrleval.o
	g++ -g -o evaluador evaluador.o

ctrlsis.o: ctrlsis.cpp

ctrleval.o: ctrleval.cpp

evaluador.o: evaluador.cpp

clean:
	rm -f *.o
	rm -f ctrlsis
	rm -f ctrleval
	rm -f evaluador
