#ifndef XMLPARSE_H_
#define XMLPARSE_H_

#include <tinyxml.h>
#include "../include/spr.hpp"
#include "../include/isolayer.hpp"


using namespace boost::numeric::ublas;
using namespace std;

class xmlparse {
	
	public:
	xmlparse(char *xmlfile);
	~xmlparse();
	
	private:
	Spr *experiment;
	TiXmlDocument *doc;
	void sprcase(TiXmlElement *input);
	void parseloaded();
};





#endif
