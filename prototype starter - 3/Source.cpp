/*
	Jen Martinez
	10/02/2023
	homework_3
	OOP
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


class Warrior {
public:

	Warrior(const string& name, const string& weaponName, int& strength)
		: name(name), weapon(weaponName, strength) {}
	// basic getters
	const string& getName() const { return name; };
	const string& getWeapon() const { return weapon.getWeaponName(); };
	int getStrength() const { return weapon.getWeaponStrength(); }

	// calling change func
	void changeStrength(int change) {
		weapon.changeStrength(change);

	}
	friend ostream& operator << (ostream& os, const Warrior& currWarrior) {
		os << "Warrior: " << currWarrior.name << ", " << currWarrior.weapon; //<-- calls os in Weapon class 
		return os;
	};
// don't wanna show weapon stats
private:
	class Weapon {
	private:
		string weaponName;
		int weaponStrength;

	public:
		Weapon(const string& weapon, int strength) : weaponName(weapon), weaponStrength(strength) {}

		// basic getters
		const string& getWeaponName() const { return weaponName; }
		const int getWeaponStrength() const { return weaponStrength; }

		void changeStrength(int change) {
			if (change < getWeaponStrength()) { //comparing strengths
				weaponStrength -= change;
			}
			else {
				// overwriting strengths
				weaponStrength = 0;
			}
		}

		// displating just weapon
		friend ostream& operator << (ostream& os, const Weapon& currWeapon) {
			os << "weapon: " << currWeapon.weaponName << ", " << currWeapon.weaponStrength; // calling ostream of weapon
			return os;
		}

	};
	string name;
	Weapon weapon;
};


void status(const vector <Warrior>& warriorVect);
void battle(const string& name1, const string& name2, vector<Warrior>& warriorVect);
int main() {
	// initializing and opening file
	ifstream warriorsFile("warriors (1).txt");
	if (!warriorsFile) {
		cerr << "The file selected could not be opened." << endl;;
		exit(1);
	}
	vector<Warrior> warriorVect; // stores warriors and their info
	string command, name, weapon;
	int strength;

	while (warriorsFile >> command) {
		if (command == "Warrior") {
			warriorsFile >> name >> weapon >> strength;
			// initializing warrior and tracking in vector
			warriorVect.emplace_back(name, weapon, strength);
		}
		else if (command == "Status") {
			status(warriorVect);
		}
		else {
			string opponent;
			warriorsFile >> name >> opponent;
			battle(name, opponent, warriorVect);
		}
	}
	warriorsFile.close();
}

void battle(const string& name1, const string& name2, vector<Warrior>& warriorVect) {
	cout << name1 << " battles " << name2 << endl;
	size_t index1 = warriorVect.size();
	size_t index2 = warriorVect.size();

	// finding warrior's strength
	for (size_t i = 0; i < warriorVect.size(); i++) {
		Warrior currWarrior = warriorVect[i];
		if (currWarrior.getName() == name1) {
			index1 = i;
		}
		else if (currWarrior.getName() == name2) {
			index2 = i;
		}
	}

	// setting warriors
	Warrior& warrior1 = warriorVect[index1];
	Warrior& warrior2 = warriorVect[index2];
	int strength1 = warrior1.getStrength();
	int strength2 = warrior2.getStrength();


	//both warriors alive
	if (strength1 != 0 && strength2 != 0) {
		if (strength1 == strength2) {
			// same strength
			cout << "Mutual Annihilation: " << warrior1.getName() << " and " << warrior2.getName()
				<< " die at each other's hands" << endl;

			// setting difference
			warrior1.changeStrength(strength2);
			warrior2.changeStrength(strength1);
		}
		else if (strength1 > strength2) { // warrior1 is stronger
			cout << warrior1.getName() << " defeats " << warrior2.getName() << endl;
			warrior1.changeStrength(strength2);
			warrior2.changeStrength(strength1);
		}
		else { // warrir2 is stronger
			cout << warrior2.getName() << " defeats " << warrior1.getName() << endl;
			warrior1.changeStrength(strength2);
			warrior2.changeStrength(strength1);
		}
	}
	else { // either or both are dead
		if (strength1 == 0 && strength2 == 0) {
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
		else if (strength1 == 0) {
			cout << "He's dead, " << warrior2.getName() << endl;
		}
		else if (strength2 == 0) {
			cout << "He's dead, " << warrior1.getName() << endl;
		}
	}
}
void status(const vector <Warrior>& warriorVect) {
	// basic display -- overwritten os in class
	cout << "There are: " << warriorVect.size() << " warriors" << endl;
	for (Warrior currWarrior : warriorVect) {
		cout << currWarrior << endl;
	}
}