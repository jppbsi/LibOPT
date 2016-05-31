LIB=./lib
INCLUDE=./include
SRC=./src
OBJ=./obj

CC=gcc 

FLAGS=  -g -O0
CFLAGS=''

all: libopt-plus

libopt-plus: $(LIB)/libopt-plus.a
	echo "libopt-plus.a built..."

$(LIB)/libopt-plus.a: \
$(OBJ)/opt.o \
$(OBJ)/common.o \
$(OBJ)/pso.o \

	ar csr $(LIB)/libopt-plus.a \
$(OBJ)/opt.o \
$(OBJ)/common.o \
$(OBJ)/pso.o \

$(OBJ)/opt.o: $(SRC)/opt.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/opt.c -o $(OBJ)/opt.o

$(OBJ)/common.o: $(SRC)/common.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/common.c -o $(OBJ)/common.o

$(OBJ)/pso.o: $(SRC)/pso.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/pso.c -o $(OBJ)/pso.o

clean:
	rm -f $(LIB)/lib*.a; rm -f $(OBJ)/*.o
