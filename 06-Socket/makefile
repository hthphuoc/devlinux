CUR := .
SRC := $(CUR)/src
BIN := $(CUR)/bin

tcp:
	gcc $(SRC)/tcp_server.c -o $(BIN)/tcp_server
	gcc $(SRC)/tcp_client.c -o $(BIN)/tcp_client

udp:
	gcc $(SRC)/udp_server.c -o $(BIN)/udp_server
	gcc $(SRC)/udp_client.c -o $(BIN)/udp_client

unix_stream:
	gcc $(SRC)/unix_stream_server.c -o $(BIN)/unix_stream_server
	gcc $(SRC)/unix_stream_client.c -o $(BIN)/unix_stream_client

unix_dia:
	gcc $(SRC)/unix_dia_server.c -o $(BIN)/unix_dia_server
	gcc $(SRC)/unix_dia_client.c -o $(BIN)/unix_dia_client

all: tcp udp unix_stream unix_dia

clean:
	rm -f $(BIN)/*
