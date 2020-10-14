#include "teacher.h"
#include <limits>
#include "sqlite3.h"
#include <bits/stdc++.h>

void addFaculty(){

    sqlite3 *db;
    char *errMsg;

    int rc = sqlite3_open("studentsDb.db",&db);

    if(rc){
        cerr<<"Can't connect to db\n"<<sqlite3_errmsg(db)<<"\n";
        return;
    }

    // now add 'n' no. of faculties

    system("CLS");

    Faculty fact;
    string name;
    string phoneNo;
    short teachesClass;
    string subject;
    float salary;

    cin.ignore(numeric_limits<streamsize>::max(),'\n');  // discard buffer
    cout<<"Enter faculty's name "<<setw(12)<<": ";
    getline(cin,name);
    //cin.ignore(numeric_limits<streamsize>::max(),'\n');  // discard buffer
    cout<<"Enter faculty's contact number "<<setw(2)<<": ";
    cin>>phoneNo;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');  // discard buffer
    cout<<"Class taught by the faculty "<<setw(5)<<": ";
    cin>>teachesClass;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');  // discard buffer
    cout<<"Subject taught by the faculty "<<setw(3)<<": ";
    getline(cin,subject);
    //cin.ignore(numeric_limits<streamsize>::max(),'\n');  // discard buffer
    cout<<"Enter salary "<<setw(20)<<": ";
    cin>>salary;

    fact.setName(name);
    fact.setPhoneNo(phoneNo);
    fact.setSalary(salary);
    fact.setSubject(subject);
    fact.setTeachesClass(teachesClass);

    // now try inserting the data

    string squery = "INSERT INTO FACULTYLIST(NAME,PHONENO,CLASS,SUBJECT,SALARY) "
         "VALUES('" + fact.getName() + "','"
         + fact.getPhoneNo() + "','" + fact.getTeachesClass()+ "','"
         + fact.getSubject()+ "','" + fact.getSalary()+"');";

    //cout<<"query generated: "<<squery<<endl;
    rc = sqlite3_exec(db, squery.c_str(), NULL, 0, &errMsg);

    if(rc!=SQLITE_OK){
        cerr<<"Error inserting data\n";
        printf("%s",errMsg);
        sqlite3_free(errMsg);
        return;
    }
    else{
        cout<<"\n<--------------Insertion Successful------------------->\n";
        sqlite3_close(db);
    }
}

static int callback(void *data, int argc, char **argv, char **ColName){
    for(int i = 0; i<argc; i++){
       printf("%s = %s\n", ColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void viewFaculty(){

    sqlite3 *db;
    char *errMsg;

    int rc = sqlite3_open("studentsDb.db",&db);

    if(rc){
        cerr<<"Can't connect to db\n"<<sqlite3_errmsg(db)<<"\n";
        return;
    }

    system("CLS");
    //cout<<setw(15)<<"PRESS 1. VIEW SPECIFIC DATA\n2. VIEW ALL DATA\n3. GO BACK\n";

    bool run = true;
    int choice;
    while(run){
        cout<<setw(15)<<"\nPRESS\n1. VIEW ALL DATA\n2. VIEW SPECIFIC DATA\n3. GO BACK\nChoice : ";
        cin>>choice;
        if (!cin)
        {
          cout << "Wrong Choice. Enter again " << endl;
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          continue;
        }
        else{
            if(choice>=1 && choice<=3){
                run = false;
            }
        }
    }

    if(choice==3)
        return;
    else{
        string query;
        if(choice==1){
            query = "SELECT * FROM FACULTYLIST;";
        }
        else{
            int id;
            run = true;
            while(run){
                cout<<"\nEnter faculty id(numeric) : ";
                cin>>id;
                if (!cin)
                {
                  cout << "Wrong Choice. Enter again " << endl;
                  cin.clear();
                  cin.ignore(numeric_limits<streamsize>::max(), '\n');
                  continue;
                }
                else{
                    if(id>=1){
                        run = false;
                    }
                }
            }

            query = "SELECT * FROM FACULTYLIST WHERE ID="+to_string(id)+";";
        }

        system("CLS");
        cout<<"\n<---------RESULT---------->\n";
        // we have a query and db is open

        rc = sqlite3_exec(db,query.c_str(),callback,NULL,&errMsg);

        if(rc!=SQLITE_OK){
            cerr<<"Unable to read data\n";
            printf("%s",errMsg);
            sqlite3_free(errMsg);
            return;
        }
        else{
            cout<<"\n<----------Successfully executed command----------->\n";
            sqlite3_close(db);
        }
    }

}

void menu(){
    //system("CLS");
    short choice;
    bool run = true;
      while (run)
      {
        cout<<"\nPRESS\n"
                "1. ADD NEW FACULTIES' DATA\n"
               "2. VIEW ALL FACULTIES' DATA\n"
               "3. UPDATE AN EXISTING FACULTIES DATA\n"
               "4. DELETE A FACULTIES'S DATA\n"
               "5. EXIT\nChoice: ";
        cin >> choice;
        if (!cin)
        {
          cout << "Wrong Choice. Enter again " << endl;
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          continue;
        }
        else {

               if(choice>=1 && choice<=5){
                    switch(choice){
                        case 1: addFaculty();
                                break;
                        case 2: viewFaculty();
                                break;
                        case 3: cout<<"updateFaculty()\n";
                                break;
                        case 4: cout<<"deleteFaculty()\n";
                                break;
                        case 5: run = false;
                                break;
                    }
               }
        }
      }
    cout<<"<---------------------Exiting application--------------->";
    return;
}

void createDB(){
    sqlite3 *db;
    char *errMsg;

    int rc = sqlite3_open("studentsDb.db",&db);

    if(rc){
        cerr<<"Can't connect to db\n"<<sqlite3_errmsg(db)<<"\n";
        exit(0);
    }
    else{
        cout<<setw(30)<<"Connection established successfully\n";

        sqlite3_close(db); // terminate connection
    }
}

void createTable(){
    sqlite3 *db;
    char *msgError;
    string query = "CREATE TABLE IF NOT EXISTS FACULTYLIST("
    "ID INTEGER PRIMARY KEY AUTOINCREMENT, NAME VARCHAR(50) NOT NULL,"
    "PHONENO VARCHAR(10) NOT NULL, CLASS VARCHAR(2) NOT NULL,"
    "SUBJECT VARCHAR(50) NOT NULL, SALARY VARCHAR NOT NULL);";

    try{
        int exit  = sqlite3_open("studentsDb.db",&db);
        exit = sqlite3_exec(db,query.c_str(),NULL,0,&msgError);

        if(exit!=SQLITE_OK){
            cerr<<"Error Creating Table\n";
            printf("%s",msgError);
            sqlite3_free(msgError);
        }
        sqlite3_close(db);
    }
    catch(const exception &e){
        cerr<<e.what()<<"\n";
    }
}


int main()
{

    createDB();
    createTable();
    menu();

    return 0;
}
