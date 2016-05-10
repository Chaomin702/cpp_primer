#include <iostream>
#include "strblob.h"
using namespace std;
int main(){
	StrBlob s = { "wang", "chao", "min" };
	s.push_back("haha");
	s.pop_back();
	for (auto it = s.begin(); it != s.end(); ++it){
		cout << it.dref() << endl;
	}
	const StrBlob ss = { "who", "are", "you", "?" };
	for (auto it = ss.begin(); it != ss.end(); ++it){
		cout << it.dref() << endl;
	}
	return 0;
}