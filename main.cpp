#include "teacher.h"
#include <typeinfo>
#include <limits>

void menu(){
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
                        case 1: cout<<"addFaculty()\n";
                                break;
                        case 2: cout<<"viewFaculty()\n";
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
    cout<<"Exiting application";
    return;
}


int main()
{
    Faculty obj1;
    cout<<obj1.getName();
    menu();

    return 0;
}
