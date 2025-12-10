CUR := .
SRC := $(CUR)/src
BIN := $(CUR)/bin

all:
	gcc $(SRC)/worker.c -o $(BIN)/worker -pthread -lrt
	gcc $(SRC)/dispatcher.c -o $(BIN)/dispatcher -pthread -lrt

clean:
	rm -f $(BIN)/*
