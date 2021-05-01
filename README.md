# TCP-Simple-Client-Server-File-Sharing
C Socket Programming code to get a file present in the Server's directory and store it in the Client's directory.  
  
The client sends a query to server requesting data from <filename> present in the server's directory. The server returns the contents of this file to the client, which the client stores in its directory under the same filename.  
  
If the file requested is not present in the server, the server returns a blank file to the client.

## Step1: Compilation of code
`make`

## Step2: Running server.c
`./Server/server 8000`

## Step3: Running client.c
`./Client/client 127.0.0.1 8000`  
  
The executable for the client will ask for the name of the file as a stdin. Input the name of the file along with the `./Server/` directory.
For example:  
`----- Enter name of the file: ./Server/input.txt`
