#include <iostream>
#include <conio.h>
#include <dir.h>
/*** key values ***/
#define UP           0x48
#define DOWN         0x50
#define RIGHT        0x4D
#define LEFT         0x4B
#define ESC          0x1B
#define ENTER        0x0D
#define DELETE       0x53
///global variable
int gstudent_count = 0;///total girl students count
int bstudent_count = 0;///total boy  student count
/// Operators are here ------------------////////
class IT_operator
{
private:
    char user[10];
    char pass[10];
public:
    IT_operator()
    {
        strcpy(user,"admin");
        strcpy(pass,"admin");
    }
    void set_user(char a[10])
    {
        strcpy(user,a);
    }
    void set_pass(char a[10])
    {
        strcpy(pass,a);
    }
    char* get_user()
    {
        return user;
    }
    char* get_pass()
    {
        return pass;
    }
} admin;

class food_operator
{
    char user[10];
    char pass[10];
public:
    food_operator()
    {
        strcpy(user,"foperator");
        strcpy(pass,"12345");
    }
    void set_user(char a[10])
    {
        strcpy(user,a);
    }
    void set_pass(char a[10])
    {
        strcpy(pass,a);
    }
    char* get_user()
    {
        return user;
    }
    char* get_pass()
    {
        return pass;
    }
} foperator;

/// operrators ends here


class student
{
public:
    char name[20];
    char family[20];
    char st_ID[14];
    char ID_num[18];
    int bal;//money balance
    char user[20];
    char pass[20];
    bool gen;//true = man, false = woman
public:
    student *next;
    void set_balance(int b)
    {
        bal = b;
    }
    /*char* get_name(){return name;}
    char* get_family(){return family;}
    char* get_ID_num(){return ID_num;}
    char* get_st_ID(){return st_ID;}

    void set_name(char a[20]){strcpy(name,a);}
    void set_family(char a[20]){strcpy(family,a);}
    void set_st_ID(char b[20]){strcpy(st_ID,b);}
    void set_ID_num(char c[10]){strcpy(ID_num,c);}
    ////////////////////////////////////////////////*/
    void set_user(char c[])
    {
        strcpy(user,c);
    }
    void set_pass(char c[])
    {
        strcpy(pass,c);
    }
    char* get_user()
    {
        return user;
    }
    char* get_pass()
    {
        return pass;
    }
};
class st_list
{
public:
    student *first;
    student *last;
    st_list()
    {
        first = last = NULL;
    }
    ~st_list()
    {
        student *curptr = first;
        student *temp;
        while(curptr)
        {
            temp = curptr;
            curptr = curptr->next;
            delete temp;
        }
    }
    void del_all()
    {
        student *curptr = first;
        student *temp;
        while(curptr)
        {
            temp = curptr;
            curptr = curptr->next;
            delete temp;
        }
    }
    void isuniqe();
    bool isuniqe(student *curptr);
    void sort();
    void addst();
    void delst(student *curptr);
    void slist();
    void editst(student *curptr);
    void editst();
    void findst();
    student findst(student *curptr);
//    student* friend tofirst();
    void stinfo(student *curptr);
    void st_list::stinfo(student *curptr,int x,int y);
    void friend fmenu(int m);
    void kslist(int mood);
    void kslist(int mood,int page);
    void save_students_data();
    void load_students_data();
    void swap(student *curptr,student *nextptr);
    student* tofirst(student *curptr)
    {
        curptr = first;
        return curptr;
    }
    friend class IT_operator;
};
void st_list::save_students_data()
{
    //isuniqe();
    ofstream sav("students_list.dat");
    student *curptr = first;
    while(curptr)
    {
        sav<<curptr->st_ID<<"\t";
        sav<<curptr->gen<<"\t";
        sav<<curptr->name<<"\t";
        sav<<curptr->family<<"\t";
        sav<<curptr->ID_num<<"\t";
        sav<<curptr->bal<<"\t";
        sav<<curptr->user<<"\t";
        sav<<curptr->pass<<"\n";
        curptr = curptr->next;
    }
    sav<<"---";
    sav.close();
}
///..........load ............///
void st_list::load_students_data()
{
    system("cls");
    ifstream load("students_list.dat");
    bool flag = true;
    while(flag)
    {
        student *newptr = new student;
        newptr->next = NULL;
        if(first == NULL)
            first = last = newptr;
        else
        {
            last->next = newptr;
            last = newptr;
        }
        //reading data
        load>>newptr->st_ID;
        if(strcmp(newptr->st_ID,"---")== 0)
        {
            flag = false;
            break;
        }

        load>>newptr->gen;
        if(newptr->gen)
            bstudent_count++;
        else
            gstudent_count++;
        load>>newptr->name;
        load>>newptr->family;
        load>>newptr->ID_num;
        load>>newptr->bal;
        load>>newptr->user;
        load>>newptr->pass;
        newptr = newptr->next;
    }
    student *cptr = first,*nptr = first;
    while(nptr)
    {
        if(strcmp("---",nptr->st_ID)==0)
        {
            if(nptr ==first)
            {
                first = first->next;
                delete nptr;
                break;
            }
            else
            {
                if(nptr ==last)
                    last = cptr;
                cptr->next = nptr->next;
                delete nptr;
                break;
            }
        }
        else
        {
            cptr = nptr;
            nptr = nptr->next;
        }
    }
    load.close();
    isuniqe();
    //sort();
}
///----------------ADD----------------------///
void st_list::addst()
{
    int xpos = 5,ypos = 6;
    student *newptr = new student;
    if(!newptr)
    {
        cout<<"\t\t\t\tAllocation ERROR!\n";
        getch();
        return;
    }
    newptr->next = NULL;
    /// ////// HEADER  ////////////
    system("cls");
    border();
    gotoxy(0,0);
    gotoxy(30,2);
    cout<<"ADD NEW STUDENT";
//
    gotoxy(2,45);
    cout<<"Enter 'end' to exite adding";
///      main                         ///
    gotoxy(xpos,ypos);
    cout<<"Enter student name : ";
    gotoxy(xpos,ypos +=2);
    cout<<"Enter student family name : ";
    gotoxy(xpos,ypos +=2);
    cout<<"Enter student ID number: ";
    gotoxy(xpos,ypos +=2);
    cout<<"Enter the ID number : ";
    gotoxy(xpos,ypos +=2);
    cout<<"Gender (male/female) : ";
    gotoxy(xpos,ypos +=2);
    cout<<"Enter account balance (Riall) : ";
    ypos = 6;
    //now getting identifications . . . .!
    gotoxy(xpos+ 21,ypos=6);
    gets(newptr->name);
    gets(newptr->name);
    if(strcmp(newptr->name,"end")==0)
    {
        return;
    }
    else line(2,45,30,' ');
    gotoxy(xpos+28,ypos +=2);
    gets(newptr->family);
    gotoxy(xpos+25,ypos +=2);
    gets(newptr->st_ID);
    gotoxy(xpos+22,ypos +=2);
    gets(newptr->ID_num);
    gotoxy(xpos+23,ypos +=2);
    char gen[20];
    cin>>gen;
    for(int i=0; gen[i]; i++)
        gen[i] = tolower(gen[i]);
    if(strcmp(gen,"male")==0 || strcmp(gen,"mal")==0 || strcmp(gen,"m")==0|| strcmp(gen,"1")==0)
    {
        bstudent_count++;
        newptr->gen = true;
    }
    else if (strcmp(gen,"female")==0 || strcmp(gen,"f")==0|| strcmp(gen,"0")==0)
    {
        newptr->gen = false;
        gstudent_count++;
    }
    gotoxy(strlen("Enter account balance (Riall) : ") + xpos,ypos+=2);
    char bal[15];
    cin>>bal;
    newptr->bal = atoi(bal);
    ///---------------
    strcpy(newptr->user,newptr->st_ID);
    strcpy(newptr->pass,newptr->ID_num);
    if(isuniqe(newptr))
    {
        blink(10,20,2,"Added Successfuly !");
        if(first ==NULL)
            first = last = newptr;
        else
        {
            last->next = newptr;
            last = newptr;
        }
    }
    else
    {
        gotoxy(10,20);
        write("Student ID Existed in the list !!!");
        blink(10,22,4," Adding failed !!!");
    }

    gotoxy(2,47);
    write("Press any key to go back");

}
/// ---------------- ///

void st_list::findst()
{
    char s[20];
    int mood = 1;
    for(;;)
    {
        fmenu(mood);
        int ch = getch();
        if(!ch || ch == 0xe0)
        {
            ch = getch(); // extended keys
            switch(ch)
            {
            case UP:
                system("cls");
                if(--mood == 0) mood = 4;
                fmenu(mood);
                break;
            case DOWN:
                system("cls");
                if(++mood == 5) mood = 1;
                fmenu(mood);
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
                loadbar(10,10,"Quitting!");;
                exit(0);
            }
            case ESC:
                return;
                break;
            case ENTER:
                system("cls");
                border();
                gotoxy(3,47);
                cout<<"Press ESC to go back";
                gotoxy(0,0);
                switch(mood)
                {
                case 1:
                {
                    int y =1 ;
                    bool found = 0;
                    gotoxy(25,2);
                    cout<<"Search by name ";
                    gotoxy(3,7);
                    cout<<"Enter the name : ";
                    gotoxy(3+strlen("Enter the name : "),7);
                    cin>>s;
                    student *curptr = first;
                    int i = 0;
                    while(curptr)
                    {
                        i++;
                        blink(50,7,1,"Searching  ",1);
                        cout<<i*100/(gstudent_count+bstudent_count)<<'%';

                        //pbar(40,6,20,i*100/(gstudent_count+bstudent_count),7);
                        if(strcmp(strlwr(curptr->name),strlwr(s))==0)
                        {
                            gotoxy(2,11+(++y*2));
                            stinfo(curptr);
                            found = true;
                            if(found)
                            {
                                gotoxy(2,11);
                                cout<<"Student ID Number\tGender\tName\tFamily\tID number\tBalance";
                                line(1,12,78);
                            }
                        }
                        curptr =curptr->next;
                    }
                    gotoxy(50,7);
                    write("Finished !");
                    if(!found)
                    {
                        border(3,9,20,5);
                        gotoxy(5,11);
                        write("Not Found . . .!",3);
                    }
                    getch();
                    break;/// end of mood 1
                }//end of case 1
                case 2:
                {
                    int y =1 ;
                    bool found = 0;
                    gotoxy(25,2);
                    cout<<"Search by Last name ";
                    gotoxy(3,7);
                    cout<<"Enter the last name : ";
                    gotoxy(3+strlen("Enter the last name : "),7);
                    cin>>s;
                    student *curptr = first;
                    int i = 0;
                    while(curptr)
                    {
                        i++;
                        blink(50,7,1,"Searching  ",1);
                        cout<<i*100/(gstudent_count+bstudent_count)<<'%';
                        // pbar(40,6,20,i*100/(gstudent_count+bstudent_count),7);
                        if(strcmp(curptr->family,s)==0)
                        {
                            gotoxy(2,11+(++y*2));
                            stinfo(curptr);
                            found = true;
                            if(found)
                            {
                                gotoxy(2,11);
                                cout<<"Student ID Number\tGender\tName\tFamily\tID number\tBalance";
                                line(1,12,78);
                            }
                        }
                        curptr =curptr->next;
                    }
                    gotoxy(50,7);
                    write("Finished !");
                    if(!found)
                    {
                        border(3,9,20,5);
                        gotoxy(5,11);
                        write("Not Found . . .!",3);
                    }
                    getch();
                    break;/// end of mood 2
                }
                case 3:
                {
                    int y =1 ;
                    bool found = 0;
                    gotoxy(25,2);
                    cout<<"Search by ID number ";
                    gotoxy(3,7);
                    cout<<"Enter the ID number : ";
                    gotoxy(3+strlen("Enter the ID number : "),7);
                    cin>>s;
                    student *curptr = first;
                    int i = 0;
                    while(curptr)
                    {
                        i++;
                        blink(50,7,1,"Searching  ",1);
                        cout<<i*100/(gstudent_count+bstudent_count)<<'%';
                        // pbar(56,6,20,i*100/(gstudent_count+bstudent_count),7);
                        if(strcmp(curptr->ID_num,s)==0)
                        {
                            gotoxy(2,11+(++y*2));
                            stinfo(curptr);
                            found = true;
                            if(found)
                            {
                                gotoxy(2,11);
                                cout<<"Student ID Number\tGender\tName\tFamily\tID number\tBalance";
                                line(1,12,78);
                            }
                        }
                        curptr =curptr->next;
                    }
                    gotoxy(50,7);
                    write("Finished !");
                    if(!found)
                    {
                        border(3,9,20,5);
                        gotoxy(5,11);
                        write("Not Found . . .!",3);
                    }
                    getch();
                    break;
                }    ///end of case 3
                case 4:
                {
                    int y =1 ;
                    bool found = 0;
                    gotoxy(25,2);
                    cout<<"Search by Student ID number ";
                    gotoxy(3,7);
                    cout<<"Enter the Student ID number : ";
                    gotoxy(4+strlen("Enter the Student ID number : "),7);
                    cin>>s;
                    student *curptr = first;
                    int i = 0;
                    while(curptr)
                    {
                        i++;
                        blink(50,7,1,"Searching  ",1);
                        cout<<i*100/(gstudent_count+bstudent_count)<<'%';
                        //pbar(54,6,20,i*100/(gstudent_count+bstudent_count),7);
                        if(strcmp(curptr->st_ID,s)==0)
                        {
                            gotoxy(2,11+(++y*2));
                            stinfo(curptr);
                            found = true;
                            if(found)
                            {
                                gotoxy(2,11);
                                cout<<"Student ID Number\tGender\tName\tFamily\tID number\tBalance";
                                line(1,12,78);
                            }
                        }
                        curptr =curptr->next;
                    }
                    gotoxy(50,7);
                    write("Finished !");
                    if(!found)
                    {
                        border(3,9,20,5);
                        gotoxy(5,11);
                        write("Not Found . . .!",3);
                    }
                    getch();
                    break;/// end of mood 4
                }
                }///end of switch mood
                break;//case Enter
            }
        }//end of else
    }//end of for
}
/// --------- student list ----- ////
void st_list::slist() //we want to have edit and delet here! + the list!
{
    this->load_students_data();
    int mood =1,page=1;
    int lpage = (gstudent_count + bstudent_count)/20;
    if((gstudent_count + bstudent_count)%20)
        lpage++;
    int st_per_page ;
    if((gstudent_count + bstudent_count)<21)
        st_per_page = gstudent_count + bstudent_count;
    else
        st_per_page  = 20;//first value for : st_per_page
    kslist(mood,page);
    for(;;)
    {
        int ch = _getch();
        if(!ch || ch == 0xe0)
        {
            ch = _getch(); // extended keys
            switch(ch)
            {
            case UP:
                if(--mood <= 0) mood = st_per_page;
                kslist(mood,page);
                break;
            case DOWN:
                if(++mood > st_per_page) mood = 1;
                kslist(mood,page);
                break;
            case LEFT:
                if(--page < 1) page = lpage;
                if(page < lpage)
                    st_per_page = 20;
                else
                    st_per_page = (gstudent_count + bstudent_count)%20 +1;
                kslist(1,page);
                break;
            case RIGHT:
                if(++page > lpage) page = 1;
                if(page < lpage)
                    st_per_page = 20;
                else
                    st_per_page = (gstudent_count + bstudent_count)%20 +1;
                kslist(1,page);
                break;
            case DELETE:
            {
                student *curptr =first;
                int choice2 = mood-1;
                int ch_page = page ;
                ch_page--;
                ch_page *=20;//20 rows in each page;
                for(; ch_page; ch_page--)
                {
                    curptr = curptr->next;
                }
                while(choice2--)
                {
                    curptr = curptr->next;
                }
                border(2,6+mood,strlen("Do you want to delete  (y/n)? ")+strlen(curptr->name)+4,3);
                gotoxy(3,6+mood +1);
                cout<<" Do you want to delete "<<curptr->name<<" (y/n)?  "<<"\b";
                char ch = getche();
                ch = tolower(ch);
                if(ch =='y')
                {
                    border(2,9+mood,strlen(" Enter admin password : ")+10,3);
                    gotoxy(3,10+mood);
                    write("Enter admin Password : ");
                    if(checkpass(admin.get_pass()))
                    {
                        delst(curptr);
                        blink(3,13+mood,3,"      \b\b\b\b\bDeleted Successfully     ");
                        kslist(1,page);
                    }
                    else
                    {
                        blink(30,10+mood,3,"wrong password");
                    }
                }
                kslist(1,page);
                break;
            }
            } // switch()
        } // if()
        else
        {
            switch(ch)
            {
            case 'q':
            case 'Q':
            {
                std::cout << "Quitting!\n";
                return;
            }
            case ESC:
                return;
                break;
            case ENTER:
            {
                student *curptr =first;
                int ch_page = page ;
                ch_page--;
                ch_page *=20;//20 rows in each page;
                for(; ch_page; ch_page--)
                {
                    curptr = curptr->next;
                }
                int choice = mood-1;
                while(choice--)
                {
                    curptr = curptr->next;
                }
                editst(curptr);
                kslist(mood,page);
                break;
            }
            }
        }
    }
}
/*void st_list::kslist(int mood){
    int i=0,count_st = 0 ;
    system("cls");
    border(0,0,79,3);//first
    border(0,47,79,3);//end
    border(0,3,79,44);//main
    gotoxy(3,1);
    cout<<"Student ID Number\tGender\tName\tFamily\tID number\tBalance";
    gotoxy(2,48);
    cout<<"Press ESC to go back\t, DEL to delete \t& ENTER to Edit";
    student *curptr =first;
    while(curptr){
    gotoxy(3,6+2*(i++));
    stinfo(curptr);
    curptr = curptr->next;
        }
    gotoxy(2,6+2*(mood-1));
    cout<<">";
    gotoxy(0,0);
    gotoxy(2,6+2*(mood-1));

}*/
void st_list::kslist(int mood,int page)
{
    int i=0,count_st = 0 ;
    student *curptr =first;
    system("cls");
    border(0,0,79,3);//first
    border(0,47,79,3);//end
    border(0,3,79,44);//main
    gotoxy(3,1);
    cout<<"Student ID Number\tGender\tName\tFamily\tID number\tBalance";
    if((gstudent_count + bstudent_count)>20)
    {
        gotoxy(1,48);
        cout<<"<< Previose page        |Press ESC to go back|                 Next page >>";
    }
    else
    {
        gotoxy(2,48);
        cout<<"Press ESC to go back, Del to delete & Enter to Edit";
    }
    for(page--; page; page--)
    {
        for(int i=0; i<20; i++)
        {
            curptr = curptr->next;
        }
    }
    int st_per_page =0;
    while(curptr && i<20)
    {
        st_per_page++;
        gotoxy(3,6+2*(i++));
        stinfo(curptr);
        curptr = curptr->next;
    }
    border(1,6+2*((mood%21)-1)-1,77,3,1);
    gotoxy(0,0);
    gotoxy(2,6+2*(mood-1));
    cout<<">";
}
/// ------------ find menu ------------ ////
void fmenu(int m)
{
    system("cls");
    border();
    border(25,2,28,5);
    gotoxy(33,4);
    cout<<" FIND STUDENT ";
    border(22,15,37,11);
    gotoxy(24,17);
    cout<<" 1.Search by name ";
    gotoxy(24,19);
    cout<<" 2.Search by Family name";
    gotoxy(24,21);
    cout<<" 3.Search by ID number";
    gotoxy(24,23);
    cout<<" 4.Search by Student ID number";
    gotoxy(24,17+2*(m-1));
    cout<<">";
    gotoxy(3,47);
    cout<<"Press Esc to go back";
    gotoxy(0,0);

}
/// ........... student info ...............///
void st_list::stinfo(student *curptr)
{
    char st[20];
    if(curptr->gen)
        strcpy(st,"Male");
    else
        strcpy(st,"Female");
    cout<<curptr->st_ID<<"\t\t"<<st<<"\t"<<curptr->name<<"\t"<<curptr->family<<"\t"
        <<curptr->ID_num<<"\t"<<curptr->bal<<endl;
}
void st_list::stinfo(student *curptr,int x,int y)
{
    char st[20];
    if(curptr->gen)
        strcpy(st,"Male");
    else
        strcpy(st,"Female");
    border(x,y,75,7);
    gotoxy(x+1,y+2);
    cout<<"Student ID Number\tGender\tName\tFamily\tID number\tBalance";
    gotoxy(x+1,y+4);
    cout<<curptr->st_ID<<"\t\t"<<st<<"\t"<<curptr->name<<"\t"<<curptr->family<<"\t"
        <<curptr->ID_num<<"\t"<<curptr->bal<<endl;
}
///...............delete Student ..............///
void st_list::delst(student *nextptr)
{
    if(nextptr->gen)///checks boys and girls!
        bstudent_count--;
    else
        gstudent_count--;
    if(nextptr ==first)
    {
        first = first->next;
        delete nextptr;
    }
    else
    {
        student *curptr = first;
        while(curptr->next != nextptr) ///seeking behind nextptr
        {
            curptr = curptr->next;
        }
        if(nextptr ==last)
        {
            last = curptr;
            curptr->next = nextptr->next;
            delete nextptr;
        }
    }
}
void st_list::editst()
{
    clrscr();
    border();
    gotoxy(30,2);
    cout<<"Edit Student";
    gotoxy(0,0);
    gotoxy(2,4);
    cout<<"Enter the Student ID number : ";
    char I[30];
    gotoxy(2+strlen("Enter the Student ID number : "),4);
    cin>>I;
    student *cur = first;
    while(cur)
    {
        if(strcmp(cur->st_ID,I)== 0)
        {
            editst(cur);
            break;
        }

        cur = cur->next;
    }
    if(cur==NULL)
    {
        gotoxy(2,6);
        cout<<"ST ID Number not found!";
        getch();
    }
}
void st_list::editst(student *curptr)
{
    system("cls");
    border();
    gotoxy(0,0);
    gotoxy(30,2);
    cout<<"Edit "<<curptr->name<<"'s info";
    border(2,4,75,7);
    gotoxy(4,6);
    cout<<"Student ID Number\tGender\tName\tFamily\tID number\tBalance";
    gotoxy(2,48);
    cout<<"Press 'B' key to go Back";
    gotoxy(4,8);
    stinfo(curptr);
    gotoxy(3,13);
    cout<<"1.Edit completely";
    gotoxy(3,15);
    cout<<"2.Edit info partly ";
    gotoxy(3,17);
    cout<<"3.Delete";
    /*gotoxy(2,15);
    cout<<"4.See "<<curptr->name<<"'s full info";*/ ///balance ,reserved foods,user,pass
    ///more info should be added later
    gotoxy(4,19);
    cout<<"Enter your choice (1-3) : ";
    ///--------------
    int choice =1;
    char ch = getche();
    ch = tolower(ch);
    if(ch == 'b')
        return;
    else
    {
        choice = ch - '0';
        if(choice >=1 && choice <= 3)
        {
            switch(choice)
            {
            case 1://edit fully
            {
                student *newptr = curptr;
                system("cls");
                border();
                gotoxy(0,0);
                gotoxy(30,2);
                cout<<"Edit "<<curptr->name<<"'s info";
                border(2,3,75,7);
                gotoxy(4,5);
                cout<<"Student ID Number\tGender\tName\tFamily\tID number\tBalance";
                gotoxy(4,7);
                stinfo(curptr);
                int xpos = 3,ypos =12;
                gotoxy(xpos,ypos);
                cout<<"Enter new name : ";
                gotoxy(xpos,ypos +=2);
                cout<<"Enter new family name : ";
                gotoxy(xpos,ypos +=2);
                cout<<"Enter new student ID number: ";
                gotoxy(xpos,ypos +=2);
                cout<<"Enter new  ID number : ";
                gotoxy(xpos,ypos +=2);
                cout<<"Gender (male/female) : ";
                gotoxy(2,45);
                write("Press BackSpace to skip entering new date");
                ypos = 12;
                gotoxy(xpos+ 18,ypos);
                char back = getch();
                if(back =='\b')
                {
                    break;
                }
                cin>>newptr->name;
                gotoxy(xpos+25,ypos +=2);
                cin>>newptr->family;
                gotoxy(xpos+29,ypos +=2);
                cin>>newptr->st_ID;
                gotoxy(xpos+23,ypos +=2);
                cin>>newptr->ID_num;
                gotoxy(xpos+23,ypos +=2);
                char gen[20];
                cin>>gen;
                for(int i=0; gen[i]; i++)
                    gen[i] = tolower(gen[i]);
                if(strcmp(gen,"male")==0 || strcmp(gen,"mal")==0 || strcmp(gen,"m")==0|| strcmp(gen,"1")==0)
                {
                    bstudent_count++;
                }
                else if (strcmp(gen,"female")==0 || strcmp(gen,"f")==0|| strcmp(gen,"0")==0)
                {
                    newptr->gen = false;
                }
                gotoxy(2,47);
                write("Press any key to go back");
                getch();
                editst(curptr);
                break;
            }
            case 2:///edit partly
            {
                student *newptr = curptr;
                gotoxy(4,19);
                cout<<"                            ";
                gotoxy(2,19);
                write("Choose one (1-6) : ");
                int y = 19;
                gotoxy(3,y+=2);
                cout<<"[1].Edit Student ID number";
                gotoxy(3,y+=2);
                cout<<"[2].Change Gender";
                gotoxy(3,y+=2);
                cout<<"[3].Edit name";
                gotoxy(3,y+=2);
                cout<<"[4].Edit family name";
                gotoxy(3,y+=2);
                cout<<"[5].Edit ID number";
                gotoxy(3,y+=2);
                cout<<"[6].Change account balance";
                gotoxy(2+strlen("Choose one (1-6) : "),19);
                char select = getche();
                int s = select - '0';
                if(s>=1 && s<=6)
                {
                    if(s == 1)
                    {
                        border(2,33,50,3);
                        gotoxy(4,34);
                        cout<<"Enter new Student ID number : ";
                        cin>>curptr->st_ID;
                    }
                    if(s == 2)
                    {
                        border(2,33,50,3);
                        gotoxy(4,34);
                        cout<<"Gender (male/female) : ";
                        char gen[20];
                        cin>>gen;
                        for(int i=0; gen[i]; i++)
                            gen[i] = tolower(gen[i]);
                        if(strcmp(gen,"male")==0 || strcmp(gen,"mal")==0 || strcmp(gen,"m")==0|| strcmp(gen,"1")==0)
                        {
                            newptr->gen = true;
                        }
                        else if (strcmp(gen,"female")==0 || strcmp(gen,"f")==0|| strcmp(gen,"0")==0)
                        {
                            newptr->gen = false;
                        }
                    }
                    if(s == 3)
                    {
                        border(2,33,50,3);
                        gotoxy(4,34);
                        cout<<"Enter new name : ";
                        cin>>curptr->name;
                    }
                    if(s == 4)
                    {
                        border(2,33,50,3);
                        gotoxy(4,34);
                        cout<<"Enter new family name : ";
                        cin>>curptr->family;
                    }
                    if(s == 5)
                    {
                        border(2,33,40,3);
                        gotoxy(4,34);
                        cout<<"Enter new ID number : ";
                        cin>>curptr->ID_num;
                    }
                    if(s == 6)
                    {
                        border(2,33,50,3);
                        gotoxy(4,34);
                        cout<<"Enter balance : ";
                        cin>>curptr->bal;
                    }
                    blink(3,37,2,"Done!");
                }
                else
                {
                    editst(curptr);
                }
                editst(curptr);
                break;
            }

            case 3:///delete student
            {
                gotoxy(4,19);
                cout<<"                            ";
                border(2,20,strlen("Do you want to delete  (y/n)? ")+strlen(curptr->name)+5,5);
                gotoxy(4,22);
                cout<<"Do you want to delete "<<curptr->name<<" (y/n)? ";
                char c=getche();
                c = tolower(c);
                if(c=='y')
                {
                    border(2,27,40,5);
                    gotoxy(5,29);
                    write("Enter Admin password : ");
                    if(checkpass(admin.get_pass()))
                    {
                        gotoxy(5,33);
                        write("Deleted !!!");
                        delst(curptr);
                        return;
                    }
                    else
                    {
                        write("\n\n\nWrong Password");
                        cout<<admin.get_pass();
                    }
                    editst(curptr);
                }
                else
                {
                    editst(curptr);
                }
                break;
            }
            }///end of switch
        }///end of if
        else
            blink(10,21,3,"Wrong choice");
    }/// end of else =='b'
}
void st_list::sort()
{
    student *curptr,*nextptr;

    for(curptr = first; curptr->next != NULL; curptr = curptr->next)
    {
        for(nextptr  =first; nextptr->next != NULL; nextptr = nextptr->next)
        {
            if(atoi(nextptr->st_ID)<atoi(curptr->st_ID))
            {
                ///swap time!
                swap(curptr,nextptr);
                cout<<nextptr->st_ID<<"\t"<<curptr->st_ID<<"\n";
            }

        }///end of second for
    }///end of first for
    getch();
}
void st_list::swap(student *curptr,student *nextptr)
{
    if(curptr != nextptr)
    {
        if(curptr == first)
        {
            curptr->next = nextptr->next;
            nextptr->next = curptr;
            first = nextptr;
        }
        else
        {
            curptr->next = nextptr->next;
            nextptr->next = curptr;
        }///else
    }///main if
}
///this func checks uniqeness of one node if it is uniqe returns true other way it returns false!
bool st_list::isuniqe(student *curptr)
{
    int count = 0;
    student *temp = first;
    for(temp = first; temp !=NULL; temp = temp->next)
    {
        if(strcmp(strlwr(temp->st_ID),strlwr(curptr->st_ID)) == 0)
        {
            count++;
            if(count>1)
                return false;
        }

    }
    return true;

}
///checks the whole nodes and deletes ununiqe nodes!
void st_list::isuniqe()
{
    student *curptr = first;
    student *temp;
    while(curptr)
    {
        temp = curptr;
        if(!isuniqe(curptr))
            delst(temp);


        curptr=curptr->next;
    }

}
