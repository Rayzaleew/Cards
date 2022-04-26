#pragma once
#include <iostream>
#include <vector>
#include <string>
#include<algorithm>

using namespace std;

struct cards {
	string names;
	string suits;
	int values;
};

class Player {
	friend class Game;
public:
	vector<cards> hand;

};



class Game {
	friend class Deck;
public:
	vector <cards> deck;
	vector <string> names = { "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
	vector <string> suits = { "Пики", "Крести", "Черви", "Буби" };
	vector <cards> table;
	string trump;
	void draft(vector <cards>& hand);
	int deque(vector <cards>& hand);
	void move(vector <cards>& hand, string name);
	bool counter_move(vector <cards>& hand, string name);
	bool toss(vector <cards>& hand);
public:
	void start(Player& first_player, Player& second_player);
};

class Deck  : public Game{
public:
	void build_deck(Game &launcher) {
		building(launcher.deck);
		shuffle(launcher.deck);
		trump_pick(launcher.deck, launcher.trump);
		
	}
public:
	void building(vector <cards> &deck) {

		for (int i = 0; i < suits.size(); i++) {
			for (int j = 0; j < names.size(); j++) {
				deck.push_back({ names[j], suits[i], j + 6 });

			}
		}
	}
	void shuffle(vector <cards>& deck) {
		srand(unsigned(time(NULL)));
		random_shuffle(deck.begin(), deck.end());
	}

	void trump_pick(vector <cards>& deck, string &trump) {
		trump = deck.at(0).suits;
		cout << "Козырь: " << trump << endl;
		deck.push_back(deck.front());
		deck.erase(deck.begin());
		for (int i = 0; i < deck.size(); i++) {
			if (deck.at(i).suits == trump) {
				deck.at(i).values += 9;
			}

		}
	}
};


