#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

using namespace std;
using std::string;

void line(int x,int y,int len,char type);
void vline(int x,int y,int len,char type);
void gotoxy(int x, int y);
void blink(int x,int y,char st[]);
void border()
{
    int i,j;
    gotoxy(0,0);
    cout<<(char)201;
    gotoxy(1,0);
    for(i=1; i<79; i++)
        cout<<(char)205;
    cout<<(char)187;
    for(j=1; j<49; j++)
    {
        gotoxy(0,j);
        cout<<(char)186;
        gotoxy(79,j);
        cout<<(char)186;
    }
    gotoxy(0,49);
    cout<<(char)200;
    gotoxy(1,49);
    for(i=1; i<79; i++)
        cout<<(char)205;
    cout<<(char)188;

}
void border(int x,int y,int col,int r,char t = 2,bool fill = false)
{
    char ruc  ;///right up corner
    char rdc  ;///right down corner
    char luc  ;///left up corner
    char ldc  ;///left down corner
    char h  ;///horizental char
    char v  ;///vertical line
    switch(t)
    {
    case 1:
        ruc = 191;
        rdc = 217;
        luc = 218;
        ldc = 192;
        h = 196;
        v = 179;
        break;
    case 2:
        ruc = 187;
        rdc = 188;
        luc = 201;
        ldc = 200;
        h = 205;
        v=186;
        break;
    default:
        ruc = rdc = luc = ldc = h = v = t;
        break;
    }

    int i,j;
    if(fill == true)
    {
        for(i=x; x<(x+col-1); i++)
            for(j=y; j<(y+r-1); j++)
                cout<<NULL;
    }
    if(col==1)
        for(j=y; j<(y+r); j++)
        {
            gotoxy(x,j);
            cout<<v;
        }
    else if(r==1)
        for(i=x; i<(x+col); i++)
            cout<<h;
    else
    {
        gotoxy(x,y);
        cout<<luc;
        gotoxy(x+1,y);
        for(i=x+1; i<(x+col-1); i++)
            cout<<h;
        cout<<ruc;
        for(j=y+1; j<(y+r-1); j++)
        {
            gotoxy(x,j);
            cout<<v;
            gotoxy(x+col-1,j);
            cout<<v;
        }
        gotoxy(x,y+r-1);
        cout<<ldc;
        gotoxy(x+1,y+r-1);
        for(i=x+1; i<(x+col-1); i++)
            cout<<h;
        cout<<rdc;
    }


}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void pbar(int x,int y,int len,int progress)
{
    border(x-1,y-1,len+2,3);
    static int prog;
    prog = progress;
    if(prog<1)
        border(x-1,y-1,len+3,3);
    gotoxy(x+len/2,y-1);
    cout<<prog<<"%";
    prog =prog*len/(100.0);
    gotoxy(x+prog,y);
    cout<<"|";
    Sleep(30);
    cout<<"\b/";
    Sleep(30);
    cout<<"\b-";
    Sleep(30);
    cout<<"\b\\";
    Sleep(30);
    cout<<"\b|";
    Sleep(30);
    cout<<"\b"<<(char)219;
    Sleep(30);

}
void pbar(int x,int y,int len,int progress,int speed)
{
    int sleep_time;
    switch(speed)
    {
    case 0:
        sleep_time = 1;
        break;
    case 1:
        sleep_time = 10;
        break;
    case 2:
        sleep_time = 20;
        break;
    case 3:
        sleep_time = 30;
        break;
    case 4:
        sleep_time = 40;
        break;
    case 5:
        sleep_time = 50;
        break;
    case 6:
        sleep_time = 60;
        break;
    case 7:
        sleep_time = 70;
        break;
    }
    static int prog;
    border(x-1,y-1,len+2,3);
    gotoxy(x+(len/2)-1,y-1);
    cout<<progress<<"%";
    progress =progress*len/(100.0);
    /*gotoxy(x+prog,y);
    cout<<"|";
    Sleep(sleep_time);
    cout<<"\b/";
    Sleep(sleep_time);
    cout<<"\b-";
    Sleep(sleep_time);
    cout<<"\b\\";
    Sleep(sleep_time);
    cout<<"\b|";
    Sleep(sleep_time);
    cout<<"\b"<<(char)219;
    Sleep(sleep_time);*/
    for(; progress-prog; prog++)
    {
        gotoxy(x+prog,y);
        cout<<(char)219;
    }
    gotoxy(x+progress+1,y);
    Sleep(sleep_time);
}
void pbar(int x,int y,int len)
{
    int i;
    int prog = x;
    int sleep_time = 5;
    for(i=0; i<101; i++)
    {
        gotoxy(prog/len,y);
        prog++;
        cout<<(char)219;
        gotoxy(prog/len +1,y);
        Sleep(sleep_time);
    }
}

void loadbar(int x,int y,char a[20])
{
    int len = 5,i=0;
    gotoxy(x,y);
    cout<<a;
    for(i=0; i<5; i++)
    {
        gotoxy(x+strlen(a)+1,y);
        cout<<(char)219;
        Sleep(20);
        cout<<"\b ";
        Sleep(20);
        cout<<(char)219;
        Sleep(20);
        cout<<"\b ";
        Sleep(20);
        cout<<(char)219;
        Sleep(20);
        cout<<"\b ";
        Sleep(20);
        cout<<(char)219;

        Sleep(20);
        cout<<"\b ";
        Sleep(20);
        cout<<(char)219;
        Sleep(20);
        cout<<"\b ";
        Sleep(20);
    }

}
void blink(int x,int y,char st[])
{
    char clear[strlen(st)];
    strcpy(clear,st);
    for(int i=0; clear[i]; i++)
        clear[i] =' ';
    int i = 1;///blink times
    for(; i!=0; i--)
    {
        gotoxy(x,y);
        cout<<st;
        Sleep(200);
        gotoxy(x,y);
        cout<<clear;
        Sleep(200);
    }
}/// end of func
void blink(int x,int y,int times,char st[],int speed = 4)  ///this func blinks a text!
{
    int wait;
    switch(speed)
    {
    case 0:
        wait = 10;
        break;
    case 1:
        wait = 50;
        break;
    case 3:
        wait = 100;
        break;
    case 4:
        wait = 150;
        break;
    case 5:
        wait = 200;
        break;
    case 6:
        wait = 250;
        break;
    case 7:
        wait = 350;
        break;
    }

    char clear[strlen(st)];
    strcpy(clear,st);
    for(int i=0; clear[i]; i++)
        clear[i] =' ';
    int i;
    if(times !=0)
    {
        i = times;///blink times
        for(; i!=0; i--)
        {
            gotoxy(x,y);
            cout<<st;
            Sleep(wait);
            gotoxy(x,y);
            cout<<clear;
            Sleep(wait);
        }
    }
    else
        for(;;)
        {
            gotoxy(x,y);
            cout<<st;
            Sleep(wait);
            gotoxy(x,y);
            cout<<clear;
            Sleep(200);
            if(kbhit())
                break;
        }

}/// end of func
void write(char *st,int speed = 3,bool style = true)
{
    char ch = 219;
    int write_speed;//wait time
    int wait;
    switch(speed)
    {
    case 1:
        write_speed = 5;
        wait = 100;
        break;
    case 2:
        write_speed = 25;
        wait = 300;
        break;
    case 3:
        write_speed = 150;
        wait = 450;
        break;
    }
    int i=0;
    for(i=0; *(st+i); i++)
    {
        cout<<ch<<'\b';
        Sleep(25);
        cout<<st[i];
    }
    Sleep(350);
}
void tostar(char a[],int len)///length of string which is needed
{
    char c;
    int i =0;
    for(i; i<len && c!='\n'; i++) ///checking if ENTER key is pressed
    {
        c = getche();
        /*if(c=='\b'){
        cout<<" \b*";
        a[i-1] = NULL;
        i--;
        continue;}*/
        if((c>=48 && c<=57)||(c>=65 && c<=90) || (c>=97 && c<=122))///alphabets + numbers
        {
            a[i]=c;
            cout<<"\b*";
        }
    }
}
///gets a * password and checks it with the string you had send to it .returns true if correct and false if incorrect
bool checkpass(char pass[])
{
    char a[15];
    tostar(a,15);
    if(strcmp(a,pass)==0)
        return true;
    else
        return false;
}
char* getpass(int len)
{
    char a[len];
    tostar(a,len);
    return a;
}
///draw a horizental line
void line(int x,int y,int len,char type = 196)
{
    gotoxy(x,y);
    for(int i =x; i<(len+x); i++)
        cout<<type;
}

void vline(int x,int y,int len,char type = 179)
{
    for(int i = y; i<y+len; i++)
    {
        gotoxy(x,i);
        cout<<type;
    }
    gotoxy(x+1,y);
}

///returns false if out char not enterred ,else it returns true
bool smartget(char s[],int len=40,char out = '/')
{
    bool charfound = false;
    int i = 0,exten =0,j=0;;
    char ch,st[len+100];
    for(int i=0; i<len+exten; i++)
    {
        ch = getche();
        if(ch == 8)
        {
            st[i] = '\b';
            cout<<" \b";
        }
        else if(ch == 13)
        {
            st[i] = NULL;
            break;
        }
        else if(ch == out)
        {
            st[i] = NULL;
            charfound = true;
            break;
        }
        else
        {
            st[i] = ch;
        }
    }
    for(i=0; i<len; i++)
    {
        if(st[i] != '\b')
            s[j++] = st[i];
    }

    strcpy(s,st);
    return !charfound;
}
bool cpy(char a[],char b[],int n,int start = 0)
{
    int i ;
    for(i=start; i<(n+start); i++)
        a[i] = b[i];
    a[i] = '\0';
    return true;
}
bool clean(char a[])
{
    int i=strlen(a);
    while(i--)
        a[i] = '\0';
}

void digital_num(int x,int y,int num,char t = 1)
{
    char ruc  ;///right up corner
    char rdc  ;///right down corner
    char luc  ;///left up corner
    char ldc  ;///left down corner
    char h  ;///horizental char
    char v  ;///vertical line
    char r3;///three way joint : -|
    char l3;///three way joint : |-
    switch(t)
    {
    case 1:
        ruc = 191;
        rdc = 217;
        luc = 218;
        ldc = 192;
        h = 196;
        v = 179;
        r3 = 180;
        l3 = 195;
        break;
    case 2:
        ruc = 187;
        rdc = 188;
        luc = 201;
        ldc = 200;
        h = 205;
        v=186;
        r3=185;
        l3=204;
        break;
    default:
        ruc = rdc = luc = ldc = h = v = r3 = l3 = t ;
        break;
    }
    switch(num)
    {
    case 1://number : 1
        vline(x,y,7);
        break;
    case 2://number : 2
        line(x,y,4);
        line(x,y+3,4);
        line(x,y+6,4);
        vline(x,y+3,4);
        vline(x+3,y,4);
        gotoxy(x+3,y);
        cout<<ruc;
        gotoxy(x+3,y+3);
        cout<<rdc;
        gotoxy(x,y+3);
        cout<<luc;
        gotoxy(x,y+6);
        cout<<ldc;
        break;
    case 3:
        line(x,y,4);
        line(x,y+3,4);
        line(x,y+6,4);
        vline(x+3,y,7);
        gotoxy(x+3,y);
        cout<<ruc;
        gotoxy(x+3,y+3);
        cout<<r3;
        gotoxy(x+3,y+6);
        cout<<rdc;
        break;
    case 4:
        line(x,y+3,4);
        vline(x,y,4);
        vline(x+3,y,7);
        gotoxy(x,y+3);
        cout<<ldc;
        gotoxy(x+3,y+3);
        cout<<r3;
        break;
    case 5:
        line(x,y,4);
        line(x,y+3,4);
        line(x,y+6,4);
        vline(x,y,4);
        vline(x+3,y+3,4);
        gotoxy(x,y);
        cout<<luc;
        gotoxy(x,y+3);
        cout<<ldc;
        gotoxy(x+3,y+3);
        cout<<ruc;
        gotoxy(x+3,y+6);
        cout<<rdc;
        break;
    case 6:
        line(x,y,4);
        line(x,y+3,4);
        line(x,y+6,4);
        vline(x,y,7);
        vline(x+3,y+3,4);
        gotoxy(x,y);
        cout<<luc;
        gotoxy(x,y+3);
        cout<<l3;
        gotoxy(x,y+6);
        cout<<ldc;
        gotoxy(x+3,y+3);
        cout<<ruc;
        gotoxy(x+3,y+6);
        cout<<rdc;
        break;
    case 7:
        line(x,y,4);
        vline(x+3,y,7);
        gotoxy(x+3,y);
        cout<<ruc;
        break;
    case 8:
        line(x,y,4);
        line(x,y+3,4);
        line(x,y+6,4);
        vline(x,y,7);
        vline(x+3,y,7);
        gotoxy(x,y);
        cout<<luc;
        gotoxy(x+3,y);
        cout<<ruc;
        gotoxy(x,y+3);
        cout<<l3;
        gotoxy(x+3,y+3);
        cout<<r3;
        gotoxy(x,y+6);
        cout<<ldc;
        gotoxy(x+3,y+6);
        cout<<rdc;
        break;
    case 9:
        line(x,y,4);
        line(x,y+3,4);
        line(x,y+6,4);
        vline(x,y,4);
        vline(x+3,y,7);
        gotoxy(x,y);
        cout<<luc;
        gotoxy(x+3,y);
        cout<<ruc;
        gotoxy(x,y+3);
        cout<<ldc;
        gotoxy(x+3,y+3);
        cout<<r3;
        gotoxy(x+3,y+6);
        cout<<rdc;
        break;
    case 0:
        line(x,y,4);
        line(x,y+6,4);
        vline(x,y,7);
        vline(x+3,y,7);
        gotoxy(x,y);
        cout<<luc;
        gotoxy(x+3,y);
        cout<<ruc;
        gotoxy(x,y+6);
        cout<<ldc;
        gotoxy(x+3,y+6);
        cout<<rdc;
        break;

    }
}
void endprog()
{
    int t =10;
    for(int i=0; i<41; i++)
    {
        vline(i,0,50);
        vline(80-i,0,50);
        Sleep(t);
        vline(i,0,50,' ');
        vline(80-i,0,50,' ');
    }
    for(int j=25; j !=0; j--)
    {
        vline(40,25-j,2*j);
        Sleep(t);
        vline(40,25-j,2*j,' ');
    }
    exit(0);
}
void rounder(int x,int y,int times = 0)///kbhit() if = 0 ,else times
{
    bool flag=true;
    int count =times;
    while(flag)
    {
        if(times >0)
        {
            if(count-- <=0)
                flag = false;
        }
        else if(times == 0)
        {
            if(kbhit())
                flag = false;
        }

        /// ---luc ->left up corner
        gotoxy(x,y);
        cout<<char(218);
        Sleep(100);
        gotoxy(x,y);
        cout<<' ';
        ///---ldc---- ->left down corner
        gotoxy(x,y+1);
        cout<<char(192);
        Sleep(100);
        gotoxy(x,y+1);
        cout<<' ';
        ///---rdc----
        gotoxy(x+1,y+1);
        cout<<char(217);
        Sleep(100);
        gotoxy(x+1,y+1);
        cout<<' ';
        ///----ruc---
        gotoxy(x+1,y);
        cout<<char(191);
        Sleep(100);
        gotoxy(x+1,y);
        cout<<' ';

    }
}
void clrscr()
{
    system("cls");
}
