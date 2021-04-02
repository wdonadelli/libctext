all: libctext.o cText.o
	gcc -Wall -g -o cText cText.o libctext.o
	@ chmod a+x cText
	@ echo "Executable file cText created."

libctext.o:
	gcc -Wall -g -o libctext.o -c libctext.c
	@ echo "libctext.o file created."

cText.o:
	gcc -Wall -g -o cText.o -c cText.c
	@ echo "cText.o file created."

clean:
	@ rm -f cText.o libctext.o cText
	@ echo "Done!"

run: all
	./cText

check: clean all
	@ valgrind --tool=memcheck --leak-check=yes --track-origins=yes -s ./cText
