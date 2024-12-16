

all: f1.exe f2.exe f3.exe

f1.exe: f1.c
	gcc -o f1.exe f1.c

f2.exe: f2.c
	gcc -o f2.exe f2.c

f3.exe: f3.c
	gcc -o f3.exe f3.c

test: f1.exe f2.exe f3.exe
	./f1.exe
	./f2.exe
	./f3.exe

clean:
	rm -f *.exe