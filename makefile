objectfile = data/object
Source= sources
header = ./headers
library = -lglfw

main:$(objectfile)/main.o $(objectfile)/glad.o
	gcc   $(objectfile)/main.o $(objectfile)/glad.o -o main $(library)
$(objectfile)/glad.o:$(Source)/glad.c
	gcc -c -I./headers  -g $(Source)/glad.c -o $(objectfile)/glad.o
$(objectfile)/main.o:main.c 
	gcc -c -I./headers  -g main.c -o $(objectfile)/main.o
clean:main.c
	rm -f  $(objectfile)/main.o