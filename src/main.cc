#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "../include/spr.hpp"
#include "../include/isolayer.hpp"
#include <cstdio>
#include <tinyxml.h>

using namespace boost::numeric::ublas;

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
		TiXmlHandle iRoot(0);
		
		std::string str_spr = "spr";		//different modes and experiments
		std::string str_ewe = "ewe";
		std::string str_sim = "simulation";
		// how do we handle simulations around loops
		
		job = docHandle.FirstChild("document").Element();		// must start with document
		if(job)
		{
			cout << "Loaded Document Element" << endl << endl;
			hRoot=TiXmlHandle(job);
		}

		
		input = hRoot.FirstChild("simulation").FirstChild("type").Element();		
		if(input)
		{
			if(input->FirstAttribute()->Name() == str_sim && input->FirstAttribute()->Value() == str_spr)
			{	
				cout << "SPR Simulation Mode" << endl;			// we know it is this mode
				cout << "Parsing data file...." << endl;
				iRoot = TiXmlHandle(input);
				TiXmlElement *sim, *layer_element;
				
				const char *read;
				int N;
				double n_entry, n_exit;
				int layer_count = 1;

				sim = iRoot.FirstChild("data_points").Element();
				read = sim->GetText();	
				N = atoi(read);
				cout << "Using " << N << " data points" << endl;

				sim = iRoot.FirstChild("n_entry").Element();
				read = sim->GetText();	
				n_entry = atof(read);
				cout << "Entry Media Index: " << n_entry << endl;

				sim = iRoot.FirstChild("n_exit").Element();
				read = sim->GetText();	
				n_exit= atof(read);
				cout << "Exit Media Index: " << n_exit << endl;

				layer_element = iRoot.FirstChild("layer").Element();
				for(layer_element;layer_element;layer_element=layer_element->NextSiblingElement())
				{
					cout << "Processing layer " << layer_count << endl;
					const char* type = layer_element->FirstAttribute()->Value();					

					Isolayer a_layer;

					const char* name = layer_element.FirstChild("name").Element()->GetText();
					cout << name << endl;
					layer_element.FirstChild("epsreal").Element();
					layer_element.FirstChild("epsimag").Element();
					layer_element.FirstChild("d").Element();
					
			

					layer_count +=1;
				}

				cout << "Starting Simulation..." << endl;

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
				experiment.setendangle(80); //not implemented yet
				experiment.setna(n_entry);
				experiment.setnf(n_exit);
				experiment.setlambda(633e-9); //not implemented yet

				experiment.run();  //error handling required
				experiment.getdata(result);
				
				cout << "Simulation Complete" << endl;

			}
		}		
	}

	else {
		fprintf(stderr, "XML data file not loaded\n", appname);
	}
	return 0;
}


