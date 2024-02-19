//jen martinez
//homework_2
//9/21/2023
//OOP


#include <iostream>
#include <fstream>
#include <vector>
using namespace std;



struct Warrior {
	// maybe make these varibles private
	string name;
	int strength;
	void setStats(const string& theName, int theStrength) {
		name = theName;
		strength = theStrength;
	}
};
void battle(Warrior& warriorOne, Warrior warriorTwo);
void status(const vector<Warrior>& allWarriors);
size_t location(string& name, vector<Warrior> allWarriors);

int main() {
	ifstream warriorsFile("warriors.txt");
	if (!warriorsFile) {
		cerr << "The file could not be opened.";
	}

	string command, name;
	int strength;
	vector<Warrior> allWarriors;
	while (warriorsFile >> command) {
		if (command == "Warrior") {
			warriorsFile >> name >> strength;
			Warrior currWarrior;
			currWarrior.setStats(name, strength);
			allWarriors.push_back(currWarrior);
		}
		else if (command == "Status") {
			status(allWarriors);
		}
		else {
			string nameOne, nameTwo;
			warriorsFile >> nameOne >> nameTwo;
			size_t warriorOne = location(nameOne, allWarriors);
			size_t warriorTwo = location(nameTwo, allWarriors);
			battle(allWarriors[warriorOne], allWarriors[warriorTwo]);
		}
	}
}

void status(const vector<Warrior>& allWarriors){
	cout << "There are: " << allWarriors.size() << " warriors" << endl;
	for (int i = 0; i < allWarriors.size(); i++) {
		Warrior currWarrior;
		currWarrior = allWarriors[i];
		cout << "Warrior: " << currWarrior.name << ", strength: " << currWarrior.strength << endl;
	}
}

size_t location(string& name, vector<Warrior> allWarriors) {
	size_t warriorIndex = 0;
	for (int i = 0; i < allWarriors.size(); i++) {
		Warrior currWarrior;
		currWarrior = allWarriors[i];
		if (currWarrior.name == name) {
			warriorIndex = i;
			break;
		}
	}
	return warriorIndex;
}

void battle(Warrior& warriorOne, Warrior warriorTwo) {
	cout << warriorOne.name << " battles " << warriorTwo.name << endl;
	// checking if alive
	if (warriorOne.strength > 0 && warriorTwo.strength > 0) {
		if (warriorOne.strength > warriorTwo.strength) {
			cout << warriorOne.name + " defeats " + warriorTwo.name << endl;
			warriorTwo.strength = 0;
			cout << "HERE.";
		}
		else if (warriorOne.strength < warriorTwo.strength) {
			cout << warriorTwo.name + " defeats " + warriorOne.name << endl;
			warriorOne.strength = 0;
		}
		else {
			cout << "Mutual Annihilation: " << warriorOne.name << " and " <<
				warriorTwo.name << " die at each other's hands" << endl;
			warriorOne.strength = 0;
			warriorTwo.strength = 0;
		}
	}
	else {
		if (warriorOne.strength == 0) {
			cout << "He's dead, " + warriorOne.name << endl;
		}
		else if(warriorTwo.strength == 0){
			cout << "He's dead, " + warriorTwo.name << endl;
		}
		else {
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
	}
}