LIB=./lib
INCLUDE=./include
SRC=./src
OBJ=./obj

CC=gcc 

FLAGS=  -g -O0
CFLAGS=''

all: libopt-plus sphere rosenbrock dixon_price

libopt-plus: $(LIB)/libopt-plus.a
	echo "libopt-plus.a built..."

$(LIB)/libopt-plus.a: \
$(OBJ)/common.o \
$(OBJ)/function.o \
$(OBJ)/random.o \
$(OBJ)/pso.o \
$(OBJ)/ba.o \
$(OBJ)/fpa.o \
$(OBJ)/fa.o \

	ar csr $(LIB)/libopt-plus.a \
$(OBJ)/common.o \
$(OBJ)/function.o \
$(OBJ)/random.o \
$(OBJ)/pso.o \
$(OBJ)/ba.o \
$(OBJ)/fpa.o \
$(OBJ)/fa.o \

$(OBJ)/common.o: $(SRC)/common.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/common.c -o $(OBJ)/common.o

$(OBJ)/function.o: $(SRC)/function.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/function.c -o $(OBJ)/function.o

$(OBJ)/random.o: $(SRC)/random.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/random.c -o $(OBJ)/random.o
	
$(OBJ)/pso.o: $(SRC)/pso.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/pso.c -o $(OBJ)/pso.o

$(OBJ)/ba.o: $(SRC)/ba.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/ba.c -o $(OBJ)/ba.o

$(OBJ)/fpa.o: $(SRC)/fpa.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/fpa.c -o $(OBJ)/fpa.o

$(OBJ)/fa.o: $(SRC)/fa.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/fa.c -o $(OBJ)/fa.o

sphere: examples/sphere.c
	$(CC) $(FLAGS) examples/sphere.c -o examples/bin/sphere -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

rosenbrock: examples/rosenbrock.c
	$(CC) $(FLAGS) examples/rosenbrock.c -o examples/bin/rosenbrock -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

dixon_price: examples/dixon_price.c
	$(CC) $(FLAGS) examples/dixon_price.c -o examples/bin/dixon_price -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

clean:
	rm -f $(LIB)/lib*.a; rm -f $(OBJ)/*.o; rm -rf examples/bin/*
