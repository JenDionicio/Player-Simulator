
#ifndef polynomial_hpp
#define polynomial_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

class Polynomial{
    struct Node{
        Node(int data);
        Node();
        int data;
        Node* next;
    };
    Node* header;
    int degree;

    friend std::ostream&  operator<<(std::ostream& os, const Polynomial& rhs );
    
    friend bool operator !=(const Polynomial& lhs, const Polynomial& rhs);

    friend bool operator ==(const Polynomial& lhs, const Polynomial& rhs);
    
public:
    Polynomial();
    
    Polynomial(const std::vector<int>& coeff);

    //copy constructor
    ~Polynomial();

    Polynomial(const Polynomial& rhs);   

    Polynomial& operator = (const Polynomial& rhs);
    
    // += operator
    Polynomial& operator+=(const Polynomial& rhs);

    // methods
    int evaluate(int value) const;
    int eval_curr(int val, int exp) const;
    
    void cleanup();
     
};


// + operator
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);


void doNothing(Polynomial temp);


#endif /* polynomial_hpp */

