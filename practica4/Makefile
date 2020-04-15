server=servidor
fileServer=serverHeader
cliente=cliente
fileCliente=clienteHeader
init: ${server}.c
	gcc -c ${fileServer}.c -o ${fileServer}.o
	gcc ${server}.c ${fileServer}.o -o ${server} -lpthread -Wall
	gcc -c ${fileCliente}.c -o ${fileCliente}.o
	gcc ${cliente}.c ${fileCliente}.o -o ${cliente} -lpthread -Wall
