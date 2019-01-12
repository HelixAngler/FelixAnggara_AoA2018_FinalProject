/*
 * main.cpp
 *
 *  Created on: Dec 13, 2018
 *      Author: DarkHelix
 *
 *
 *
 *  All Functions other than main are in Function folder in allfunctions.cpp
 *  For menu1(), menu2(), and menu3(), these functions are included in navigation.hpp and navigation.cpp
 *  allfunctions.hpp is actually a hub for it
 * */

#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<windows.h>
#include<fstream>
#include "Classes/allclasses.hpp"
#include "Function/allfunctions.hpp"
using namespace std;

/* Find and Replace Program
 * By Felix Anggara
 * */



// Main function

int main(){

	bool isRunning = true; // Boolean to trigger the loop
	int optone; // Container for menu1 function
	FindNReplace findReplaceEngina; // Find and Replace Class
	string currentdirectory = "c:/"; // Directory Navigation
	string fileopenlocation = ""; // Current Opened File Directory
	string filename = "NULL"; // Current Opened File Filename
	bool navindic=SetCurrentDirectory(currentdirectory.c_str()); // Switch directory to system default root directory (C:/) function from Windows API (windows.h) to switch directory

	// Main Loop For Program

	while(isRunning){

		system("cls"); // Clear screen (I wont mention it again)
		cout<<"Current Directory :"<<currentdirectory<<endl; // Show current search directory
		cout<<"Current File Path :"<<fileopenlocation<<filename<<endl<<endl<<endl; // Show current file path
		findReplaceEngina.printout(); // Print the result
		cout<<endl<<endl;
		optone = menu1(); // Run menu1 (Main menu)

		//Check which option is elected from menu1
		switch(optone){

		//Search and probe into the directory
		case 0:{

			system("cls");
			string tempcontainer;
			cout<<"Type the target directory :";
			getline(cin,tempcontainer);
			navindic=SetCurrentDirectory(tempcontainer.c_str());

			if(navindic){

				while(tempcontainer[tempcontainer.length()-1] == ' '){

					tempcontainer.pop_back();

				}

				if(tempcontainer[tempcontainer.length()-1] == '/' || tempcontainer[tempcontainer.length()-1] == '/'){

					tempcontainer.pop_back();

				}

				currentdirectory=tempcontainer+'/';

			}

			else{

				system("cls");
				cerr<<"Error: Directory Not Found"<<endl;
				_getch();

			}

			break;

		}

		// Select file from current probed directory
		case 1:{

			system("cls");
			string tempcontainer;
			string tempstorage;
			tempstorage.reserve(35000000);
			cout<<"Type the target file :";
			getline(cin,tempcontainer);
			ifstream myfile;
			myfile.open(tempcontainer);

			if(myfile.is_open()){

				//Option to save or not or cancel
				if(filename != "NULL"){
					system("cls");
					cout<<"Save or Not?"<<endl;
					int savenotorcancel=menu3();

					if(savenotorcancel == 0){

						ofstream mifile;
						SetCurrentDirectory(fileopenlocation.c_str());
						mifile.open(filename);

						if(mifile.is_open()){

							mifile<<findReplaceEngina.returning();
							mifile.close();

						}

						SetCurrentDirectory(currentdirectory.c_str());

					}

					else if(savenotorcancel == 2){

						myfile.close();
						break;

					}

				}

				filename = tempcontainer;

				while(!myfile.eof()){

					getline(myfile,tempcontainer);
					tempstorage = tempstorage + tempcontainer +'\n';

				}

				myfile.close();
				tempstorage.pop_back();
				findReplaceEngina.manualinserttext(tempstorage);
				fileopenlocation = currentdirectory;

			}

			else{

				system("cls");
				cerr<<"Error: File Not Found"<<endl;
				_getch();

			}

			break;

		}

		// Option to find pattern
		case 2:{

			if(filename != "NULL"){

				string tempcontainer;
				cout<<"\rType the pattern that wanted to be found :                                         "<<endl;
				getline(cin,tempcontainer);
				findReplaceEngina.run(tempcontainer);

			}

			else{

				system("cls");
				cerr<<"Error: File Not Selected"<<endl;
				_getch();

			}

			break;

		}

		//Option to replace pattern
		case 3:{

			int tempor;

			if(filename != "NULL"){

				string tempcontainer;
				cout<<"\rType the pattern that wanted to be found :                                         "<<endl;
				getline(cin,tempcontainer);

				system("cls");

				bool secondphase;
				findReplaceEngina.run(tempcontainer);

				if(findReplaceEngina.isallchanged()){

					break;

				}

				findReplaceEngina.printout();
				cout<<endl<<endl;
				cout<<"Type the replacer For the pattern :"<<endl;
				getline(cin,tempcontainer);

				system("cls");
				cout<<"Replace all or certain part or cancel?"<<endl;
				tempor = menu2(); // Trigger menu2

				// Receive the result from menu2
				switch(tempor){

				// Replace All
				case 0 :{

					findReplaceEngina.replaceall(tempcontainer);
					break;

				}

				// Replace certain part
				case 1 :{

					system("cls");
					findReplaceEngina.printout();
					cout<<endl<<endl;

					cout<<"Type the order number of the pattern that wanted to be replaced :";
					cin>>tempor;
					findReplaceEngina.replace(tempor,tempcontainer);
					break;

				}

				// Cancel
				case 2 :{

					findReplaceEngina.clearing();
					break;

				}

				default:{}

				}

			}

			else{

				// Prevent replace option to run when no file selected
				system("cls");
				cerr<<"Error: File Not Selected"<<endl;
				_getch();

			}

			break;

		}

		// Option to Exit program
		case 4:{

			//Option to save or not or cancel
			if(filename != "NULL"){

				system("cls");
				cout<<"Save or Not?"<<endl;
				int savenotorcancel=menu3();

				if(savenotorcancel == 0){

					ofstream mifile;
					SetCurrentDirectory(fileopenlocation.c_str());
					mifile.open(filename);

					if(mifile.is_open()){

						mifile<<findReplaceEngina.returning();
						mifile.close();

					}

				}

				else if(savenotorcancel == 2){

					break;

				}

			}

			isRunning=false;
			break;

		}

		}

	}

}


