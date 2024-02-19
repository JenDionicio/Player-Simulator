#ifndef Noble_hpp
#define Noble_hpp
#include <iostream>
#include <vector>
#include <string>

#include <stdio.h>

namespace WarriorCraft{

    class Protector;

    class Noble{
        std::string name;
        bool alive;
       
    public:
        const bool isAlive() const;
        void changeAlive(bool new_status);
        virtual double getStrength() const =0;
        bool checkLiving(Noble& noble);
        virtual void lose()=0;
        virtual void win(const Noble& noble)=0;
        virtual void battleCry()=0;
        void battle(Noble& noble);
        Noble(const std::string& name);
        const std::string& getName()const;
    }; // Noble

    class Lord : public Noble {
        friend std::ostream& operator<<(std::ostream& os, const Lord& lord);
        std::vector<Protector*>army;

    public:
        // getters
        double getStrength() const;

        // methods
        bool ranaway(Protector& protector);
        Lord(const std::string& name);
        void changeAlive();
        bool hires(Protector& protector);
        bool fires(Protector& protector);  
        void lose();
        void win(const Noble& noble);
        void battleCry();
    }; // lord



    class  PersonWithStrengthToFight : public Noble{
        friend std::ostream& operator<<(std::ostream& os , 
        const PersonWithStrengthToFight& person);
        double strength;
    public:
        PersonWithStrengthToFight (const std::string& name, double strength);
        
        // getters
        double getStrength() const;

        // methods
        void win(const Noble& noble);
        void lose();
        void battleCry();
        
    }; //PersonWithStrengthToFight

}



#endif /* Noble_hpp */