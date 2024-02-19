#include "Noble.hpp"
#include "Protector.hpp"
#include <iostream>
#include <string> 

using namespace std;

namespace  WarriorCraft{

        
    Noble::Noble(const string& theName): name(theName), alive(true){}
    const string& Noble::getName() const {return name;}
    const bool Noble::isAlive() const {return alive;}
    void Noble::changeAlive(bool newStatus){alive=newStatus;}
    bool Noble::checkLiving(Noble& noble){
        if (!(alive) && !(noble.alive) ){
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
            return true;
        }
        if (!(alive)) {
            cout << "He's dead " << noble.name << endl;
            return true;
        }
        if(!(noble.alive)){
            cout << "He's dead " << name << endl;
            return true;
        }
        return false;
    }
    void Noble::battle(Noble& noble){
        cout<< name << " battles " << noble.name<< endl;
        
        if(alive){
            battleCry();
        }
        if(noble.alive){
            noble.battleCry();
        }
        
        if(!(checkLiving(noble))){
            if (getStrength()==noble.getStrength()){
                cout<<"Mutual Annihilation: "<< name << " and "<<noble.name;
                
                cout<<" die at each other's hands"<< endl;
                
                lose();
                noble.lose();

            }else if(getStrength() > noble.getStrength()){
                cout<< name <<" defeats "<<noble.name<<endl;
                win(noble);
                noble.lose();
            }else{
                cout<< noble.name <<" defeats "<< name << endl;
                noble.win(*this);
                lose();
            }
            
        }
        
    }


    ostream& operator<<(ostream& os, const Lord& lord){
        os << lord.getName() << " has an army of size: " << lord.army.size() << endl;
        for(Protector* protectors: lord.army){
            os << "    ";
            os << *protectors;
        }
        return os;
    }

    Lord::Lord(const string& theName):Noble(theName){}

    void Lord::changeAlive(){
        if (army.size() !=0 && getStrength() == 0){
            Noble::changeAlive(false);
        }
        Noble::changeAlive(true);
    }

    bool Lord::ranaway(Protector& protector){
        size_t temp = army.size();
        for(size_t index=0; index<army.size(); ++index){
            if(army[index] == &protector){
                temp=index;
                break;
            }
        }
        if(temp== army.size()){return false;}
        
        if(temp == army.size()-1){
            army[temp]->setBoss(nullptr);
            army.pop_back();
            
        }else{
            army[temp]->setBoss(nullptr);
            for(size_t index = temp; index<army.size()-1; ++index){
                army[index]=army[index+1];
            }
            army.pop_back();
        }
        return true;
    }

    bool Lord::hires(Protector& protector){
        if(protector.getStrength()==0){
            return false;
        }
        if (!(isAlive())){
            return false;
        }
        if(protector.isHired()!=nullptr){
            return false;
        }
        Protector* protectorPtr = &protector;
        army.push_back(protectorPtr);
        protector.setBoss(nullptr);
        protector.setBoss(this);
        return true;
    }

    bool Lord::fires(Protector& protector){
        if(protector.getStrength()==0){
            return false;
        }
        if(!(isAlive())){
            return false;
        }
        size_t temp=army.size();
        for(size_t index = 0; index < army.size(); ++index){
            if(army[index] == &protector){
                temp=index;
                break;
            }
        }
        cout<<protector.getName()<< " You don't work for me anymore "<<"! ";
        
        cout << " -- " << getName() << endl;
        if(temp==army.size()){return false;}
        
        if(temp==army.size()-1){
            army[temp]->setBoss(nullptr);
            army.pop_back();
        }else{
            army[temp]->setBoss(nullptr);
            for(size_t index= temp; index<army.size()-1; ++index){
                army[index]=army[index+1];
            }
            army.pop_back();
        }
        return true;
    }

    double Lord::getStrength() const{
        double strength=0;
        for(size_t index=0; index< army.size(); ++index){
            strength+=army[index]->getStrength();
        }
        return strength;
    }

    void Lord::lose(){
        for(size_t i=0; i<army.size(); ++i){
            army[i]->changeStrength(0);
        }
        Noble::changeAlive(false);
    }

    void Lord::win(const Noble& noble){
        double strength_1=getStrength();
        double strength_2=noble.getStrength();
        for(size_t i=0; i<army.size(); ++i){
            double new_strength=(army[i]->getStrength()-(army[i]->getStrength()*(strength_2/strength_1)));
            army[i]->changeStrength(new_strength);
        }

    }

    void Lord::battleCry(){
        for(Protector* protector:army){
            protector->defend();
        }
    }


    ostream& operator<<(ostream& os , const PersonWithStrengthToFight& person){
        os << person.getName() << " has strength: "
         << person.getStrength() << endl;
        return os;
    }


    PersonWithStrengthToFight::PersonWithStrengthToFight (const string& name, double strength): Noble(name), strength(strength) {}

    double PersonWithStrengthToFight::getStrength() const{return strength;}

    void PersonWithStrengthToFight::lose(){
        strength=0;
        changeAlive(false);
    }

    void PersonWithStrengthToFight::win(const Noble& noble){
        double strength_1= getStrength();
        double strength_2= noble.getStrength();
        double update_strength=(strength_1 -(strength_1 * (strength_2 / strength_1)));
        strength=update_strength;
    }

    void PersonWithStrengthToFight::battleCry(){
        cout<<"Ugh!"<<endl;
    }
}