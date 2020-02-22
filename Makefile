CC=gcc
CXX=g++
NAME=22
FILES=${NAME}.c
FLAGS=--std=c11 -Wall -extras -pedantic -g
OUTPUT=./bin/${NAME}

main: ${FILES}
	${CC} ${FILES} ${FLAGS} -o ${OUTPUT}

prog: ${FILES} main
	${OUTPUT}
remove:	${OUTPUT}
		-rm -rf ${OUTPUT}
