
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>

class Buyer {
public:
    int products = 1 + rand() % 30;
    bool busy = false;
    int cash_register_number;
};

class Queue {
public:
    Buyer person;
    Queue* prev, * next;
public:
    Queue(Buyer person) {
        this->person = person;
        this->prev = this->next = NULL;
    }
};

class LinkedList {
public:
    Queue* head, * tail;
public:
    LinkedList() {
        head = tail = NULL;
    }
    Queue* push_front(Buyer person) {
        Queue* ptr = new Queue(person);
        ptr->next = head;
        if (head != NULL) {
            head->prev = ptr;
        }
        if (tail == NULL) {
            tail == ptr;
        }
        head = ptr;
        return ptr;
    }
    Queue* push_back(Buyer person) {
        Queue* ptr = new Queue(person);
        ptr->prev = tail;
        if (tail != NULL) {
            tail->next = ptr;
        }
        if (head == NULL) {
            head == ptr;
        }
        tail = ptr;
        return ptr;
    }
    void pop_front() {
        if (head == NULL) {
            return;
        }
        Queue* ptr = head->next;
        if (ptr != NULL) {
            ptr->prev = NULL;
        }
        else {
            tail = NULL;
        }
        delete head;
        head = ptr;
    }
    void pop_back() {
        if (tail == NULL) {
            return;
        }
        Queue* ptr = tail->next;
        if (ptr != NULL) {
            ptr->next = NULL;
        }
        else {
            head = NULL;
        }
        delete tail;
        tail = ptr;
    }
    Queue* getAt(int index) {
        Queue* ptr = head;
        int n = 0;

        while (n != index) {
            if (ptr == NULL) {
                return ptr;
            }
            ptr = ptr->next;
            n++;
        }

        return ptr;
    }

    Queue* operator [] (int index) {
        return getAt(index);
    }

    Queue* insert(int index, Buyer person) {
        Queue* right = getAt(index);
        if (right == NULL) {
            return push_back(person);
        }
        Queue* left = right->prev;
        if (left == NULL) {
            return push_front(person);
        }

        Queue* ptr = new Queue(person);

        ptr->prev = left;
        ptr->next = right;
        left->next = ptr;
        right->prev = ptr;
        return ptr;
    }

    void erase(int index) {
        Queue* ptr = getAt(index);
        if (ptr == NULL){
            return;
        }
        if (ptr->prev == NULL) {
            pop_front();
            return;
        }
        if (ptr->next == NULL) {
            pop_back();
            return;
        }
        Queue* left = ptr->prev;
        Queue* right = ptr->next;

        left->next = right;
        right->prev = left;
        delete ptr;
    }
};

class Cash_register {
private:
    LinkedList Cash;
public:
    void Add_Buyer() {
        Buyer person;
        Cash.push_back(person);
    }

    void Next() {
        Cash.pop_front();
    }

    Buyer Get_Buyer(int i) {
        return Cash[i]->person;
    }
};

int main()
{
    bool working = true;
    while (working == true){
        srand(time(0));
        std::cout << "Enter number of buyers or enter 0 for random" << std::endl;
        int user_choice;
        int number_of_buyers;
        int number_of_cashregisters;
        std::cin >> user_choice;
        if (user_choice == 0) {
            number_of_buyers = 1 + rand() % 15;
        }
        else {
            number_of_buyers = user_choice;
        }
        std::cout << "Enter number of cash registers or enter 0 for random" << std::endl;
        std::cin >> user_choice;
        if (user_choice == 0) {
            number_of_cashregisters = 1 + rand() % 4;
        }
        else {
            number_of_cashregisters = user_choice;
        }
        std::cout << number_of_buyers << std::endl;
        std::cout << number_of_cashregisters << std::endl; ///udalit
        int i = 0;
        while (i != number_of_buyers) {
            std::cout << i;
            i++;
        }
        std::cout << "For exit enter 0, to restart enter any number" << std::endl;
        std::cin >> user_choice;
        if (user_choice == 0) {
            working = false;
        }
        Cash_register cash1;
        int h = 0;
        while (h < 10) {
            cash1.Add_Buyer();
            h++;
        }
        std::cout << cash1.Get_Buyer(1).products << std::endl;
    }

}

