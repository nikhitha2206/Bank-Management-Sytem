#include<fstream>
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<process.h>
#include<dos.h>
#include <windows.h>
#include<ios> //used to get stream size
#include<limits> //used to get numeric limits
#define MAX_NAME_LEN 60 // Maximum len of your name can't be more than 60
#define MAX_ADDRESS_LEN 120 // Maximum len of your address can't be more than 120
#define MAX_PHONE_LEN 13
using namespace std;

//MARK:- Interface Functions Here =>

void intro() {
	cout<<"\n\n\t            ";
	cout<<"     C++ Project On Hotel Management System";
	cout<<"\n\n\t\t\t\t     MADE BY\n";
	cout<<"\n";
	cout<<"\t\t\t\t  GAYAM NIKHITHA \t\t\t      ";
}

void head() {
	system("cls");
	cout<<"\n\n\n\n\n";
	cout<<"\t\t\t\t\t   XYZ Group of Hotels\t\t\t       ";
	cout<<"\n";
}
void time() {
	int i=0;
	long long j;
	cout<<"	\n\n\n	Connecting to Server\n 	Syncing DaTa";
	while(i<10)	{
		for (j=5;j>4;j++) {
			if (j==99999) {
				cout<<".";
				break;
			}
		}
		++i;
	}
}
//MARK:- Hotel Class Here =>
class hotel {
	private:
			int room_no;
			//string name, addr, phone,dummy;
			char name[30];
			char addr[50];
			char phone[15];
	
			int days;
			float fare;
	public:
			void main_menu();		//to display the main menu
			void add();				//to book a room
			void display(); 		//to display the customer record
			void rooms();			//to display allotted rooms
			void edit();			//to edit the customer record
			int check(int);	     	//to check room status
			void modify(int);		//to modify the record
			void delete_rec(int);   //to delete the record
};
void hotel::main_menu() {
	int choice;
	while(choice!=5) {
		system("cls");
		head();
		cout<<"\n\t\t\t\t*************";
		cout<<"\n\t\t\t\t* MAIN MENU *";
		cout<<"\n\t\t\t\t*************";
		cout<<"\n\n\n\t\t\t1.Book A Room";
		cout<<"\n\t\t\t2.Customer Record";
		cout<<"\n\t\t\t3.Rooms Allotted";
		cout<<"\n\t\t\t4.Edit Record";
		cout<<"\n\t\t\t5.Exit";
		cout<<"\n\n\t\t\tEnter Your Choice: ";
		cin>>choice;
		switch(choice) {
			case 1:	add();
					break;
			case 2: display();
					break;
			case 3: rooms();
					break;
			case 4:	edit();
					break;
			case 5: break;
			default: 
				cout<<"\n\n\t\t\tWrong choice.....!!!..Choose again!!";
				break;
		}
	}
}
void hotel::add() {
	system("cls");
	head();
	int r,flag;
	ofstream fout("Record.txt",ios::app);
	cout<<"\n Enter Customer Details";
	cout<<"\n ----------------------";
	cout<<"\n\n Room no: ";
	cin>>r;
	flag=check(r);
	if(flag)
		cout<<"\n Sorry..!!!Room is already booked";
	else {
        cout<<"Enter Your Name : ";
        cin.ignore();
        cout<<" ";
		cin.getline(name,50);
		cout<<"Enter Your Address : ";
		cin.getline(addr,50);
		cout<<"Enter your Phone Number(with country code) : ";
		cin.getline(phone,15);
		cout<<"Number of days to checkout : ";
		cin>>days;
		fare=days*900;
		room_no = r;					//900 is currently set as the	//default price per day
		fout.write((char*)this,sizeof(hotel));
		cout<<"\n Room is booked...!!!";
	}
	cout<<"\n Press any key to continue.....!!";
	getch();
	fout.close();
}
void hotel::display() {
	system("cls");
	head();
	ifstream fin("Record.txt",ios::in);
	int r,flag;
	cout<<"\n Enter room no: ";
	cin>>r;
	while(!fin.eof()) {
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r) {
		    system("cls");
			head();
			cout<<"\n Customer Details";
			cout<<"\n ----------------";
			cout<<"\n\n Room no: "<<room_no;
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<addr;
			cout<<"\n Phone no: "<<phone;
			cout<<"\n Days: "<<days;
			cout<<"\n Total Fare: "<<fare<<"Rs";
			flag=1;
		}
	}
	if(flag==0)
		cout<<"\n Sorry Room no. not found or vacant....!!";
	cout<<"\n\n Press any key to continue....!!";
	getch();
	fin.close();
}
void hotel::rooms() {
	system("cls");
	head();
	ifstream fin("Record.txt",ios::in);
	cout<<"\n\t\t\t    List Of Rooms Allotted";
	cout<<"\n\t\t\t    ----------------------";
	while(fin.read((char*)this,sizeof(hotel))) {
		cout<<"\n Room no: "<<room_no;
		cout<<"\n Name: "<<name;
		cout<<"\n Address: "<<addr<<"\n Phone: "<<phone;
		cout<<"\n Days: "<<days<<"\n Total money to be paid: "<<fare<<"Rs";
		cout<<"\n**********************************";
	}
	cout<<"\n\n\n\t\t\tPress any key to continue.....!!";
	getch();
	fin.close();
}
void hotel::edit() {
	system("cls");
	head();
	int choice,r;
	cout<<"\n EDIT MENU";
	cout<<"\n ---------";
	cout<<"\n\n 1.Modify Customer Record";
	cout<<"\n 2.Delete Customer Record";
	cout<<"\n Enter your choice: ";
	cin>>choice;
	system("cls");
	head();
	cout<<"\n Enter room no: " ;
	cin>>r;
	switch(choice) {
		case 1:	modify(r);
				break;
		case 2:	delete_rec(r);
				break;
		default: cout<<"\n Wrong Choice.....!!";
	}
	cout<<"\n Press any key to continue....!!!";
	getch();
}
int hotel::check(int r) {
	int flag=0;
	ifstream fin("Record.txt",ios::in);
	while(!fin.eof()) {
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r) {
			flag=1;
			break;
		}
	}
	fin.close();
	return(flag);
}
void hotel::modify(int r) {
	system("cls");
	head();
	long pos,flag=0;
	fstream file("Record.txt",ios::in|ios::out|ios::binary);
	while(!file.eof()) {
		pos=file.tellg();
		file.read((char*)this,sizeof(hotel));
		if(room_no==r) {
			cout<<"Enter Your Name : ";
		    cin.ignore();
		    cout<<" ";
		    cin.getline(name,50);
		    cout<<"Enter Your Address : ";
		    cin.getline(addr,50);
		    cout<<"Enter your Phone Number(with country code) : ";
		    cin.getline(phone,15);
		    cout<<"Number of days to checkout : ";
		    cin>>days;
		    fare=days*900;
		    room_no = r;
			file.seekg(pos);
			file.write((char*)this,sizeof(hotel));
			cout<<"\n Record is modified....!!";
			flag=1;
			break;
		}
	}
	if(flag==0)
		cout<<"\n Sorry Room no. not found or vacant...!!";
	file.close();
}
void hotel::delete_rec(int r) {
	system("cls");
	head();
	int flag=0;
	char ch;
	ifstream fin("Record.txt",ios::in);
	ofstream fout("temp.txt",ios::out);
	while(!fin.eof()) {
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r) {
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<addr;
			cout<<"\n Phone No: "<<phone;
			cout<<"\n Days: "<<days;
			cout<<"\n Total Fare: "<<fare;
			cout<<"\n\n Do you want to delete this record(y/n): ";
			cin>>ch;
			if(ch=='n')
				fout.write((char*)this,sizeof(hotel));
			flag=1;
			break;
		}
		else
			fout.write((char*)this,sizeof(hotel));
	}
	fin.close();
	fout.close();
	if(flag==0)
		cout<<"\n Sorry room no. not found or vacant...!!";
	else {
		remove("Record.txt");
		rename("temp.txt","Record.txt");
	}
}
//MARK:- Main() Function Here =>
int main() {
	system("Color 0B");
	hotel h;
	system("cls");
	cout<<"\n\n\n";
	intro();
	time();
	cout<<"\n\n\n\t\t\tPress any key to continue....!!";
	getch();
	system("cls");
	head();
	char id[5],pass[7];
	cout<<"\n\n\t\t\t\tusername => ";
	cin>>id;
	cout<<"\n\t\t\t\tpassword => ";
	cin>>pass;
	cout<<"\n\n\t";
	time();
	cout<<"\t";
	if(strcmp(id,"admin")==0&&strcmp(pass,"nikki")==0)
		cout<<"\n\n\t\t\t  !!!Login Successfull!!!";
	else {
		cout<<"\n\n\t\t\t!!!INVALID CREDENTIALS!!!";
		getch();
		exit(-1);
	}
	system("cls");
	h.main_menu();
	getch();
	
	return 0;
} 
