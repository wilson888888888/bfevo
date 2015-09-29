#include "funct.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#define MEM 1000000

struct bf{
	std::string str;
	int fit, time;
};

struct strnum{
	std::string str;
	int n;
};

bool comp(bf a, bf b){
	if(a.fit == b.fit){
		if(a.time == b.time)
			return a.str.length() < b.str.length();
		return a.time < b.time;
	}
	return a.fit < b.fit;
}

//runs brainfuck program
strnum run(std::string bf, std::string in){
	int pos = 0;
	int cpos = MEM/2;
	int ipos = 0;
	int cells[MEM];
	int layer;
	std::string out = "";
	int iter = 0;
	while (pos < bf.length()){
		iter ++;
		if(iter > 100000)
			break;
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
	strnum ret;
	ret.str = out;
	ret.n = iter;
	return ret;
}

//n = 9 for blank included
//n = 8 for all symbols
//n = 6 to exclude brackets
char randsym(int n){
	char a = ' ';
	switch(rand() % n){
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
			break;
		case 7:
			a = ']';
			break;
		default:
			break;
		}
	return a;
}

//Generates a random brainfuck program
std::string gen(){
	std::string bf = "";
	char a;
	for (int i = 0; i < 20; i++){
		a = randsym(8);
		if(i % 2 == 0)
			bf += a;
		else
			bf = a + bf;
		if(a == '[')
			bf += ']';
		if(a == ']')
			bf = '[' + bf;
	}
	return bf;
}

//mutates string
std::string mut(std::string in){
	char a;
	int layer;
	int pos;
	std::string out (in);
	for(int i = 0; i < out.length(); i++){
		if(rand() % 15 == 0){
			a = randsym(9);
			if(out[i] == '['){
				layer = 0;
				pos = i;
				pos++;
				while(layer != 0 || out.at(pos) != ']'){
					if(out.at(pos) == '[')
						layer ++;
					if(out.at(pos) == ']')
						layer --;
					pos ++;
				}
				out[pos] = randsym(6);
			}
			else if(out[i] == ']'){
				layer = 0;
				pos = i;
				pos--;
				while(layer != 0 || out.at(pos) != '['){
					if(out.at(pos) == ']')
						layer ++;
					if(out.at(pos) == '[')
						layer --;
					pos --;
				}
				out[pos] = randsym(6);
			}
			if(a != ' ')
				out[i] = a;
			else
				out.erase(out.begin() + i);
			if(a == '['){
				if(out.length() - i == 0)
					out += ']';
				else
					out.insert(i + 1 + rand() % (out.length() - i), "]");
			}
			else if(a == ']'){
				if(i == 0)
					out = '[' + out;
				else
					out.insert(rand() % i, "[");
				i++;				
			}
		}
	}
	for(int i = 0; i < 2; i++){
		if(rand() % 3 == 0)
			out.insert(rand() % out.length(), std::string(1, randsym(6)));
	}
	return out;
}

//levenshtein distance between two strings
int dist(std::string a, std::string b){
	int m = a.length();
	int n = b.length();
	int dp[m + 1][n + 1];
	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
			dp[i][j] = 0;
	for(int i = 0; i <= m; i++)
		dp[i][0] = i;
	for(int i = 0; i <= n; i++)
		dp[0][i] = i;
	for(int j = 1; j <= n; j++){		
		for(int i = 1; i <= m; i++){
			if(a.at(i - 1) == b.at(j - 1))
				dp[i][j] = dp[i - 1][j - 1];
			else
				dp[i][j] = std::min(dp[i - 1][j] + 1, std::min(dp[i - 1][j - 1] + 1, dp[i][j - 1] + 1));
		}
	}
	return dp[m][n];
}

void evo(int iter, int tests, int m, int n){
	int tot = m * (n + 1);
	bf pop [tot];
	strnum res;
	for(int i = 0; i < tot; i++){
		pop[i].str = gen();
		pop[i].fit = 0;
	}
	std::string testcase;
	for(int i = 0; i < iter; i++){
		for(int j = 0; j < tot; j++){
			pop[j].fit = 0;
			pop[j].time = 0;
		}
		for(int j = 0; j < tot; j++){
			for(int k = 0; k < tests; k++){
				testcase = test();
				res = run(pop[j].str, testcase);
				pop[j].fit += dist(f(testcase), res.str);
				pop[j].time += res.n;
			}
		}
		std::sort(pop, pop + tot, comp);
		std::cout << "Iteration " << i << std::endl;
		for(int j = 0; j < tot; j++)
			std::cout << pop[j].str << ' ' << pop[j].fit <<  ' ' << pop[j].time << std::endl;
		for(int j = m; j < tot; j++)
			pop[j].str = mut(pop[j % m].str);
	}
}

int main(int argc, char* argv[]){
	int iter = 1000000;
	int tests = 1000;
	int m = 3;
	int n = 2;
	for(int i = 0; i < argc; i++){
		if(argv[i][0] == '-'){
			if(argv[i][1] == 'i')
				sscanf(argv[i + 1], "%d", &iter);
			if(argv[i][1] == 't')
				sscanf(argv[i + 1], "%d", &tests);
			if(argv[i][1] == 'm')
				sscanf(argv[i + 1], "%d", &m);
			if(argv[i][1] == 'n')
				sscanf(argv[i + 1], "%d", &n);
		}
	}
	srand(time(NULL));
	evo(1000000, 1000, 3, 2);
}
