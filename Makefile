CC=gcc
NAME=12
FILES=${NAME}.c
FLAGS=--std=c11 -Wall -g
OUTPUT=./bin/${NAME}

main: ${FILES}
	${CC} ${FILES} ${FLAGS} -o ${OUTPUT}
	-clear

run: ${OUTPUT} ${FILES} main
	${OUTPUT}
