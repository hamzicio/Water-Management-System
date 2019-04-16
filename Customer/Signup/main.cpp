
#include <iostream>
#include<stdio.h>
#include<windows.h>
#include<mysql.h>
#include<cstring>
#include<ctype.h>
#include"md5.h"
#include<time.h>


using namespace std;

class DataBase

{

private:

    int check;
    unsigned long clientflag;
    const char* db;
    const char* host;
    const char* password;
    unsigned int port;
    int qstate;
    const char* user;
    const char* socket;
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

public:

    DataBase(unsigned long b, const char* c,const char* d,const char* e,unsigned int f,int g=0,const char* h=NULL,const char* i=NULL)

    :clientflag(b),db(c),host(d),password(e),port(f),qstate(g),user(h),socket(i)
    {
        connect();

    }


    void connect()
    {


        conn=mysql_init(0);

        conn=mysql_real_connect(conn,host,user,password,db,port,socket,clientflag);

        if(conn)
        {
            check=1;
        }
        else
        {

            check=0;
        }


    }

    void display()
    {

        if(check==1)
        {
            cout<<"Welcome to the Customer Relationship management Software "<<endl;

        }
        else
        {

            cout<<"Sorry! Connection failed "<<endl;
        }
    }

    MYSQL* getconn()
    {
        return conn;
    }


    ~DataBase()
    {

//        delete db;
//        delete host;
//        delete password;
//        delete user;
//        delete socket;
    }

};


class Signup {
    DataBase d;
    string username;
    string password;
    string retypepass;
    string email;
    string securityquestion;
    string date;
    string contact;
    string address;
    string name;
    string deposit;

protected:
    int id_signup;
public:

    Signup(unsigned long b, const char* c,const char* d,const char* e,unsigned int f,int g=0,const char* h=NULL,const char* i=NULL):d(b,c,d,e,f,g,h,i)

    {
        Input();

    }

    void Input()
    {

        cout<<"------------------  SignUp Feasiblity ----------- "<<endl;

        fflush(stdin);

        cout<<"Enter your name : ";

        cin.clear();
        cin.sync();

        getline(cin,name);
        fflush(stdin);

        string newest_query;
        int qstate;
        MYSQL_RES *res;

        MYSQL *conn=d.getconn();

        unsigned long long variable;
        bool condition = false;
        do{

        cout<<endl<<"Enter your username :";

cin.sync();
        getline(cin,username);
cin.sync();
        fflush(stdin);

            newest_query="SELECT * FROM customers WHERE username='"+username+"'";

            const char *q_new=newest_query.c_str();

            qstate=mysql_query(d.getconn(), q_new);

            if(!qstate){
                res=mysql_store_result(conn);

                variable=mysql_num_rows(res);

                if(variable!=0){
                    condition=false;
                }else{
                    condition=true;
                }


            }


        }while(condition==false);

        do
        {

            cout<<"Enter your Password :";

            cin>>password;
            fflush(stdin);

            cout<<"Re-enter your Password :";

            cin>>retypepass;
            fflush(stdin);

            if(password!=retypepass)
            {
                cout<<"Re-type is not correctly entered "<<endl;
            }


        }while(password!=retypepass);

        string enc_password=md5(password);


        int check_email=0;

        while(check_email!=1){

        cout<<"Enter your email :";
cin.sync();
        getline(cin,email);
cin.sync();
        fflush(stdin);

            const char *test=email.c_str();

            unsigned int j=0;

            while(j<strlen(test)){
                if(test[j]=='@'){
                    check_email=1;
                }
                j++;
            }

            if(check_email!=1){
                cout<<endl<<endl<<"Sorry, please enter correct email address:"<<endl<<endl;
            }

        }

        unsigned long answer=0;
        int check=0;

        while(answer!=4 || check==1){
            check=0;

        cout<<"Enter your four digit PIN code (as a security measure) :";

        cin>>securityquestion;

            answer=securityquestion.size();

        fflush(stdin);

            if(answer!=4)
            {
                cout<<endl<<endl<<"Sorry, please make sure the length of PIN is 4"<<endl;
            }

            const char *temp=securityquestion.c_str();

           unsigned int i=0;
            while(i<answer)
            {

                if(!isdigit(temp[i]))
                {

                    check=1;

                }
                i++;

            }
            if(check==1){
                cout<<endl<<"Sorry, invalid character entered in PIN code."<<endl;
            }
          //  check=0;

        }







        cout<<"Enter your Contact number :";

        cin>>contact;
        fflush(stdin);

        cout<<"Enter your address :";
        cin.sync();
        getline(cin,address);
        cin.sync();
        fflush(stdin);

        cout<<"Enter your deposit :";

        cin>>deposit;
        fflush(stdin);

    #include "File.txt"

        qstate=mysql_query(conn,"SELECT AUTO_INCREMENT FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA='cp_project' AND TABLE_NAME='customers'");

        //MYSQL_RES *res;

        MYSQL_ROW row;

        char* id = nullptr;

        if(!qstate)
        {
            res=mysql_store_result(conn);

            while((row=mysql_fetch_row(res)))
            {
                id=row[0];

            }

            string latest_id = string(id);

            date="16-3-17";

            string query="insert into customers(ID,Date,Name,Contact,Area,Deposit,password,security_question,username,email) values ('"+latest_id+"','"+new_date+"', '"+name+"','"+contact+"','"+address+"','"+deposit+"','"+enc_password+"','"+securityquestion+"','"+username+"','"+email+"')";

            const char* q=query.c_str();

            int qstate2=mysql_query(conn,q);

            if(!qstate2)
            {

                cout<<endl<<"Your data have been transfered Successfully "<<endl;
            }
            else
            {
                cout<<"Sorry "<<endl;
            }


        }

    }

    ~Signup(){

    }

    void set_info();


};


int main()
{
    Signup obj(0,"cp_project","182.50.132.112","aliakber123",0,0,"aliakber",0);

    system("pause");

    return 0;

}



