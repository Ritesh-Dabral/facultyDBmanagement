#include "extraH/menu.h"

void createDB(){
    sqlite3 *db;
    char *errMsg;

    int rc = sqlite3_open("faculty.db",&db);

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
        int exit  = sqlite3_open("faculty.db",&db);
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
