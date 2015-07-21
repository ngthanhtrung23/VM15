/*
	Compile with C++11
	Subtask 1: m*n <= 18 (1..8)
	Subtask 2: m,n <= 100 (9..20)
	
	(For subtask "no two steps share common cells"
		I don't think it is neccesary)
*/	

#include "../../lib/testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int LIMIT = 100 + 5;
const int FLIP = 3;
const int MAX = 100;

int cnt[LIMIT][LIMIT];
int a[LIMIT][LIMIT];

void flip(int x, int y, int m, int n){
	assert(0<=x && x+FLIP<=m);
	assert(0<=y && y+FLIP<=n);
	for(int i=x; i<x+FLIP; ++i)
	for(int j=y; j<y+FLIP; ++j)
		a[i][j] ^= 1;
}

void init(){
	memset(a, 0, sizeof a);
	memset(cnt, 0, sizeof cnt);
}

set< pair<int,int> > genBoard(int m, int n, int nStep){
	set< pair<int,int> > res;
	while(nStep--){
		int i,j;
		do{
			i = rnd.next(m-FLIP+1);
			j = rnd.next(n-FLIP+1);
		}
		while (cnt[i][j]==1);
		
		cnt[i][j] = 1; flip(i,j,m,n);	
		res.insert( make_pair(i,j) );
	}
	return res;
}

void flipCells(int m, int n, int num){
	while (num--){	
		int i,j;
		do{
			i = rnd.next(m);
			j = rnd.next(n);
		} while ( cnt[i][j]==2 );		
		cnt[i][j]=2; a[i][j] ^= 1;
	}
}

string getString(int i){
	stringstream ss; ss<<i;
	return ss.str();
}

void printInput(string fileName, int m, int n){
	ofstream f(fileName);
	f << m << " " << n << endl;
	for(int i=0; i<m; ++i){
		for(int j=0; j<n; ++j) f << a[i][j] << " ";
		f << endl;
	}	
	f.close();
}

void printOutput(string fileName, const set< pair<int,int> >& res, bool wrong){
	ofstream f(fileName);
	if (wrong) f << -1 << endl;
	else {
		f << res.size() << endl;
		for(auto p: res)
			f << p.first+1 << " " << p.second+1 << endl;	
	}
	f.close();
}



void genTest(int testNum, int m, int n, bool wrong=false){
	init();
	int nStep = rnd.next((m-2)*(n-2) + 1);
	set< pair<int,int> > res = genBoard(m,n,nStep);
	if (wrong) flipCells(m,n,rnd.next(1,8));
	
	string name = getString(testNum);
	if (name.size() < 2) name = "0"+name;
	
	//input
	printInput("tests/"+name+".in", m, n);	
	printOutput("tests/"+name+".out",res,wrong);
}

void genSmall(int from, int to){
	for(int i=from; i<=to; ++i){
		int m = rnd.next(3,6);
		int n = rnd.next(3, 18/m);
		genTest(i,m,n,rnd.next(5)==0);
	}
}

void genExample(){
	int m=5, n=5; init();
	flip(0,0,m,n); flip(0,2,m,n); flip(2,1,m,n);
	set< pair<int,int> > res = { {0,0}, {0,2}, {2,1} };
	printInput("tests/0.in",m,n);
	printOutput("tests/0.out",res,false);	
}

int main(){
	rnd.setSeed(123456789);
	system("mkdir tests");
	genExample();
	genSmall(1,8);
	for(int i=9; i<=18; ++i)
		genTest(i, rnd.next(1,MAX), rnd.next(1,MAX), rnd.next(5)==0);
	genTest(19,MAX,MAX,false);
	genTest(20,MAX,MAX,true);

}