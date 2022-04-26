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