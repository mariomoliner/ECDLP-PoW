all: Main Main_test

Main:
	gcc -g Main.c ECDLP_POW/*.c SEA/src/SEA/*.c -o Main -lssl -lcrypto -I/usr/include/openssl -I/usr/include/flint/ -lflint -lgmp -w
	
Main_test: 
	gcc -g Main_test.c ECDLP_POW/*.c SEA/src/SEA/*.c -o Main_test -lssl -lcrypto -I/usr/include/openssl -I/usr/include/flint/ -lflint -lgmp -w

clean:
	find . -type f -executable -exec rm '{}' \;
