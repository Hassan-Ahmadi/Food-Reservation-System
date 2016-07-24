bool contact_admin(student *curptr)
{
    char title[28];
    int day,month,year,hour,min,sec;
    getdate(&day,&month,&year);
    gettime(&hour,&min,&sec);
    system("cls");
    border();
    gotoxy(0,0);
    gotoxy(20,2);
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
    //////////////////////////////////////////////////////
    ///main part
    gotoxy(24,10);
    kbhit();
    gets(title);
    char a[54];
    bool stop ;
    ///saving message to the file!!!
    ofstream mes("90168003-1.ms");
    if(!mes)
    {cout<<"Can't access file!";return false;}
    int i=0;
    //mes<<"###"<<st->st_ID<<">>>"<<"\t"<<title<<"\n";
    mes<<st->st_ID<<">>>"<<"\t"<<title<<"\t"<<year<<"."<<month<<"."<<day<<"\t"<<hour<<":"<<min<<":"<<sec<<"\n";
    for(int i=0;i<=10;i++)
    {
    gotoxy(12,(i*2)+14);
    stop = smartget(a,54,'/');
    mes<<a<<"\n";
    if(!stop)
        break;
    }
    mes<<"---"<<"\n";
    ofstream m("c:\\myfolder\\myfile.txt");
    //m<<st->st_ID<<"\t"<<title<<"\t"<<year<<"."<<mon<<"."<<day<<"\t"<<hour<<":"<<min<<":"<<sec;
    m<<title<<"\t"<<year<<"."<<month<<"."<<day<<"\t"<<hour<<":"<<min<<":"<<sec<<"\n";
    blink(65-strlen("Sending Message . . . "),6,4,"Sending Message . . . ");
    gotoxy(65-strlen("Sending Message . . . "),6);
    cout<<"                      ";
    gotoxy(65-strlen("Sending Message . . . "),6);
    write("Message Sent!",3);
    /*}
    else if(c == 'q')
    {
        return false;
    }*/
    ///main part ends!
    //////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////
    gotoxy(2,47);
    cout<<"Press any key to go back";
    return true;
}
bool admin_inbox()
{
    char a[100],temp[10],title[40],id[20],trash;
    int i=0;
    system("cls");
    border();
    ifstream mes("messagelist.dat");
    struct tm *t;
    while(!mes.eof())
    {
        mes>>id;
        mes>>temp;
        mes>>title;
        ///date
        mess>>t->tm_year;
        mess>>trash;
        mess>>t->tm_mon;
        mess>>trash;
        mess>>t->tm_mday;
        ///time
        mess>>t->tm_hour;
        mess>>trash;
        mess>>t.tm_min;
        mess>>trash;
        mess>>t.tm_sec;
    }
}
char* messagename(student *curptr)
{
    char c;
    char name[100];
    char messageloc[100];
    int day,month,year,hour,min,sec;
    getdate(&day,&month,&year);
    gettime(&hour,&min,&sec);
    bool end = false;
    for(int i=0;!end;i++)
    {
    c = year%10 + '0';
    year/=10;
    if(year <1)
    end = true;
    name[i] = c;}
    cout<<name;
    strcat(name,st->st_ID);
    strcat(name,"-");
    strcat(name,".mss");
    strcpy(messageloc,name);
    return messageloc;
}
