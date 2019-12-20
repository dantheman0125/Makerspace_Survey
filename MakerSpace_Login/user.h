#ifndef USER_H
#define USER_H
#include <string>
#include <list>

class user
{
public:
    user();
    void userAdd(bool NoPart);
    void setFaculty(int Fac);
    void SetTimeSpend(int Time);
    void setTools(std::list<std::string> items);
    void setSatisfaction(int rating);
    void setFeedback(std::string fBack);
private:
    void emptyUser();
    void addZero(std::string & date,int value);
    std::string GetNowDateTime();
};

#endif // USER_H
