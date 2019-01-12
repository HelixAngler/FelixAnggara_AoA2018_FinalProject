/*
 * FindNReplace.hpp
 *
 *  Created on: Dec 13, 2018
 *      Author: DarkHelix
 *
 *  Header for FindNReplace
 *  Code in FindNReplace.cpp
 */

#ifndef BIN_CLASSES_FindNReplace_HPP_
#define BIN_CLASSES_FindNReplace_HPP_
#include<iostream>
#include<vector>
#include<algorithm>
#include<windows.h>
using namespace std;
class FindNReplace{

private:
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;
	int strlength;
	int changed;
	string pattern;
	vector<int> repetlist;
	vector<int> frontmatching;
	vector<int> backmatching;
	vector<bool> tableofchange;
	string texts;
	void patterncheck();
	void replaceallreverse(string replacer, int prop);
	void replaceallfront(string replacer,int prop);
	void replacefront(int target, string replacer, int prop);
	void replaceback(int target, string replacer, int prop);
//
public:

	FindNReplace();
	void run(string sampl, string texts);
	string returning();
	void printout();
	void printout(int choosing);
	void replaceall(string replacer);
	void replace(int order, string replacer);
	void manualinserttext(string dat);
	void run(string sampl);
	void clearing();
	int patternfoundnumreturn();
	bool isallchanged();

//
};




#endif /* BIN_CLASSES_FindNReplace_HPP_ */
