#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
//#include <fstream.h>
#include <stdio.h>
#include <direct.h>
#include <string.h>

#include "border.h"
#include "food.h"
//#include "student.h"

/*** key values ***/
#define UP           0x48
#define DOWN         0x50
#define LEFT         0x4B
#define RIGHT        0x4D
#define ESC          0x1B
#define ENTER        0x0D
#define DELETE       0x53
#define F1           59
//-----------------------------------------------///
using namespace std;
class message
{
public:
    char title[60];
    char content[10][55];
    char st_ID[20];
    char message_name[50];
    char message_name_to_list[50];
    struct tm t;
    student st;
    message *next;
    friend class message_list;
};
class message_list
{
public:
    message *first;
    message *last;

    message_list()
    {
        first = last = NULL;
    }
    ~message_list()
    {
        message *curptr = first;
        message *temp;
        while(curptr)
        {
            temp = curptr;
            curptr = curptr->next;
            delete temp;
        }
    }
    bool contact_admin(student *curptr);
    int load_messages();
    bool save_new_message_list();
    void admin_inbox();
    bool show_message(message *curmes);
    int admin_inbox_list(int m,bool op );
    void delete_message(message *curmes);
};



///global variable ------------------------------
char colour[20];
int screensav = 1;
int log_out_time = 10*60;
int screen_saver_wait_time = 100;
///----------------------------------------------
///global objects:
food_list fdlist;
st_list stlist;
//IT_operator admin;
daily_list dllist;
student *st;
message_list *mesl;
///  -------------------
void screensaver3();
void admin_help();
int admin_inbox_list(int m,bool op);
void admin_inbox();
char* messagename(student *curptr);
void budgetlist(int mood);
bool contact_admin(student *curptr);
void studentlist(int mood);
void systeminfo();
void mdate(int x,int y);
void mclock(int x,int y);
void save_setting();
bool waittime(int z);
void settinglist(int a);
void setcolor(char a,char b);
void setcolor(int n);
void setting();
void adminmenu();
void adminlist(int a,int col);
void creditmenu();
void login_menu();
void main_help();
void about();
void stmenu();
void flist(int b,char a[5]);
void mlist(int a);
void screensaver2(int t);
void screensaver1();
void load_setting();///in main
void main_menu()
{
    int mood=1;
    char ans;
    mlist(mood);
    for(;;)
    {
        if(kbhit())
            mlist(mood);
        int ch = getch();
        if(!ch || ch == 0xe0 || ch ==0x29)
        {
            ch = getch(); // extended keys
            switch(ch)
            {
            case UP:
                system("cls");
                if(--mood == 0) mood = 5;
                mlist(mood);
                break;
            case DOWN:
                system("cls");
                if(++mood == 6) mood = 1;
                mlist(mood);
                break;
            case F1:
                main_help();
                getch();
                main_menu();
            } // switch()
        } // if()
        else
        {
            switch(ch)
            {
            case 'q':
            case 'Q':
            {
                system("cls");
                loadbar(10,10,"Quitting!");
                return;
                //          save_setting();
//            save_operator();
//            endprog();
            }
            case 's':
                screensaver3();
                mlist(mood);
                break;
            case ESC:
                system("cls");
                border(14,14,32,5);
                gotoxy(16,16);
                cout<<"Do you want to quit?(y/n) ";
                ans = getche();
                ans = tolower(ans);
                if(ans == 'y')
                {
                    loadbar(14,11,"Quiting");
                    //save_setting();
                    //exit(0);
                    return;
                }
                else
                    mlist(mood);
                break;
                /*case F1:
                help();
                main_menu();*/
                break;
            case ENTER:
                switch(mood)
                {
                case 1:
                    login_menu();
                    break;
                case 2:
                    main_help();
                    getch();
                    clrscr();
                    mlist(mood);
                    break;
                case 3:
                    about();
                    getch();
                    clrscr();
                    mlist(mood);
                    break;
                case 4:
                    setting();
                    getch();
                    clrscr();
                    mlist(mood);
                    break;
                case 5:
                    system("cls");
                    border(14,14,32,5);
                    gotoxy(16,16);
                    cout<<"Do you want to quit?(y/n)";
                    ans = getche();
                    ans = tolower(ans);
                    if(ans == 'y')
                    {
                        loadbar(14,11,"Quiting");
                        return;
                    }
                    else
                        mlist(mood);
                    break;
                }

                break;
            }
        }
    }
}///end of main menu

void login_menu()
{
    char user_name[20] ;
    system("cls");
    border();
    border(18,17,30,7);
    gotoxy(0,0);//just for a good shape
    gotoxy(2,2);
    gotoxy(20,19);
    cout<<"User name : ";
    gotoxy(20,21);
    cout<<"Password : ";
    gotoxy(32,19);
    /* char c;
     cin.get(c);
     if((int)c == ESC)
         return;
     else
     {cin>>user_name;
     strcat(user_name,&c);}*/
    cin>>user_name;
    gotoxy(31,21);
    /// looking for ID & Pass
    if((strcmp(user_name,admin.get_user()))==0)
    {
        if(checkpass(admin.get_pass()))
        {
            loadbar(18,15,"Logining in");
            adminmenu();
        }
        else
        {
            blink(18,15,3,"Wrong Password !!!");
            login_menu();
        }
    }
    else if((strcmp(user_name,foperator.get_user())) ==0)
    {
        if(checkpass(foperator.get_pass()))
        {
            loadbar(18,15,"Logining in");
            creditmenu();
        }
        else
        {
            blink(18,15,"Wrong Password !!!");
            login_menu();
        }
    }
    else
    {
        student *curptr = stlist.tofirst(curptr);
        for(; curptr->next!=NULL; curptr = curptr->next)
        {
            if((strcmp(user_name,curptr->user)==0))
            {
                gotoxy(19,25);
                st = curptr;
                stmenu();
                cout<<curptr->name<<" is trying to log in";
                gotoxy(31,21);
                if(checkpass(curptr->get_pass()))
                {
                    loadbar(18,15,"Logining in");
                    stmenu();

                }
                else
                {
                    blink(18,15,"Wrong Password !!!");
                    blink(2,2,5,curptr->get_pass());
                    login_menu();
                }

            }
            else
                continue;

        }///end of for loop
    }///end of else
}///end of log in menu

void stmenu()
{
    char ans;
    system("cls");
    int mood = 1;
    studentlist(mood);
    for(;;)
    {
        if(waittime(log_out_time))
        {
            loadbar(14,10," Loging out ");
            main_menu();
        }
        int ch = getch();
        if(!ch || ch == 0xe0)
        {
            ch = getch(); // extended keys
            switch(ch)
            {
            case UP:
                system("cls");
                if(--mood == 0) mood = 5;
                studentlist(mood);
                break;
            case DOWN:
                system("cls");
                if(++mood == 6) mood = 1;
                studentlist(mood);
                break;
            } // switch()
        } // if()
        else
        {
            switch(ch)
            {
            case 'q':
            case 'Q':
            {
                system("cls");
                std::cout << "Quitting!\n";
                exit(0);
            }
            case ESC:
                border();
                border(14,35,34,5);
                gotoxy(0,0);
                gotoxy(16,37);
                cout<<"Do you want to log out?(y/n)";
                ans = getch();
                ans = tolower(ans);
                if(ans == 'y')
                {
                    loadbar(16,33,"Loging out");
                    main_menu();
                }
                else
                    studentlist(mood);

                break;
            case ENTER:
            {
                switch(mood)
                {
                case 1:
                    dllist.reslist(st);
                    stmenu();
                    break;
                case 2:

                    break;
                case 3:
                {
                    system("cls");
                    border();
                    gotoxy(0,0);
                    gotoxy(30,2);
                    cout<<"Change Password";
                    border(20,10,38,7);
                    gotoxy(22,12);
                    cout<<"Enter old password :";
                    gotoxy(22,14);
                    cout<<"Enter new passeord :";
                    ///getting
                    gotoxy(22+strlen("Enter old password : "),12);
                    if(checkpass(st->get_pass()))
                    {
                        gotoxy(22+strlen("Enter new passeord : "),14);
                        char p[20];
                        cin>>p;
                        st->set_pass(p);
                        gotoxy(22,20);
                        write("Password Changed Successfully !!!");
                    }
                    else
                    {
                        blink(28,20,3,"Wrong Password !!!");

                    }
                    gotoxy(2,47);
                    write("Press any key to go back");
                    getch();
                    studentlist(mood);
                    break;
                    case 4:
                        mesl->contact_admin(st);
                        getch();
                        studentlist(mood);
                        break;
                    case 5://log out
                        system("cls");
                        border();
                        gotoxy(0,0);
                        border(14,14,35,5);
                        gotoxy(16,16);
                        cout<<"Do you want to log out?(y/n)";
                        ans = getch();
                        ans = tolower(ans);
                        if(ans == 'y')
                        {
                            loadbar(14,10,"Loging out");
                            main_menu();
                        }
                        else
                            studentlist(mood);
                        //save jobs should be done here!!!
                        break;
                    }
                    studentlist(mood);
                    break;
                }
            }///end of case enter
            }
        }
    }
}
//////////////////////////////////////////////
void mlist(int a)
{
    static int previous=20;
    system("cls");
    border();
    border(25,15,27,14);//menu border
    border(20,1,35,5);
    gotoxy(23,3);
    cout<<"PWUT Food Reservation System";
///----------------------------------
    gotoxy(27,17);
    cout<<" 1.Log in";
    gotoxy(27,19);
    cout<<" 2.Help";
    gotoxy(27,21);
    cout<<" 3.About us";
    gotoxy(27,23);
    cout<<" 4.Setting";
    gotoxy(27,25);
    cout<<" 5.Exit";
///-------------------------------------
    gotoxy(27,17+2*(a-1));
    cout<<">";
    //gotoxy(27,17+2*(previous-1));
    //cout<<" ";
///-------------------------------------
    mdate(2,2);
    mclock(70,2);
    //gotoxy(0,0);//just for a good shape
    previous = a;
}//end of func!

void adminmenu()
{
    fdlist.load_food_data();
    stlist.load_students_data();
    char ans;
    system("cls");
    // int mood1 =1,mood2 =1,mood3 =1;
    int mood = 1;
    const int max1 = 5,max2 = 7,max3 =5;
    int col =1;
    adminlist(mood,col);
    for(;;)
    {
        if(waittime(log_out_time))
        {
            loadbar(14,10,"Loging out");
            //save shold be added here!!!
            ///save func///
            main_menu();
        }
        int ch = getch();
        if(!ch || ch == 0xe0)
        {
            ch = getch(); // extended keys
            switch(ch)
            {
            case UP:

                switch(col)
                {
                case 1:
                    if(--mood < 1) mood = max1;
                    adminlist(mood,col);
                    break;
                case 2:
                    if(--mood < 1) mood = max2;
                    adminlist(mood,col);
                    break;
                case 3:
                    if(--mood < 1) mood = max3;
                    adminlist(mood,col);
                    break;
                }
                break;///end case up
            case DOWN:
                switch(col)
                {
                case 1:
                    if(++mood > max1) mood = 1;
                    adminlist(mood,col);
                    break;
                case 2:
                    if(++mood > max2) mood = 1;
                    adminlist(mood,col);
                    break;
                case 3:
                    if(++mood > max3) mood = 1;
                    adminlist(mood,col);
                    break;
                }
                break;///end case down
            case LEFT:
                if(--col < 1) col = 3;
                adminlist(1,col);
                break;
            case RIGHT:
                if(++col > 3) col = 1;
                adminlist(1,col);
                break;
            case F1:
                admin_help();
                getch();
                adminlist(1,col);
                break;
            } // switch()
        } // if()
        else
        {
            switch(ch)
            {
            case 'q':
            case 'Q':
            {
                system("cls");
                loadbar(10,10,"Quitting!");
                fdlist.save_food_data();
                dllist.save_meals();
                stlist.save_students_data();
                exit(0);
            }
            case ESC:
                system("cls");
                border();
                gotoxy(0,0);
                border(14,14,35,5);
                gotoxy(16,16);
                cout<<"Do you want to log out?(y/n)";
                ans = getch();
                ans = tolower(ans);
                if(ans == 'y')
                {
                    loadbar(14,10,"Loging out");
                    fdlist.save_food_data();
                    dllist.save_meals();
                    stlist.save_students_data();
                    main_menu();
                }
                else
                    adminlist(mood,col);
                break;
            case ENTER:
                switch(col)
                {
                case 1:///first menu col
                    switch(mood)
                    {
                    case 1:///student list
                        stlist.slist();
                        //getch();
                        adminlist(mood,col);
                        break;
                    case 2:///add student
                        stlist.addst();
                        //getch();
                        adminlist(mood,col);
                        break;
                    case 3:///edit student
                        stlist.findst();
                        adminlist(mood,col);
                        break;
                    case 4:
                        //stlist.delst();
                        adminlist(mood,col);
                        break;
                    case 5:
                        stlist.editst();
                        adminlist(mood,col);
                        break;
                    }
                    break;// end of first menu
                case 2:///second menu col
                    switch(mood)
                    {
                    case 1:///see restuarant daily menu
                        dllist.list();
                        getch();
                        adminlist(mood,col);
                        break;
                    case 2:///add new meal to daily list
                        dllist.addmeal();
                        adminlist(mood,col);
                        break;
                    case 3:///list of foods in menu
                        fdlist.displaylist();
                        adminlist(mood,col);
                        break;
                    case 4:///add food to menu
                        fdlist.addfood();
                        adminlist(mood,col);
                        break;
                    case 5:///Edit  foods in menu
                        fdlist.editfood();
                        getch();
                        adminlist(mood,col);
                        break;
                    case 6:///find food in menu
                        //fdlist.findfood();
                        break;
                    case 7:
                        fdlist.delfood();
                        adminlist(mood,col);
                        break;
                    }
                    break;//end of second menu
                case 3://third menu col
//            char u[10];
                    switch(mood)
                    {
                    case 1:///system info
                        systeminfo();
                        getch();
                        adminlist(mood,col);
                        break;
                    case 2:
                        mesl->admin_inbox();
                        getch();
                        adminlist(mood,col);
                        break;
                    case 3:///edit user & pass
                        system("cls");
                        border();
                        gotoxy(0,0);
                        gotoxy(30,2);
                        cout<<"Change Password";
                        gotoxy(2,4);
                        cout<<"Enter old password : ";
                        gotoxy(2+strlen("Enter old password : "),4);
                        if(checkpass(admin.get_pass()))
                        {
                            gotoxy(2,10);
                            cout<<"Enter new password : ";
                            gotoxy(2+ strlen("Enter new password : "),10);
                            admin.set_pass(getpass(8));
                            gotoxy(20,12);
                            write("Password changed successfuly");
                        }
//end task :)
                        gotoxy(2,47);
                        write("Press any key to go back");
                        getch();
                        adminlist(mood,col);
                        break;
                    case 4:
                        ///find all files and delete theme!
                        stlist.del_all();
                        dllist.del_all();
                        fdlist.del_all();
                        cout<<"DONE!";
                        getch();
                        adminlist(mood,col);
                        break;
                    case 5:///security ///auto log out time & ...
                        border(0,0,80,3);
                        gotoxy(30,1);
                        cout<<"System Security";
                        border(0,3,80,47);
                        gotoxy(2,47);
                        write("Press any key to go back");
                        getch();
                        adminlist(mood,col);
                        break;
                    }
                    break;//end of third menu
                }//end of switch(mood)*/
                break;/// ----- end of case Enter
            }
        }
    }
}

void adminlist(int mood,int col)
{
    /// col is between 1-3
    // static int pcol;
    system("cls");
    gotoxy(0,0);
    /// header ///
    border(0,0,80,3);//header
    gotoxy(32,1);
    cout<<"ADMIN MENU";
    border(0,3,80,44);//main border
    /// ------ tag 1 -----
    border(2,13,24,3);//tag1
    gotoxy(10,14);
    cout<<"Students";
    border(2,16,24,15);
    gotoxy(3,18);
    cout<<" 1.List of Students";
    gotoxy(3,20);
    cout<<" 2.Add Student";//edit & delete is here
    gotoxy(3,22);
    cout<<" 3.Find Student";
    gotoxy(3,24);
    cout<<" 4.Delete student";
    gotoxy(3,26);
    cout<<" 5.Edit student";
    /// ---------tag 2--------
    border(28,13,26,3);//tag2
    gotoxy(35,14);
    cout<<"Self Service";//tag 2
    border(28,16,26,18);
    gotoxy(29,18);
    cout<<" 1.See Daily meal list";
    gotoxy(29,20);
    cout<<" 2.Set Daily list";
    gotoxy(29,22);
    cout<<" 3.See Food Menu ";
    gotoxy(29,24);
    cout<<" 4.Add Food to menu";
    gotoxy(29,26);
    cout<<" 5.Edit Foods in menu";
    gotoxy(29,28);
    cout<<" 6.Find Food in Menu";
    gotoxy(29,30);
    cout<<" 7.Delete Food from Menu";
    /// ---------- tag 3 -------
    border(56,13,22,3);
    gotoxy(64,14);
    cout<<"System";
    border(56,16,22,15);
    gotoxy(57,18);
    cout<<" 1.System info";// total users,total gained money
    gotoxy(57,20);//most reserved portion, most pupular food
    cout<<" 2.Inbox";
    gotoxy(57,22);
    cout<<" 3.Change Password";
    gotoxy(57,24);
    cout<<" 4.Clear data base";
    gotoxy(57,26);
    cout<<" 5.Security";
    /// set try to log in times , set auto save time,set automatic log out time
    ///////////////////////////////////////
    switch(col)
    {
    case 1:///students
        gotoxy(3,18 +(mood-1)*2);
        //cout<<">";
        border(3,18 +(mood-1)*2 -1,22,3,1);
        break;
    case 2:///restuarant
        gotoxy(29,18 +(mood-1)*2);
        //cout<<">";
        border(29,18 +(mood-1)*2 -1,24,3,1);
        break;
    case 3:///system
        gotoxy(57,18 +(mood-1)*2);
        //cout<<">";
        border(57,18 +(mood-1)*2 -1,20,3,1);
        break;
    }
    ///////////////////////////////////////
    border(0,47,80,3);
    gotoxy(2,48);
    cout<<"Press ESC to log out";
    ///date & clock
    mdate(2,5);
    mclock(70,5);
    ///end date & clock
    gotoxy(0,0);

}//end of func!


void creditmenu()
{
    int mood=1;
    char ans;
    budgetlist(mood);
    for(;;)
    {
        int ch = getch();
        if(!ch || ch == 0xe0 || ch ==0x29)
        {
            ch = getch(); // extended keys
            switch(ch)
            {
            case UP:

                if(--mood == 0) mood = 5;
                budgetlist(mood);
                break;
            case DOWN:

                if(++mood == 6) mood = 1;
                budgetlist(mood);
                break;
            case F1:
                cout<<"F1 pressed";
                main_help();
                budgetlist(mood);
                break;
            } // switch()
        } // if()
        else
        {
            switch(ch)
            {
            case 'q':
            case 'Q':
            {
                system("cls");
                loadbar(10,10,"Quitting!");
                save_setting();
                exit(1);
            }
            case ESC:
                system("cls");
                border(14,14,34,5);
                gotoxy(16,16);
                cout<<"Do you want to log out?(y/n) ";
                ans = getche();
                ans = tolower(ans);
                if(ans == 'y')
                {
                    loadbar(14,11,"Quiting");
                    main_menu();
                }
                else
                    mlist(mood);
                break;
                /*case F1:
                help();
                main_menu();*/
                break;
            case ENTER:
                switch(mood)
                {
                case 1:
                    stlist.slist();
                    getch();
                    budgetlist(mood);
                    break;
                case 2:
                    stlist.findst();
                    getch();
                    budgetlist(mood);
                    break;
                case 3:
                    ///restaurant daily menu
                    getch();
                    budgetlist(mood);
                    break;
                case 4:
                    systeminfo();
                    getch();
                    budgetlist(mood);
                    break;
                case 5:
                    system("cls");
                    border(14,14,32,5);
                    gotoxy(16,16);
                    cout<<"Do you want to log out?(y/n)";
                    ans = getche();
                    ans = tolower(ans);
                    if(ans == 'y')
                    {
                        loadbar(14,11,"Quiting");
                        exit(1);
                    }
                    else
                        budgetlist(mood);
                    break;
                }

                break;
            }
        }
    }
}
void budgetlist(int mood)///sub menu for budget operator!
{
    clrscr();
    border();
    border(22,15,33,14);//menu border
    border(22,8,33,5);
    gotoxy(25,10);
    cout<<"Student Budget Allocater";
///----------------------------------
    gotoxy(24,17);
    cout<<" 1.List of students";
    gotoxy(24,19);
    cout<<" 2.Find student";
    gotoxy(24,21);
    cout<<" 3.See restaurant daily list";
    gotoxy(24,23);
    cout<<" 4.System info";
    gotoxy(24,25);
    cout<<" 5.Log out";
///-------------------------------------
    gotoxy(24,17+2*(mood-1));
    cout<<">";
    gotoxy(2,47);
    cout<<"Press Esc to log out";
///-------------------------------------
    mdate(2,2);
    mclock(70,2);
    gotoxy(0,0);//just for a good shape
}
void setting()
{
    border();
    char colort;
    char colorb;
    int mood =1;
    char a;
    border();
    settinglist(mood);
    for(;;)
    {
        int ch = getch();
        if(!ch || ch == 0xe0)
        {
            ch = getch(); // extended keys
            switch(ch)
            {
            case UP:
                system("cls");
                if(--mood == 0) mood = 5;
                settinglist(mood);
                break;
            case DOWN:
                system("cls");
                if(++mood == 6) mood = 1;
                settinglist(mood);
                break;
            } // switch()
        } // if()
        else
        {
            switch(ch)
            {
            case 'q':
            case 'Q':
            {
                system("cls");
                std::cout << "Quitting!\n";
                exit(0);
            }
            case ESC:
                main_menu();
                break;
            case ENTER:
                switch(mood)
                {
                case 1:
                    system("cls");
                    border();
                    gotoxy(0,0);
                    gotoxy(2,2);
                    cout<<"Choose background color :";
                    gotoxy(2,4);
                    cout<<"black = 0,\tgrey = 8";
                    gotoxy(2,6);
                    cout<<"blue = 1\tlight blue = 9";
                    gotoxy(2,8);
                    cout<<"green = 2\tlight green = A";
                    gotoxy(2,10);
                    cout<<"aqua = 3\tlight aqua = B";
                    gotoxy(2,12);
                    cout<<"red = 4\tlight red = C";
                    gotoxy(2,14);
                    cout<<"purple = 5\tlight purple = D";
                    gotoxy(2,16);
                    cout<<"yellow = 6\tlight yellow = E";
                    gotoxy(2,18);
                    cout<<"white = 7\tlight white = F";
                    gotoxy(2,20);
                    cout<<"Enter color code(0-9 or A-F) for bakground: ";
                    colorb =getch();
                    colour[6] = colorb;
                    colort = colour[7];
                    setcolor(colort,colorb);
                    settinglist(mood);
                    break;
                case 2:
                    system("cls");
                    border();
                    gotoxy(0,0);
                    gotoxy(2,2);
                    cout<<"Choose text color:";
                    gotoxy(2,4);
                    cout<<"black = 0\tgrey = 8";
                    gotoxy(2,6);
                    cout<<"blue = 1\tlight blue = 9";
                    gotoxy(2,8);
                    cout<<"green = 2\tlight green = A";
                    gotoxy(2,10);
                    cout<<"aqua = 3\tlight aqua = B";
                    gotoxy(2,12);
                    cout<<"red = 4\tlight red = C";
                    gotoxy(2,14);
                    cout<<"purple = 5\tlight purple = D";
                    gotoxy(2,16);
                    cout<<"yellow = 6\tlight yellow = E";
                    gotoxy(2,18);
                    cout<<"white = 7\tlight white = F";
                    gotoxy(2,20);
                    cout<<"Enter color code(0-9 or A-F) for text: ";
                    colort = getch();
                    colour[7] = colort;
                    colorb = colour[6];
                    setcolor(colort,colorb);
                    settinglist(mood);
                    break;
                case 3:
                    system("cls");
                    border();
                    gotoxy(2,2);
                    cout<<"Choose Screen saver :";
                    gotoxy(2,4);
                    cout<<"[1].Clock";
                    gotoxy(2,6);
                    cout<<"[2].Fire works!";
                    gotoxy(2,8);
                    cout<<"[3].Digital Clock";
                    gotoxy(50,47);
                    cout<<"press other keys to go back";
                    gotoxy(0,0);
                    gotoxy(3+strlen("Choose Screen saver :"),2);
                    a  = getche();
                    if(a =='1')
                    {
                        loadbar(5,10,"Clock screen saver choosed!");
                        screensav =1;
                        screensaver1();
                        settinglist(mood);
                    }
                    else if (a =='2')
                    {
                        loadbar(5,10,"Fire works screen saver choosed!");
                        screensav = 2;
                        screensaver2(50);
                        settinglist(mood);
                    }
                    else if (a == '3')
                    {
                        loadbar(5,10,"Digital Clock screen saver choosed!");
                        screensav = 3;
                        screensaver3();
                        settinglist(mood);
                    }
                    else
                        settinglist(mood);
                    break;
                case 4:
                    system("cls");
                    border(0,0,79,5);
                    gotoxy(0,0);
                    gotoxy(2,2);
                    cout<<"Enter auto log out time (sec): ";
                    cin>>log_out_time;
                    settinglist(mood);
                    break;
                case 5:
                    system("cls");
                    border(0,0,79,5);
                    gotoxy(0,0);
                    gotoxy(2,2);
                    cout<<"Enter wait time for activing screen saver (sec): ";
                    cin>>screen_saver_wait_time;
                    settinglist(mood);
                    break;
                }

            }
        }
    }
}
void settinglist(int a)
{
    static int y;
    system("cls");
    border();
    border(22,4,33,5);
    gotoxy(30,6);
    cout<<"System Setting";
    border(20,14,40,13);
    gotoxy(23,16);
    cout<<"1.Change background color";
    gotoxy(23,18);
    cout<<"2.Change text color";
    gotoxy(23,20);
    cout<<"3.Select Screen Saver";
    gotoxy(23,22);
    cout<<"4.Set auto log out time";
    gotoxy(23,24);
    cout<<"5.Set wait time for screen saver";
    gotoxy(22,16+2*(a-1));
    cout<<">";
    y = a;
    gotoxy(3,47);
    cout<<"Press ESC to go back";
    gotoxy(0,0);
}
void setcolor(char text,char back)
{
    text = toupper(text);
    back = toupper(back);
    if((text<='9' && text >='0')||(text>='A' && text<='F'))
        colour[7] = text;
    else
    {
        colour[7] = '7';
        blink(10,30,3,"Wrong code");
    }
    if((text<='9' && text >='0')||(text>='A' && text<='F'))
        colour[6] = back;
    else
    {
        colour[6] = '0';
        blink(10,30,3,"Wrong code");
    }
    system(colour);
}
void setcolor(int n)
{
    HANDLE hstdin  = GetStdHandle( STD_INPUT_HANDLE  );
    HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
    WORD   index   = 0;

    // Remember how things were when we started
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo( hstdout, &csbi );
    SetConsoleTextAttribute( hstdout, n );
}
int getcolor(char color[])//atoi but in hex mood!
{
    //"color:##"
    int total;
    int n;
    for(int i=6; color[i] != '\0' ; i++)
    {
        if(color[i] >='A'&& color[i] <= 'F')
        {
            n =	(int)(color[i] - 'A');
        }
        else if(color[6] >='0'&& color[6] <= '9')
        {
            n =	(int)(color[6] - '0');
        }
        total += 16*total;///hex!
    }
    return total;
}
bool waittime(int z)
{
    int wsec= 0;
    time_t rawtime;
    struct tm * timeinfo1,* timeinfo2,tem;
    time ( &rawtime );
    timeinfo1 = localtime ( &rawtime );
    tem = *timeinfo1;
    while(!kbhit())
    {
        time ( &rawtime );
        timeinfo2 = localtime ( &rawtime );
        wsec =((timeinfo2->tm_hour - tem.tm_hour) * 3600 + (timeinfo2->tm_min-tem.tm_min) *60 + (timeinfo2->tm_sec-tem.tm_sec));
        if(wsec >= z)
        {
            return true;
        }
    }
    return false;
}
void screensaver1()
{
    system("cls");
    int i=5,j=5;
    int count=0;
    time_t rawtime;
    struct tm * ti;
    while(true)
    {
        if(!kbhit())
        {
            time ( &rawtime );
            ti = localtime ( &rawtime );
            gotoxy(i,j);
            printf("%.2d:%.2d:%.2d",ti->tm_hour,ti->tm_min,ti->tm_sec);
            srand(time(&rawtime));
            count = rand();
            if(count<0)
                count=-count;
            srand(time(NULL));
            i = rand()%70 + 5;
            srand(time(NULL));
            j = rand()%40 +5;
            switch(count%12)
            {
            case 0:
                system("color 5");
                break;
            case 1:
                system("color 1");
                break;
            case 2:
                system("color D");
                break;
            case 3:
                system("color F");
                break;
            case 4:
                system("color E");
                break;
            case 5:
                system("color C");
                break;
            case 6:
                system("color 4");
                break;
            case 7:
                system("color 6");
                break;
            case 8:
                system("color 3");
                break;
            case 9:
                system("color A");
                break;
            case 10:
                system("color B");
                break;
            case 11:
                system("color 2");
                break;
            }
            border(21,1,21,5);
            gotoxy(23,3);
            cout<<"Screen Saver mood";
            gotoxy(40,47);
            cout<<"press any key to leave . . .";
            if(++i >= 75) i= 5;
            if(++j >= 45) j = 5;
            if(++i <= 0) i= 2;
            if(++j <= 0) j = 2;
            waittime(1);
            //Sleep(800);
            system("cls");
        }
        else
            break;
    }
    system(colour);
}
void screensaver2(int t = 50)
{
    /// t  = speed of screen saver
    int sx = 5,sy = 45;
    system("cls");
    while(!kbhit())
    {
        srand(time(NULL));
        sx = rand()%30 + 30;
        sy = rand()%8 + 35;
        int count = rand();
        switch(count%12)
        {
        case 0:
            system("color 5");
            break;
        case 1:
            system("color 1");
            break;
        case 2:
            system("color D");
            break;
        case 3:
            system("color F");
            break;
        case 4:
            system("color E");
            break;
        case 5:
            system("color C");
            break;
        case 6:
            system("color 4");
            break;
        case 7:
            system("color 6");
            break;
        case 8:
            system("color 3");
            break;
        case 9:
            system("color A");
            break;
        case 10:
            system("color B");
            break;
        case 11:
            system("color 2");
            break;
        }
        gotoxy(32,3);
        cout<<"Screen Saver mood";
        gotoxy(40,47);
        cout<<"press any key to leave . . .";
        for(int i=0; i<9; i++)
        {
            gotoxy(sx,sy-i);
            cout<<(char)221;
            Sleep(2*t);
            gotoxy(sx,sy-i);
            cout<<" ";
            Sleep(2*t);
        }
        gotoxy(sx,sy-6);
        cout<<"*";
        Sleep(3*t);
        gotoxy(sx,sy-6);
        cout<<" ";
        Sleep(3*t);
        int trace = 8+1;
        sy = sy - trace;
        ///////////////
        ///Level 1
        int i =0;
        for(i=1; i<14; i++)
        {
            gotoxy(sx-i,sy-i);
            cout<<(char)92;
            gotoxy(sx-i,sy);
            cout<<(char)196;//-
            gotoxy(sx-i,sy+i);
            cout<<"/";
            gotoxy(sx,sy+i);
            cout<<(char)179;
            gotoxy(sx+i,sy+i);
            cout<<(char)92;
            gotoxy(sx+i,sy);
            cout<<(char)196;
            gotoxy(sx+i,sy-i);
            cout<<"/";
            gotoxy(sx,sy-i);
            cout<<"|";
            Sleep(t);
            gotoxy(sx-i,sy-i);
            cout<<" ";
            gotoxy(sx-i,sy);
            cout<<" ";
            gotoxy(sx-i,sy+i);
            cout<<" ";
            gotoxy(sx,sy+i);
            cout<<" ";
            gotoxy(sx+i,sy+i);
            cout<<" ";
            gotoxy(sx+i,sy);
            cout<<" ";
            gotoxy(sx+i,sy-i);
            cout<<" ";
            gotoxy(sx,sy-i);
            cout<<" ";
            Sleep(t);
        }
        ///////////////
        system("cls");
    }
    system(colour);
}
void screensaver3()
{
    int x  = 23,y = 20;
    int count =0;
    time_t rawtime;
    struct tm * ti;
    while(true)
    {
        if(!kbhit())
        {
            system("cls");
            time ( &rawtime );
            ti = localtime ( &rawtime );
            border(20,18,41,11);
            //hour
            if(ti->tm_hour/10 !=1)
                digital_num(x,y,ti->tm_hour/10);
            else
                digital_num(x+2,y,ti->tm_hour/10);
            digital_num(x+5,y,ti->tm_hour%10);
            //
            border(x+10,y+1,2,2,1);
            border(x+10,y+4,2,2,1);
            //min
            if(ti->tm_min/10 != 1)
                digital_num(x+13,y,ti->tm_min/10);
            else
                digital_num(x+15,y,ti->tm_min/10);
            digital_num(x+18,y,ti->tm_min%10);
            //seperator
            border(x+23,y+1,2,2,1);
            border(x+23,y+4,2,2,1);
            //sec
            if(ti->tm_sec/10 !=1)
                digital_num(x+26,y,ti->tm_sec/10);
            else
                digital_num(x+28,y,ti->tm_sec/10);
            digital_num(x+31,y,ti->tm_sec%10);
            //
            srand(time(&rawtime));
            count = rand();
            if(count<0)
                count=-count;
            switch(count%12)
            {
            case 0:
                system("color 5");
                break;
            case 1:
                system("color 1");
                break;
            case 2:
                system("color D");
                break;
            case 3:
                system("color F");
                break;
            case 4:
                system("color E");
                break;
            case 5:
                system("color C");
                break;
            case 6:
                system("color 4");
                break;
            case 7:
                system("color 6");
                break;
            case 8:
                system("color 3");
                break;
            case 9:
                system("color A");
                break;
            case 10:
                system("color B");
                break;
            case 11:
                system("color 2");
                break;
            }///end of switch
            gotoxy(2,47);
            cout<<"Press any key to leave . . .  ";
            waittime(1);
        }///end of if
        else
            break;
    }///end of while!
    system(colour);
}
/// end of screen saver
//////////////////////////////////////////////
///clock & Date
void mclock(int x,int y)
{
    int sec_count=0;
    time_t rawtime;
    struct tm *timeinfo2;
    while(!kbhit())
    {
        time ( &rawtime );

        timeinfo2 = localtime ( &rawtime );
        if(sec_count >= log_out_time)
        {
            ///log out
        }
        if(sec_count >= screen_saver_wait_time)
        {
            if(screensav == 1 )
                screensaver1();
            else if (screensav == 2 )
                screensaver2();
            else
                screensaver3();
        }
        if(waittime(1))
        {
            gotoxy(x,y);
            printf("%.2d:%.2d:%.2d",timeinfo2->tm_hour,timeinfo2->tm_min,timeinfo2->tm_sec);
            sec_count++;
        }
    }///end of while
}
void mdate(int x,int y)
{
    time_t rawtime;
    struct tm *timeinfo2;
    time ( &rawtime );
    timeinfo2 = localtime ( &rawtime );
    gotoxy(x,y);
    cout<<(timeinfo2->tm_year + 1900)<<"."<<timeinfo2->tm_mon<<"."<<timeinfo2->tm_mday;
    gotoxy(0,0);
}///end of while

void systeminfo()
{
    system("cls");
    border(0,0,80,3);
    gotoxy(0,0);
    gotoxy(32,1);
    cout<<"System info";
    gotoxy(0,0);
    border(0,3,80,47);
    gotoxy(0,0);
    int y =8;///start point
    gotoxy(2,y);
    write("Total students : ");
    cout<<(bstudent_count + gstudent_count);
    gotoxy(12,y +=2);
    write("Females : ");
    cout<<gstudent_count;
    gotoxy(12,y+=2);
    write("Males : ");
    cout<<bstudent_count;
    gotoxy(2,y+=3);
    write("Most served meal : ");
    gotoxy(2,y+=3);
    write("Least served meal : ");
    gotoxy(2,y+=3);
    write("Total served meals : ");
    gotoxy(2,y+=3);
    write("Total foods in menu : ");
    cout<<food_count;
    gotoxy(2,47);
    cout<<"Press any key to go back";
    gotoxy(0,0);
}
void studentlist(int mood)
{
    system("cls");
    border();
    gotoxy(25,10);
    cout<<"Welcome "<<st->name;
///----------------------------------
    border(25,14,30,15);
    gotoxy(27,17);
    cout<<" 1.Reserve meal";
    gotoxy(27,19);
    cout<<" 2.List of Reserved meals";
    gotoxy(27,21);
    cout<<" 3.Change Password";
    gotoxy(27,23);
    cout<<" 4.Contact System manager";
    gotoxy(27,25);
    cout<<" 5.Log out";
///-------------------------------------
    gotoxy(27,17+2*(mood-1));
    cout<<">";
///showing balances
    border(44,43,32,5);
    gotoxy(46,45);
    cout<<"Account Balance : "<<st->bal<<" R";
    ///showing date and time
    gotoxy(2,47);
    cout<<"Press ESC to go back";
    mdate(3,3);
    mclock(70,3);

}

void main_help()
{
    system("cls");
    border();
    border(30,1,15,3);
    gotoxy(36,2);
    cout<<"Help";
    int x = 3,y = 7;
    gotoxy(x-1,y);
    cout<<"Keboard actions :";
    gotoxy(x,y+=2);
    cout<<"ESC = back , log out , Quit";
    gotoxy(x,y+=2);
    cout<<"Enter = go in , select , reserve";
    gotoxy(x,y+=2);
    cout<<"Del = Delete , Unreserve";
    gotoxy(x,y+=2);
    cout<<"Up & Down arrow keys: Go up & down";
    gotoxy(x,y+=2);
    cout<<"Right & Left arrow keys: Next page & Previose page";
    gotoxy(x,y+=2);
    cout<<"'Q'= Exit program";
    gotoxy(x,y+=2);
    cout<<"F1= help";
    line(x-1,y+=2,76);
    gotoxy(x,y+=2);
    write("This program allows you to choose color (fore color and text color)",1);
    gotoxy(x,y+=2);
    write(", use arrow keys (up,down , ...) , and test console Screen Savers!",1);
    gotoxy(2,47);
    write("Press any key to go back");
    gotoxy(0,0);

}
///about the writers

void about()
{
    system("cls");
    border();
    gotoxy(0,0);
    gotoxy(30,2);
    cout<<"About us";
    gotoxy(2,5);
    write("This system has been desigened by Hassan Ahmadi");
    gotoxy(2,7);
    write("Released in Spring 2012");
    gotoxy(2,9);
    write("Proudly superwised by Dr.Hamid Reza Mahdiani");
    gotoxy(2,12);
    write("Contact us : ");
    gotoxy(25,14);
    write("www.computerlab.miahnblog.com");
    gotoxy(2,16);
    write("Email : 1herohacker@gmail.com ");
    gotoxy(9,18);
    write("Eslahi_alireza@yahoo.com");
    gotoxy(2,20);
    write("Follow us on facebook : ");
    gotoxy(25,22);
    write("http://facebook.com/hassan.ahmadi.31?ref=tn_tnmn");

    gotoxy(2,47);
    cout<<"Press any key to go back";
    gotoxy(0,0);
    getch();
}
bool message_list::contact_admin(student *curptr)
{
    message *newmes = new message;
    newmes->next = NULL;
    ///copying studentd identifications :
    strcpy(newmes->st.name,curptr->name);
    strcpy(newmes->st.family,curptr->family);
    strcpy(newmes->st.st_ID,curptr->st_ID);
    ///
    getdate(&newmes->t.tm_mday,&newmes->t.tm_mon,&newmes->t.tm_year);
    gettime(&newmes->t.tm_hour,&newmes->t.tm_min,&newmes->t.tm_sec);
    clrscr();
    border();
    gotoxy(0,0);
    gotoxy(25,2);
    cout<<"Send Message to Admin";
    gotoxy(12,6);
    cout<<"Message : ";
    border(10,8,60,33);
    gotoxy(12,10);
    cout<<" Subject : ";
    line(12,12,56);             ///header ends
    /////////////////////////////////////////////////
    ////////////////////////////////////////////////
    line(12,36,56);             ///footer starts
    gotoxy(12,38);
    cout<<"Press '/' to end";
    gotoxy(44,38);
    cout<<"Max 540 charachters ";        ///footer ends
    //////////////////////////////////////////////////////
    ///main part
    gotoxy(24,10);
    smartget(newmes->title);
    char a[54];
    bool stop ;
    ///saving message to the file!!!
    strcpy(newmes->message_name,messagename(st));
    cout<<newmes->message_name<<endl;
    getch();
    for(int j = 0,i = strlen("message/"); newmes->message_name[i] != NULL; i++,j++)
    {
        newmes->message_name_to_list[j] = newmes->message_name[i];
    }
    cout<<newmes->message_name_to_list;
    ofstream list("message/messagelist.ms",ios::app);
    list<<newmes->message_name_to_list<<"\n";
    list.close();
    ofstream mes(newmes->message_name);
    if(!mes)
    {
        cout<<"Can't access file!";
        return false;
    }
    mes<<newmes->title<<"\t"<<newmes->t.tm_year<<" "<<newmes->t.tm_mon<<" "<<newmes->t.tm_mday<<"\t"<<newmes->t.tm_hour<<" "<<newmes->t.tm_min<<" "<<newmes->t.tm_sec<<"\n";
    for(int i=0; i<=10; i++)
    {
        gotoxy(12,(i*2)+14);
        stop = smartget(newmes->content[i],54,'/');
        mes<<newmes->content[i]<<"\n";
        if(!stop)
            break;
    }
    mes.close();
    blink(65-strlen("Sending Message . . . "),6,4,"Sending Message . . . ");
    gotoxy(65-strlen("Sending Message . . . "),6);
    cout<<"                      ";
    gotoxy(65-strlen("Sending Message . . . "),6);
    write("Message Sent!",3);
    ///main part ends!
    //////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////
    gotoxy(2,47);
    cout<<"Press any key to go back";
    if(first = NULL)
        first = last = newmes;
    else
    {
        last->next = newmes;
        last  = newmes;
    }
    return true;
}
bool message_list::save_new_message_list()
{
    message *curmes = first;
    ofstream mes("message/messagelist.ms");
    if(!mes) return false;
    while(curmes)
    {
        mes<<curmes->message_name_to_list;
        curmes = curmes->next;
    }
    mes.close();
    return true;
}
int message_list::load_messages()
{
    int message_count = 0;
    ifstream mes("message/messagelist.ms");
    if(!mes)	return -1;
    bool end = false;
    while(!end)
    {
        cout<<"LOOP\t";
        message *newmes = new message;
        newmes->next = NULL;
        mes>>newmes->message_name_to_list;
        if(strcmp(newmes->message_name_to_list,"")==0)
        {
            end = true;
            continue;
        }
        strcpy(newmes->st.st_ID,newmes->message_name_to_list);
        for(int i=0; newmes->st.st_ID[i]; i++)
        {
            if(newmes->st.st_ID[i] == '-')  newmes->st.st_ID[i] = NULL;
        }
        cout<<message_count++<<endl;
        cout<<newmes->message_name_to_list<<"\n";
        if(first == NULL)
            first = last = newmes;
        else
        {
            cout<<"else!";
            last->next = newmes;
            last = newmes;
        }
    }
    cout<<endl<<"OUt of loop";
    message *curmes = first;
    ///reading the whole files which was listed in the message list!
    int gh=0;
    cout<<'a'<<message_count;
    while(curmes)
    {
        show_message(curmes);
        curmes = curmes->next;
    }
    while(curmes)
    {
        cout<<gh++;
        char real_name[60];
        strcpy(real_name,"message/");
        strcat(real_name,curmes->message_name_to_list);
        strcpy(real_name,curmes->message_name);
        ifstream fp(curmes->message_name);
        if(!fp)	return -1;
        fp>>curmes->title;
        fp>>curmes->t.tm_year;
        fp>>curmes->t.tm_mon;
        fp>>curmes->t.tm_mday;
        fp>>curmes->t.tm_hour;
        fp>>curmes->t.tm_min;
        fp>>curmes->t.tm_sec;
        for(int i=0; !mes.eof(); i++)
        {
            fp.getline(curmes->content[i],54);
        }
        fp.close();
        show_message(curmes);
        curmes = curmes->next;
    }//end of reading all files!

}
void message_list::admin_inbox()
{
    int message_count = load_messages();
    int row = 0;
    for(;;)
    {
        int ch = _getch();
        if(!ch || ch == 0xe0)
        {
            ch = _getch(); // extended keys
            switch(ch)
            {
            case UP:
                if(--row <= 0) row = message_count;
                admin_inbox_list(row,0);
                break;
            case DOWN:
                if(++row > message_count) row = 1;
                admin_inbox_list(row,0);
                break;
            case DELETE:///delete messages!
            {
                message *curmes = first;
                int con = 1;
                while(con != row)
                {
                    curmes = curmes->next;
                    con++;
                }
                delete_message(curmes);
                gotoxy(5,5);
                load_messages();
                break;
            }

            } // switch()
        } // if()
        else
        {
            switch(ch)
            {

            case ESC:
                getch();
                adminmenu();
                break;

            case ENTER:
            {
                message *curmes = first;
                int con = 1;
                while(con != row)
                {
                    curmes = curmes->next;
                    con++;
                }
                show_message(curmes);
                admin_inbox();
                break;
            }

            }
        }
    } // for(;;)
}
void message_list::delete_message(message *curmes)
{
    if(curmes ==first)
    {
        first = first->next;
        delete curmes;
    }
    else
    {
        message *tempmes = first;
        while(tempmes->next != curmes) ///seeking behind nextptr
        {
            tempmes = tempmes->next;
        }
        if(curmes ==last)
        {
            last = tempmes;
            tempmes->next = curmes->next;
            delete curmes;
        }
    }
}
int message_list::admin_inbox_list(int m,bool op = 0)///reads messages!
{
    system("cls");
    border();
    gotoxy(0,0);
    ///header
    border(28,1,15,5);
    gotoxy(32,3);
    cout<<"Inbox";
    ///header -  -  - end!
    gotoxy(3,7);
    cout<<"## Student ID\t\tDate\t\tTime";
    int i = 0,x = 3;
    message *curmes = first;
    while(curmes)
    {
        gotoxy(x,9+2*i);
        printf("%.2d ",i);
        cout<<curmes->st_ID<<curmes->t.tm_year<<'.'<<curmes->t.tm_mon<<'.'<<curmes->t.tm_mday
            <<' '<<curmes->t.tm_hour<<':'<<curmes->t.tm_min<<':'<<curmes->t.tm_sec;
        i++;
        /*if(i%16 == 0)
            {x += 22;
            gotoxy(x,7);
            cout<<"## Student ID\t\tDate\t\tTime";
            if(i<32)
                vline(x-2,7,38);*/

    }
    if(op)//opening choosed message!
    {
        message *curmes = first;
        int con = 1;
        while(con != m)
        {
            curmes = curmes->next;
            con++;
        }
        show_message(curmes);
    }///end of if open
    if(!op)
    {
        ///point time!
        int x_border;
        if(m<=16)
            x_border = 2;
        else if(m<33)
            x_border = 26;
        else
            x_border = 51;
        border(x_border,9+2*(m%16-1)-1,15,3,1);
        gotoxy(2,47);
        cout<<"Press Esc to go back";
    }
    return i;
}
bool message_list::show_message(message *curmes)
{
    system("cls");
    border();
    gotoxy(0,0);
    border(10,8,60,33);
    gotoxy(12,10);
    cout<<" Subject : ";
    line(12,12,56);             ///header ends
    /////////////////////////////////////////////////
    ////////////////////////////////////////////////
    line(12,36,56);             ///footer starts
    gotoxy(12,38);
    cout<<"Date : ";
    gotoxy(12,6);
    cout<<"From : ";
    gotoxy(20,6);
    //cout<<curmes->st.name<<"\t"<<curmes->st.family;
    cout<<curmes->st.st_ID;
    gotoxy(27,10);
    cout<<curmes->title;
    gotoxy(20,38);
    cout<<curmes->t.tm_year<<'.'<<curmes->t.tm_mon<<'.'<<curmes->t.tm_mday;
    gotoxy(53,38);
    cout<<"Time : ";
    gotoxy(60,38);
    printf("%.2d:%.2d:%.2d",curmes->t.tm_hour,curmes->t.tm_min,curmes->t.tm_sec);
    for(int i=0; curmes->content[i] != NULL; i++)
    {
        gotoxy(12,(i*2)+12);
        cout<<curmes->content[i];
    }
    gotoxy(2,47);
    cout<<"Press any key to go back";
    getch();
    return true;
}



char* messagename(student *curptr)
{
    char temp[10];
    char name[100];
    char messageloc[100];
    int day,month,year,hour,min,sec;
    getdate(&day,&month,&year);
    gettime(&hour,&min,&sec);
    /// we have collected data ! now lets make the file name!
    strcpy(name,"message/");
    strcat(name,st->st_ID);
    strcat(name,"-");
    //
    itoa(year,temp,10);
    strcat(name,temp);
    //
    itoa(month,temp,10);
    strcat(name,temp);
    //
    itoa(day,temp,10);
    strcat(name,temp);
    //
    itoa(hour,temp,10);
    strcat(name,temp);
    //
    itoa(min,temp,10);
    strcat(name,temp);
    //
    itoa(sec,temp,10);
    strcat(name,temp);
    //
    strcat(name,".ms");

    return name;
}
///----------------------------------///
void admin_help()
{
    system("cls");
    border();
    gotoxy(0,0);
    border(30,1,10,3);
    gotoxy(34,2);
    cout<<"HELP";
    int x=2,y=7;
    gotoxy(2,5);
    cout<<">> Student : ";
    gotoxy(x,y);
    cout<<"> You can see list of students , and by pressing Enter key go for editing";
    gotoxy(x,y+=2);
    cout<<"   a student or by pressing Del key delete a student";
    gotoxy(x,y+=2);
    cout<<"> In Find menu you can find students by : name ,family name ,ID or Student";
    gotoxy(x,y+=2);
    cout<<"  ID number and edit or delete the student you want!";
    gotoxy(x,y+=2);
    cout<<"> You can stil Edit and Delete directly  by Student ID number in choices 3&4 ";

    //----------------------
    line(2,y+=2,76);
    ///---------------------
    /// /// // / \ \\ \\\ \\\\
    y = 23;
    gotoxy(x,y+=2);
    cout<<">>  Restaurant : ";
    gotoxy(x,y+=2);
    cout<<"> Daily list of self service lets you see the list,edit meals by pressing Enter key.";
    gotoxy(x,y+=2);
    cout<<"> ";

}
