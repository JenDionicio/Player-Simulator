#ifndef Protectors_hpp
#define Protectors_hpp
#include <iostream>
#include <vector>
#include <string>

#include <stdio.h>


namespace WarriorCraft{
    class Protector{
        friend std::ostream& operator<<(std::ostream& os, const Protector& rhs);
        std::string name;
        double strength;
        Lord* lordptr;
    public:
        
        Protector(const std::string& name, double strength);
        // getters 
        const std::string& getName()const;
        double getStrength() const;

        // methods
        const Lord* isHired() const;
        void changeStrength(double new_strength);
        void setBoss(Lord* lord);
        void runaway();
        virtual void defend()=0;
    };

    class Warrior: public Protector{
    public:
        using Protector::Protector;
    };
    class Wizard: public Protector{
        friend std::ostream& operator<<(std::ostream& os, const Wizard& rhs);
    public:
        using Protector::Protector;
        void defend();
    };
    class Archer: public Warrior{
        friend std::ostream& operator<<(std::ostream& os, const Archer& rhs);
    public:
        using Warrior::Warrior;
        void defend();
    };
    class Swordsman: public Warrior{
        friend std::ostream& operator<<(std::ostream& os, const Swordsman& rhs);
    public:
        using Warrior::Warrior;
        void defend();
        
    };
}

#endif //protector.hpp
