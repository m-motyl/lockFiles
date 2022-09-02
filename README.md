# Communication via files (using lockfiles)
Pair of programs (client - server) communicating each other via files that form a text messenger. 
There is a single, continously working server and may be more than one client (client sends the messages, prints the response and disconnects).
Every program has a subordinate file ([program].txt) which is its buffer. Client sends a name of its buffer file, next lines of
the message read from standard input and (also from standard input) the char of message end to the server buffer file, which name is generally known. 
Server saves the client buffer file name and sends a response there.
(next lines of the message and the char of message end). Client reads and prints the message from its buffer, then disconnects.

There can be many clients, but the only one can be connected to the server, the rest are waiting until the server is free. 
Access to the server buffer is synchornized with a lockfile created by the client in the working directory of the server 
and deleted by the server after answering the client.

## remarks
* run programs in separate terminals
* run server program first
