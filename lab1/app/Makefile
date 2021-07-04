INCLUDES=-I../freetype/include -I../libpng
STATICLIBPATH=-LstaticLIB
ELF_FILES=../elfloader-master/elf_loader.c ../elfloader-master/main.c ../elfloader-master/wheelc/list.c
CFLAGS_BLOB=-fno-stack-protector -fno-exceptions -s -nostdlib -pie -fPIE -fPIC -DBLOB

all: clean static dynamic blob

static:
	g++ $(INCLUDES) $(STATICLIBPATH) main.c -lfreetype -lpng -lzlib -o main-static
	
dynamic:
	g++ $(INCLUDES) -DDYNAMIC main.c -ldl -o main-dynamic
	
blob:
	gcc $(ELF_FILES) -lm -ldl -o main-blob
	g++ $(INCLUDES) $(STATICLIBPATH) $(CFLAGS_BLOB) -emain main.c -lfreetype -lpng -lzlib -lm -lc -o blob.bin
	
clean:
	rm -f -d blob.bin
	rm -f -d main-*
