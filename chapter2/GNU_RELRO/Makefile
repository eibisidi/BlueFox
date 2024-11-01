#Page 41 The GNU_RELRO Program Header
#1.make these three executables
#2.Examine GNU_RELRO program header with: readelf -lW <exec>
#3.Trace system call with: strace -o <exec>.strace ./<exec>
#4.Examine the output file generated in step 3. Find which
#  mprotect() system call corresponds to the GNU_RELRO program header

all : now relro norelro

#Full RELRO mitigation
now : main.c
	gcc -znow -o $@ $^

#Parital RELRO mitigation
relro : main.c
	gcc -zrelro -o $@ $^

#Disable RELRO mitigation entirely
norelro : main.c
	gcc -znorelro -o $@ $^

.PHONY : clean
clean:
	rm now relro norelro
