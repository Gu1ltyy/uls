all: LIBMX create_lib

LIBMX:
	mkdir obj
	clang -std=c11 -Wall -Wextra -Werror -Wpedantic -Iinc -c src/*.c
	mv *.o obj/

create_lib:
	ar -rc libmx.a obj/*.o
	ranlib libmx.a

clean:
	rm -rf obj

uninstall:
	rm -rf obj
	rm -rf libmx.a

reinstall:
	make uninstall
	make
