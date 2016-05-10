#include "str_vec.h"
void str_vec::reallocate(){
	auto new_capacity = size() ? 2 * size() : 1;
	auto src = alloc.allocate(new_capacity);
	//auto b = element, s = src;
	//for (size_t i = 0; i != size(); ++i){
	//	alloc.construct(s++, std::move(*(b++)));
	//}
	//free();
	//element = src;
	//first_free = s;
	//cap = src + new_capacity;
	auto last = std::uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), src);
	free();
	element = src;
	first_free = last;
	cap = element + new_capacity;
}
void str_vec::push_back(const std::string& s){
	chk_n_alloc();
	alloc.construct(first_free++, s);
}
void str_vec::push_back(std::string&& s){
	chk_n_alloc();
	alloc.construct(first_free++, std::move(s));
}
std::pair<std::string*, std::string*> str_vec::alloc_n_copy(const std::string *b, const std::string *e){
	auto data_size = e - b;
	auto src = alloc.allocate(data_size);
	return{ src, std::uninitialized_copy(b, e, src)};
}
str_vec::str_vec(const str_vec& s){
	auto data = alloc_n_copy(s.begin(), s.end());
	element = data.first;
	first_free = cap = data.second;
	std::cout << "copy constructor" << std::endl;
}
str_vec::str_vec(str_vec&& s) :element(s.element), first_free(s.first_free), cap(s.cap){
	s.element = s.first_free = s.cap = nullptr;
	std::cout << "move constructor" << std::endl;
}
str_vec::~str_vec(){
	free();
}
void str_vec::free(){
	auto s = first_free;
	while (s != element){
		alloc.destroy(--s);
	}
	alloc.deallocate(element, capacity());
}
str_vec& str_vec::operator=(const str_vec& s){
	auto data = alloc_n_copy(s.begin(), s.end());
	free();
	element = data.first;
	first_free = cap = data.second;
	std::cout << "copy assignment" << std::endl;
	return *this;
}
str_vec& str_vec::operator=(str_vec&& s){
	if (this != &s){
		free();
		element = s.element;
		first_free = s.first_free;
		cap = s.cap;
		s.element = s.first_free = s.cap = nullptr;
	}
	std::cout << "move assignment" << std::endl;
	return *this;
}