#include "user.h"
#include <string>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <list>

std::string Nowtime = "NULL";
std::string faculty = "NULL";
std::string timeSpend = "NULL";
std::string tools = "NULL";
std::string satisfaction = "NULL";
std::string feedback = "NULL";

user::user(){}

void user::setFaculty(int Fac){
    switch (Fac) {
    case 0:
        faculty = "teknologi kunst og design";
        break;
    case 1:
        faculty = "laerarutdanning og internasjonale studium";
        break;
    case 2:
        faculty = "helsevitenskap";
        break;
    case 3:
        faculty = "samfunnsvitenskap";
        break;
    case 4:
        faculty = "None";
        break;
    case 5:
        faculty = "NULL";
        break;
    default:
        faculty = "Error";
        break;
    }
}

void user::SetTimeSpend(int Time){
    switch (Time) {
    case 0:
        timeSpend = "NULL";
        break;
    case 1:
        timeSpend = "0:30";
        break;
    case 2:
        timeSpend = "1:00";
        break;
    case 3:
        timeSpend = "1:30";
        break;
    case 4:
        timeSpend = "2:00";
        break;
    case 5:
        timeSpend = "2:30";
        break;
    case 6:
        timeSpend = "3:00";
        break;
    case 7:
        timeSpend = "3:30";
        break;
    case 8:
        timeSpend = "4:00";
        break;
    case 9:
        timeSpend = "4:30";
        break;
    case 10:
        timeSpend = "5:00";
        break;
    case 11:
        timeSpend = "5:30";
        break;
    case 12:
        timeSpend = "6:00";
        break;
    default:
        timeSpend = "Error";
        break;
    }
}

void user::setTools(std::list<std::string> items){
    if(!items.empty() || tools == "NULL")
        tools = "";
    for(auto item : items)
        tools += item+",";
    if(!items.empty())
        tools.pop_back();
}

void user::setSatisfaction(int rating){
    switch (rating) {
    case 0:
        satisfaction = "0";
        break;
    case 1:
        satisfaction = "33";
        break;
    case 2:
        satisfaction = "67";
        break;
    case 3:
        satisfaction = "100";
        break;
    case 4:
        satisfaction = "NULL";
        break;
    default:
        satisfaction = "Error";
        break;
    }
}

void user::setFeedback(std::string fBack){
    if(fBack.empty())
        feedback = "NULL";
    else{
        std::replace( fBack.begin(), fBack.end(), ',', ';');
        feedback = fBack;
    }
}

std::string user::GetNowDateTime(){
    time_t now;
    time(&now);
    tm ltm = *localtime(&now);
    std::string year= std::to_string(1900 + ltm.tm_year);
    std::string month = std::to_string(1+ltm.tm_mon);
    std::string day = std::to_string(ltm.tm_mday);
    std::string time = std::to_string(ltm.tm_hour)+":"+ std::to_string(ltm.tm_min);
    // Display like HH:MM DD-MM-YYYY
    std::string DateTime=time+" "+day+"/"+month+"/"+year;
    return DateTime;
}

void user::emptyUser(){
    Nowtime = "NULL";
    faculty = "NULL";
    timeSpend = "NULL";
    tools = "NULL";
    satisfaction = "NULL";
    feedback = "NULL";
}

void user::userAdd(bool NoPart){
    Nowtime = GetNowDateTime();
    std::string userdata;
    if(!NoPart){
        userdata = Nowtime + "," + faculty + "," + timeSpend + "," + tools + "," + satisfaction + "," + feedback + "\n";
        emptyUser();
    }else{
        emptyUser();
        userdata = Nowtime + "," + faculty + "," + timeSpend + "," + tools + "," + satisfaction + "," + feedback + "\n";
    }

    std::fstream file;
    file.open("/home/pi/Documents/userdata/users.csv", std::ios_base::app);
    file << userdata;
}
