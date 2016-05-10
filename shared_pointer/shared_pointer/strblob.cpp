#include "strblob.h"
StrBlob::StrBlob() :data(std::make_shared<std::vector<std::string>>()){}
StrBlob::StrBlob(std::initializer_list<std::string> il) : 
	data(std::make_shared<std::vector<std::string>>(il)){}
void StrBlob::check(size_type i, const std::string &msg)const{
	if (i >= data->size())
		throw std::out_of_range(msg);
}
void StrBlob::pop_back(){
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}
std::string& StrBlob::front(){
	check(0, "front on empty StrBlob");
	return data->front();
}
const std::string& StrBlob::front()const{
	check(0, "front on empty StrBlob");
	return data->front();
}
std::string& StrBlob::back(){
	check(0, "back on empty StrBlob");
	return data->back();
}
const std::string& StrBlob::back()const{
	check(0, "back on empty StrBlob");
	return data->back();
}
StrBlobPtr StrBlob::begin()const{ return StrBlobPtr(*this, 0); }
StrBlobPtr StrBlob::end()const{ return StrBlobPtr(*this, data->size()); }


StrBlobPtr::StrBlobPtr(StrBlob &a, size_type sz) :wptr(a.data), curr(sz){}
StrBlobPtr::StrBlobPtr(const StrBlob &a, size_type sz) : wptr(a.data), curr(sz){}
std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(size_type i, const std::string &msg)const{
	auto ret = wptr.lock();
	if (!ret)
		throw std::runtime_error("unbound StrBolbPtr");
	if (i >= ret->size())
		throw std::out_of_range(msg);
	return ret;
}

StrBlobPtr& StrBlobPtr::operator++(){
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}

std::string& StrBlobPtr::dref(){
	auto p = check(curr, "dereference past end");
	return (*p)[curr];
}
bool operator==(const StrBlobPtr& lhs, const StrBlobPtr& rhs){
	auto l = lhs.wptr.lock(), r = rhs.wptr.lock();
	if (l == r)
		return (!l || lhs.curr == rhs.curr);
	else
		return false;
}
bool operator!=(const StrBlobPtr& lhs, const StrBlobPtr& rhs){
	return !(lhs == rhs);
}