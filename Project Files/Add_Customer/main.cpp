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
                    exit(1);
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



class Customer{
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

    Login l;

protected:
    int id_signup;
public:

    Customer(unsigned long b, const char* c,const char* d,const char* e,unsigned int f,int g=0,const char* h=NULL,const char* i=NULL):l(b,c,d,e,f,g,h,i)

    {
        Input();

    }

    MYSQL* conn=l.d.getconn();

    MYSQL_ROW row=l.getrow();

    MYSQL_RES *res=l.getres();

    int qstate;

    void Input()
    {

        cout<<"------------------  ADD Customer Below Feasiblity ----------- "<<endl;

        fflush(stdin);

        cout<<"Enter customer's name : ";


cin.sync();
        getline(cin,name);
        cin.sync();
        fflush(stdin);



        cout<<endl<<"Enter customer's username :";


        getline(cin,username);

        fflush(stdin);

        do
        {

            cout<<"Enter customer's Password :";

            cin>>password;
            fflush(stdin);

            cout<<"Re-enter customer's Password :";

            cin>>retypepass;
            fflush(stdin);

            if(password!=retypepass)
            {
                cout<<"Re-type is not correctly entered "<<endl;
            }


        }while(password!=retypepass);

        string enc_password=md5(password);


        cin.sync();

        int check_email=0;

        while(check_email!=1){

            cout<<"Enter customer's email :";

            getline(cin,email);

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







        cout<<"Enter customer's Contact number :";

        cin>>contact;
        fflush(stdin);

        cout<<"Enter customer's address :";

        cin.sync();
        getline(cin,address);
        cin.sync();
        fflush(stdin);

        cout<<"Enter customer's deposit :";

        cin>>deposit;
        fflush(stdin);

#include "File.txt"

        qstate=mysql_query(conn,"SELECT AUTO_INCREMENT FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA='cp_project' AND TABLE_NAME='customers'");

        MYSQL_RES *res;

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

                cout<<endl<<"Customer's data have been transfered Successfully "<<endl;
            }
            else
            {
                cout<<"Sorry,process Failed. "<<endl;
            }


        }

    }

    ~Customer(){

    }

    void set_info();


};


int main(){

  if(system("ping www.google.com -t 2 > nul")){
   Customer obj(0,"cp_project","182.50.132.112","aliakber123",0,0,"aliakber",0);
  }else{

    cout<<"Sorry, Internet Connection Not available. Please try again!"<<endl;

  }

    system("pause");

    cout<<endl<<endl;

    return 0;


}
