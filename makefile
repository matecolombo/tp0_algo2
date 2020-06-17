OBJS = tp1_main_v0.o cmdline.o tp1_imagen.o complejo.o
BINARY = tp1
CC = g++
CPPFLAGS = -g -Wall

#Main
all: tp1

#Compiacion de archivos
tp1: $(OBJS)
	$(CC) $(CFLAGS) -o $(BINARY) $(OBJS)

tp1_main_v0.o: tp1_main_v0.cpp tp1_config.h tp1_imagen.h cmdline.h 
#g++ $(CFLAGS) -c tp1_main_v0.cpp

tp1_imagen.o: tp1_imagen.cpp tp1_imagen.h tp1_matrix.h complejo.h tp1_pila.h
#g++ $(CFLAGS) -c tp1_imagen.cpp

cmdline.o: cmdline.cpp cmdline.h 
#g++ $(CFLAGS) -c cmdline.cc

complejo.o: complejo.cpp complejo.h
#g++ $(CFLAGS) -c complejo.cpp

#Limpia archivos temporales
clean:
	rm -f tp1 *.o