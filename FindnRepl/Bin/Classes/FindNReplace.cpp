/*
 * FindNReplace.cpp
 *
 *  Created on: Dec 13, 2018
 *      Author: DarkHelix
 *
 *  FindNReplace & Find And Replace
 */

#include "FindNReplace.hpp"
using namespace std;

//Initializer
FindNReplace::FindNReplace(){

	this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(this->hConsole, &this->consoleInfo);
	this->saved_attributes = this->consoleInfo.wAttributes;
	this->frontmatching.reserve(3500000);
	this->backmatching.reserve(3500000);
	this->tableofchange.reserve(3500000);
	this->strlength = 0;
	this->changed = 0;

}

//FindNReplace algorithm to scan pattern
void FindNReplace::patterncheck(){

	int patlen = this->pattern.length(), j = 0;
	this->repetlist.clear();
	this->repetlist.resize(patlen);

	for(int i = 1; i < patlen; i++){

		while(j >= 0 && this->pattern[j] != this->pattern[i]){

			if(j-1 < 0){

				j = -1;
				break;

			}

			j = this->repetlist[j - 1];

		}

		j += 1;
		this->repetlist[i] = j;

	}


}

//Insert text manually
void FindNReplace::manualinserttext(string dat){

	if(dat != this->texts){

		this->texts = dat;
		this->strlength=this->texts.length();
		this->frontmatching.clear();
		this->backmatching.clear();
		this->tableofchange.clear();
		this->changed=0;

	}

}

//Run main FindNReplace mechanism
void FindNReplace::run(string sampl){

	this->run(sampl,this->texts);

}

void FindNReplace::run(string sampl, string txts){

	if((sampl == this->pattern || sampl == "" )&& txts == this->texts){

		return;

	}

	if(sampl != this->pattern){

		this->pattern=sampl;
		this->patterncheck();

	}

	if(txts != this->texts){

		this->texts = txts;
		this->strlength=this->texts.length();

	}

	int samplen = this->pattern.length(), txtlen = this->texts.length(), j = 0;
	this->frontmatching.clear();
	this->backmatching.clear();
	this->tableofchange.clear();

	for(int i = 0; i < txtlen; i++){

		while(j >= 0 && this->texts[i] != this->pattern[j]){

			if (j-1 < 0){

				j = -1;
				break;

			}

			j = this->repetlist[j-1];

		}

		j += 1;

		if(j == samplen){

			j = this->repetlist[samplen - 1];
			this->frontmatching.push_back(i - samplen + 1);
			this->backmatching.push_back(i);
			this->tableofchange.push_back(false);

		}

	}

	this->changed = 0;

}

//Print the result of FindNReplace & Find and Replace (ALL RESULT)
void FindNReplace::printout(){

	int runaround = 0;

	for(int k = 0; k < this->strlength;k++){

		if(runaround < this->frontmatching.size()){

			if((k >= this->frontmatching[runaround] && k <= this->backmatching[runaround])){

				if(!this->tableofchange[runaround])SetConsoleTextAttribute(this->hConsole, 10);
				else SetConsoleTextAttribute(this->hConsole, 8);
				runaround = k == this->backmatching[runaround] ? runaround + 1 : runaround;
			}

		}

		cout<<this->texts[k];
		SetConsoleTextAttribute(this->hConsole,this->saved_attributes);

	}

	cout<<endl;

}

//Print the result of FindNReplace & Find and Replace (CERTAIN PART RESULT)
void FindNReplace::printout(int choosing){

	for(int k = 0; k < this->strlength;k++){

		if((k >= this->frontmatching[choosing-1] && k <= this->backmatching[choosing-1])){

			if(!this->tableofchange[choosing-1])SetConsoleTextAttribute(this->hConsole, 10);

		}

		cout<<this->texts[k];
		SetConsoleTextAttribute(this->hConsole,this->saved_attributes);

	}
	cout<<endl;

}

//Replace ALL of the result of string finding
void FindNReplace::replaceall(string replacer){

	if(this->tableofchange.size() <= 0 || replacer == this->pattern){

		return;

	}

	if(this->changed < this->tableofchange.size()){

		int workout = replacer.length()-this->pattern.length();

	if(workout == 0){

		for(int i = 0;i < this->frontmatching.size();i++){

			if(!this->tableofchange[i]){

				int tempprober = this->frontmatching[i];

				for(int j = 0;j < replacer.length();j++){

					this->texts[tempprober]=replacer[j];
					tempprober++;

				}

				this->changed++;
				this->tableofchange[i] = true;

			}

		}

	}

	else if(workout>0){

		this->replaceallreverse(replacer,workout);

	}

	else{

		this->replaceallfront(replacer,workout);

	}

	}

}

//String 'REPLACE ALL' mechanism from behind
void FindNReplace::replaceallreverse(string replacer, int prop){

	int prevlast=this->strlength-1;
	int occurtoken = this->tableofchange.size();

	this->strlength=this->strlength+(prop * (occurtoken - this->changed));

	if(this->strlength > this->texts.length()){

		this->texts.resize(this->strlength);

	}

	int prober=this->strlength - 1;

	while(occurtoken > 0 /*prevlast >= this->frontmatching[0]*/){

		while(prevlast != this->backmatching[occurtoken - 1]){

			this->texts[prober]=this->texts[prevlast];
			prober--;
			prevlast--;

		}

		if(prevlast == this->backmatching[occurtoken-1] && !this->tableofchange[occurtoken-1]){

			occurtoken--;
			prevlast = this->frontmatching[occurtoken] - 1;
			this->backmatching[occurtoken]=prober;

			for(int i = replacer.length()-1; i >= 0; i--){

				this->texts[prober] = replacer[i];
				prober--;

			}

			this->frontmatching[occurtoken]=prober + 1;
			this->tableofchange[occurtoken]=true;
			this->changed++;

		}

		else{

			occurtoken--;
			this->backmatching[occurtoken]=prober;

			while(prevlast > this->frontmatching[occurtoken]){
				this->texts[prober]=this->texts[prevlast];
				prober--;
				prevlast--;
			}

			this->frontmatching[occurtoken]=prober;

		}

	}

}

//String 'REPLACE ALL' mechanism from front
void FindNReplace::replaceallfront(string replacer, int prop){

	int occurtoken = 0;
	int alreadychanged = this->changed;

	int probpoint=this->frontmatching[0];

	int j = probpoint;

	while(j < this->strlength){

		if(occurtoken < this->tableofchange.size()){

			if(j == this->frontmatching[occurtoken] && !this->tableofchange[occurtoken]){

				j += this->pattern.length();
				this->frontmatching[occurtoken]=probpoint;

				for(int i = 0; i < replacer.length(); i++){

					this->texts[probpoint]=replacer[i];
					probpoint++;

				}

				this->backmatching[occurtoken] = probpoint - 1;
				this->tableofchange[occurtoken] = true;
				this->changed++;
				occurtoken++;

			}
			else if(j == this->frontmatching[occurtoken] && this->tableofchange[occurtoken]){

				this->frontmatching[occurtoken]=probpoint;

				while(j < this->backmatching[occurtoken]){

					this->texts[probpoint] = this->texts[j];
					probpoint++;
					j++;

				}

				this->backmatching[occurtoken] = probpoint;

				occurtoken++;
			}

			else{

				this->texts[probpoint] = this->texts[j];
				probpoint++;
				j++;

			}

		}

		else{

			this->texts[probpoint] = this->texts[j];
			probpoint++;
			j++;

		}


	}

	this->strlength=this->strlength + ((this->tableofchange.size() - alreadychanged)*prop);

}


//Replace CERTAIN PART of the result of string finding
void FindNReplace::replace(int order, string replacer){

	if(this->tableofchange.size() <= 0 || replacer == this->pattern){

		return;

	}

	int target = order < 1 ? 0 : order > this->tableofchange.size() ? this->tableofchange.size() - 1: order - 1;

	int workout = replacer.length()-this->pattern.length();

	if(!this->tableofchange[target]){

		if(workout == 0){

			int tempprober = this->frontmatching[target];

			for(int j = 0;j < replacer.length();j++){

				this->texts[tempprober]=replacer[j];
				tempprober++;

			}

			this->changed++;
			this->tableofchange[target] = true;

		}

		else if(workout > 0){

			this->replaceback(target,replacer,workout);

		}

		else{

			this->replacefront(target,replacer,workout);

		}

	}

}

//String 'REPLACE PARTIAL' mechanism from front
void FindNReplace::replacefront(int target, string replacer, int prop){

	int j = this->frontmatching[target];
	int probpoint=j;
	j += this->pattern.length();

	for(int i = 0; i < replacer.length(); i++){

		this->texts[probpoint]=replacer[i];
		probpoint++;

	}

	this -> backmatching[target] = probpoint - 1;
	this -> tableofchange[target] = true;
	this -> changed++;
	int aftertarget = target + 1;

	while(j < this->strlength){

		if(aftertarget < this->tableofchange.size()){

			if(j == this->frontmatching[aftertarget]){

				this->frontmatching[aftertarget] = probpoint;

				while(j < this->backmatching[aftertarget]){

					this->texts[probpoint] = this->texts[j];
					probpoint++;
					j++;

				}

				this->backmatching[aftertarget] = probpoint;
				aftertarget++;

			}

		}

		this->texts[probpoint] = this->texts[j];
		probpoint++;
		j++;

	}

	this->strlength=this->strlength + prop;

}

//String 'REPLACE PARTIAL' mechanism from behind
void FindNReplace::replaceback(int target, string replacer, int prop){

	int prevlast = this->strlength - 1;
	this->strlength = this->strlength + prop;

	if(this->strlength > this->texts.length()){

		this->texts.resize(this->strlength);

	}

	int prober=this->strlength - 1;
	int helper=this->tableofchange.size() - 1;

	while(prevlast > this->backmatching[target]){

		if(prevlast == this->backmatching[helper]){

			this->backmatching[helper] = prober;

			while(prevlast > this->frontmatching[helper]){

				this->texts[prober] = this->texts[prevlast];
				prober--;
				prevlast--;

			}

			this->frontmatching[helper] = prober;
			helper--;

		}

		this->texts[prober] = this->texts[prevlast];
		prober--;
		prevlast--;

	}

	this->backmatching[target]=prober;

	for(int i = replacer.length()-1; i >= 0; i--){

		this->texts[prober] = replacer[i];
		prober--;

	}

	this->frontmatching[target]=prober + 1;
	this->tableofchange[target]=true;
	this->changed++;

}

//Return Result String
string FindNReplace::returning(){

	this->texts.resize(this->strlength);
	return this->texts;

}

//Clear search results
void FindNReplace::clearing(){

	this->pattern="";
	this->frontmatching.clear();
	this->backmatching.clear();
	this->tableofchange.clear();
	this->changed = 0;
}

//Return the number of discovered results
int FindNReplace::patternfoundnumreturn(){

	return this->tableofchange.size();

}

//Return the status whether all of the search results has been replaced
bool FindNReplace::isallchanged(){

	return this->changed == this->tableofchange.size();

}
