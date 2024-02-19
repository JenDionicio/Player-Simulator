#include "Noble.hpp"
#include "Protector.hpp"
#include <iostream>
#include <string>

using namespace std;

namespace WarriorCraft{

    ostream& operator<<(ostream& os, const Protector& protector){
        os << protector.getName() << " has strength " << protector.getStrength() << endl;
        return os;
    }


    Protector::Protector(const string& theName, double theStrength):
        name(theName),strength(theStrength), lordptr(nullptr){}

    // getters
    double Protector::getStrength() const {return strength;}
    const string& Protector::getName()const {return name;}
    
    // methids
    const Lord* Protector::isHired() const {return lordptr;}
    void Protector::setBoss(Lord* newLord) {lordptr=newLord;}
    void Protector::changeStrength(double newStrength) {strength=newStrength;}

    void Protector::runaway(){
        cout << name << " flees in terror, abandoning his lord, " <<  lordptr->getName() << endl;
        lordptr->ranaway(*this);
    }
        
    // could be implemented together
    ostream& operator<<(ostream& os, const Wizard& warrior){
        os << warrior.getName() << " has strength " << warrior.getStrength() << endl;
        return os;
    }
    void Wizard::defend(){
        cout << "POOF! " << endl;
    }
    ostream& operator<<(ostream& os, const Archer& warrior){
        os << warrior.getName() << " has strength " << warrior.getStrength() << endl;
        return os;
    }

    void Archer::defend(){
        cout << "TWANG!  " << getName() << " says: Take that in the name of my lord, " <<  
        isHired()->getName() << endl;
    }


    ostream& operator<<(ostream& os, const Swordsman& warrior){
        os << warrior.getName() << " has strength: " << warrior.getName() << endl;
        return os;
    }

    void Swordsman::defend(){
        cout << "CLANG!  " << getName() << " says: Take that in the name of my lord, " <<  
        isHired()->getName() << endl;
    }


}