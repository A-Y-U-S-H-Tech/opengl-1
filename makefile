objectfile = data/object
Source= sources
header = ./headers
DSA = sources/DataStruture
library =  -lglfw -lm -lfreetype
freetype = -I/usr/include/freetype2 -I/usr/include/libpng16 -DWITH_GZFILEOP -I/usr/include/harfbuzz -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/sysprof-6 

main:$(objectfile)/main.o $(objectfile)/glad.o $(objectfile)/shader.o $(objectfile)/loger.o $(objectfile)/vertex.o $(objectfile)/grid.o $(objectfile)/Sprite.o	$(objectfile)/Matrix.o $(objectfile)/text.o $(objectfile)/color.o $(objectfile)/vector.o $(objectfile)/Queue.o
	gcc $(freetype) $(objectfile)/Queue.o $(objectfile)/vector.o  $(objectfile)/color.o $(objectfile)/text.o $(objectfile)/Matrix.o  $(objectfile)/glad.o $(objectfile)/loger.o $(objectfile)/vertex.o $(objectfile)/Sprite.o $(objectfile)/grid.o $(objectfile)/shader.o $(objectfile)/main.o $ -g -o main $(library) $(freetype)

$(objectfile)/glad.o:$(Source)/glad.c
	gcc -c -I./headers  -g $(Source)/glad.c -o $(objectfile)/glad.o

$(objectfile)/shader.o:$(Source)/shader.c
	gcc -c -I./headers -g $(Source)/shader.c -o $(objectfile)/shader.o

$(objectfile)/loger.o:$(Source)/loger.c
	gcc -c -I./headers -g $(Source)/loger.c -o $(objectfile)/loger.o

$(objectfile)/vertex.o:$(Source)/vertex.c
	gcc -c -I./headers -g $(Source)/vertex.c -o $(objectfile)/vertex.o

$(objectfile)/grid.o:$(Source)/grid.c
	gcc -c -I./headers -g $(Source)/grid.c -o $(objectfile)/grid.o

$(objectfile)/Sprite.o:$(Source)/Sprite.c
	gcc -c -I./headers -g $(Source)/Sprite.c -o $(objectfile)/Sprite.o

$(objectfile)/Matrix.o:$(Source)/Matrix.c
	gcc -c -I./headers -g $(Source)/Matrix.c -o $(objectfile)/Matrix.o

$(objectfile)/text.o:$(Source)/ui/text.c
	gcc $(freetype)  -c -I./headers  -g $(Source)/ui/text.c -o $(objectfile)/text.o

$(objectfile)/color.o:$(Source)/ui/color.c
	gcc  -c -I./headers  -g $(Source)/ui/color.c -o $(objectfile)/color.o

$(objectfile)/vector.o:$(Source)/vector.c
	gcc  -c -I./headers  -g $(Source)/vector.c -o $(objectfile)/vector.o

$(objectfile)/Queue.o:$(DSA)/Queue.c
	gcc -c -I./headers -g $(DSA)/Queue.c -o $(objectfile)/Queue.o

$(objectfile)/main.o:main.c 
	gcc  -c -I./headers  -g main.c -o $(objectfile)/main.o

clean:main.c $(Source)/*.c
	rm -f  $(objectfile)/*.o