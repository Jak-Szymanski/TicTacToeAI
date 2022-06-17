TRGDIR=.
OBJ=./obj
SRC=./src
INC=./inc
FLAGS= -Wall -g

${TRGDIR}/main: ${OBJ} ${OBJ}/main.o ${OBJ}/gamestate.o\
                     ${OBJ}/vertex.o ${OBJ}/edge.o ${OBJ}/graph.o
	g++ -o ${TRGDIR}/main ${OBJ}/main.o ${OBJ}/gamestate.o\
                     ${OBJ}/vertex.o ${OBJ}/edge.o ${OBJ}/graph.o 
                   
${OBJ}:
	mkdir ${OBJ}

${OBJ}/main.o: ${SRC}/main.cpp inc/graph.h 
	g++ -c ${FLAGS} -o ${OBJ}/main.o ${SRC}/main.cpp

${OBJ}/gamestate.o: ${SRC}/gamestate.cpp inc/gamestate.h
	g++ -c ${FLAGS} -o ${OBJ}/gamestate.o ${SRC}/gamestate.cpp

${OBJ}/vertex.o: ${SRC}/vertex.cpp inc/vertex.h
	g++ -c ${FLAGS} -o ${OBJ}/vertex.o ${SRC}/vertex.cpp

${OBJ}/edge.o: ${SRC}/edge.cpp inc/edge.h
	g++ -c ${FLAGS} -o ${OBJ}/edge.o ${SRC}/edge.cpp

${OBJ}/graph.o: ${SRC}/graph.cpp inc/graph.h
	g++ -c ${FLAGS} -o ${OBJ}/graph.o ${SRC}/graph.cpp

run:
	${TRGDIR}/main

clean:
	rm -f ${TRGDIR}/main ${OBJ}/*
