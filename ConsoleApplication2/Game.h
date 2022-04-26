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
private:
	vector<cards> hand;

};



class Game {
private:
	vector <cards> deck;
	vector <string> names = { "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
	vector <string> suits = { "Пики", "Крести", "Черви", "Буби" };
	vector <cards> table;
	string trump;
	void building();
	void shuffle();
	void draft(vector <cards>& hand);
	void trump_pick();
	int deque(vector <cards>& hand);
	void move(vector <cards>& hand, string name);
	bool counter_move(vector <cards>& hand, string name);
	bool toss(vector <cards>& hand);
public:
	void start(Player& first_player, Player& second_player);
};

