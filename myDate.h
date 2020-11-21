#include <iostream>
#include <string>

using namespace std;

#ifndef MYDATE_H
#define MYDATE_H
class myDate{
    private:
    int month;
    int day;
    int year;
    static const int NUMBER_OF_MONTHS = 12;
    string nameMonth[NUMBER_OF_MONTHS] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int daysPerMonth[NUMBER_OF_MONTHS] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    public:
    myDate(){
        month = 5;
        day = 11;
        year = 1959;
    };
    myDate(int m, int d, int y);
    void display();
    void increaseDate(int n);
    void decreaseDate(int n);
    int daysBetween(myDate d);
    int getMonth();
    int getDay();
    int getYear();
    int dayOfYear();
    string dayName();
};
#endif