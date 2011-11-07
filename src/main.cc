#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "../include/spr.hpp"
#include "../include/isolayer.hpp"
#include <cstdio>
#include <tinyxml.h>

using namespace boost::numeric::ublas;


void spr_simulation(){

	const int N = 5;
	int nlayers = 1;

	boost::numeric::ublas::vector<double> result(N);
	std::vector<Isolayer> vlayers(nlayers);

	Isolayer gold, SAM;
	gold.seteps(complex<double>(-12.0,0.8));
	gold.setd(49e-9);

	//SAM.seteps(complex<double>(2.10,0));
	//SAM.setd(2e-9);
	
	vlayers.push_back(gold);
	//vlayers.push_back(SAM);

	Spr experiment(N);

	experiment.setnlayers(nlayers);
	experiment.setlayers(vlayers);

	experiment.setstartangle(10); //not implemented yet
	experiment.setendangle(80);
	experiment.setna(1.85);
	experiment.setnf(1.33);
	experiment.setlambda(633e-9);

	experiment.run();  //error handling required
	experiment.getdata(result);
	
	//cout << result << endl;
}

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

	TiXmlDocument doc( xmlfile );
	bool loaded = doc.LoadFile();   //load the xml file into memory

	if(loaded) {
		// do check on file structure
		// logic for parsing simulation file
		// run simulation and write results to data file

		TiXmlHandle docHandle(&doc);
		TiXmlElement *job, *input;
		TiXmlHandle hRoot(0);
		//TiXmlText *type;
		
		job = docHandle.FirstChild("document").Element();
		if(job)
		{
			cout << "loaded document element" << endl;
			hRoot=TiXmlHandle(job);
		}
		//
		
		input = hRoot.FirstChild("simulation").FirstChild("type").Element();
		if(input)
		{
			cout << "loaded child element" << endl;	
			// we now know we
			
			cout << input->FirstAttribute()->Name() << endl;
			cout << input->FirstAttribute()->Value() << endl;
			cout << input->FirstAttribute()->ValueStr() << endl;
		}
		

		//spr_simulation();

		
	}

	else {
		fprintf(stderr, "XML data file not loaded\n", appname);
	}
	return 0;
}


