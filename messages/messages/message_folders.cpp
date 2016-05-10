#include "message_folders.h"
void message::save(folder& f){
	folders.insert(&f);
	f.save_msg(*this);
}

void message::remove(folder& f){
	folders.erase(&f);
	f.remove_msg(*this);
}
void message::add_to_folders(){
	for (auto i : folders)
		i->save_msg(*this);
}
void message::remove_from_folders(){
	for (auto i : folders)
		i->remove_msg(*this);
}
message::message(const message& m) :contents(m.contents), folders(m.folders){
	add_to_folders();
}
message::~message(){
	remove_from_folders();
}
message& message::operator=(const message& m){
	remove_from_folders();
	contents = m.contents;
	folders = m.folders;
	add_to_folders();
	return *this;
}

void folder::save_msg(message& m){
	messages.insert(&m);
}
void folder::remove_msg(message& m){
	messages.erase(&m);
}
void folder::add_messages(){
	for (auto i : messages)
		i->add_folder(*this);
}
void folder::remove_messages(){
	for (auto i : messages)
		i->remove_folder(*this);	
}
folder::folder(const folder& f) :messages(f.messages){
	add_messages();
}
folder::~folder(){
	remove_messages();
}
folder& folder::operator=(const folder& f){
	remove_messages();
	messages = f.messages;
	add_messages();
	return *this;
}