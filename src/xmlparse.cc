#include "../include/xmlparse.hpp"

xmlparse::xmlparse(char *xmlfile) {

	TiXmlDocument doc(xmlfile);
	bool loaded = doc.LoadFile();   //load the xml file into memory

	if(loaded) {
		// do check on file structure
		// logic for parsing simulation file
		// run simulation and write results to data file

		TiXmlHandle docHandle(&doc);
		TiXmlElement *job, *input;
		TiXmlHandle hRoot(0);
		TiXmlHandle iRoot(0);
		TiXmlHandle jRoot(0);
		
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
				cout << "Parsing data file...." << endl;		// must do error handling on missing parameters
				iRoot = TiXmlHandle(input);
				TiXmlElement *sim, *layer_element;
				
				const char *read;
				int N;
				double n_entry, n_exit;
				int layer_count = 0;
				std::vector<Isolayer> vlayers(0);  // dont know size of array

				cout << "Starting Simulation..." << endl;

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
					jRoot=TiXmlHandle(layer_element);
					double epsreal, epsimag, d;
		
					cout << "Processing layer " << layer_count+1 << endl;
					const char* type = layer_element->FirstAttribute()->Value();					
					
					Isolayer a_layer; //if isolayer

					read = jRoot.FirstChild("name").Element()->GetText();
					cout << "Layer Name: "<< read << endl;
					
					read = jRoot.FirstChild("epsreal").Element()->GetText();
					epsreal= atof(read);
					read = jRoot.FirstChild("epsimag").Element()->GetText();
					epsimag= atof(read);
					a_layer.seteps(complex<double>(epsreal,epsimag));

					read = jRoot.FirstChild("d").Element()->GetText();
					d = atof(read);
					a_layer.setd(d);

					vlayers.push_back(a_layer);

					layer_count +=1;
				}

				Spr *experiment;

				experiment = new Spr(N);
				boost::numeric::ublas::vector<double> result(N);

				//cout << vlayers.size() << endl;

				experiment->setnlayers(layer_count);
				experiment->setlayers(vlayers);

				experiment->setstartangle(0); 
				experiment->setendangle(90);
				experiment->setna(n_entry);
				experiment->setnf(n_exit);
				experiment->setlambda(633e-9); //not implemented yet

				experiment->run();  //error handling required
				experiment->getdata(result);
				//cout << result << endl;
				
				cout << "Simulation Complete" << endl;

			}
		}		
	}

	else {
		fprintf(stderr, "XML data file not loaded\n");
	}


}


