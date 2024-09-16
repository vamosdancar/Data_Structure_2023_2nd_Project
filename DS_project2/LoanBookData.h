#pragma once

#include<iostream>
#include<string>
using namespace std;

class LoanBookData
{
private:
    string name;        // book
    int code;           // Unique code
    string author;      // Author
    int year;           // Publication year
    int loan_count;     // Count of loaned

public:
    // Constructor
    LoanBookData() { this->loan_count = 0; }
    
    // Destructor
    ~LoanBookData() {};

    // Method to set
    void setBookData(string name, int code, string author, int year, int loan_count) {
        this->name = name;
        this->code = code;
        this->author = author;
        this->year = year;
        this->loan_count = loan_count;
    }

    // Setter methods 
    void setName(string name) { this->name = name; }
    void setCode(int code) { this->code = code; }
    void setAuthor(string author) { this->author = author; }
    void setYear(int year) { this->year = year; }
    // Method to increment the loan count by 1
    void updateCount() { this->loan_count += 1; }

    // Getter methods 
    string getName() { return name; }
    int getCode() { return code; }
    string getAuthor() { return author; }
    int getYear() { return year; }
    int getLoanCount() { return loan_count; }
};
