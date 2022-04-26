#include "Game.h"



int main() {
	setlocale(LC_ALL, "");
	Player first_player, second_player;
	Game launcher;
	//Deck builder;
	//builder.build_deck();
	launcher.start(first_player, second_player);
	
	return 0;
}