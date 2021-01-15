all: folder experience

experience: libctext.o experience.o
	@ echo "\033[1;3;96mCompiling experience.o and libctext.o:\033[0m"
	gcc -Wall -g -o experience objects/experience.o objects/libctext.o
	@ echo "\033[1;3;96mExecute experience:\033[0m"
	./experience
	@ echo "\033[1;3;96mDone!\033[0m"

libctext.o:
	@ echo "\033[1;3;96mCompiling libctext.c:\033[0m"
	gcc -Wall -g -o objects/libctext.o -c source/libctext.c

experience.o:
	@ echo "\033[1;3;96mCompiling experience.c:\033[0m"
	gcc -Wall -g -o objects/experience.o -c source/experience.c

folder:
	@ echo "\033[1;3;96mCopying library files to the source directory...\033[0m"
	@ cp "../libctext.c" "source/"
	@ cp "../libctext.h" "source/"

clean:
	@ echo "\033[1;3;96mCleaning up...\033[0m"
	@ rm -f experience
	@ rm -rf objects/*.o
	@ echo "\033[1;3;96mDone!\033[0m"

#see valgrind --tool=memcheck --leak-check=yes ./experience/experience
