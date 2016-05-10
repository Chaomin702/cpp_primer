#pragma once
#include <memory>
#include <string>
#include <iostream>
class str_vec{
public:
	str_vec() :element(nullptr), first_free(nullptr), cap(nullptr){}
	str_vec(const str_vec&);
	str_vec(str_vec&&);
	~str_vec();
	str_vec& operator=(const str_vec&);
	str_vec& operator=(str_vec&&);
	void push_back(const std::string&);
	void push_back(std::string&&);
	size_t size()const{ return first_free - element; }
	size_t capacity()const{ return cap - element; }
	std::string* begin()const { return element; }
	std::string* end()const{ return first_free; }
private:
	std::allocator<std::string> alloc;
	void chk_n_alloc(){
		if (capacity() == size())
			reallocate();
	}
	std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
	void reallocate();
	void free();
	std::string *element;
	std::string *first_free;
	std::string *cap;
};