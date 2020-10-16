#include <bits/stdc++.h>
using namespace std;

class Faculty{
    /*
    @params
        name         : teacher's name
        phoneNo      : contact no
        teachesClass : class or grade taught by the teacher
        subject      : subject taught by the teacher
        salary       : salary
    */

    string name;
    string phoneNo;
    short teachesClass;
    string subject;
    float salary;

public:
        // Default constructor
    Faculty();

    // setters
    void setName(string name);
    void setPhoneNo(string phoneNo);
    void setTeachesClass(short teachesClass);
    void setSubject(string subject);
    void setSalary(float salary);

    // getters
    string getName();
    string getPhoneNo();
    string  getTeachesClass();
    string getSubject();
    string  getSalary();

    // static Func
    //destructor
    //~Faculty();
};

/************ Function definitions ***********/


/*
    Constructor and destructor
*/
Faculty::Faculty(){
       name="";
       phoneNo="";
       teachesClass = 0;
       subject="";
       salary = 0.0f;
}



/*
    @setters
        setName         : sets name
        setPhoneNo      : sets phone no
        setTeachesClass : sets the class taught by the faculty
        setSubject      : sets the subject taught by the faculty
        setSalary       : sets salary


*/
void Faculty::setName(string name){
    this->name = name;
}

void Faculty::setPhoneNo(string phoneNo){
    this->phoneNo = phoneNo;
}

void Faculty::setTeachesClass(short teachesClass){
    this->teachesClass = teachesClass;
}

void Faculty::setSubject(string subject){
    this->subject =  subject;
}

void Faculty::setSalary(float salary){
    this->salary = salary;
}



/*
    @getters
        getName         : get teacher's name
        getPhoneNo      : get phone no.
        getTeachesClass : get class taught
        getSubject      : get subject taught
        getSalary       : get salary
        getId           : get ID

*/
string Faculty::getName(){
    return name;
}

string Faculty::getPhoneNo(){
    return phoneNo;
}

string Faculty::getTeachesClass(){
    return to_string(teachesClass);
}

string Faculty::getSubject(){
    return subject;
}

string Faculty::getSalary( ){
    return to_string(salary*1.0f);
}
