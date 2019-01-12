/*
 * allfunctions.cpp
 *
 *  Created on: Jan 9, 2019
 *      Author: DarkHelix
 */

#include "navigation.hpp"
using namespace std;


/*
 * menu1()
 * A function for main menu navigation interface
 * */

int menu1(){

	HANDLE consolehandler=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(consolehandler, &consoleInfo);
	WORD saved_attributes=consoleInfo.wAttributes;
	int totaloptions=5;
	int decision=0;
	int selector;
	bool working=true;

	string options[totaloptions]={"Choose Directory","Select File","Find Pattern","Replace Pattern","Exit"};
	while(working){
		cout<<"\r";
		for(int i = 0; i < totaloptions; i++){

			if(i == decision){

				SetConsoleTextAttribute(consolehandler, 16);

			}

			cout<<options[i];
			SetConsoleTextAttribute(consolehandler, saved_attributes);
			cout<<"   ";

		}
		selector=_getch();

		switch(selector){

		case 75:

		case 97:{

			if(decision==0){

				decision=totaloptions-1;

			}

			else{

				decision--;

			}

			break;

		}

		case 77:

		case 100:{

			if(decision==totaloptions-1){

				decision=0;

			}

			else{

				decision++;

			}

			break;

		}

		case 13:{

			working=false;
			break;
		}

		default:{}

		}

	}

	return decision;

}

/* menu2()
 *
 * A function for interface of whether replace all or certain part or cancel it
 * */

int menu2(){

	HANDLE consolehandler=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(consolehandler, &consoleInfo);
	WORD saved_attributes=consoleInfo.wAttributes;
	int totaloptions=3;
	int decision=0;
	int selector;
	bool working=true;

	string options[totaloptions]={"All","Choose One","Cancel"};
	while(working){
		cout<<"\r";
		for(int i = 0; i < totaloptions; i++){

			if(i == decision){

				SetConsoleTextAttribute(consolehandler, 16);

			}

			cout<<options[i];
			SetConsoleTextAttribute(consolehandler, saved_attributes);
			cout<<"   ";

		}
		selector=_getch();

		switch(selector){

		case 75:

		case 97:{

			if(decision==0){

				decision=totaloptions-1;

			}

			else{

				decision--;

			}

			break;

		}

		case 77:

		case 100:{

			if(decision==totaloptions-1){

				decision=0;

			}

			else{

				decision++;

			}

			break;

		}

		case 13:{

			working=false;
			break;
		}

		default:{}

		}

	}

	return decision;

}

/* menu3()
 *
 * A function for interface of whether want to save or not or cancel it
 * */

int menu3(){

	HANDLE consolehandler=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(consolehandler, &consoleInfo);
	WORD saved_attributes=consoleInfo.wAttributes;
	int totaloptions=3;
	int decision=0;
	int selector;
	bool working=true;

	string options[totaloptions]={"Yes","No","Cancel"};
	while(working){
		cout<<"\r";
		for(int i = 0; i < totaloptions; i++){

			if(i == decision){

				SetConsoleTextAttribute(consolehandler, 16);

			}

			cout<<options[i];
			SetConsoleTextAttribute(consolehandler, saved_attributes);
			cout<<"   ";

		}
		selector=_getch();

		switch(selector){

		case 75:

		case 97:{

			if(decision==0){

				decision=totaloptions-1;

			}

			else{

				decision--;

			}

			break;

		}

		case 77:

		case 100:{

			if(decision==totaloptions-1){

				decision=0;

			}

			else{

				decision++;

			}

			break;

		}

		case 13:{

			working=false;
			break;
		}

		default:{}

		}

	}

	return decision;

}
