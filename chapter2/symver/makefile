#This project demostrates Symbol Versioning
#1. make
#2. examine every executive with: readelf --dyn-syms
#3. make test
#4. examine output

LIBDIR=/usr/local/lib
all : lib1.so lib2.so lib3.so use1 use2 use3

lib1.so : lib1.c
	gcc -o $@ -shared -fPIC $<

lib2.so : lib2.c
	gcc -o $@ -shared -fPIC $< -Wl,--version-script=lib2.ver

lib3.so : lib3.c
	gcc -o $@ -shared -fPIC $< -Wl,--version-script=lib3.ver

use1 : use1.c lib1.so
	ln -sf lib1.so libfoo.so
	gcc -o $@ $< -L. -lfoo

use2 : use2.c lib2.so
	ln -sf lib2.so libfoo.so
	gcc -o $@ $< -L. -lfoo

use3 : use3.c lib3.so
	ln -sf lib3.so libfoo.so
	gcc -o $@ $< -L. -lfoo

test: lib1.so lib2.so lib3.so use1 use2 use3
	@echo "------Running with lib1.so------"
	ln -sf ${PWD}/lib1.so ${LIBDIR}/libfoo.so
	ldconfig
	./use1 
	./use2 
	./use3 
	@echo "------Running with lib2.so------"
	ln -sf ${PWD}/lib2.so ${LIBDIR}/libfoo.so
	ldconfig
	./use1 
	./use2
#use3 won't run with lib2.so
#	./use3 
	@echo "------Running with lib3.so------"
	ln -sf ${PWD}/lib3.so ${LIBDIR}/libfoo.so
	ldconfig
	./use1
	./use2
	./use3
	rm ${LIBDIR}/libfoo.so

.PHONY : clean

clean:
	rm *.o *.so use1 use2 use3
