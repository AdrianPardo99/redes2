server=servidor
fileServer=serverHeader
init: ${server}.c
	gcc -c ${fileServer}.c -o ${fileServer}.o
	gcc ${server}.c ${fileServer}.o -o ${server} -lpthread -Wall
