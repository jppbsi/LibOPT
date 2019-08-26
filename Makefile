LIB=./lib
INCLUDE=./include
SRC=./src
OBJ=./obj

CC=gcc

FLAGS=  -g -O0
CFLAGS=''

all: libopt PSO AIWPSO BA FPA FA CS GP GA BHA WCA MBO GSGP BGSGP ABC HS IHS PSF-HS BSO BSA JADE LOA SA DE ABO CGP TensorPSO TensorAIWPSO TensorBA TensorFPA TensorFA TensorCS TensorBHA TensorABC TensorHS TensorIHS TensorPSF-HS TensorGP

libopt: $(LIB)/libopt.a
	echo "libopt.a built..."

$(LIB)/libopt.a: \
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
$(OBJ)/wca.o \
$(OBJ)/mbo.o \
$(OBJ)/abc.o \
$(OBJ)/hs.o \
$(OBJ)/bso.o \
$(OBJ)/bsa.o \
$(OBJ)/jade.o \
$(OBJ)/loa.o \
$(OBJ)/sa.o \
$(OBJ)/de.o \
$(OBJ)/abo.o \
$(OBJ)/cgp.o \

	ar csr $(LIB)/libopt.a \
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
$(OBJ)/wca.o \
$(OBJ)/mbo.o \
$(OBJ)/abc.o \
$(OBJ)/hs.o \
$(OBJ)/bso.o \
$(OBJ)/bsa.o \
$(OBJ)/jade.o \
$(OBJ)/loa.o \
$(OBJ)/sa.o \
$(OBJ)/de.o \
$(OBJ)/abo.o \
$(OBJ)/cgp.o \

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

$(OBJ)/wca.o: $(SRC)/wca.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/wca.c -o $(OBJ)/wca.o

$(OBJ)/mbo.o: $(SRC)/mbo.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/mbo.c -o $(OBJ)/mbo.o

$(OBJ)/abc.o: $(SRC)/abc.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/abc.c -o $(OBJ)/abc.o

$(OBJ)/hs.o: $(SRC)/hs.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/hs.c -o $(OBJ)/hs.o

$(OBJ)/bso.o: $(SRC)/bso.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/bso.c -o $(OBJ)/bso.o

$(OBJ)/bsa.o: $(SRC)/bsa.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/bsa.c -o $(OBJ)/bsa.o

$(OBJ)/jade.o: $(SRC)/jade.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/jade.c -o $(OBJ)/jade.o

$(OBJ)/loa.o: $(SRC)/loa.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/loa.c -o $(OBJ)/loa.o

$(OBJ)/sa.o: $(SRC)/sa.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/sa.c -o $(OBJ)/sa.o

$(OBJ)/de.o: $(SRC)/de.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/de.c -o $(OBJ)/de.o

$(OBJ)/abo.o: $(SRC)/abo.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/abo.c -o $(OBJ)/abo.o

$(OBJ)/cgp.o: $(SRC)/cgp.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $(SRC)/cgp.c -o $(OBJ)/cgp.o

PSO: examples/PSO.c
	$(CC) $(FLAGS) examples/PSO.c -o examples/bin/PSO -I $(INCLUDE) -L $(LIB) -lopt -lm;

AIWPSO: examples/AIWPSO.c
	$(CC) $(FLAGS) examples/AIWPSO.c -o examples/bin/AIWPSO -I $(INCLUDE) -L $(LIB) -lopt -lm;

BA: examples/BA.c
	$(CC) $(FLAGS) examples/BA.c -o examples/bin/BA -I $(INCLUDE) -L $(LIB) -lopt -lm;

FPA: examples/FPA.c
	$(CC) $(FLAGS) examples/FPA.c -o examples/bin/FPA -I $(INCLUDE) -L $(LIB) -lopt -lm;

FA: examples/FA.c
	$(CC) $(FLAGS) examples/FA.c -o examples/bin/FA -I $(INCLUDE) -L $(LIB) -lopt -lm;

CS: examples/CS.c
	$(CC) $(FLAGS) examples/CS.c -o examples/bin/CS -I $(INCLUDE) -L $(LIB) -lopt -lm;

GP: examples/GP.c
	$(CC) $(FLAGS) examples/GP.c -o examples/bin/GP -I $(INCLUDE) -L $(LIB) -lopt -lm;

GA: examples/GA.c
	$(CC) $(FLAGS) examples/GA.c -o examples/bin/GA -I $(INCLUDE) -L $(LIB) -lopt -lm;

BHA: examples/BHA.c
	$(CC) $(FLAGS) examples/BHA.c -o examples/bin/BHA -I $(INCLUDE) -L $(LIB) -lopt -lm;

WCA: examples/WCA.c
	$(CC) $(FLAGS) examples/WCA.c -o examples/bin/WCA -I $(INCLUDE) -L $(LIB) -lopt -lm;

MBO: examples/MBO.c
	$(CC) $(FLAGS) examples/MBO.c -o examples/bin/MBO -I $(INCLUDE) -L $(LIB) -lopt -lm;

GSGP: examples/GSGP.c
	$(CC) $(FLAGS) examples/GSGP.c -o examples/bin/GSGP -I $(INCLUDE) -L $(LIB) -lopt -lm;

BGSGP: examples/BGSGP.c
	$(CC) $(FLAGS) examples/BGSGP.c -o examples/bin/BGSGP -I $(INCLUDE) -L $(LIB) -lopt -lm;

ABC: examples/ABC.c
	$(CC) $(FLAGS) examples/ABC.c -o examples/bin/ABC -I $(INCLUDE) -L $(LIB) -lopt -lm;

HS: examples/HS.c
	$(CC) $(FLAGS) examples/HS.c -o examples/bin/HS -I $(INCLUDE) -L $(LIB) -lopt -lm;

IHS: examples/IHS.c
	$(CC) $(FLAGS) examples/IHS.c -o examples/bin/IHS -I $(INCLUDE) -L $(LIB) -lopt -lm;

PSF-HS: examples/PSF-HS.c
	$(CC) $(FLAGS) examples/PSF-HS.c -o examples/bin/PSF-HS -I $(INCLUDE) -L $(LIB) -lopt -lm;

BSO: examples/BSO.c
	$(CC) $(FLAGS) examples/BSO.c -o examples/bin/BSO -I $(INCLUDE) -L $(LIB) -lopt -lm;

BSA: examples/BSA.c
	$(CC) $(FLAGS) examples/BSA.c -o examples/bin/BSA -I $(INCLUDE) -L $(LIB) -lopt -lm;

JADE: examples/JADE.c
	$(CC) $(FLAGS) examples/JADE.c -o examples/bin/JADE -I $(INCLUDE) -L $(LIB) -lopt -lm;

LOA: examples/LOA.c
	$(CC) $(FLAGS) examples/LOA.c -o examples/bin/LOA -I $(INCLUDE) -L $(LIB) -lopt -lm;

SA: examples/SA.c
	$(CC) $(FLAGS) examples/SA.c -o examples/bin/SA -I $(INCLUDE) -L $(LIB) -lopt -lm;

DE: examples/DE.c
	$(CC) $(FLAGS) examples/DE.c -o examples/bin/DE -I $(INCLUDE) -L $(LIB) -lopt -lm;

ABO: examples/ABO.c
	$(CC) $(FLAGS) examples/ABO.c -o examples/bin/ABO -I $(INCLUDE) -L $(LIB) -lopt -lm;

CGP: examples/CGP.c
	$(CC) $(FLAGS) examples/CGP.c -o examples/bin/CGP -I $(INCLUDE) -L $(LIB) -lopt -lm;

TensorPSO: examples/TensorPSO.c
	$(CC) $(FLAGS) examples/TensorPSO.c -o examples/bin/TensorPSO -I $(INCLUDE) -L $(LIB) -lopt -lm;

TensorAIWPSO: examples/TensorAIWPSO.c
	$(CC) $(FLAGS) examples/TensorAIWPSO.c -o examples/bin/TensorAIWPSO -I $(INCLUDE) -L $(LIB) -lopt -lm;

TensorBA: examples/TensorBA.c
	$(CC) $(FLAGS) examples/TensorBA.c -o examples/bin/TensorBA -I $(INCLUDE) -L $(LIB) -lopt -lm;

TensorFPA: examples/TensorFPA.c
	$(CC) $(FLAGS) examples/TensorFPA.c -o examples/bin/TensorFPA -I $(INCLUDE) -L $(LIB) -lopt -lm;

TensorFA: examples/TensorFA.c
	$(CC) $(FLAGS) examples/TensorFA.c -o examples/bin/TensorFA -I $(INCLUDE) -L $(LIB) -lopt -lm;

TensorCS: examples/TensorCS.c
	$(CC) $(FLAGS) examples/TensorCS.c -o examples/bin/TensorCS -I $(INCLUDE) -L $(LIB) -lopt -lm;

TensorBHA: examples/TensorBHA.c
	$(CC) $(FLAGS) examples/TensorBHA.c -o examples/bin/TensorBHA -I $(INCLUDE) -L $(LIB) -lopt -lm;

TensorABC: examples/TensorABC.c
	$(CC) $(FLAGS) examples/TensorABC.c -o examples/bin/TensorABC -I $(INCLUDE) -L $(LIB) -lopt -lm;

TensorHS: examples/TensorHS.c
	$(CC) $(FLAGS) examples/TensorHS.c -o examples/bin/TensorHS -I $(INCLUDE) -L $(LIB) -lopt -lm;

TensorIHS: examples/TensorIHS.c
	$(CC) $(FLAGS) examples/TensorIHS.c -o examples/bin/TensorIHS -I $(INCLUDE) -L $(LIB) -lopt -lm;

TensorPSF-HS: examples/TensorPSF-HS.c
	$(CC) $(FLAGS) examples/TensorPSF-HS.c -o examples/bin/TensorPSF-HS -I $(INCLUDE) -L $(LIB) -lopt -lm;

TensorGP: examples/TensorGP.c
	$(CC) $(FLAGS) examples/TensorGP.c -o examples/bin/TensorGP -I $(INCLUDE) -L $(LIB) -lopt -lm;

clean:
	rm -f $(LIB)/lib*.a; rm -f $(OBJ)/*.o; rm -rf examples/bin/*
