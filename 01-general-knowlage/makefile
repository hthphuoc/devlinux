CUR := .
INC := $(CUR)/inc
LIB := $(CUR)/lib
LIB_SHARED := $(LIB)/shared
LIB_STATIC := $(LIB)/static
OBJ := $(CUR)/obj
SRC := $(CUR)/src
BIN := $(CUR)/bin

create_obj:
	gcc -c $(SRC)/bstrutils.c -fPIC -o $(OBJ)/bstrutils.o -I $(INC)
	gcc -c $(SRC)/main.c -o $(OBJ)/main.o -I $(INC)

static: create_obj
	ar rcs $(LIB_STATIC)/libstrutils.a $(OBJ)/bstrutils.o
	gcc   $(OBJ)/main.o -L$(LIB_STATIC) -lstrutils -o $(BIN)/main_static

shared: create_obj
	gcc -shared $(OBJ)/bstrutils.o -o $(LIB_SHARED)/libstrutils.so
	gcc  $(OBJ)/main.o -L$(LIB_SHARED) -lstrutils -o $(BIN)/main_shared

all: static shared

clean:
	rm -f $(OBJ)/*
	rm -f $(LIB_STATIC)/*
	rm -f $(LIB_SHARED)/*
	rm -f $(BIN)/*
