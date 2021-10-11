/*
   BANKING SYSTEM
   
   AUTHOR : SHRUTHI S
   CREATED ON : OCTOBER 11,2021

*/

#include <iostream>
#include<fstream>
#include <stdlib.h>
#include <ctime>
using namespace std;

void WriteInfo();
void ReadInfo();
void operation();
void delete_account();

//declaring class
class Bank
 {
   public:
    
    char name[30],password[30];//boundary condition of the name is 29 characters 
    int acc_no;
    char acc_type;// boundary one char ,,,'s' ,'c'
    float balance; 
 

  int retacc_no() 
{
	return acc_no;
}

//main initialisation
    void initialize()
 {
   cout<<"Welcome to JanaSeva Bank Portal"<<endl;
   cout<<"\nEnter your name\n";
   cin>>name;
   cout<<"\nEnter your account number\n";
   cin>>acc_no;
   cout<<"\nEnter your password\n";
   cin>>password;
   cout<<"\nEnter Account type\n'S' for savings account\n'C' for current account\n";
   cin>>acc_type;
   if((acc_type=='S')||(acc_type=='C')||(acc_type=='s')||(acc_type=='c'))
   {//checking if its savings account or current account
   cout<<"\nEnter amount to deposit\n";
   cin>>balance;
   }
   else 
   {//if not both,will go back to the beginning
     cout<<"Please select available account type"<<endl;
     initialize();
   }

  }
//operations initialisation
    void operations()
{
  int choice,choice1,x=1;
  while(x==1)
                {
                 cout<<"\nPress '1' to know your information\nPress '2' to deposit\nPress '3' to withdraw amount\n";
                 cin>>choice1;
            
              switch(choice1)
              {
                case 1 : display();//function to display the information
                break;

                case 2 : deposit();//function to deposit 
                break;

                case 3 : withdraw();//function to withdraw
                break;
              }

                cout<<"\nWanna do more transactions?\nClick '1' for yes \nClick '0' for no\n";
                cin>>x;
              
      }
}
//deposit function
     void deposit()
       {
         int amt;
         cout<<"\nEnter amount to deposit\n";
         cin>>amt;
         balance=balance+amt;//adds the new amount to the existing balance
         display();//displays the information
       }
//withdraw function
     void withdraw()
       {
        int amt;
        cout<<"\nYour balance is : "<<balance;
        cout<<"\nEnter amount you wanna withdraw\n";
        cin>>amt;
          if(amt<=balance)
           {
             balance=balance-amt;//subtracts the new amount to the existing balance
             display();//displays the information
           }
          else
           {
             cout<<"You cannot withdraw amount more than your balance\n";
             display();//displays the information
           }
       }
//display function
      void display()
        {
            cout<<"\nName :"<<name;
            cout<<"\nAccount Number :"<<acc_no;
            cout<<"\nAccount Type :"<<acc_type;
            cout<<"\nYour balance : "<<balance;
        }
   
};
//delete account function
void delete_account(int n);
int main() {
    int choice,choice1,x=1,c=1,acc_no;
    Bank bank;
    while(c)
    {
      cout<<"Press '1' if you already have an account and want to do transactions\nPress '2' if you wanna create an account\nPress '3' to read information\nPress '4' to delete account\n";
      cin>>choice;

      switch(choice)
      {
        case 1 : bank.initialize();//calling initialize function
                 bank.operations();//calling operations function
        break;
      
        case 2 : WriteInfo();//creating a new account in file
        break;
      
        case 3 : ReadInfo();//reading information ifrom file
        break;

        case 4 : cout<<"Enter account number : ";           
		         cin>>acc_no;
		         delete_account(acc_no);//calling delete_account function to delete account
        break;
      
        default : cout<<"Sorry..no such operation";
        
      }
 cout<<"Thank You ....."<<endl;
 cout<<"Next customer....\nPlease click on '1' to make use of the banking system"<<endl;
 cin>>c;
  }
}

//function for writing information in file
void WriteInfo()
{
    char name[30];
    char password[30];
    char acc_type;
    float balance;
    int acc_no;
    int num,select,x;
            cout<<"Please enter your name"<<endl;
            cin.ignore();
            cin.getline(name,30);
            cout<<"Please create a password"<<endl;
            cin.getline(password,30);
            cout<<"Please enter what kind of account you want to create\n's' for Savings\n'c' for current\n";
            cin>>acc_type;
            acc_type=toupper(acc_type);
            cout<<"Enter account number"<<endl;
            cin>>acc_no;
            cout<<"Please make an initial deposit :D"<<endl;
            cin>>balance;

            fstream accInfo;
            accInfo.open("accInfo.txt",ios::app); 
            accInfo<<acc_no;
            accInfo<<"\n\n";
            accInfo<<name;
            accInfo<<"\n\n";
            accInfo<<balance;
            accInfo<<"\n\n";
            accInfo<<acc_type;
            accInfo<<"\n\n";
            cout<<"\nPress '1' to deposit\nPress '2' to withdraw\n";
            cin>>select;
            if(select==1)
            {
               int amt;
               cout<<"\nEnter amount to deposit\n";
               cin>>amt;
               balance=balance+amt;
               accInfo<<"Updated Balance : \t\t"<<balance;
            }
            else if(select==2)
            {
              int amt;
               cout<<"\nYour balance is : "<<balance;
               cout<<"\nEnter amount you wanna withdraw\n";
               cin>>amt;
              if(amt<=balance)
             {
              balance=balance-amt;
              accInfo<<"Updated Balance : \t\t"<<balance;
             }
          else
           {
             cout<<"You cannot withdraw amount more than your balance\n";
            }

          }           
            accInfo.close();

}
//funtion for reading information from file
void ReadInfo()
{
    fstream accInfo;
    accInfo.open("accInfo.txt",ios::in);
    char infor[100];
    while(accInfo)
    {
        accInfo.getline(infor,100);
        cout<<infor<<"\n";
    }
    accInfo.close();
}
//function for deleting information from file
 void delete_account(int n)
     {
    Bank ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("accInfo.txt",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.txt",ios::binary);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank)))
    {
        if(ac.retacc_no()!=n)
        {
            outFile.write(reinterpret_cast<char *> (&ac), sizeof(Bank));
        }
    }
    inFile.close();
    outFile.close();
    remove("accInfo.txt");
    rename("Temp.txt","accInfo.txt");
    cout<<"\n\n\tRecord Deleted ..";
 }




