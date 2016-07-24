#include <string.h>
//#include <fstream.h>
#include <string.h>
#include "student.h"
#include <windows.h>
/*** key values ***/
#define UP           0x48
#define DOWN         0x50
#define ESC          0x1B
#define ENTER        0x0D
#define HOME         0x47
#define END          0x4f
#define PAGE_UP      0x49
#define PAGE_DOWN    0x51
#define LEFT         0x4B
#define RIGHT        0x4D
#define INSERT       0x52
#define DELETE       0x53

///global variable
int day_count=0;
int meal_count=0;
struct tm *sys_time;
///
class daily_meal;
class daily_list;
int food_count = 0;
///global OBJECTS :
student *s;
///
void getdate(int *day,int *mon,int *year)
{
    time_t rawtime;
    struct tm *timeinfo2;
    time ( &rawtime );
    timeinfo2 = localtime ( &rawtime );
    *year = (timeinfo2->tm_year + 1900);
    *mon = timeinfo2->tm_mon;
    *day = timeinfo2->tm_mday;

}
void gettime(int *hour,int *min,int *sec)
{
    time_t rawtime;
    struct tm *timeinfo2;
    time ( &rawtime );
    timeinfo2 = localtime ( &rawtime );
    *hour = timeinfo2->tm_hour;
    *min = timeinfo2->tm_min;
    *sec = timeinfo2->tm_sec;
}
class food
{
public :
    char name[20];
    int price;
    food *next;
    friend class food_list;
    friend class daily_list;
    char* get_food_name()
    {
        return name;
    }
    int get_food_price()
    {
        return  price;
    }
};

class food_list
{
    food *first;
    food *last;
public:
    food_list()
    {
        first = last = NULL;
    }
    ~food_list()
    {
        food *curptr = first;
        food *temp;
        while(curptr)
        {
            temp = curptr;
            curptr = curptr->next;
            delete temp;
        }
    }
    food* choose_food(int num)
    {
        food *curptr = first;
        while(--num)
        {
            curptr = curptr->next;
        }
        return curptr;
    }

    void del_all()
    {
        food *curptr = first;
        food *temp;
        while(curptr)
        {
            temp = curptr;
            curptr = curptr->next;
            delete temp;
        }
    }
    void addfood();
    void addfood(food *curptr);
    void delfood();
    void delfood(food *curptr);
    void foodinfo(food *curptr);
    void displaylist();
    void displaylist(int x,int y);
    void editfood();
    food* tofirst(food *curptr)
    {
        curptr= first;
        return curptr;
    }
    void save_food_data();
    void load_food_data();
    void isuniqe();
    bool isuniqe(food *curptr);
    friend class daily_list;
    friend class daily_meal;
};


class daily_meal:public food
{
    bool res;///reservation state
    //date:
    int day;
    int mon;
    int year;
    int meal;/// meal = 0 -> lunch1 ,1 -> lunch2 ,2->dinner 1,3 -> dinner2 ///
    daily_meal *next;
    friend class daily_list;
    //friend class food_list;
};
class  daily_list
{
    daily_meal *head;
    daily_meal *end;
public:
    daily_list()
    {
        head = end = NULL;
    }
    ~daily_list()
    {
        daily_meal *curptr = head;
        daily_meal *temp;
        while(curptr)
        {
            temp = curptr;
            curptr = curptr->next;
            delete temp;
        }
    }

    void del_all()
    {
        daily_meal *curptr = head;
        daily_meal *temp;
        while(curptr)
        {
            temp = curptr;
            curptr = curptr->next;
            delete temp;
        }
    }
    void delmeal(daily_meal *curptr);
    void addmeal();
    bool addmeal(int i);///randomly sets meal for i days
    void editmeal();
    void list();
    void reslist(student *stptr);
    void sub_reslist(int row,int page);
    void mealinfo(daily_meal *curptr);
    void stmealinfo(daily_meal *curptr);
    void deletemeal();
    void load_meals();
    void save_meals();
    bool save_reservation(student *stptr);
    bool load_reservation(student *stptr);
    bool isuniqe(daily_meal *curptr);
    void isuniqe();
};

///-----------food part-----------------
void food_list::save_food_data()
{
    ofstream sav("food_menu.dat");
    food *curptr = first;
    while(curptr)
    {
        sav<<curptr->name<<"\t";
        sav<<curptr->price<<"\n";
        curptr = curptr->next;
    }
    sav<<"---";
    sav.close();
}
void daily_list::save_meals()
{
    ofstream sav("restaurant.dat");
    daily_meal *curptr = head;
//    char meal_name[10];
    while(curptr)
    {
        sav<<curptr->year<<".";
        sav<<curptr->mon<<".";
        sav<<curptr->day<<"\t";
        sav<<curptr->meal<<"\t";
        sav<<curptr->name<<"\t";
        sav<<curptr->price<<"\n";
        curptr = curptr->next;
    }
    sav<<"0";
    sav.close();
}
void food_list::load_food_data()
{

    ifstream load("food_menu.dat");
    bool flag = true;
    while(flag)
    {
        food *newptr = new food;
        newptr->next = NULL;
        if(first ==NULL)
            first = last = newptr;
        else
        {
            last->next = newptr;
            last = newptr;
        }
        load>>newptr->name;
        if(strcmp(newptr->name,"---")== 0)
        {
            flag = false;
        }
        load>>newptr->price;
        newptr = newptr->next;
        food_count++;
    }
    if(!flag)
    {
        food *curptr = first,*nextptr = first;
        while(nextptr)
        {
            if(strcmp("---",nextptr->name)==0)
            {
                food_count--;
                if(nextptr ==first)
                {
                    first = first->next;
                    delete nextptr;
                    break;
                }
                else
                {
                    if(nextptr ==last)
                        last = curptr;
                    curptr->next = nextptr->next;
                    delete nextptr;
                    break;
                }
            }
            else
            {
                curptr = nextptr;
                nextptr = nextptr->next;
            }
        }
    }
    load.close();
    isuniqe();
}
void daily_list::load_meals()
{
    this->del_all();
    ifstream load("restaurant.dat");
    bool flag = true;
    char tr;//trash char
    while(flag)
    {
        daily_meal *newptr = new daily_meal;
        newptr->next = NULL;
        if(head ==NULL)
            head = end = newptr;
        else
        {
            end->next = newptr;
            end = newptr;
        }
        load>>newptr->year;
        if(newptr->year== 0)
        {
            flag = false;
        }
        load>>tr>>newptr->mon;
        load>>tr>>newptr->day;
        load>>newptr->meal;
        load>>newptr->name;
        load>>newptr->price;
        newptr = newptr->next;
        meal_count++;
    }
    if(!flag)
    {
        daily_meal *curptr = head,*nextptr = head;
        while(nextptr)
        {
            if(nextptr->year==0)
            {
                meal_count--;
                if(nextptr ==head)
                {
                    head = head->next;
                    delete nextptr;
                    break;
                }
                else
                {
                    if(nextptr ==end)
                        end = curptr;
                    curptr->next = nextptr->next;
                    delete nextptr;
                    break;
                }
            }
            else
            {
                curptr = nextptr;
                nextptr = nextptr->next;
            }
        }
    }
    load.close();
}
///-----------------------------
void food_list::addfood()
{
    system("cls");
    food *newptr = new food;
    if(!newptr)
    {
        cout<<"\t\t\t\tAllocation ERROR!\n";
        getch();
    }
    newptr->next = NULL;
    ///////////////////////////////
    border();
    gotoxy(0,0);
    gotoxy(30,2);
    cout<<"ADD NEW MEAL";
    gotoxy(2,4);
    cout<<"Enter food name : ";
    cin>>newptr->name;
    gotoxy(2,6);
    cout<<"Enter Price : ";
    cin>>newptr->price;
    food_count++;
    if(first ==NULL)
        first = last = newptr;
    else
    {
        last->next = newptr;
        last = newptr;
    }
    blink(20,10,3,"Meal added successfuly");
    gotoxy(2,47);
    write("Press any key to go back");
    gotoxy(0,0);
}
void food_list::addfood(food *newptr)
{
    newptr->next = NULL;
    if(first ==NULL)
        first = last = newptr;
    else
    {
        last->next = newptr;
        last = newptr;
    }
}
void food_list::delfood()
{
    char name[15];
    clrscr();
    border();
    gotoxy(30,2);
    cout<<"DELETE FOOD";
    gotoxy(0,0);
    gotoxy(2,4);
    cout<<"Enter the name of the FOOD : ";
    cin>>name;
    food *curptr = first;
    while(curptr)
    {
        if(strcmp(strlwr(name),strlwr(curptr->name))==0)
        {
            gotoxy(2,6);
            foodinfo(curptr);
            food_count--;
            gotoxy(2,8);
            cout<<"Successfully Deleted . . . . ";
            delfood(curptr);
            break;
        }
        curptr=curptr->next;
    }
    if(!curptr)
    {
        gotoxy(2,6);
        cout<<"There is no food with the name '"<<name<<"'!";
    }
    getch();
}
void food_list::delfood(food *nextptr)
{
    if(nextptr == first)
    {
        first = first->next;
        delete nextptr;
    }
    else
    {
        food *curptr = first;
        while(curptr->next != nextptr) ///seeking behind nextptr
        {
            curptr = curptr->next;
        }
        if(nextptr == last)
        {
            last = curptr;
            curptr->next = nextptr->next;
            delete nextptr;
        }
    }
    food_count--;
}
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
void food_list::displaylist()
{
    int x = 2,pos=5,i=1;
    system("cls");
    border(0,0,80,3);
    gotoxy(0,0);
    gotoxy(30,1);
    cout<<"LIST OF MEALS";
    border(0,3,80,47);
    gotoxy(2,5);
    cout<<"### FOOD"<<"\t\tPRICE";
    gotoxy(0,0);
    food *curptr =first;
    while(curptr)
    {
        gotoxy(x,pos+=2);
        if(pos>43)
        {
            pos = 7;
            x= 35;
            vline(30,5,40);
            gotoxy(35,5);
            cout<<"### FOOD"<<"\t\tPRICE";
            gotoxy(x,pos);
        }
        printf("%.3d ",i++);
        foodinfo(curptr);
        curptr = curptr->next;
    }
    line(2,45,76);
    gotoxy(2,47);
    write("Press any key to go back");
    gotoxy(0,0);
    getch();

}
void food_list::displaylist(int X,int Y)
{
    int x = 2+X,pos=5+Y,i=1;
    gotoxy(x,pos);
    cout<<"### FOOD"<<"\t\tPRICE";
    food *ptr =first;
    while(ptr)
    {
        gotoxy(x,pos+=2);
        if(pos>43)
        {
            pos = 7+Y;
            x= 35+X;
            vline(30+X,5+Y,40-Y);
            gotoxy(35+X,5+Y);
            cout<<"### FOOD"<<"\t\tPRICE";
            gotoxy(x,pos);
        }
        printf("%.3d ",i++);
        foodinfo(ptr);
        ptr = ptr->next;
    }
}
///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////
void food_list::editfood()
{
    clrscr();
    char no[15];
    border();
    gotoxy(0,0);
    gotoxy(30,2);
    cout<<"EDIT MEAL";
    gotoxy(2,5);
    cout<<"Enter the NAME of the FOOD to edit : ";
    cin>>no;
    food *cptr = first;
    bool found = false;
    char test[30];
    while(cptr)
    {
        if(strcmp(no,cptr->name)==0)
        {
            found = true;
            cout<<"\nPerivious food info . . .\n";
            foodinfo(cptr);
            cout<<"\nEnter new name : ";
            cin>>cptr->name;
            cout<<"\nEnter new price :";
            cin>>test;
            cptr->price = atoi(test);
        }
        else
            cptr = cptr->next;

        break;//for while
    }
    if(!found)
        cout<<"\nNAME '"<<no<<"'NOT FOUND!";
}
////////////////////////////////////////////|
////////////////////////////////////////////|
////////////////////////////////////////////|
void food_list::foodinfo(food *curptr)
{
    cout<<curptr->name;
    if(strlen(curptr->name)>6)
        cout<<"\t"<<curptr->price<<endl;
    else
        cout<<"\t\t"<<curptr->price<<endl;
}
///---------------reserving part -------------------////

void daily_list::addmeal()
{
    daily_meal *newptr = new daily_meal;
    if(!newptr)
    {
        cout<<"Allocation ERROR!\n";
        getch();
        return;
    }
    newptr->next=NULL;
    if(head==NULL)
        head = end = newptr;
    else
    {
        end->next = newptr;
        end = newptr;
    }
    food_list a;
    food *curptr;
    a.load_food_data();
//    int pos = 7 ;/// y start postion
    system("cls");
    border();
    gotoxy(0,0);
    gotoxy(30,2);
    cout<<"Add New Meal";
    char meal_name[20];
    switch(meal_count%4)
    {
    case 0:
        strcpy(meal_name,"Lunch 1");
        newptr->meal = 0;
        break;
    case 1:
        strcpy(meal_name,"Lunch 2");
        newptr->meal = 1;
        break;
    case 2:
        strcpy(meal_name,"Dinner 1");
        newptr->meal = 2;
        break;
    case 3:
        strcpy(meal_name,"Dinner 2");
        newptr->meal = 3;
        break;
    }
    daily_meal *loop = head;
    if(head ==NULL)
        getdate(&newptr->day,&newptr->mon,&newptr->year);
    else
    {
        while(loop->next !=end)
        {
            loop = loop->next;
        }
        newptr->year = loop->year;
        newptr->mon =   loop->mon;
        newptr->day = loop->day;
    }
    ++meal_count;
    if(loop->meal == 3)
    {
        newptr->day++;
    }
    if(newptr->mon<7)
        if(newptr->day>=31)
        {
            newptr->day -= 31;
            newptr->mon += 1;
        }
        else if(newptr->day>=30)
        {
            newptr->day -= 30;
            newptr->mon += 1;
        }
    if(newptr->mon>12)///if true means it has more than 12 monthes and should be subtracted
    {
        newptr->mon -=12;
        newptr->year +=1;
    }
    /// meal spesification------------///
    gotoxy(2,4);
    cout<<"Meal : "<<meal_name<<"\t"<<"Date : "<<newptr->year<<"."<<newptr->mon<<"."<<newptr->day;
    ///giving food list to be choosed
    line(2,45,74);
    ///------choose meal ----------------///
    gotoxy(2,6);
    cout<<"Choose food from menu (number) : ";
    ///giving food list to be choosed
    a.displaylist(0,3);
    gotoxy(2,47);
    cout<<"Press any key to go back";
    ///-------------------------------
    char ans[5];
    gotoxy(2 + strlen("Choose food from menu (number) : "),6);
    cin>>ans;
    int num = atoi(ans);
    ///now choosed food should be added to the list!
    curptr = a.choose_food(num);
    strcpy(newptr->name , curptr->name);
    newptr->price = curptr->price;
    system("cls");
    border();
    gotoxy(30,2);
    cout<<"Add New Meal";
    //gotoxy(2,4);
    //cout<<"Meal : "<<meal_name<<"\t"<<"Date : "<<newptr->year<<"."<<newptr->mon<<"."<<newptr->day;
    border(2,4,76,5);
    gotoxy(4,6);
    mealinfo(newptr);
    gotoxy(0,0);
    getch();
}

void daily_list::list()
{
    daily_meal *c;
    c = head;
    int i=1;
    system("cls");
    border();
    gotoxy(5,1);
    cout<<"Date\tMeal time\tFood\t\tPrice";
    gotoxy(0,0);
    line(1,2,78);
    while(c )
    {
        gotoxy(5,2+(i++*2));
        mealinfo(c);
        c = c->next;
        if(i%4==0)
        {
            line(2,2+(i*2+1),76);
        }
    }
    line(1,47,78);
    gotoxy(1,48);
    cout<<"<- Previous page        Press any key to go back                  Next Page ->";
    gotoxy(0,0);
    getch();
}
void daily_list::reslist(student *stptr)
{
    s = stptr;
    //load_reservation(stptr);
    daily_meal *curptr;
    curptr = head;
///variables:
    int row = 1;
//    int i=1;
    int page =1;
    int last_page = meal_count/20;
    if(meal_count%20!=0)
        last_page += 1;
    int meals_per_page ;
    if(meal_count <= 20)
        meals_per_page = meal_count;
    else
        meals_per_page = 20;
///getting keys from keyboard
    sub_reslist(row,page);
    for(;;)
    {
        int ch = _getch();
        if(!ch || ch == 0xe0)
        {
            ch = _getch(); // extended keys
// std::cout << std::hex << ch << '\t';
            switch(ch)
            {
            case UP:
                if(--row <= 0) row = meals_per_page;
                sub_reslist(row,page);
                break;
            case DOWN:
                if(++row > meals_per_page) row = 1;
                sub_reslist(row,page);
                break;
            case LEFT://next page
                if(--page < 1) page = last_page;
                if(page < last_page)
                    meals_per_page = 20;
                else
                    meals_per_page = meal_count%20 +1;
                sub_reslist(1,page);
                break;
            case RIGHT://previouse page
                if(++page > last_page) page = 1;
                if(page < last_page)
                    meals_per_page = 20;
                else
                    meals_per_page = meal_count%20 +1;
                sub_reslist(1,page);
                break;
            case DELETE:
            {
                daily_meal *curptr =head;
                int choice2 = row-1;
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
                ///now we are on the right node!
                if(((sys_time->tm_year - curptr->year)*365 + (sys_time->tm_mon-curptr->mon) *30 + (sys_time->tm_mday - curptr->day))<-2)//48 hours before !
                {
                    stptr->bal += curptr->price;//giving back money!
                    curptr->res = false;
                }
                else
                    cout<<"Can't change! Out of date !!!";
                Sleep(800);
                sub_reslist(row,page);
                break;
            }
            } // switch()
        } // if()
        else
        {
            switch(ch)
            {
            case ESC:
                //saving func is here!!!
                save_reservation(stptr);
                return;
                break;
            case ENTER://reservaing key
            {
                daily_meal *curptr =head;
                int choice2 = row-1;
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
                ///now we are on the right node!
                stptr->bal -= curptr->price;//Getting money!
                curptr->res = true;
                sub_reslist(row,page);
                break;
            }
            }
        }
    } // for(;;)
    getch();
}
void daily_list::sub_reslist(int row,int page)
{
    gettime(&sys_time->tm_hour,&sys_time->tm_min,&sys_time->tm_sec);
    getdate(&sys_time->tm_mday,&sys_time->tm_mon,&sys_time->tm_year);
    daily_meal *curptr = head;
//	int count=0;
    int i=1;
    int last_page = meal_count/20;
    if(meal_count%20!=0)
        last_page += 1;
    int meals_per_page ;
    if(meal_count <= 20)
        meals_per_page = meal_count;
    else
        meals_per_page = 20;

    system("cls");
    border();
    /******************  header  *************************************/
    gotoxy(5,1);
    cout<<"Date\tMeal time\tFood\t\tPrice\tReservation";
    gotoxy(0,0);
    line(1,2,78);

    /**                     end of header                             */
    /**                                footer                        */
    line(1,47,78);
    if((meal_count)>20)
    {
        gotoxy(1,48);
        cout<<"<< Page ";
        printf("%.2d",(page-1 == 0 ? last_page:page-1));
        cout<<"  |Press ESC to go back|  "<<"Page : "<<page<<"  Balance : "<<s->bal<<" R    Page ";
        printf("%.2d",(page+1 > last_page ? 1:page+1));
        cout<<" >>";
    }
    else
    {
        gotoxy(2,48);
        cout<<"Press ESC to go back, Del to Delete Reservation & Enter to Reserve";
    }

    /***************************************************************************////end of footer
    for(page--; page; page--)
    {
        for(int i=0; i<20; i++)
        {
            curptr = curptr->next;
        }
    }
//    int st_per_page =0;
    while(curptr && i<=20)
    {
        meals_per_page++;
        gotoxy(3,4+2*(i++));
        stmealinfo(curptr);
        if(i%4==0) line(1,4+2*(i)+1,78);
        curptr = curptr->next;
    }
    border(1,5+2*((row)-1),78,3,1);
    gotoxy(0,0);
}
bool daily_list::addmeal(int n)
{
    int i,num,y=5;
    srand(n);///setting rand() seed
    for(i=0; i<n; i++)
    {
        daily_meal *newptr = new daily_meal;
        if(!newptr)
        {
            cout<<"\t\t\t\tAllocation ERROR!\n";
            getch();
            return false;
        }

        newptr->next = NULL;
        border();
        gotoxy(0,0);
        gotoxy(30,2);
        cout<<"Add New Meal";
        char meal_name[20];
        switch(meal_count%4)
        {
        case 0:
        {
            strcpy(meal_name,"Lunch 1");
            newptr->meal = 0;
            break;
        }
        case 1:
        {
            strcpy(meal_name,"Lunch 2");
            newptr->meal = 1;
            break;
        }
        case 2:
        {
            strcpy(meal_name,"Dinner 1");
            newptr->meal = 2;
            break;
        }
        case 3:
        {
            strcpy(meal_name,"Dinner 2");
            newptr->meal = 3;
            break;
        }
        }
        getdate(&newptr->day,&newptr->mon,&newptr->year);
        if(newptr->mon<7)
        {
            if((newptr->day += day_count)>=31)
                newptr->day -= 31;
            newptr->mon += 1;
        }
        else
        {
            if((newptr->day += day_count)>=30)
                newptr->day -= 30;
            newptr->mon += 1;
        }
        if(newptr->mon>12)///if true means it has more than 12 monthes and should be subtracted
        {
            newptr->mon -=12;
            newptr->year +=1;
        }
        gotoxy(2,47);
        cout<<"Press any key to go back";
        ///now choosed food should be added to the list!
        cout<<"Point 1";
        if(head ==NULL)
            head = end= newptr;
        else
        {
            end->next = newptr;
            end = newptr;
        }
        food *curptr;
        food_list fd;
        cout<<"point 2";
        num = 1;//rand()%10 +2;///except 10 i should place : total food count!
        cout<<"point 2.5";
        curptr = fd.choose_food(num);
        cout<<"point 3";
        strcpy(newptr->name , curptr->name);
        newptr->price = curptr->price;
        if(++meal_count % 4 ==0)
        {
            day_count++;
        }
        gotoxy(2,y+2);
        mealinfo(newptr);
    }
    cout<<"point 4";
    gotoxy(5,6);
    cout<<n;
    write(" Meal(s) set successfuly!");
    cout<<"\n";
    getch();
    return true;
}

void daily_list::mealinfo(daily_meal *curptr)
{
    char meal_name[20];
    switch(curptr->meal)
    {
    case 0:
        strcpy(meal_name,"Lunch 1");
        break;
    case 1:
        strcpy(meal_name,"Lunch 2");
        break;
    case 2:
        strcpy(meal_name,"Dinner 1");
        break;
    case 3:
        strcpy(meal_name,"Dinner 2");
        break;
    }
    cout<<curptr->year<<"."<<curptr->mon<<"."<<curptr->day<<"\t"
        <<meal_name<<" \t"<<curptr->name;
    if(strlen(curptr->name)>6)
        cout<<"\t";
    else
        cout<<"\t\t";
    cout<<curptr->price;
}
void daily_list::stmealinfo(daily_meal *curptr)
{
    char meal_name[20];
    switch(curptr->meal)
    {
    case 0:
        strcpy(meal_name,"Lunch 1");
        break;
    case 1:
        strcpy(meal_name,"Lunch 2");
        break;
    case 2:
        strcpy(meal_name,"Dinner 1");
        break;
    case 3:
        strcpy(meal_name,"Dinner 2");
        break;
    }
    cout<<curptr->year<<"."<<curptr->mon<<"."<<curptr->day<<"\t"
        <<meal_name<<" \t"<<curptr->name;
    if(strlen(curptr->name)>6)
        cout<<"\t";
    else
        cout<<"\t\t";
    cout<<curptr->price<<"\t";
    if(curptr->res==true)
        cout<<"reserved";
    else
        cout<<"--------";
}
bool daily_list::save_reservation(student *stptr)
{
    char save_address[60];
    strcpy(save_address,"restaurant/");
    strcat(save_address,stptr->st_ID);
    strcat(save_address,".dat");
    ofstream sav(save_address);
    if(!sav)	return false;
    else
    {
        daily_meal *curptr = head;
        while(curptr)
        {
            if(curptr->res == true)
            {
                sav<<curptr->year<<".";
                sav<<curptr->mon<<".";
                sav<<curptr->day<<"\t";
                sav<<curptr->meal<<"\t";//lunch , . . .  , dinner
                sav<<curptr->name<<"\t";
                sav<<curptr->price<<"\n";
            }
            curptr = curptr->next;
        }
        sav<<0;///my own eof !!!
        sav.close();
        return true;
    }
}
bool daily_list::load_reservation(student *stptr)
{
//    daily_list *lptr;
    daily_meal *dptr=head;
    while(dptr)
    {
        dptr->res = false;
        dptr=dptr->next;
    }
    char load_address[60];
    strcpy(load_address,"restaurant/");
    strcat(load_address,stptr->st_ID);
    strcat(load_address,".dat");
    ifstream load(load_address);
    if(!load)	return false;
    else
    {
        daily_meal *curptr = new daily_meal;
        bool flag = true;
        char tr;//trash char
        while(flag)
        {
            load>>curptr->year;
            if(curptr->year== 0)
            {
                flag = false;
            }
            cout<<'\n'<<curptr->year;
            load>>tr>>curptr->mon;
            cout<<curptr->mon;
            load>>tr>>curptr->day;
            cout<<curptr->day;
            load>>curptr->meal;
            cout<<curptr->meal;
            load>>curptr->name;
            cout<<curptr->name<<"\t";
            load>>curptr->price;
            cout<<curptr->price;
            ///now we should mark the res part of aproprite node!
            daily_meal *ptr = head;
            cout<<"OUter\n";
            Sleep(200);
//                    int j = 0;
            while(ptr)
            {
                if(curptr->year == ptr->year)
                {
                    if(curptr->mon == ptr->mon)
                    {
                        if(curptr->day == ptr->day)
                        {
                            if(curptr->meal==ptr->meal)
                            {
                                ptr->res = true;
                                stmealinfo(ptr);
                                cout<<"\n";
                                break;
                            }
                        }
                    }
                }

                ptr=ptr->next;
                mealinfo(ptr);
                Sleep(10);
            }//end of inner while
        }//end of while
        load.close();
        getche();
        return true;
    }
}
void food_list::isuniqe()
{
    food *curptr = first;
    food *temp;
    while(curptr)
    {
        temp = curptr;
        if(!isuniqe(curptr))
            delfood(temp);
        curptr=curptr->next;
    }
    cout<<'\a';
}
bool food_list::isuniqe(food *curptr)
{
    int count = 0;
    food *temp = first;
    for(temp = first; temp !=NULL; temp = temp->next)
    {
        if(strcmp(strlwr(temp->name),strlwr(curptr->name)) == 0)
        {
            count++;
            if(count>1)
                return false;
        }

    }
    return true;
}

void daily_list::isuniqe()
{
    daily_meal *curptr = head;
    daily_meal *temp;
    while(curptr)
    {
        temp = curptr;
        if(!isuniqe(curptr))
            delmeal(temp);
        curptr=curptr->next;
    }
    cout<<'\a';
}
bool daily_list::isuniqe(daily_meal *curptr)
{
    int count = 0;
    daily_meal *temp = head;
    for(temp = head; temp !=NULL; temp = temp->next)
    {
        if(temp->year == curptr->year)
        {
            if(temp->mon == curptr->mon)
            {
                if(temp->day == curptr->day)
                {
                    if(temp->meal == temp->meal)
                    {
                        count++;
                        if(count>1)
                            return false;
                    }
                }
            }
        }

    }
    return true;
}
void daily_list::delmeal(daily_meal *curptr)
{
    meal_count--;
    if(curptr ==head)
    {
        head = head->next;
        delete curptr;
    }
    else
    {
        daily_meal *temp = head;
        while(temp->next != curptr) ///seeking behind nextptr
        {
            temp = temp->next;
        }
        if(curptr ==end)
        {
            end = temp;
            temp->next = curptr->next;
            delete curptr;
        }
    }
}
