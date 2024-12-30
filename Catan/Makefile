CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g -Werror=vla -D_GLIBCXX_USE_CXX11_ABI=0
EXEC = watan
OBJECTS = board.o criterion.o dice.o fairdice.o road.o loaddice.o main.o resourcearray.o state.o student.o textdisplay.o tile.o playerinput.o watan.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
