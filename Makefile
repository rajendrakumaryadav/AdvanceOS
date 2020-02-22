CC=gcc
CXX=g++
NAME=22
FILES=${NAME}.c
FLAGS=--std=c11 -Wall -g
OUTPUT=./bin/${NAME}

main: ${FILES}
	${CC} ${FILES} ${FLAGS} -o ${OUTPUT}

run: main ${FILES}
	${OUTPUT}
