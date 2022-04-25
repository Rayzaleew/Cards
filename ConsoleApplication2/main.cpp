#include <iostream>
#include <vector>
#include <string>
#include<algorithm>

using namespace std;

class Game {
private:
	struct cards {
		string names;
		string suits;
		int values;
	};
	vector <cards> deck;
	vector <string> names = { "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
	vector <string> suits = { "Пики", "Крести", "Черви", "Буби" };
	vector <cards> first_player;
	vector <cards> second_player;
	vector <cards> table;
	string trump;

	void start() {
		string name;
		int toss_checker = 0;
		building();
		shuffle();
		trump_pick();
		draft(first_player);
		draft(second_player);
		
		if (deque(first_player) > deque(second_player)) {
			name = "Боб";
		}
		else {
			name = "Алиса";
		}
		while (true) {
			if (first_player.size() == 0) {
				cout << "Первый игрок победил! " << endl;
				break;
			} else if (second_player.size() == 0) {
				cout << "Второй игрок победил! " << endl;
				break;
			}
			else if ((first_player.size() == 0) && (second_player.size() == 0)) {
				cout << "Ничья! " << endl;
			}
			
			if (name == "Алиса") {
				while (true) {
					if (toss_checker == 0) {
						move(first_player, name);
						name = "Боб";
					}
					if (counter_move(second_player, name)) {
						if (toss(first_player) != 1) {
							table.clear();
							toss_checker = 0;
							break;
						}
						else {
							toss_checker = 1;
						}
					}
					else {
						for (int i = 0; i < table.size(); i++) {
							second_player.push_back(table.at(i));
						}
						name = "Алиса";
						toss_checker = 0;
						table.clear();
						break;
					}
				}
				
			}
			else if (name == "Боб") {
				if (toss_checker == 0) {
					move(second_player, name);
					name = "Алиса";
				}
				while (true) {
					if (counter_move(first_player, name)) {
						if (toss(second_player) == 0) {
							table.clear();
							break;
						}
						
					}
					else {
						for (int i = 0; i < table.size(); i++) {
							first_player.push_back(table.at(i));
							
						}
						name = "Боб";
						toss_checker = 0;
						table.clear();
						break;
					}
				}
				
			} 
			if (deck.size() != 0) {
				draft(first_player);
			}
			if (deck.size() != 0) {
				draft(second_player);
			}
		}
	}

		

	void building() {
		
		for (int i = 0; i < suits.size(); i++) {
			for (int j = 0; j < names.size(); j++) {
				deck.push_back({names[j], suits[i], j+6});
				
			}
		}
	}
	void shuffle() {
		srand(unsigned(time(NULL)));
		random_shuffle(deck.begin(), deck.end());
	}
	void draft(vector <cards> &hand) {
		int n = 0;
		for (vector <cards>::iterator i = hand.begin(); i != hand.end(); i++) {
			n++;
		}
		if (n > deck.size()) {
			n = deck.size();
		}
			for (int i = 0; i < 6 - n; i++) {
				hand.push_back(deck.at(0));
				deck.erase(deck.begin());
			}
	}
	void trump_pick() {
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

	int deque(vector <cards> &hand) {
		int deque = 14;
		for (int i = 0; i < 6; i++) {
			if ((hand.at(i).suits == trump) && (hand.at(i).values <= deque)) {
				deque = hand.at(i).values;
			}
		}
		return deque;
	}
	void move(vector <cards> &hand, string name) {
		int index = 0;
		cout << "Ходит игрок " << name << endl;
		cout << "Ваши карты: " << endl;
		for (int i = 0; i < hand.size(); i++) {
			cout << i+1 << ". " << hand.at(i).names << ".." << hand.at(i).suits << endl;
		}
		while (true) {
			cout << "Чем Вы хотите сходить? " << endl;
			cin >> index;
			if (index <= hand.size()) {
				table.push_back(hand.at(index-1));
				hand.erase(hand.begin() + (index-1));
				break;
			}
			else {
				cout << "Выберите другую карту" << endl;
			}
		}

	}
	bool counter_move(vector <cards> &hand, string name) {
		int index = 0;
		string choice;
		cout << "Бьётся игрок " << name << endl;
		cout << "Положение на столе:" << endl;
		for (int i = 0; i < table.size(); i++) {
			cout << i+1 << ". " << table.at(i).names << ".." << table.at(i).suits << endl;
		}
		while (true) {
			cout << "Ваши карты: " << endl;
			for (int i = 0; i < hand.size(); i++) {
				cout << i + 1 << ". " << hand.at(i).names << ".." << hand.at(i).suits << "\n";
			}
			
			cout << "Чем Вы хотите отбиться? (0 - взять)" << endl;
			cin >> index;
		if (index != 0) {
			
			if ((hand.at(index - 1).values > table.back().values) &&
				((hand.at(index - 1).suits == table.back().suits)) ||
				(hand.at(index - 1).suits == trump)) {
				table.push_back(hand.at(index - 1));
				hand.erase(hand.begin() + (index - 1));
				return 1;
				//toss();
			}
			else {
				cout << "Выберите другую карту " << endl;
			}
		}
		else {
			cout << "Вы берёте " << endl;
			return 0;
		}
		}
		return 0;
	}

	bool toss(vector <cards>& hand) {
		string choice;
		int index = 0;
		cout << "Положение на столе:" << endl;
		for (int i = 0; i < table.size(); i++) {
			cout << i + 1 << ". " << table.at(i).names << ".." << table.at(i).suits << endl;
		}
		

		while (true) {
			cout << "Какую карту вы хотите подкинуть? (0 - бито)" << endl;

			for (int i = 0; i < hand.size(); i++) {
				cout << i + 1 << ". " << hand.at(i).names << ".." << hand.at(i).suits << endl;
			}
			cin >> index;
			if (index != 0) {
				for (int i = 0; i < table.size(); i++) {
					if (hand.at(index - 1).names == table.at(i).names) {
						table.push_back(hand.at(index - 1));
						hand.erase(hand.begin() + (index - 1));
						return 1;
					}
				}
				cout << "Выберите другую карту (0 - бито)" << endl;
				cout << "Положение на столе:" << endl;
				for (int i = 0; i < table.size(); i++) {
					cout << i + 1 << ". " << table.at(i).names << ".." << table.at(i).suits << endl;
				}
			}
			else {
				return 0;
			}
		}
			
		
		
	}
	public: 
		static Game launch() {
			static Game launcher;
			launcher.start();
			return launcher;
		}
	
};


int main() {
	setlocale(LC_ALL, "");

	Game::launch();
	
	return 0;
}