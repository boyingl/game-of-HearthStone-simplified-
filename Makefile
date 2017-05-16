CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla 
EXEC = sorcery
OBJECTS = sorcery.o gameMaster.o player.o card.o complexMinion.o minion.o enchantment.o ritual.o spell.o concreteRitual.o concreteSpell.o concreteMinion.o concreteEnchantment.o textDisplay.o graphicDisplay.o ascii_graphics.o graphicUtil.o window.o display.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
  
