#include <bits/stdc++.h>
using namespace std;

int a[105][105];

void flip(int x, int y){
	for(int i=x; i<x+3; ++i)
	for(int j=y; j<y+3; ++j)
		a[i][j] ^= 1;
}

int main(){
	int m, n; cin >> m >> n;	
	for(int i=1; i<=m; ++i)
	for(int j=1; j<=n; ++j)
		cin >> a[i][j];
		
	vector< pair<int,int> > result;
	for(int i=1; i<=m-2; ++i)
	for(int j=1; j<=n-2; ++j)
		if (a[i][j]==1){
			result.push_back( pair<int,int>(i,j) );
			flip(i,j);
		}
		
	for(int i=1; i<=m; ++i)
	for(int j=1; j<=n; ++j)
		if (a[i][j]) {
			cout << -1 << endl;
			return 0;
		}
		
	cout << result.size() << endl;
	for(int k=0; k<(int)result.size(); ++k)
		cout << result[k].first << " " << result[k].second << endl;

}