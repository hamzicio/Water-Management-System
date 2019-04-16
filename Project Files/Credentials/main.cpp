
#include <iostream>
#include<stdio.h>
#include<windows.h>
#include<mysql.h>
#include<cstring>
#include<ctype.h>
#include<cmath>
#include"md5.h"
#include<ctime>



using namespace std;
class DataBase

{

protected:

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

     MYSQL * getconn(){

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





class Login{
    int qstate;

    string input_password;
    string forgot;
    string newpass;
    string retype;
 //   MYSQL_RES *res;
  //  MYSQL_ROW row;
  MYSQL_RES *res;
      MYSQL_ROW row;

protected:
    int id_login;
    int user_id;
    string input_username;


public:
    DataBase d;
    Login(unsigned long b, const char* c,const char* d,const char* e,unsigned int f,int g=0,const char* h=NULL,const char* i=NULL):d(b,c,d,e,f,g,h,i)

    {
        Input1();

    }

    void Input1()
    {
         MYSQL *conn=d.getconn();

        cout<<"------------------  Login Feasiblity ----------- "<<endl;

        cout<<endl<<"Press 1 to login and 0 to reset password"<<endl;
        int ques;

        bool check_new=false;

        do{
            cin>>ques;

            if(ques==1 || ques==0){

                check_new=true;

            }else{

                cout<<endl<<"Please enter again!"<<endl;

            }

        }while(check_new==false);

        if(ques==1){
        login_step:
            bool result=false;
            do{
            cout<<"Enter username"<<endl;
            cin>>input_username;

            cout<<"Enter password"<<endl;
            cin>>input_password;

            string enc_password=md5(input_password);

            string query="SELECT * FROM owner WHERE username='"+input_username+"' AND password='"+enc_password+"'";

            const char *q=query.c_str();


            qstate=mysql_query(conn,q);

            if(!qstate)
            {
                res=mysql_store_result(conn);
                unsigned long long check1;

                check1=mysql_num_rows(res);

                if(check1==0)
                {

                    cout<<"Login Failed. Please try again:"<<endl<<endl;
                }
                else
                {
                    row=mysql_fetch_row(res);
                    cout<<"Login Successfully"<<endl<<endl;
                    result=true;
                }

            }

            }while(result==false);

        }// END for first IF

        else{

            string input_username;
            string input_new_password;
            string retype_new_password;

            cout<<endl<<"Enter Username:"<<endl;
            cin>>input_username;

            string query="SELECT * FROM owner WHERE username='"+input_username+"'";

            const char *q=query.c_str();

            int qstate_query= mysql_query(conn, q);

            if(!qstate_query){
                res=mysql_store_result(conn);

                unsigned long long rows_wanted=mysql_num_rows(res);

                if(rows_wanted==1){
                    do{

                        cout<<"Enter your new password:"<<endl;
                        cin>>input_new_password;

                        cout<<endl<<"Retype your new password:"<<endl;
                        cin>>retype_new_password;

                        if(input_new_password!=retype_new_password){
                            cout<<endl<<endl<<"Sorry, passwords didn't match"<<endl;
                        }


                    }while (input_new_password!=retype_new_password);
                }else{
                    cout<<endl<<endl<<"Sorry, Username wasn't found in database"<<endl;
                }

                if(rows_wanted==1){
                    string new_enc_pass=md5(input_new_password);
                    string latest_query="UPDATE owner SET password='"+new_enc_pass+"' WHERE username='"+input_username+"'";

                    const char *update_query=latest_query.c_str();

                    int new_qstate=mysql_query(conn, update_query);

                    if(!new_qstate){
                        cout<<endl<<endl<<"Your password has been changed successfully"<<endl;
                        goto login_step;
                    }else{
                        cout<<endl<<endl<<"Sorry, error changing your password"<<endl;
                    }

                }

            }


        }

    }

     string getUsername(){
        return input_username;
    }

    MYSQL_RES * getres(){

        return res;

    }

    MYSQL_ROW getrow(){
        return row;
    }


    ~Login(){

    }
    void set_newpass();

};



class Credentials{
    Login l;

       string username;

public:

    Credentials(unsigned long b, const char* c,const char* d,const char* e,unsigned int f,int g=0,const char* h=NULL,const char* i=NULL):l(b,c,d,e,f,g,h,i)

    {
        menu();
    }
    MYSQL* conn=l.d.getconn();

    MYSQL_ROW row=l.getrow();

    MYSQL_RES *res=l.getres();

    int qstate;


    void menu(){

        cout<<endl<<endl<<"To change customer's password, please enter their username below:"<<endl;

        bool result=false;

        do{

        cin>>username;

        string query_check="SELECT * FROM customers WHERE username='"+username+"'";
        const char *q_check=query_check.c_str();

        mysql_query(conn, q_check);

        res=mysql_store_result(conn);

        unsigned long long row_req=mysql_num_rows(res);

        if(row_req>0){
            result=true;
        }

            if(row_req==0){
                cout<<endl<<endl<<"Sorry, username not found in the customer's records. Please type in again:"<<endl;
            }

        }while(result==false);

        string pin_in;
        bool pin_check=false;

        cout<<endl<<endl<<"Please type your security PIN:"<<endl;

        do{
        cin>>pin_in;

        string pin_query="SELECT * FROM customers WHERE security_question='"+pin_in+"'";
        const char *q_pin=pin_query.c_str();

        mysql_query(conn, q_pin);

        res=mysql_store_result(conn);

        unsigned long long pin_rows=mysql_num_rows(res);

        if(pin_rows>0){
            pin_check=true;
        }else{
            cout<<endl<<endl<<"Sorry, PIN not correct. Please try again!"<<endl;
        }

        }while(pin_check==false);

        string new_pass,retype_pass;

        do{

        cout<<endl<<endl<<"Enter new password"<<endl;
        cin>>new_pass;

        cout<<endl<<endl<<"Retype password"<<endl;
        cin>>retype_pass;

            if(new_pass!=retype_pass){
                cout<<endl<<endl<<"Sorry, passwords didn't match."<<endl<<endl;
            }

        }while(new_pass!=retype_pass);


        string final_pass=md5(new_pass);

        string change_query="UPDATE customers SET password='"+final_pass+"' WHERE username='"+username+"'";
        const char *q_change=change_query.c_str();

       int qstate_pass= mysql_query(conn,q_change);

        if(!qstate_pass){
            cout<<endl<<endl<<"Password changed successfully"<<endl<<endl;
        }else{
            cout<<endl<<endl<<"Failure"<<endl<<endl;
        }


    }




};


int main(){

   Credentials obj(0,"cp_project","182.50.132.112","aliakber123",0,0,"aliakber",0);

   system("pause");

   cout<<endl<<endl;

   return 0;

}


