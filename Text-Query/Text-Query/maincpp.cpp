#include "text_query.h"
using namespace std;
int main(void){
	std::ifstream infile("abc.txt", std::ifstream::in);
	text_query tq(infile);
	while (true){
		cout << "enter word to look for, or q to quite: ";
		string s;
		if (!(cin >> s) || s == "q") break;
		print(cout, tq.query(s)) << endl;
	}
}