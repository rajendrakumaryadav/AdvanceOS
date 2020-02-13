CC=gcc
NAME=10
FILES=${NAME}.c
OUTPUT=${NAME}
main:
	${CC} ${FILES}  -o ${OUTPUT}
run: ${OUTPUT} ${FILES}
	./${OUTPUT}
