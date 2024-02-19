/*
	homework_1.cpp
	Jen Martinez
	CS-1124
	9/14/2023

	PROGRAM PURPOSE:
	Program decode a hidden message with rotated letter
	with certain amount of steps to left or right of alphabet.
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// prototypes
void word_traversal(string word, bool reverse, int steps);
char decode(char letter, bool reverse, int steps);

int main() {
	fstream encrypted_text("encrypted.txt");
	if (!encrypted_text) {
		cerr << "The file could not be opened";
	}

	// getting the integer value
	int steps;
	encrypted_text >> steps;

	// setting a reverse steps checker
	bool reverse;
	if (steps > 0) {
		reverse = false;
	}
	else {
		reverse = true;

	}

	// adding data to vector
	string words;
	vector<string> lines;
	while (encrypted_text >> words) {
		lines.push_back(words);
	}
	encrypted_text.close();


	for(size_t i = lines.size()-1; i != 0; --i) {
		string word = lines[i];
		word_traversal(word, reverse, steps);
	}
	// accounts for last instance
	string word = lines[0];
	word_traversal(word, reverse, steps);

}


char decode(char letter, bool reverse, int steps) {
	if (letter >= 'A' && letter <= 'Z') {
		letter -= steps;

		if (!reverse) { // if the steps are reversed
			letter += 26;
		}
		else if (letter > 'Z') {
			letter -= 26;
		}
	}
	return letter;
}

void word_traversal(string word, bool reverse, int steps) {
	for (char& letter : word) {
		letter = decode(letter, reverse, steps); // decode letters
	}
}