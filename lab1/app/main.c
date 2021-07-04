#include "ft2build.h"
#include "png.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include <stdlib.h>

int pos_x = 21;
int pos_y = 50;
const int kFontSize = 48;
const int image_heigth = kFontSize + 17;

#ifdef DYNAMIC
#include <dlfcn.h>
#define FT_Init_FreeType			SO_FT_Init_FreeType
#define FT_New_Face					SO_FT_New_Face
#define FT_Set_Pixel_Sizes			SO_FT_Set_Pixel_Sizes
#define FT_Load_Char				SO_FT_Load_Char
#define png_create_write_struct		SO_png_create_write_struct
#define png_create_info_struct		SO_png_create_info_struct
#define png_init_io					SO_png_init_io
#define png_set_IHDR				SO_png_set_IHDR
#define png_write_info				SO_png_write_info
#define png_write_image				SO_png_write_image
#define png_set_longjmp_fn			SO_png_set_longjmp_fn
#define png_write_end				SO_png_write_end
#define png_destroy_write_struct	SO_png_destroy_write_struct

png_structrp (*SO_png_create_write_struct)(const char*, void*, void*, void*);
png_infop (*SO_png_create_info_struct)(void*);
void (*SO_png_init_io)(void*, void*);
void (*SO_png_set_IHDR)(void*, void*, unsigned int, unsigned int, int, int, int, int, int);
void (*SO_png_write_info)(png_structp png_ptr, png_infop info_ptr);
void (*SO_png_write_image)(png_structp png_ptr, unsigned char **image);
void (*SO_png_write_end)(void*, void*);
jmp_buf* (*SO_png_set_longjmp_fn)(png_structrp png_ptr, png_longjmp_ptr longjmp_fn, size_t jmp_buf_size);
void (*SO_png_destroy_write_struct)(void*, void*);
int (*SO_FT_Init_FreeType)(FT_Library*);
int (*SO_FT_New_Face)(FT_Library, const char*, FT_Long, FT_Face*);
int (*SO_FT_Set_Pixel_Sizes)(FT_Face, FT_UInt, FT_UInt);
int (*SO_FT_Load_Char)(FT_Face, FT_ULong, FT_Int32);

void* SO_freetype;
void* SO_libpng;

int SO_Init()
{
	SO_libpng = dlopen("dynamicLIB/libpng.so", RTLD_LAZY);
	if (!SO_libpng) 
	{
		printf("Error of load libpng.so\n");
		return 0;
	}
	SO_png_create_write_struct = (png_structrp (*)(const char*, void*, void*, void*))dlsym(SO_libpng, "png_create_write_struct");
	SO_png_create_info_struct = (png_infop (*)(void*))dlsym(SO_libpng, "png_create_info_struct");
	SO_png_init_io = (void (*)(void*, void*))dlsym(SO_libpng, "png_init_io");
	SO_png_set_IHDR = (void (*)(void*, void*, unsigned int, unsigned int, int, int, int, int, int))dlsym(SO_libpng, "png_set_IHDR");
	SO_png_write_end = (void (*)(void*, void*))dlsym(SO_libpng, "png_write_end");
	SO_png_set_longjmp_fn = (jmp_buf* (*)(png_structrp png_ptr, png_longjmp_ptr longjmp_fn, size_t jmp_buf_size))dlsym(SO_libpng, "png_set_longjmp_fn");
	SO_png_write_info = (void (*)(png_structp png_ptr, png_infop info_ptr))dlsym(SO_libpng, "png_write_info");
	SO_png_write_image = (void (*)(png_structp png_ptr, unsigned char **image))dlsym(SO_libpng, "png_write_image");
	SO_png_destroy_write_struct = (void (*)(void*, void*))dlsym(SO_libpng, "png_destroy_write_struct");

	SO_freetype = dlopen("dynamicLIB/libfreetype.so", RTLD_LAZY);
	if (!SO_freetype)
	{
		printf("Error of load libfreetype.so\n");
		return 0;
	}
	SO_FT_Init_FreeType = (int (*)(FT_Library*))dlsym(SO_freetype, "FT_Init_FreeType");
	SO_FT_New_Face = (int (*)(FT_Library, const char*, FT_Long, FT_Face*)) dlsym(SO_freetype, "FT_New_Face");
	SO_FT_Set_Pixel_Sizes = (int (*)(FT_Face, FT_UInt, FT_UInt)) dlsym(SO_freetype, "FT_Set_Pixel_Sizes");
	SO_FT_Load_Char = (int (*)(FT_Face, FT_ULong, FT_Int32)) dlsym(SO_freetype, "FT_Load_Char");
	return 1;
}

void SO_close()
{
	dlclose(SO_freetype);
	dlclose(SO_libpng);
}

#endif

#ifdef BLOB
void **gFunctions;
clock_t clock(void){
	return ((clock_t (*)(void))gFunctions[0])();
}

int puts(const char *str){
	return ((int (*)(const char *))gFunctions[1])(str);
}

size_t strlen(const char *str){
	return ((size_t (*)(const char *))gFunctions[2])(str);
}


const char *strrchr(const char *str, int ch){
	return ((char* (*)(const char *, int))gFunctions[3])(str, ch);
}

const char *strstr(const char *str1, const char *str2){
	return ((char* (*)(const char *, const char*))gFunctions[4])(str1, str2);
}

char *getenv(const char *name){
	return ((char* (*)(const char *))gFunctions[5])(name);
}

int strncmp(const char *str1, const char *str2, size_t count){
	return ((int (*)(const char *, const char*, size_t))gFunctions[6])(str1, str2, count);
}

const void *memchr(const void *buffer, int ch, size_t count){
	return ((void* (*)(const void*, int, size_t))gFunctions[7])(buffer, ch, count);
}

int strcmp(const char *str1, const char *str2){
	return ((int (*)(const char *, const char*))gFunctions[8])(str1, str2);
}

void *memset(void *buf, int ch, size_t count){
	return ((void* (*)(void*, int, size_t))gFunctions[9])(buf, ch, count);
}

char *strncpy(char *dest, const char *source, size_t count){
	return ((char* (*)(char*, const char *, size_t))gFunctions[10])(dest, source, count);
}

void * mmap(void *start, size_t length, int prot , int flags, int fd, off_t offset){
	return ((char* (*)(void *, size_t, int, int, int, off_t))gFunctions[11])(start, length, prot, flags, fd, offset);
}

void *realloc(void *ptr, size_t newsize){
	return ((void* (*)(void *, size_t))gFunctions[12])(ptr, newsize);
}

void *memmove(void *dest, const void *source, size_t count){
	return ((void* (*)(void*, const void *, size_t))gFunctions[13])(dest, source, count);
}

double frexp (double num, int *exp){
	return ((double (*)(double, int*))gFunctions[14])(num, exp);
}

double modf (double num, double *i){
	return ((double (*)(double, double*))gFunctions[15])(num, i);
}

double pow (double base, double exp){
	return ((double (*)(double, double))gFunctions[16])(base, exp);
}

int fputc(int ch, FILE *stream){
	return ((int (*)(int, FILE*))gFunctions[17])(ch, stream);
}

int memcmp(const void *buf1, const void *buf2, size_t count){
	return ((int (*)(const void*, const void *, size_t))gFunctions[18])(buf1, buf2, count);
}

size_t fread(void *buf, size_t size, size_t count, FILE *stream){
	return ((size_t (*)(void *, size_t, size_t, FILE*))gFunctions[19])(buf, size, count, stream);
}

FILE *fopen(const char *fname, const char *mode){
	return ((FILE * (*)(const char *, const char *))gFunctions[20])(fname, mode);
}

int munmap(void *start, size_t length){
	return ((int (*)(void *, size_t))gFunctions[21])(start, length);
}

void free(void *ptr){
	return ((void (*)(void*))gFunctions[22])(ptr);
}

size_t fwrite(const void *buf, size_t size, size_t count, FILE *stream){
	return ((size_t (*)(const void *, size_t, size_t, FILE*))gFunctions[23])(buf, size, count, stream);
}

int fflush(FILE *stream){
	return ((int (*)(FILE *))gFunctions[24])(stream);
}

void *memcpy(void *dest, const void *source, size_t count){
	return ((void* (*)(void*, const void *, size_t))gFunctions[25])(dest, source, count);
}

void *malloc(size_t size){
	return ((void* (*)(size_t))gFunctions[26])(size);
}

long int strtol( const char * string, char ** endptr, int basis){
	return ((long int (*)(const char *, char **, int))gFunctions[27])(string, endptr, basis);
}

int * __errno_location(void){
	return NULL;
}

double strtod( const char * string, char ** endptr){
	return ((double (*)(const char *, char **))gFunctions[28])(string, endptr);
}

char * strcpy( char * destptr, const char * srcptr){
	return ((char* (*)(char*, const char *))gFunctions[29])(destptr, srcptr);
}

void qsort(void *__base, size_t __nmemb, size_t __size,  int ( * comparator ) ( const void *, const void * )){
	return ((void (*)(void *, size_t, size_t,  int( const void *, const void * )))gFunctions[30])(__base, __nmemb, __size, comparator);
}

int fclose(FILE *__stream){
	return ((int (*)(FILE*))gFunctions[31])(__stream);
}

int close(int __fd){
	return ((int (*)(int))gFunctions[32])(__fd);
}

char *strerror(int __errnum){
	return ((char *(*)(int))gFunctions[33])(__errnum);
}

int remove(const char *__filename){
	return ((int (*)(const char *))gFunctions[34])(__filename);
}

int fprintf(FILE *__restrict__ __stream, const char *__restrict__ __format, ...){
	return ((int (*)(FILE *, const char *, ...))gFunctions[35])(__stream, __format);
}

ssize_t read(int __fd, void *__buf, size_t __nbytes){
	return ((ssize_t (*)(int, void *, size_t))gFunctions[36])(__fd, __buf, __nbytes);
}

void longjmp(struct __jmp_buf_tag *__env, int __val){
	return ((void (*)(struct __jmp_buf_tag *, int))gFunctions[37])(__env, __val);
}

int _setjmp( jmp_buf environment ){
	return ((int (*)(jmp_buf))gFunctions[38])(environment);
}

void abort(){
	return ((void (*)())gFunctions[39])();
}

int printf(const char * format, ...){
	return ((int (*)(const char * format, ...))gFunctions[40])(format);
}

char *stpcpy(char *str1, const char *str2){
	return ((char* (*)(char*, const char*))gFunctions[41])(str1,str2);
}

int sprintf(char *__restrict__ __s, const char *__restrict__ __format, ...){
	return ((int (*)(char *, const char *, ...))gFunctions[42])(__s, __format);
}

int open(const char *__file, int __oflag, ...){
	return ((int (*)(const char *, int, ...))gFunctions[43])(__file, __oflag);
}

int __fxstat (int vers, int fd, struct stat *buf){
	return ((int (*)(int, int, struct stat*))gFunctions[44])(vers,fd,buf);
}

struct tm *gmtime(const time_t *__timer){
	return ((struct tm* (*)(const time_t *))gFunctions[45])(__timer);
}

int ferror(FILE *__stream){
	return ((int (*)(FILE *))gFunctions[46])(__stream);
}
#endif

void my_draw_bitmap(FT_Bitmap bitmap, int left_corn, int top_corn, unsigned char **image)
{
	
	for (int y = 0; y < bitmap.rows; ++y)
		for (int x = 0; x < bitmap.width; ++x)
			if (bitmap.buffer[y * bitmap.width + x] != 0)
			{
				image[top_corn + y][left_corn + 3 * x] = image[top_corn + y][left_corn + 3 * x + 1] = image[top_corn + y][left_corn + 3 * x + 2] = 0;
			}
	pos_x = left_corn + 3 * bitmap.width;
}

void mem_free(png_bytep * row_pointers, png_bytep * image)
{
	for (int i = 0; i < image_heigth; ++i)
	{
		free(image[i]);
		free(row_pointers[i]);
	}
	free(image);
	free(row_pointers);
}

#ifdef BLOB
int main(int argc, char* argv[], void** functions) 
{
    gFunctions = functions;
#else
int main (int argc, char **argv)
{
#endif
	clock_t beginProgram = clock();
	if (argc != 4) 
	{
#ifdef DYNAMIC
		printf("Error: incorrect arguments: ./main-dynamic <font_file.ttf> <text> <image.png>\n");
#else
		printf("Error: incorrect arguments: ./main-static <font_file.ttf> <text> <image.png>\n");
#endif
		return 1;
	}
	char* fontName = argv[1];
	FILE* fileFont = fopen(fontName, "rb");
	if (!fileFont) 
	{
		printf("Error of opening font file.\n");
		return 1;
	}
	fclose(fileFont);
	char* textFromArg = argv[2];
	char* imageName = argv[3];
	
#ifdef DYNAMIC
	if (!SO_Init())
		return 1;
	clock_t soLoaded = clock();
    printf("so files loaded, time: %ld clocks (%ld seconds)\n", soLoaded - beginProgram, (soLoaded - beginProgram) / CLOCKS_PER_SEC);
#endif
	
	FT_Library library;
	FT_Face face;
	FT_Bitmap bitmap;
	
	if (FT_Init_FreeType( &library ))
	{
		return 1;
	}
	if (FT_New_Face( library, fontName, 0, &face ))
	{
		return 1;
	}
	
	FT_Set_Pixel_Sizes(face, 0, kFontSize);
	
	int len = strlen(textFromArg);
	
	
	png_bytep * row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * image_heigth);
  	for(int y = 0; y < image_heigth; ++y) 
  	{
    	row_pointers[y] = (png_byte*)malloc(3 * len * kFontSize);
    	memset(row_pointers[y], 0xFF, 3 * len * kFontSize);
  	}
	
	for (int i = 0; i < len; ++i)
	{
		if (textFromArg[i] == ' ') 
		{
			pos_x += kFontSize / 2;
			continue;
		}
		FT_Load_Char(face, textFromArg[i], FT_LOAD_RENDER);
		bitmap = face->glyph->bitmap;
		
		my_draw_bitmap( bitmap, pos_x + 3 * face->glyph->bitmap_left, pos_y - face->glyph->bitmap_top, row_pointers);
	}
	
	png_bytep * image = (png_bytep*)malloc(sizeof(png_bytep) * image_heigth);
	for(int y = 0; y < image_heigth; ++y)
    	image[y] = (png_byte*)malloc(pos_x + 21);
    for (int y = 0; y < image_heigth; ++y)
    	for (int x = 0; x < pos_x + 21; ++x)
    		image[y][x] = row_pointers[y][x];
	
	FILE* png_file = fopen(imageName, "wb");
	
	if (!png_file)
	{
		printf("\tError of writing to png file\n");
		mem_free(image, row_pointers);
		return 0;
	}
	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	
	if (!png_ptr)
	{
		fclose(png_file);
		printf("\tError of writing to png file\n");
		mem_free(image, row_pointers);
		return 0;
	}
	png_infop png_info;
	if (!(png_info = png_create_info_struct(png_ptr)))
	{
		png_destroy_write_struct(&png_ptr, NULL);
		fclose(png_file);
		printf("\tError of writing to png file\n");
		return 0;
	}
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_write_struct(&png_ptr, NULL);
		fclose(png_file);
		printf("\tError of writing to png file\n");
		mem_free(image, row_pointers);
		return 0;
	}
	
	png_init_io(png_ptr, png_file);
	png_set_IHDR(png_ptr, png_info, pos_x / 3 + 7, image_heigth, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	
	png_write_info(png_ptr, png_info);
	png_write_image(png_ptr, image);
	png_write_end(png_ptr, png_info);
	
	png_destroy_write_struct(&png_ptr, &png_info);
	fclose(png_file);
	
	mem_free(image, row_pointers);
	
	clock_t endProgram = clock();

#ifdef BLOB
	printf("Program works: %ld clocks\n", endProgram - beginProgram);
#else
    printf("Program works: %ld clocks (%ld seconds)\n", endProgram - beginProgram, (endProgram - beginProgram) / CLOCKS_PER_SEC);
#endif
	
#ifdef DYNAMIC
	SO_close();
#endif
	
	return 0;
}
