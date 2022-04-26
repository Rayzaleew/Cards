#include "Game.h"


void Game::start(Player& first_player, Player& second_player) {

	string name;
	int toss_checker = 0;
	building();
	shuffle();
	trump_pick();
	draft(first_player.hand);
	draft(second_player.hand);

	if (deque(first_player.hand) > deque(second_player.hand)) {
		name = "���";
	}
	else {
		name = "�����";
	}
	while (true) {
		if (first_player.hand.size() == 0) {
			cout << "������ ����� �������! " << endl;
			break;
		}
		else if (second_player.hand.size() == 0) {
			cout << "������ ����� �������! " << endl;
			break;
		}
		else if ((first_player.hand.size() == 0) && (second_player.hand.size() == 0)) {
			cout << "�����! " << endl;
		}

		if (name == "�����") {
			if (toss_checker == 0) {
				move(first_player.hand, name);
				name = "���";
			}
			while (true) {
				if (counter_move(second_player.hand, name)) {
					if (toss(first_player.hand) != 1) {
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
						second_player.hand.push_back(table.at(i));
					}
					name = "�����";
					toss_checker = 0;
					table.clear();
					break;
				}
			}

		}
		else if (name == "���") {
			if (toss_checker == 0) {
				move(second_player.hand, name);
				name = "�����";
			}
			while (true) {
				if (counter_move(first_player.hand, name)) {
					if (toss(second_player.hand) == 0) {
						table.clear();
						break;
					}

				}
				else {
					for (int i = 0; i < table.size(); i++) {
						first_player.hand.push_back(table.at(i));

					}
					name = "���";
					toss_checker = 0;
					table.clear();
					break;
				}
			}

		}
		if (deck.size() != 0) {
			draft(first_player.hand);
		}
		if (deck.size() != 0) {
			draft(second_player.hand);
		}
	}
}

void Game::building() {

	for (int i = 0; i < suits.size(); i++) {
		for (int j = 0; j < names.size(); j++) {
			deck.push_back({ names[j], suits[i], j + 6 });

		}
	}
}
void Game::shuffle() {
	srand(unsigned(time(NULL)));
	random_shuffle(deck.begin(), deck.end());
}
void Game::draft(vector <cards>& hand) {
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
void Game::trump_pick() {
	trump = deck.at(0).suits;
	cout << "������: " << trump << endl;
	deck.push_back(deck.front());
	deck.erase(deck.begin());
	for (int i = 0; i < deck.size(); i++) {
		if (deck.at(i).suits == trump) {
			deck.at(i).values += 9;
		}

	}
}

int Game::deque(vector <cards>& hand) {
	int deque = 23;
	for (int i = 0; i < 6; i++) {
		if ((hand.at(i).suits == trump) && (hand.at(i).values <= deque)) {
			deque = hand.at(i).values;
		}
	}
	return deque;
}
void Game::move(vector <cards>& hand, string name) {
	int index = 0;
	cout << "����� ����� " << name << endl;
	cout << "���� �����: " << endl;
	for (int i = 0; i < hand.size(); i++) {
		cout << i + 1 << ". " << hand.at(i).names << ".." << hand.at(i).suits << endl;
	}
	while (true) {
		cout << "��� �� ������ �������? " << endl;
		cin >> index;
		if (index <= hand.size()) {
			table.push_back(hand.at(index - 1));
			hand.erase(hand.begin() + (index - 1));
			break;
		}
		else {
			cout << "�������� ������ �����" << endl;
		}
	}

}
bool Game::counter_move(vector <cards>& hand, string name) {
	int index = 0;
	string choice;
	cout << "������ ����� " << name << endl;
	cout << "��������� �� �����:" << endl;
	for (int i = 0; i < table.size(); i++) {
		cout << i + 1 << ". " << table.at(i).names << ".." << table.at(i).suits << endl;
	}
	while (true) {
		cout << "���� �����: " << endl;
		for (int i = 0; i < hand.size(); i++) {
			cout << i + 1 << ". " << hand.at(i).names << ".." << hand.at(i).suits << "\n";
		}

		cout << "��� �� ������ ��������? (0 - �����)" << endl;
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
				cout << "�������� ������ ����� " << endl;
			}
		}
		else {
			cout << "�� ����� " << endl;
			return 0;
		}
	}
	return 0;
}

bool Game::toss(vector <cards>& hand) {
	string choice;
	int index = 0;
	cout << "��������� �� �����:" << endl;
	for (int i = 0; i < table.size(); i++) {
		cout << i + 1 << ". " << table.at(i).names << ".." << table.at(i).suits << endl;
	}


	while (true) {
		cout << "����� ����� �� ������ ���������? (0 - ����)" << endl;

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
			cout << "�������� ������ ����� (0 - ����)" << endl;
			cout << "��������� �� �����:" << endl;
			for (int i = 0; i < table.size(); i++) {
				cout << i + 1 << ". " << table.at(i).names << ".." << table.at(i).suits << endl;
			}
		}
		else {
			return 0;
		}
	}



}


