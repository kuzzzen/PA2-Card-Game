card.o: src/card.cpp src/card.h src/effects/effect.h \
  src/effects/effectDamage.h src/effects/effectHealing.h \
  src/effects/effectGetCard.h src/effects/../players/player.h \
  src/effects/../players/../card.h src/effects/effectRestriction.h
deckLoader.o: src/deckLoader.cpp src/deckLoader.h src/card.h \
  src/effects/effect.h src/effects/effectDamage.h \
  src/effects/effectHealing.h src/effects/effectGetCard.h \
  src/effects/../players/player.h src/effects/../players/../card.h \
  src/effects/effectRestriction.h
game.o: src/game.cpp src/game.h src/card.h src/effects/effect.h \
  src/effects/effectDamage.h src/effects/effectHealing.h \
  src/effects/effectGetCard.h src/effects/../players/player.h \
  src/effects/../players/../card.h src/effects/effectRestriction.h \
  src/menus/menu.h src/menus/../card.h src/menus/gameMenu.h \
  src/players/player.h src/players/playerComputer.h src/deckLoader.h
howToPlayWindow.o: src/howToPlayWindow.cpp src/howToPlayWindow.h
main.o: src/main.cpp src/menus/menu.h src/menus/../card.h \
  src/effects/effect.h src/effects/effectDamage.h \
  src/effects/effectHealing.h src/effects/effectGetCard.h \
  src/effects/../players/player.h src/effects/../players/../card.h \
  src/effects/effectRestriction.h src/game.h src/card.h \
  src/menus/gameMenu.h src/players/player.h src/players/playerComputer.h \
  src/howToPlayWindow.h src/deckLoader.h
