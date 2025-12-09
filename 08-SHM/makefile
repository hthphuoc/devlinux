CUR := .
SRC := $(CUR)/src
BIN := $(CUR)/bin

all:
	gcc $(SRC)/producer.c -o $(BIN)/producer -pthread -lrt
	gcc $(SRC)/consumer.c -o $(BIN)/consumer -pthread -lrt

clean:
	rm -f $(BIN)/*
