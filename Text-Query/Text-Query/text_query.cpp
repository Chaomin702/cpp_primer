#include "text_query.h"
text_query::text_query(std::ifstream& is) :file(std::make_shared<std::vector<std::string >>()){
	std::string line;
	while (std::getline(is,line)){
		file->push_back(line);
		line_no n = file->size() - 1;
		std::stringstream ss(line);
		std::string word;
		while (ss >> word){
			auto &sptr = wm[word];
			if (!sptr){
				sptr.reset(new std::set<line_no>());
			}
			sptr->insert(n);
		}
	}
}

query_result text_query::query(const std::string& s)const{
	static std::shared_ptr<std::set<line_no>> no_line(new std::set<line_no>);
	auto it = wm.find(s);
	if (it != wm.end()){
		return query_result(s, file, it->second);
	}
	else{
		return query_result(s, file, no_line);
	}
}

std::ostream&  print(std::ostream& os, const query_result &qr){
	os << qr.query << " occurs " << qr.line_no_set->size() << " " << std::endl;
	for (auto num : *qr.line_no_set)
		os << "\t(line " << num + 1 << ") "
		<< *(qr.file->begin() + num) << std::endl;
	return os;
}