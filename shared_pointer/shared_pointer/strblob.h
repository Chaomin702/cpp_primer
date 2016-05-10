#pragma once
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
class StrBlobPtr;	//前置声明只能作为指针或引用，不可定义类的对象，也不可调用类的方法
class StrBlob{
public:
	friend class StrBlobPtr;
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const{ return data->size(); }
	bool empty() const{ return data->empty(); }
	void push_back(const std::string &t){
		data->push_back(t);
	}
	void pop_back();
	std::string& front();
	const std::string& front()const;
	std::string& back();
	const std::string& back()const;
	StrBlobPtr begin()const;
	StrBlobPtr end()const;
private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i, const std::string &msg)const;
};
class StrBlobPtr{
public:
	friend bool operator==(const StrBlobPtr& lhs, const StrBlobPtr& rhs);
	typedef std::vector<std::string>::size_type size_type; 
	StrBlobPtr() :curr(0){}
	StrBlobPtr(StrBlob &a, size_type sz = 0);
	StrBlobPtr(const StrBlob &a, size_type sz = 0);
	StrBlobPtr& operator ++();
	std::string& dref();
private:
	size_type curr;
	std::weak_ptr<std::vector<std::string>> wptr;
	std::shared_ptr<std::vector<std::string>> check(size_type i, const std::string &msg)const;
};

bool operator==(const StrBlobPtr& lhs, const StrBlobPtr& rhs);
bool operator!=(const StrBlobPtr& lhs, const StrBlobPtr& rhs);