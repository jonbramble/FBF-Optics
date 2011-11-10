#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "../include/xmlparse.hpp"
#include <cstdio>

int main(int argc, char* argv[]) {
	
	int c;
	char* xmlfile;
	char* appname = argv[0];

	while((c = getopt(argc, argv, "x:")) != -1){			//taken from gnu example
		switch(c){
		case 'x':
			xmlfile = optarg;
			break;
		default:
			fprintf(stderr, "usage: %s [-x xml simulation file]\n", appname);
			exit(-1);
			
		}
	}

	xmlparse parser;
	parser(*xmlfile);

	
	
	return 0;
}


