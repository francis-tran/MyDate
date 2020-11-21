#include "myDate.h"
#include <iostream>
#include <string>

using namespace std;

bool isLeapYear(int year){
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int findLarger(int x, int y){
    if(x > y){
        return x;
    }
    return y;
}

int findSmaller(int x, int y){
    if(x < y){
        return x;
    }
    return y;
}

int Greg2Julian(int month, int day, int year){
    int I = year;
    int J = month;
    int K = day;
    
    return K - 32075 + 1461 * (I + 4800 + (J-14) / 12) / 4 + 367 * (J-2-(J-14)/12*12) / 12 - 3 * (( I+4900 + (J-14)/12)/100)/4;
}

void Julian2Greg(int JD, int & month, int & day, int & year){
    int L = JD + 68569;
    int N = 4*L/146097;
    L = L-(146097*N+3)/4;
    int I = 4000*(L+1)/1461001;
    L = L-1461*I/4+31;
    int J = 80 * L/2447;
    int K = L-2447*J/80;
    L = J/11;
    J = J+2-12*L;
    I = 100*(N-49)+I+L;
    
    year = L;
    month = J;
    day = K;
}

myDate::myDate(int m, int d, int y){
    if((m == 2 && d == 29 && isLeapYear(y)) || (m <= 12 && m > 0 && d > 0 && d <= daysPerMonth[m - 1])){
        month = m;
        day = d;
        year = y;
    }
    else{
        cout << "Error, false input. Going to default values." << endl;
        month = 5;
        day = 11;
        year = 1959;
    }
}
void myDate::display(){
    cout << nameMonth[month - 1] << " " << day << ", " << year; 
}
void myDate::increaseDate(int n){
    int totalDays = this->dayOfYear() + n;
    int yearsAdded = totalDays / 365;
    for(int i = year; i < year + yearsAdded; i++){
        if(isLeapYear(i)){
            totalDays -= 366;
        }
        else{
            totalDays -= 365;
        }
    }
    year += yearsAdded;
    int monthCount = 1;
    for(int i = 0; totalDays - daysPerMonth[i] > 0; i++){
        if(i == 1 && isLeapYear(year)){
            totalDays -= 29;
        }
        else{
            totalDays -= daysPerMonth[i];
        }
        monthCount++;
    }
    month = monthCount;
    day = totalDays;
}
void myDate::decreaseDate(int n){
    if(n < day){
        day -= n;
    }
    else if(n == day){
        month--;
        if(isLeapYear(year) && month == 2){
            day = 29;
        }
        else{
            day = daysPerMonth[month - 1];
        }
    }
    else{
        int totalDays = n - day;
        if(month == 1){
            year--;
            month = 12;
        }
        else{
            month--;
        }
        while(totalDays - daysPerMonth[month - 1] > 0){
            totalDays -= daysPerMonth[month - 1];
            if(month == 1){
                month = 12;
                year--;
            }
            else if (month == 2 && isLeapYear(year)){
                month--;
                totalDays--;
            }
            else{
                month--;
            }
        }
        day = daysPerMonth[month - 1] - totalDays;
    }
}
int myDate::daysBetween(myDate d){
    if(day == d.getDay() && month == d.getMonth() && year == d.getYear()){
        return 0;
    }
    int thisTotalDays;
    if(isLeapYear(year)){
        thisTotalDays = 366 - this->dayOfYear();
    }
    else{
        thisTotalDays = 365 - this->dayOfYear();
    }
    int daysBetween = 0;
    for(int i = findSmaller(year, d.getYear()) + 1; i < findLarger(year, d.getYear()); i++){
        if(isLeapYear(i)){
            daysBetween += 366;
        }
        else{
            daysBetween += 365;
        }
    }
    int totalDays = thisTotalDays + daysBetween + d.dayOfYear();
    return totalDays;
}
int myDate::getMonth(){
    return month;
} 
int myDate::getDay(){
    return day;
}
int myDate::getYear(){
    return year;
}
int myDate::dayOfYear(){
    int num = day;
    bool isLeapYearNotAdded = true;
    for(int i = 0; i < month; i++){
        if(i != month - 1){
            num += daysPerMonth[i];
        }
        if(i > 1 && isLeapYear(year) && isLeapYearNotAdded){
            isLeapYearNotAdded = false;
            num++;
        }
    }
    return num;
}
string myDate::dayName(){
    string dayNames[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    int days[12] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 }; 
      
    if (month < 3){ 
        year -= 1; 
    }
    int i = ((year + year / 4 - year / 100 + year / 400 + days[month - 1] + day) % 7);
    return dayNames[i]; 
}
