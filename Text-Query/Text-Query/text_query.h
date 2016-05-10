#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <memory>
#include <algorithm>
class query_result;
class text_query{
public:
	friend class query_result;
	using line_no = std::vector<std::string>::size_type;
	text_query(std::ifstream&);
	query_result query(const std::string&)const;
private:
	std::shared_ptr<std::vector<std::string>> file;
	std::map < std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class query_result{
public:
	friend std::ostream& print(std::ostream& os, const query_result &qr);  //友元声明不需要指定域？
	query_result(const std::string &q, std::shared_ptr<std::vector<std::string>> f, std::shared_ptr<std::set<text_query::line_no>> l) :
		query(q), file(f), line_no_set(l){}
private:
	std::string query;
	std::shared_ptr<std::vector<std::string>> file;
	std::shared_ptr<std::set<text_query::line_no>> line_no_set;
};
std::ostream& print(std::ostream& os, const query_result &qr);