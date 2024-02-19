#include "polynomial.h"
using namespace std;

ostream& operator<<(ostream& os, const Polynomial& rhs ){
    Polynomial::Node* curr = rhs.header;
    int degree = rhs.degree;

    if(curr != nullptr && curr->data == 0 && degree == 0){
        os <<  0;
        return os;
    }

    while(curr != nullptr){
        while(curr->data == 0){
            curr = curr->next;
            --degree;
        }

        if(curr->data <= 1 && degree == 1){
            if(curr->data != -1){
                os <<  "x + ";
            }else{
                os <<  "-x + ";
            }
        }
        if(curr->data > 1 && degree >= 1) {
            if(degree == 1){
                os << curr->data << "x" <<  " + ";
            }
            if(curr->data == -1) {
                os << curr->data << "-x^" << degree << " + ";
            }else{
                os << curr->data << "x^" << degree << " + ";
            }

            }
        if(curr->data <= 1   && degree > 1 ){
            if(curr->data != -1){
                os << "x^" << degree << " + ";
            }else{
                os << "-x^" << degree << " + ";
            }


        }
        if(degree == 0 ){
            os << curr->data;
        }
        --degree;
        curr = curr->next;
    }
    return os;
}

Polynomial::Node::Node():data(0),next(nullptr){}
Polynomial::Node::Node(int data): data(data), next(nullptr){}


Polynomial::Polynomial():header(new Node()), degree(0){}
Polynomial::Polynomial(const vector<int>& coeff): degree(coeff.size()-1){
    header=new Node(coeff[0]);
    Node* curr=header;
    for(size_t i=1; i<coeff.size(); i++){
        Node* curr_node=new Node(coeff[i]);
        curr->next=curr_node;
        curr=curr->next;
    }
    cleanup();
}

Polynomial::~Polynomial(){
    while(header!=nullptr){
        Node* hold=header->next;
        delete header;
        header=hold;
        
    }
    header=nullptr;
   
}


Polynomial::Polynomial(const Polynomial& rhs): degree(rhs.degree) {
    header = new Node(rhs.header -> data);
    Node* curr = header;
    Node* other = rhs.header -> next;
    while(other != nullptr){
        Node* curr_node = new Node(other -> data);
        curr -> next = curr_node;
        curr = curr->next;
        other = other -> next;
    }
    degree = rhs.degree;
}

Polynomial& Polynomial::operator = (const Polynomial& rhs){
    if (this != &rhs){
        Node* curr = header;
        while(curr != nullptr){
            Node* curr = curr -> next;
            delete curr;
            curr = curr;
        }
        header = nullptr;
        header = new Node(rhs.header -> data);
        Node* curr = header;
        Node* other = rhs.header -> next;
        while (other != nullptr){
            Node* curr_node = new Node(other -> data);
            curr -> next = curr_node;
            curr = curr -> next;
            other = other -> next;
        }
        degree = rhs.degree;

    }
    return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
    Node* lhs = header;
    Node* other = rhs.header;

    if(rhs.degree > degree) {
        int diff=degree-rhs.degree;
        for(size_t i=0; i<diff; i++){
            lhs=lhs->next;
        }
        //Node* curr_lhs = lhs;
        while(other != nullptr) {
            int new_val = lhs->data + other->data;
            lhs->data = new_val;
            lhs = lhs->next;
            other = other->next;
        }

    } else {
            int diff = rhs.degree - degree;//3
            Node* new_head = new Node(other->data);
            Node* new_curr = new_head;
            other = other->next;
            for(size_t i = 1; i < diff; i++) {
                Node* new_node = new Node(other->data);
                new_curr->next = new_node;
                new_curr = new_curr->next;
                other = other->next;
            }
            while(other != nullptr) {
                int new_val = lhs->data + other->data;
                lhs->data = new_val;
                lhs = lhs->next;
                other = other->next;
            }
            degree = rhs.degree;
            new_curr->next = header;
            header = new_head;
    }
    cleanup();
    return *this;
}


int Polynomial::evaluate(int value) const{
    Node* curr = header;
    int result = 0;
    int degree = degree;
    while(curr != nullptr){
        if(degree == 0){
            result += curr->data;
        }else{
            result += (curr->data * eval_curr(value,degree));

        }
        curr = curr->next;
        degree--;
    }
    return result;

}

int Polynomial::eval_curr(int val, int exp) const{
   while (exp > 1){
       val *= val; 
       --exp;
   }
   return val;
}

void Polynomial::cleanup() {
    while (header->next && header->data == 0){
        header = header->next;
        --degree;
    }
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial res = lhs;
    // making use of the other functions
    res += rhs;
    return res;
}

void doNothing(Polynomial temp) {}

bool operator !=(const Polynomial& lhs, const Polynomial& rhs){
    return !(lhs==rhs);
}

bool operator ==(const Polynomial& lhs, const Polynomial& rhs){
    if (lhs.degree==rhs.degree){
        Polynomial::Node* lhs_curr=lhs.header;
        Polynomial::Node* rhs_curr=rhs.header;
        while(lhs_curr!=nullptr){
            if(lhs_curr->data != rhs_curr->data){
                return false;
            }
            lhs_curr=lhs_curr->next;
            rhs_curr=rhs_curr->next;
        return true;
    }
    }
    return false;
}
