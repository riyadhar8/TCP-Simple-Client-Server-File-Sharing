all: ./Server/server ./Client/client

server: ./Server/server.c
		gcc ./Server/server.c -o ./Server/server

client:	./Client/client.client
		gcc ./Client/client.c -o ./Client/client

clean:
		rm -rf ./Server/server ./Client/client