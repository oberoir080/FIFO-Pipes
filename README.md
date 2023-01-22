
# FIFO pipes (Communication between client and server)

The first code is a client-side program that generates 50 random strings and assigns each one a unique ID. It then uses two named pipes (FIFO) to communicate with a server. The client sends 5 strings at a time to the server through the first pipe, and waits for a response from the server through the second pipe. The response from the server is the ID of the last string it received, which the client uses to determine the next set of strings to send. The client continues to send strings to the server until it has sent all 50 strings.

The second code is a server-side program that uses two named pipes (FIFO) to communicate with a client. The server repeatedly reads 5 strings from the client through the first pipe, it prints the string and the id of each received string, then it sends back the ID of the last received string through the second pipe. The server continues to read strings from the client until it receives an ID greater than or equal to 50, at which point it exits. This code is designed to work in conjunction with the first code, which is the client-side program that sends the strings to the server.
