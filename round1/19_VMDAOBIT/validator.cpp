#include "../../lib/testlib.h"

int main(){
	registerValidation();
	int m = inf.readInt(3,100,"m");
	inf.readSpace();
	int n = inf.readInt(3,100,"n");
	inf.readEoln();
	for(int i=0; i<m; ++i){
		for(int j=0; j<n; ++j){
			inf.readInt(0,1);		
			if (j+1==n)
				inf.readEoln();
			else
				inf.readSpace();
		}		
	}
	inf.readEof();
}