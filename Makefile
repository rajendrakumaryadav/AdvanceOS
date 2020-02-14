CC=gcc
NAME=13
FILES=${NAME}.c
FLAGS=--std=c11 -Wall -g
OUTPUT=${NAME}
main:
	${CC} ${FILES} ${FLAGS}  -o ${OUTPUT}
run: ${OUTPUT} ${FILES}
	./${OUTPUT}
