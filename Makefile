LIB=./lib
INCLUDE=./include
SRC=./src
OBJ=./obj

CC=gcc 

FLAGS=  -g -O0
CFLAGS=''

all: libopt-plus sphere

libopt-plus: $(LIB)/libopt-plus.a
	echo "libopt-plus.a built..."

$(LIB)/libopt-plus.a: \
$(OBJ)/opt.o \
$(OBJ)/common.o \
$(OBJ)/function.o \
$(OBJ)/random.o \
$(OBJ)/pso.o \

	ar csr $(LIB)/libopt-plus.a \
$(OBJ)/opt.o \
$(OBJ)/common.o \
$(OBJ)/function.o \
$(OBJ)/random.o \
$(OBJ)/pso.o \

$(OBJ)/opt.o: $(SRC)/opt.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/opt.c -o $(OBJ)/opt.o

$(OBJ)/common.o: $(SRC)/common.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/common.c -o $(OBJ)/common.o

$(OBJ)/function.o: $(SRC)/function.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/function.c -o $(OBJ)/function.o

$(OBJ)/random.o: $(SRC)/random.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/random.c -o $(OBJ)/random.o
	
$(OBJ)/pso.o: $(SRC)/pso.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/pso.c -o $(OBJ)/pso.o

sphere: examples/sphere.c
	gcc $(FLAGS) examples/sphere.c -o examples/bin/sphere -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

clean:
	rm -f $(LIB)/lib*.a; rm -f $(OBJ)/*.o; rm -rf examples/bin/*
