/*
 * main.cc
 * Copyright (C) Jonathan Bramble 2011
 * 
FBF-Optics is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gtk-testrun is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "../include/xmlparse.hpp"
#include <cstdio>

/// Application entry point
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
	
	
	xmlparse *parser;
	parser = new xmlparse(xmlfile);
	
	return 0;
}


