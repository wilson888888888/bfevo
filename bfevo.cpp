#include "funct.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#define MEM 1000000

struct bf{
	std::string str;
	int fit;
};

bool comp(bf a, bf b){
	return a.fit < b.fit;
}

//runs brainfuck program
std::string run(std::string bf, std::string in){
	std::cout << "run" << std::endl;	
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
	return out;
}

//n = 8 for all symbols
//n = 6 to exclude brackets
char randsym(int n){
	std::cout << "randsym" << std::endl;
	char a;
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
	std::cout << "gen" << std::endl;
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
	std::cout << "mut" << std::endl;
	char a;
	int layer;
	int pos;
	std::string out (in);
	for(int i = 0; i < out.length(); i++){
		if(rand() % 15 == 0){
			a = randsym(8);
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
			out[i] = a;
			if(a == '['){
				out.insert(i + 1 + rand() % (out.length() - i), "]");
			}
			else if(a == ']'){
				out.insert(rand() % i, "[");
				i++;
			}
		}
	}
	return out;
}

//levenshtein distance between two strings
int dist(std::string a, std::string b){
	std::cout << "dist" << std::endl;
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
	for(int i = 0; i < tot; i++){
		pop[i].str = gen();
		pop[i].fit = 0;
	}
	std::string testcase;
	for(int i = 0; i < iter; i++){
		for(int j = 0; j < tot; j++)
			pop[j].fit = 0;
		for(int j = 0; j < tot; j++){
			for(int k = 0; k < tests; k++){
				testcase = test();
				pop[j].fit += dist(f(testcase), run(pop[j].str, testcase));
			}
		}
		std::sort(pop, pop + tot, comp);
		std::cout << "Iteration " << i << std::endl;
		for(int j = 0; j < tot; j++)
			std::cout << pop[j].str << ' ' << pop[j].fit << std::endl;
		for(int j = m; j < tot; j++)
			pop[j].str = mut(pop[j % m].str);
	}
}

int main(){
	srand(time(NULL));
	evo(10, 10, 3, 2);
	std::string str;
}
