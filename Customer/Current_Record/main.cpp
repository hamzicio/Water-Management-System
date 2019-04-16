#include <iostream>
#include<stdio.h>
#include<windows.h>
#include<mysql.h>
#include<cstring>
#include<ctype.h>
#include"md5.h"

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


        cout<<"------------------  Login Feasibility ----------- "<<endl;

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

        string query="SELECT * FROM customers WHERE username='"+input_username+"' AND password='"+enc_password+"'";

        const char *q=query.c_str();


        qstate=mysql_query(conn,q);

        if(!qstate)
        {
            res=mysql_store_result(conn);
            unsigned long long check1;

            check1=mysql_num_rows(res);

            if(check1==0)
            {

                cout<<"Login Failed. Please try again: "<<endl<<endl;

            }
            else
            {
                row=mysql_fetch_row(res);
                cout<<"Login Succesfull!"<<endl<<endl;
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

            string query="SELECT * FROM customers WHERE username='"+input_username+"'";

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
                     string latest_query="UPDATE customers SET password='"+new_enc_pass+"' WHERE username='"+input_username+"'";

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
    ~Login(){

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



};



class Current_Record{
    Login l;

public:
    Current_Record(unsigned long b, const char* c,const char* d,const char* e,unsigned int f,int g=0,const char* h=NULL,const char* i=NULL):l(b,c,d,e,f,g,h,i)

    {
        show_current_record();

    }
    MYSQL * conn=l.d.getconn();

    MYSQL_ROW row=l.getrow();

    MYSQL_RES *res=l.getres();

    int qstate;




    void show_current_record(){
        string input_id;



        input_id=l.getUsername();

        string new_query="SELECT * FROM customers WHERE username='"+input_id+"'";
        const char *q_new=new_query.c_str();

        mysql_query(conn, q_new);

        res=mysql_store_result(conn);

        row=mysql_fetch_row(res);

        char *user_id_c=row[0];
        string user_id=string(user_id_c);
        char *deposit_c=row[5];
        string deposit=string(deposit_c);
        char *email_c=row[9];
        string email=string(email_c);
        char *contact_c=row[3];
        string contact=string(contact_c);
        char *date_from_c=row[1];
        string date_from=string(date_from_c);


        string rec_query="SELECT * FROM entries WHERE user_id='"+user_id+"'";

        const char *q_rec=rec_query.c_str();

        mysql_query(conn, q_rec);

        res=mysql_store_result(conn);

        unsigned long long row_req=mysql_num_rows(res);

        cout<<endl<<endl;



        if(row_req>0){
            cout<<endl<<"Your Current Record/Bill is as follows:"<<endl<<endl;

            cout<<"Email: "<<email<<"\t\t Contact: "<<contact<<"\t\t Date From: "<<date_from<<endl<<endl<<endl;

            cout<<"ID\t\t"<<"Name\t  "<<" Date\t     "<<"  Empty\t"<<"Refill\t "<<"Cash\t"<<"Credit "<<" B-Bal\t "<<"Balance \t"<<"Total \t"<<endl;

            while((row=mysql_fetch_row(res))){
                cout<<row[0]<<"\t    "<<row[1]<<"\t  "<<row[3]<<"\t  "<<row[4]<<"\t "<<row[5]<<"\t"<<row[6]<<"\t"<<row[7]<<"\t "<<row[8]<<"\t "<<row[9]<<"   \t "<<row[10]<<endl;
            }

            cout<<endl<<endl;
            cout<<"-----------------------"<<"Total Deposit: "<<deposit;
        }
        cout<<endl<<endl;
    }

};


int main()
{
    Current_Record obj(0,"cp_project","182.50.132.112","aliakber123",0,0,"aliakber",0);

    system("pause");

    cout<<endl<<endl;

    return 0;

}


