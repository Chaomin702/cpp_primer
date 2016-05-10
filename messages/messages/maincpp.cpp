#include "message_folders.h"

int main(void){
	message m1("wang"), m2("chao"), m3("min");
	folder f;
	m1.save(f);
	m2.save(f);
	m3.save(f);
	folder ff = f;
	return 0;
}