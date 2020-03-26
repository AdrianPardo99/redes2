file1=servidor
file2=cliente
com: ${file1}.c ${file2}.c
	gcc ${file1}.c -o ${file1} -Wall
	gcc ${file2}.c -o ${file2} -Wall
servidor: ${file1}.c
	gcc ${file1}.c -o ${file1} -Wall
cliente: ${file2}.c
	gcc ${file2}.c -o ${file2} -Wall
