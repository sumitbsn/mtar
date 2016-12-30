CC = gcc
mtar: main.o compress_rl.o compress_ke.o decompress_rl.o decompress_ke.o dir_compress.o dir_decompress.o
	${CC} -o mtar main.o compress_rl.o compress_ke.o decompress_rl.o decompress_ke.o dir_compress.o dir_decompress.o mtar.h -lm  
main.o: main.c
	${CC} -c -g main.c mtar.h
compress_rl.o: compress_rl.c
	${CC} -c -g compress_rl.c mtar.h
compress_ke.o: compress_ke.c 
	${CC} -c -g compress_ke.c mtar.h
decompress_rl.o: decompress_rl.c
	${CC} -c -g decompress_rl.c mtar.h
decompress_ke.o: decompress_ke.c
	${CC} -c -g decompress_ke.c mtar.h
dir_compress.o: dir_compress.c
	${CC} -c -g dir_compress.c mtar.h
dir_decompress.o: dir_decompress.c
	${CC} -c -g dir_decompress.c mtar.h
clean:
	rm -rf *.o mtar
