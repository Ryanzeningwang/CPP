#include <iostream>
#include <cmath>
#include <fstream>
#include <ostream>
using namespace std;

class accountTest{
private:
    int account;
    string firstName;
    string lastName;
    float totalBalance;
public:
    void record();
    void show();
    void finish();
    void screen();
    void edit();
    void search();
};
/*
 * record all the user information
 * */
void accountTest::record(){
    cout <<"Enter your account number: ";
    cin >> account;
    //cout <<"You account number is  " << account << " .";

    cout <<"Enter your first name: ";
    cin >> firstName;
    //cout <<"your first name is "<< firstName << " .";

    cout <<"Enter your last name: ";
    cin >> lastName;
    //cout <<"your last name is " << lastName << " .";

    cout << "Enter your total balance: ";
    cin >>totalBalance;
    //cout <<"your total balance is "<< totalBalance<< ". ";

}
/*
 * output format.
 * */
void accountTest::show(){
    cout <<"your account number is: "<< account <<endl;
    cout <<"your first name is: "<<firstName<<endl;
    cout <<"your last name is: "<<lastName<<endl;
    cout <<"your total balance is: "<<totalBalance<<endl;

};
/*
 * output user information into console
 * */
void accountTest::finish(){

    ofstream out;
    out.open("record.bank", ios::binary|ios::app);
    record();
    out.write(reinterpret_cast<char *>(this), sizeof(*this));
    out.close();
}
/*
 * show all the information on screen
 *
 * */
void accountTest::screen(){
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if(!infile)
    {
        cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
    }
    cout<<"\n****Data from file****"<<endl;
    while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this)>0))
        {
            show();
        }
    }
    infile.close();

}
/*
 * searching method
 * */
void accountTest::search()
{
    int number;
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if(!infile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to Search: ";
    cin>>number;
    infile.seekg((number-1)*sizeof(*this));
    infile.read(reinterpret_cast<char*>(this), sizeof(*this));
    show();
}
/*
 * edit method for update information
 *
 * */
void accountTest::edit()
{
    int number;
    fstream iofile;
    iofile.open("record.bank", ios::in|ios::binary);
    if(!iofile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    iofile.seekg(0, ios::end);
    int count = iofile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to edit: ";
    cin>>number;
    iofile.seekg((number-1)*sizeof(*this));
    iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
    cout<<"Record "<<number<<" has following data"<<endl;
    show();
    iofile.close();
    iofile.open("record.bank", ios::out|ios::in|ios::binary);
    iofile.seekp((number-1)*sizeof(*this));
    cout<<"\nEnter data to Modify "<<endl;
    record();
    iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
}
/*
 * main mathod for testing
 *
 * */
int main() {
    int choice;
    accountTest test;
    while(true){
        cout <<"Enter the following instruction: ";
        cout <<"\n\t1. start to record a account.";
        cout <<"\n\t2. show the record.";
        cout <<"\n\t3. search a account.";
        cout <<"\n\t4. edit a account.";
        cout <<"\n\t5. quit.";
        cout <<"\n\tchoice a number: ";
        cin >> choice;
        switch(choice){
            case 1:
                test.finish();
                break;

            case 2:
                test.screen();
                break;
            case 3:
                test.search();
                break;
            case 4:
                test.edit();
                break;
            case 5:
                exit(0);
                break;
            default:
                cout<<"\nEnter correct choice";
                exit(0);
        }

    }



    return 0;
}
