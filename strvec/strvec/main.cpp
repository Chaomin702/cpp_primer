#include "str_vec.h"

int main(){
	str_vec s;
	s.push_back("wang");
	s.push_back("chao");
	s.push_back("min");
	str_vec v(s);
	str_vec t(std::move(v));
	t = s;
	t= std::move(s);
	return 0;
}