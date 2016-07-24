#include "MENU.h"
#include <iostream>
//#include <fstream.h>
/// -------function prototypes--------///
void load_operator();
void load_setting();
void save_setting();
void save_operator();
///---------------------///
int main()
{
    message_list a;
    st_list b;
    b.load_students_data();
    a.contact_admin(b.first);
    a.load_messages();

    //  a.show_message(a.first);
    // a.admin_inbox();
    /*    load_setting();
        load_operator();
        stlist.load_students_data();
        dllist.load_meals();
        fdlist.load_food_data();
        main_menu();
        save_operator();
        save_setting();*/
    return 0;
}

///--------SAVE TIME!!!!------------
void save_setting()
{
    ofstream sav("setting.dat");
    colour[5] = ':';
    sav<<colour<<"\n";
    sav<<screensav<<"\n";
    sav<<log_out_time<<"\n";
    sav<<screen_saver_wait_time<<"\n";
    sav.close();
}
/// saving data base
void save_operator()
{
    ofstream sav("admin.dat");
    sav<<admin.get_user()<<"\t";
    sav<<admin.get_pass()<<"\n";
    sav<<foperator.get_user()<<"\t";
    sav<<foperator.get_pass()<<"\n";
    sav.close();///admin save finished
}
///--------END OF SAVE FUNCS -------
///--------- LOAD PART -------------
void load_setting()
{
    ifstream load("setting.dat");
    load>>colour;
    colour[5] = ' ';
    load>>screensav;
    load>>log_out_time;
    load>>screen_saver_wait_time;
    load.close();
    system(colour);
}
void load_operator()
{
    ifstream load("admin.dat");
    char string[30];
    load>>string;
    admin.set_user(string);
    //cout<<admin.get_user()<<endl;
    load>>string;
    admin.set_pass(string);
    //cout<<admin.get_pass()<<endl;
    load>>string;
    foperator.set_user(string);
    //cout<<foperator.get_user()<<endl;
    load>>string;
    foperator.set_pass(string);
    //cout<<foperator.get_pass()<<endl;
    load.close();///admin load finished
    //getch();
}
///--------- END OF LOAD TIME ------
