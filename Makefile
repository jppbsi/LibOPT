LIB=./lib
INCLUDE=./include
SRC=./src
OBJ=./obj

CC=gcc 

FLAGS=  -g -O0
CFLAGS=''

all: libopt-plus PSO AIWPSO BA FPA FA CS GP GA BHA MBO BGSGP ABC TensorPSO TensorFPA TensorFA TensorCS TensorBHA TensorABC

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
$(OBJ)/cs.o \
$(OBJ)/gp.o \
$(OBJ)/ga.o \
$(OBJ)/bha.o \
$(OBJ)/mbo.o \
$(OBJ)/abc.o \

	ar csr $(LIB)/libopt-plus.a \
$(OBJ)/common.o \
$(OBJ)/function.o \
$(OBJ)/random.o \
$(OBJ)/pso.o \
$(OBJ)/ba.o \
$(OBJ)/fpa.o \
$(OBJ)/fa.o \
$(OBJ)/cs.o \
$(OBJ)/gp.o \
$(OBJ)/ga.o \
$(OBJ)/bha.o \
$(OBJ)/mbo.o \
$(OBJ)/abc.o \

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

$(OBJ)/cs.o: $(SRC)/cs.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/cs.c -o $(OBJ)/cs.o

$(OBJ)/gp.o: $(SRC)/gp.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/gp.c -o $(OBJ)/gp.o

$(OBJ)/ga.o: $(SRC)/ga.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/ga.c -o $(OBJ)/ga.o

$(OBJ)/bha.o: $(SRC)/bha.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/bha.c -o $(OBJ)/bha.o
	
$(OBJ)/mbo.o: $(SRC)/mbo.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/mbo.c -o $(OBJ)/mbo.o

$(OBJ)/abc.o: $(SRC)/abc.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/abc.c -o $(OBJ)/abc.o

PSO: examples/PSO.c
	$(CC) $(FLAGS) examples/PSO.c -o examples/bin/PSO -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

AIWPSO: examples/AIWPSO.c
	$(CC) $(FLAGS) examples/AIWPSO.c -o examples/bin/AIWPSO -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

BA: examples/BA.c
	$(CC) $(FLAGS) examples/BA.c -o examples/bin/BA -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

FPA: examples/FPA.c
	$(CC) $(FLAGS) examples/FPA.c -o examples/bin/FPA -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

FA: examples/FA.c
	$(CC) $(FLAGS) examples/FA.c -o examples/bin/FA -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

CS: examples/CS.c
	$(CC) $(FLAGS) examples/CS.c -o examples/bin/CS -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

GP: examples/GP.c
	$(CC) $(FLAGS) examples/GP.c -o examples/bin/GP -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

GA: examples/GA.c
	$(CC) $(FLAGS) examples/GA.c -o examples/bin/GA -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

BHA: examples/BHA.c
	$(CC) $(FLAGS) examples/BHA.c -o examples/bin/BHA -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

MBO: examples/MBO.c
	$(CC) $(FLAGS) examples/MBO.c -o examples/bin/MBO -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

BGSGP: examples/BGSGP.c
	$(CC) $(FLAGS) examples/BGSGP.c -o examples/bin/BGSGP -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

ABC: examples/ABC.c
	$(CC) $(FLAGS) examples/ABC.c -o examples/bin/ABC -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

TensorPSO: examples/TensorPSO.c
	$(CC) $(FLAGS) examples/TensorPSO.c -o examples/bin/TensorPSO -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

TensorFPA: examples/TensorFPA.c
	$(CC) $(FLAGS) examples/TensorFPA.c -o examples/bin/TensorFPA -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

TensorFA: examples/TensorFA.c
	$(CC) $(FLAGS) examples/TensorFA.c -o examples/bin/TensorFA -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

TensorCS: examples/TensorCS.c
	$(CC) $(FLAGS) examples/TensorCS.c -o examples/bin/TensorCS -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

TensorBHA: examples/TensorBHA.c
	$(CC) $(FLAGS) examples/TensorBHA.c -o examples/bin/TensorBHA -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

TensorABC: examples/TensorABC.c
	$(CC) $(FLAGS) examples/TensorABC.c -o examples/bin/TensorABC -I $(INCLUDE) -L $(LIB) -lopt-plus -lm;

clean:
	rm -f $(LIB)/lib*.a; rm -f $(OBJ)/*.o; rm -rf examples/bin/*
