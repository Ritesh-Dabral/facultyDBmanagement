#include "teacher.h"
#include <limits>
#include "sqlite3.h"
#include <bits/stdc++.h>

static int callback(void *data, int argc, char **argv, char **ColName){
    for(int i = 0; i<argc; i++){
       printf("%s = %s\n", ColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

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

void deleteFaculty(){
    sqlite3 *db;
    char *errMsg;

    int rc = sqlite3_open("studentsDb.db",&db);

    if(rc){
        cerr<<"Can't connect to db\n"<<sqlite3_errmsg(db)<<"\n";
        return;
    }

    // all good
    system("CLS");

    int id;
    cout<<"\n<------------ DELETE COMMAND ------------->\n";
    bool run=true;
    while(run){
        cout<<"\nEnter faculty id to delete : ";
        cin>>id;

        if(!cin){
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

    // now delete it

    // first show the data to be deleted:
    string query;
    query = "SELECT * FROM FACULTYLIST WHERE ID="+to_string(id)+";";

    cout<<"\n\n--- Showing the required data to be deleted ---\n\n";
    rc = sqlite3_exec(db,query.c_str(),callback,NULL,&errMsg);

    if(rc!=SQLITE_OK){
        cerr<<"Unable to read data\n";
        printf("%s",errMsg);
        sqlite3_free(errMsg);
        return;
    }

    query = "DELETE FROM FACULTYLIST WHERE ID="+to_string(id)+";";

    // process the delete query
    rc = sqlite3_exec(db,query.c_str(),NULL,NULL,&errMsg);
    if(rc!=SQLITE_OK){
        cerr<<"Unable to delete data\n";
        printf("%s",errMsg);
        sqlite3_free(errMsg);
        return;
    }
    else{
        cout<<"\n<----------Successfully Deleted----------->\n";
        sqlite3_close(db);
    }
}

void updateFaculty(){
    sqlite3 *db;
    char *errMsg;

    int rc = sqlite3_open("studentsDB.db",&db);

    if(rc){
        cerr<<"Can't connect to db\n"<<sqlite3_errmsg(db)<<"\n";
        return;
    }

    // main update
        system("CLS");

    int id;
    cout<<"\n<------------ UPDATE COMMAND ------------->\n";
    bool run=true;
    while(run){
        cout<<"\nEnter faculty id to update : ";
        cin>>id;

        if(!cin){
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


    run = true;
        run = true;
        int querySelect;
        while(run){
            cout<<"\n\nUPDATE\n1. NAME \n2. PHONE NUMBER\n3. CLASS TEACHES\n4. SUBJECT\n5. SALARY\n6. EXIT\nChoice : ";
            cin>>querySelect;

            if(!cin){
              cout << "Wrong Choice. Enter again " << endl;
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              continue;
            }
            else{
                if(querySelect>=1 && querySelect<=6){
                    run = false;
                }
            }
        }

        string myChoice,query,selectQuery;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');  // discard buffer
        query = "UPDATE FACULTYLIST SET";
        if(querySelect==1){
            cout<<"\nSet name : ";
            getline(cin,myChoice);
            query = query+" NAME = \""+myChoice+"\"";
        }
        else if(querySelect==2){
            cout<<"\nSet phone number : ";
            cin>>myChoice;
            query = query+" PHONENO = \""+myChoice+"\"";
        }
        else if(querySelect==3){
            cout<<"\nSet class teaches : ";
            cin>>myChoice;
            query = query+" CLASS = \""+myChoice+"\"";
        }
        else if(querySelect==4){
            cout<<"\nSet subject teaches : ";
            getline(cin,myChoice);
            query = query+" SUBJECT = \""+myChoice+"\"";
        }
        else if(querySelect==5){
            cout<<"\nSet salary : ";
            getline(cin,myChoice);
            query = query+" SALARY = \""+myChoice+"\"";
        }
        else{
            return;
        }

    query = query+" WHERE ID = "+to_string(id)+";";

        //cout<<"query: "<<query<<endl;

    // record before update
    cout<<"\n\nData fetched before update: \n\n";
    selectQuery = "SELECT * FROM FACULTYLIST WHERE ID="+to_string(id)+";";
    rc = sqlite3_exec(db,selectQuery.c_str(),callback,NULL,&errMsg);
    if(rc!=SQLITE_OK){
        cerr<<"Unable to read data\n";
        printf("%s",errMsg);
        sqlite3_free(errMsg);
        return;
    }

    // actual query
    rc = sqlite3_exec(db,query.c_str(),NULL,NULL,&errMsg);

    if(rc!=SQLITE_OK){
        cerr<<"Unable to update data\n";
        printf("%s",errMsg);
        sqlite3_free(errMsg);
        return;
    }

    // query after update
    cout<<"\n\nData fetched after update: \n\n";
    selectQuery = "SELECT * FROM FACULTYLIST WHERE ID="+to_string(id)+";";
    rc = sqlite3_exec(db,selectQuery.c_str(),callback,NULL,&errMsg);
    if(rc!=SQLITE_OK){
        cerr<<"Unable to read data\n";
        printf("%s",errMsg);
        sqlite3_free(errMsg);
        return;
    }
    else{
        cout<<"\n<----------Successfully Updated----------->\n";
        sqlite3_close(db);
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
                        case 3: updateFaculty();
                                break;
                        case 4: deleteFaculty();
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
