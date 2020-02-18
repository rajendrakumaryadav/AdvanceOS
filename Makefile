CC=gcc
NAME=16
FILES=${NAME}.c
FLAGS=--std=c11 -Wall -g
OUTPUT=./bin/${NAME}

main: ${FILES}
	${CC} ${FILES} ${FLAGS} -o ${OUTPUT}
	-clear

run: main ${FILES}
	${OUTPUT}
