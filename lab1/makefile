
all: clean static dynamic blob

static:
	$(MAKE) -C freetype -f makefile_freetype static
	$(MAKE) -C libpng -f makefile_libpng static
	$(MAKE) -C zlib -f makefile_zlib static
	$(MAKE) -C app -f Makefile static
	
dynamic:
	$(MAKE) -C freetype -f makefile_freetype dynamic
	$(MAKE) -C libpng -f makefile_libpng dynamic
	$(MAKE) -C app -f Makefile dynamic
	
blob:
	$(MAKE) -C freetype -f makefile_freetype blob
	$(MAKE) -C libpng -f makefile_libpng blob
	$(MAKE) -C zlib -f makefile_zlib blob
	$(MAKE) -C app -f Makefile blob

clean:
	$(MAKE) -C freetype -f makefile_freetype clean
	$(MAKE) -C libpng -f makefile_libpng clean
	$(MAKE) -C zlib -f makefile_zlib clean
	$(MAKE) -C app -f Makefile clean
