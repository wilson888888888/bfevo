#include "funct.h"
#include <iostream>
#include <stdlib.h>
#include <map>
#include <deque>
#define MEM 1000000

std::string run(std::string bf, std::string in){
	int pos = 0;
	int cpos = MEM/2;
	int ipos = 0;
	int cells[MEM];
	int layer;
	std::string out = "";
	while (pos < bf.length()){
		switch(bf.at(pos)){
		case '+':
			cells[cpos]++;
			break;
		case '-':
			cells[cpos]--;
			break;
		case '>':
			cpos++;
			break;
		case '<':
			cpos--;
			break;
		case '.':
			out += cells[cpos];
			break;
		case ',':
			if(ipos >= in.length())
				break;
			cells[cpos] = in.at(ipos);
			ipos++;
			break;
		case '[':
			if(cells[cpos] != 0)
				break;
			layer = 0;
			pos++;
			while(layer != 0 || bf.at(pos) != ']'){
				if(bf.at(pos) == '[')
					layer ++;
				if(bf.at(pos) == ']')
					layer --;
				pos ++;
			}
			break;
		case ']':
			if(cells[cpos] == 0)
				break;
			layer = 0;
			pos--;
			while(layer != 0 || bf.at(pos) != '['){
				if(bf.at(pos) == ']')
					layer ++;
				if(bf.at(pos) == '[')
					layer --;
				pos --;
			}
			break;
		default:
			break;
		}
		pos++;
	}
	return out;
}

std::string gen(){
	std::string bf = "";
	char a;
	bool l, r;
	for (int i = 0; i < 20; i++){
		l = false;
		r = false;
		switch(rand() % 8){
		case 0:
			a = '+';
			break;
		case 1:
			a = '-';
			break;
		case 2:
			a = '>';
			break;
		case 3:
			a = '<';
			break;
		case 4:
			a = '.';
			break;
		case 5:
			a = ',';
			break;
		case 6:
			a = '[';
			l = true;
			break;
		case 7:
			a = ']';
			r = true;
			break;
		default:
			break;
		}
		if(i % 2 == 0)
			bf += a;
		else
			bf = a + bf;
		if(l)
			bf += ']';
		if(r)
			bf = '[' + bf;
	}
	return bf;
}

int main(){
	srand(time(NULL));
	for(int i = 0; i < 10; i++)
		std::cout << gen() << std::endl;
}
