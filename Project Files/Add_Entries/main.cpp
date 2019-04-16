

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


class Entries{
    Login l;

public:

    Entries(unsigned long b, const char* c,const char* d,const char* e,unsigned int f,int g=0,const char* h=NULL,const char* i=NULL):l(b,c,d,e,f,g,h,i)

    {

        AddEntries();
    }
    MYSQL* conn=l.d.getconn();

    MYSQL_ROW row=l.getrow();

    MYSQL_RES *res=l.getres();

    int qstate;

     #include "Date_Diff.txt"

    void AddEntries(){
    #include "File.txt"

        char *max_id;
        int ques;
        string date_input;
        string month_f,day_f,year_f;
         int month_in = 0,day_in = 0,year_in = 0;

        cout<<endl<<"To auto-fetch date, press 1 or to enter your own date, press 2:"<<endl;

        bool check_new=false;

        do{
            cin>>ques;

            if(ques==1 || ques==2){

                check_new=true;

            }else{

                cout<<endl<<"Please enter again!"<<endl;

            }

        }while(check_new==false);

        if(ques==1){
            cout<<endl<<"Date: "<<new_date<<endl;
            month_in=stoi(month);
            day_in=stoi(day);
            year_in=stoi(year);

        }else{



            cout<<endl<<"Enter the month:"<<endl;
            cin>>month_in;

            cout<<endl<<"Enter the day:"<<endl;
            cin>>day_in;

            cout<<endl<<"Enter the year:"<<endl;
            cin>>year_in;



            month_f=to_string(month_in);
            day_f=to_string(day_in);
            year_f=to_string(year_in);

            if(month_in<10){
                month_f="0"+month_f;
            }

            if(day_in<10){
                day_f="0"+day_f;
            }

            date_input=year_f+"-"+month_f+"-"+day_f;

            new_date=date_input;
            cout<<endl;

        }

        cout<<"Select and enter ID of the registered customers below:"<<endl;

        string input_ID;

        int qstate=mysql_query(conn, "SELECT * FROM customers");

        if(!qstate){
            res=mysql_store_result(conn);

            while((row=mysql_fetch_row(res))){
                cout<<row[0]<<": "<<row[2]<<endl;

            }


            bool for_test=false;

            do{

            cin>>input_ID;

                string test="SELECT * FROM customers WHERE ID='"+input_ID+"'";
                const char *q_check=test.c_str();
                mysql_query(conn, q_check);

                res=mysql_store_result(conn);

                unsigned long long my_test=mysql_num_rows(res);

                if(my_test>0){
                    for_test=true;
                }else{
                    for_test=false;
                    cout<<endl<<"Sorry, wrong input. Please select and enter ID from the above list:"<<endl;
                }

            }while(for_test==false);

        }

        string refill,empty_rec,total,cash,credit,deposit;

        mysql_query(conn, "SELECT AUTO_INCREMENT FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA='cp_project' AND TABLE_NAME='entries'");

        res=mysql_store_result(conn);
        row=mysql_fetch_row(res);
        char *entries_id_c=row[0];
        string entries_id=string(entries_id_c);

        cout<<endl<<"Enter Refill Bottles:"<<endl;
        cin>>refill;

        cout<<endl<<"Enter Empty Received Bottles:"<<endl;
        cin>>empty_rec;



        cout<<endl<<"Enter Cash"<<endl;
        cin>>cash;

        cout<<endl<<"Enter Credit"<<endl;
        cin>>credit;

        cout<<endl<<"Enter Deposit"<<endl;
        cin>>deposit;

        double total_d=stod(cash)+stod(credit);

        total=to_string(total_d);


        // FOR CHECK OF ITEMS IN ENTRIES TABLE:

        string ent_query="SELECT * FROM entries WHERE user_id='"+input_ID+"'";
        const char *q1=ent_query.c_str();
        mysql_query(conn, q1);

        res=mysql_store_result(conn);

        unsigned long long rows_fetched=mysql_num_rows(res);

        if(rows_fetched>0){
            string newest_query="SELECT max(ID) FROM entries WHERE user_id='"+input_ID+"'";
            const char *q=newest_query.c_str();
            mysql_query(conn, q);

            res=mysql_store_result(conn);

            row=mysql_fetch_row(res);
            max_id=row[0];

            string latest_id=string(max_id);

            string query_for_id="SELECT * FROM entries WHERE ID='"+latest_id+"'";

            const char *q2=query_for_id.c_str();

            mysql_query(conn, q2);

            res=mysql_store_result(conn);
            row=mysql_fetch_row(res);

            char *bottle_balance_c=row[8];
            char *balance_c=row[9];

            string bottle_balance=string(bottle_balance_c);
            string balance=string(balance_c);

            double final_balance_d=stod(total)-stod(cash)+stod(balance);
            string final_balance=to_string(final_balance_d);  // NEEDED

            double bottle_balance_1_d=stod(refill)-stod(empty_rec);
            double final_bottle_balance_d=bottle_balance_1_d+stod(bottle_balance_c);
            string final_bottle_balance=to_string(final_bottle_balance_d);  //NEEDED


            string deposit_query="SELECT * FROM customers WHERE ID='"+input_ID+"'";
            const char *q_deposit=deposit_query.c_str();

            mysql_query(conn, q_deposit);

            res=mysql_store_result(conn);
            row=mysql_fetch_row(res);

            char *name_of_cust_c=row[2];
            string name_of_cust=string(name_of_cust_c);

            char *deposit_c=row[5];
            string deposit_old=string(deposit_c);

            double final_deposit_d=stod(deposit_old)+stod(deposit);

            string final_depsoit=to_string(final_deposit_d);  //NEEDED

            string deposit_update="UPDATE customers SET Deposit='"+final_depsoit+"' WHERE ID='"+input_ID+"'";
            const char *q_deposit_update=deposit_update.c_str();

            mysql_query(conn, q_deposit_update);
            double dep_ins_d=0;
            string dep_ins=to_string(dep_ins_d);

            string date_query="SELECT * FROM customers WHERE ID='"+input_ID+"'";
            const char *q_date=date_query.c_str();

            mysql_query(conn, q_date);

            res=mysql_store_result(conn);

            row=mysql_fetch_row(res);

            char *date_coming_c=row[1];

            string date_coming=string(date_coming_c);

        //    cout<<endl<<"Date to string: "<<date_coming<<endl;

            char y1_c=date_coming[0];
            //string y1=string(&y1_c);

            int test1=y1_c-'0';
            string y1=to_string(test1);

          //  cout<<endl<<"New check: "<<y1<<endl;


            char y2_c=date_coming[1];
            //string y2=string(&y2_c);

            int test2=y2_c-'0';
            string y2=to_string(test2);

            char y3_c=date_coming[2];
            //string y3=string(&y3_c);

            int test3=y3_c-'0';
            string y3=to_string(test3);


            char y4_c=date_coming[3];
            //string y4=string(&y4_c);

            int test4=y4_c-'0';
            string y4=to_string(test4);

          //  cout<<endl<<"Y3: "<<y3<<endl;

            string year_coming=y1+y2+y3+y4;

          //cout<<endl<<endl<<"Year coming: "<<y1_c<<endl;

            char m1_c=date_coming[5];
            //string m1=string(&m1_c);

            int m_test1=m1_c-'0';
            string m1=to_string(m_test1);

            char m2_c=date_coming[6];
            //string m2=string(&m2_c);

            int m_test2=m2_c-'0';
            string m2=to_string(m_test2);

            string month_coming=m1+m2;

            char d1_c=date_coming[8];
           // string d1=string(&d1_c);

            int d_test1=d1_c-'0';
            string d1=to_string(d_test1);

            char d2_c=date_coming[9];
            //string d2=string(&d2_c);

            int d_test2=d2_c-'0';
            string d2=to_string(d_test2);

            string day_coming=d1+d2;


            int year_coming_d=stoi(year_coming);
            int month_coming_d=stoi(month_coming);
            int day_coming_d=stoi(day_coming);


            int date_diff_1=diff(year_in,month_in,day_in)-diff(year_coming_d,month_coming_d,day_coming_d);
            int date_diff=abs(date_diff_1);

            string ins_query;
            string del_query;

            if(date_diff>=30){
                ins_query="INSERT INTO old_entries SELECT * FROM entries WHERE user_id='"+input_ID+"'";
                const char *q_ins=ins_query.c_str();

                mysql_query(conn, q_ins);

                del_query="DELETE FROM entries WHERE user_id='"+input_ID+"'";
                const char *q_del=del_query.c_str();

                mysql_query(conn,q_del);

                string date_update_query="UPDATE customers SET Date='"+new_date+"' WHERE ID='"+input_ID+"'";
                const char * q_date_update=date_update_query.c_str();

                mysql_query(conn, q_date_update);

               // cout<<endl<<"Date diff:"<<date_diff<<endl;
               // cout<<endl<<year_coming_d<<" "<<month_coming_d<<" "<<day_coming_d<<endl;
              //  cout<<endl<<year_in<<" "<<month_in<<" "<<day_in<<endl;

            }

           string final_input="insert into entries(ID,Name,user_id,Date,Empty,Refill,Cash,Credit,Bottle_Balance,Balance,Total,Deposit) values ('"+entries_id+"','"+name_of_cust+"','"+input_ID+"','"+new_date+"','"+empty_rec+"','"+refill+"','"+cash+"','"+credit+"','"+final_bottle_balance+"','"+final_balance+"','"+total+"','"+dep_ins+"')";

            const char *q_f_input=final_input.c_str();

          int my_new_qstate= mysql_query(conn, q_f_input);

            if(!my_new_qstate){
                cout<<endl<<endl<<"----Entry added successfully----"<<endl<<endl;
            }

        }else{


            double final_balance_d=stod(total)-stod(cash);
             string final_balance=to_string(final_balance_d);  // NEEDED

             double bottle_balance_1_d=stod(refill)-stod(empty_rec);
             string final_bottle_balance=to_string(bottle_balance_1_d);  //NEEDED


            string deposit_query="SELECT * FROM customers WHERE ID='"+input_ID+"'";
            const char *q_deposit=deposit_query.c_str();

            mysql_query(conn, q_deposit);

            res=mysql_store_result(conn);
            row=mysql_fetch_row(res);

            char *name_of_cust_c=row[2];
            string name_of_cust=string(name_of_cust_c);

            char *deposit_c=row[5];
            string deposit_old=string(deposit_c);

            double final_deposit_d=stod(deposit_old)+stod(deposit);

            string final_depsoit=to_string(final_deposit_d);  //NEEDED

            string deposit_update="UPDATE customers SET Deposit='"+final_depsoit+"' WHERE ID='"+input_ID+"'";
            const char *q_deposit_update=deposit_update.c_str();

            mysql_query(conn, q_deposit_update);
            double dep_ins_d=0;
            string dep_ins=to_string(dep_ins_d);

           string date_query="SELECT * FROM customers WHERE ID='"+input_ID+"'";
            const char *q_date=date_query.c_str();

            mysql_query(conn, q_date);

            res=mysql_store_result(conn);

            row=mysql_fetch_row(res);

            char *date_coming_c=row[1];

            string date_coming=string(date_coming_c);
            char y1_c=date_coming[0];
            //string y1=string(&y1_c);

            int test1=y1_c-'0';
            string y1=to_string(test1);

            //  cout<<endl<<"New check: "<<y1<<endl;


            char y2_c=date_coming[1];
            //string y2=string(&y2_c);

            int test2=y2_c-'0';
            string y2=to_string(test2);

            char y3_c=date_coming[2];
            //string y3=string(&y3_c);

            int test3=y3_c-'0';
            string y3=to_string(test3);


            char y4_c=date_coming[3];
            //string y4=string(&y4_c);

            int test4=y4_c-'0';
            string y4=to_string(test4);

            //  cout<<endl<<"Y3: "<<y3<<endl;

            string year_coming=y1+y2+y3+y4;

            //cout<<endl<<endl<<"Year coming: "<<y1_c<<endl;

            char m1_c=date_coming[5];
            //string m1=string(&m1_c);

            int m_test1=m1_c-'0';
            string m1=to_string(m_test1);

            char m2_c=date_coming[6];
            //string m2=string(&m2_c);

            int m_test2=m2_c-'0';
            string m2=to_string(m_test2);

            string month_coming=m1+m2;

            char d1_c=date_coming[8];
            // string d1=string(&d1_c);

            int d_test1=d1_c-'0';
            string d1=to_string(d_test1);

            char d2_c=date_coming[9];
            //string d2=string(&d2_c);

            int d_test2=d2_c-'0';
            string d2=to_string(d_test2);

            string day_coming=d1+d2;




            int year_coming_d=stoi(year_coming);
            int month_coming_d=stoi(month_coming);
            int day_coming_d=stoi(day_coming);


         int date_diff_1=diff(year_in,month_in,day_in)-diff(year_coming_d,month_coming_d,day_coming_d);
            int date_diff=abs(date_diff_1);

            string ins_query;
            string del_query;

            if(day_coming=="01"){
                ins_query="INSERT INTO old_entries SELECT * FROM entries WHERE user_id='"+input_ID+"'";
                const char *q_ins=ins_query.c_str();

                mysql_query(conn, q_ins);

                del_query="DELETE FROM entries WHERE user_id='"+input_ID+"'";
                const char *q_del=del_query.c_str();

                mysql_query(conn,q_del);

                string date_update_query="UPDATE customers SET Date='"+new_date+"' WHERE ID='"+input_ID+"'";
                const char * q_date_update=date_update_query.c_str();

                mysql_query(conn, q_date_update);

               // cout<<endl<<"date diff:"<<date_diff<<endl;
            }

            string final_input="insert into entries(ID,Name,user_id,Date,Empty,Refill,Cash,Credit,Bottle_Balance,Balance,Total,Deposit) values ('"+entries_id+"','"+name_of_cust+"','"+input_ID+"','"+new_date+"','"+empty_rec+"','"+refill+"','"+cash+"','"+credit+"','"+final_bottle_balance+"','"+final_balance+"','"+total+"','"+dep_ins+"')";

            const char *q_f_input=final_input.c_str();

            int my_new_qstate= mysql_query(conn, q_f_input);

            if(!my_new_qstate){
                cout<<endl<<endl<<"----Entry added successfully----"<<endl<<endl;
            }



        }



    }



};



int main(){

    if(system("ping www.google.com -t 2 > nul")){

    Entries obj(0,"cp_project","182.50.132.112","aliakber123",0,0,"aliakber",0);

    }else{

    cout<<"Sorry, Internet Connection Not available. Please try again!"<<endl;
    }
    system("pause");

    cout<<endl<<endl;

    return 0;


}
