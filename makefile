#-------------------------------------------------#
# Carlos Daniel de Sousa Pinho       2014208236   #
# Dinis Coelho Marques               2014206409   #
#-------------------------------------------------#


main: main.o atendimento.o listas.o ficheiros.o
	gcc -o main main.o atendimento.o listas.o ficheiros.o
main.o: main.c header.h
	gcc -c main.c
atendimento.o: atendimento.c header.h
	gcc -c atendimento.c
listas.o: listas.c header.h
	gcc -c listas.c
ficheiros.o: ficheiros.c header.h
	gcc -c ficheiros.c