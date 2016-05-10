#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
class folder;
class message{
public:
	friend class folder;
	explicit message(const std::string &str = "") :contents(str){}
	message(const message&);
	message& operator =(const message&);
	~message();
	void save(folder&);
	void remove(folder&);
private:
	std::string contents;
	std::set<folder*> folders;
	void add_to_folders();
	void remove_from_folders();
	void add_folder(folder& f){ folders.insert(&f); }
	void remove_folder(folder& f){ folders.erase(&f); }
};

class folder{
public:
	folder(){}
	folder(const folder&);
	folder& operator=(const folder&);
	~folder();
	void save_msg(message&);
	void remove_msg(message&);
private:
	std::set<message*> messages;
	void add_messages();
	void remove_messages();

};