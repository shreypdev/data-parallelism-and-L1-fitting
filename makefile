# build an executable named myprog from myprog.c
CC = gcc
C_FLAGS = -Wall -g
OPENMP_FLAG = -fopenmp
MATH_LIB_FLAG = -lm
FILE_NAME = dataPar.c
EXECUTABLE_NAME = dataPar
OBJECT_FILE_NAME = dataPar.o

all: ${FILE_NAME} 
	${CC} -o ${EXECUTABLE_NAME} ${FILE_NAME} ${OPENMP_FLAG} ${MATH_LIB_FLAG}
clean:
	rm -f ${EXECUTABLE_NAME} ${OBJECT_FILE_NAME}
run: ${EXECUTABLE_NAME}
	./${EXECUTABLE_NAME}


# "all" can also have : ${CC} ${C_FLAGS} -o ${EXECUTABLE_NAME} ${FILE_NAME} ${THREAD_FLAG},
# but this will check for warnings and thus not need for production builds.