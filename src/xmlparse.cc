/*
 * xmlparse.cc
 * Copyright (C) Jonathan Bramble 2011
 * 
FBF-Optics is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FBF-Optics is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../include/xmlparse.hpp"

xmlparse::~xmlparse(){
	delete spr_simulation;
	delete ewe_simulation;
	delete doc;
}

void xmlparse::ewecase(TiXmlElement *input)
{
	cout << "EWE Simulation Mode" << endl;			// we know it is this mode
	cout << "Parsing data file...." << endl;		// must do error handling on missing parameters

	cout << "Simulation Complete" << endl;
}

void xmlparse::sprcase(TiXmlElement *input) 
{
	cout << "SPR Simulation Mode" << endl;			// we know it is this mode
	cout << "Parsing data file...." << endl;		// must do error handling on missing parameters

	TiXmlHandle iRoot(0);
	TiXmlHandle jRoot(0);

	iRoot = TiXmlHandle(input);
	TiXmlElement *sim, *layer_element;
			
	const char *read;
	int N;
	double n_entry, n_exit, lambda, start_angle, end_angle;
	int layer_count = 0;
	std::vector<Layer> vlayers(0);  // dont know size of array

	cout << "Starting Simulation..." << endl;
	
	//seg fault if these are not present
	//datapoints
	read = iRoot.FirstChild("data_points").Element()->GetText();
	N = atoi(read);
	cout << "Using " << N << " data points" << endl;

	read = iRoot.FirstChild("start_angle").Element()->GetText();
	start_angle = atof(read);
	cout << "Starting Angle: " << start_angle << endl;

	read = iRoot.FirstChild("end_angle").Element()->GetText();
	end_angle = atof(read);
	cout << "End Angle: " << end_angle << endl;

	read = iRoot.FirstChild("n_entry").Element()->GetText();	
	n_entry = atof(read);
	cout << "Entry Media Index: " << n_entry << endl;

	read = iRoot.FirstChild("n_exit").Element()->GetText();	
	n_exit= atof(read);
	cout << "Exit Media Index: " << n_exit << endl;

	read = iRoot.FirstChild("lambda").Element()->GetText();
	lambda = atof(read);

	layer_element = iRoot.FirstChild("layer").Element();
	for(layer_element;layer_element;layer_element=layer_element->NextSiblingElement())
	{
		jRoot=TiXmlHandle(layer_element);
		double epsreal, epsimag, d;
		
		cout << "Processing layer " << layer_count+1 << endl;
		const char* type = layer_element->FirstAttribute()->Value();					
					
		Layer a_layer; //if isolayer

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

	spr_simulation = new Spr(N);
	boost::numeric::ublas::vector<double> result(N);

	spr_simulation->setnlayers(layer_count);
	spr_simulation->setlayers(vlayers);

	spr_simulation->setstartangle(start_angle); 
	spr_simulation->setendangle(end_angle);
	spr_simulation->setna(n_entry);
	spr_simulation->setnf(n_exit);
	spr_simulation->setlambda(lambda);

	spr_simulation->run();  //more error handling required
	spr_simulation->getdata(result);
	//cout << result << endl;
				
	cout << "Simulation Complete" << endl;
		
}

void xmlparse::parseloaded()
{
	// do check on file structure
	// logic for parsing simulation file
	// run simulation and write results to data file

	TiXmlHandle docHandle(doc);
	TiXmlElement *job, *input;
	TiXmlHandle hRoot(0);
		
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
			sprcase(input);
		}
		else if(input->FirstAttribute()->Name() == str_sim && input->FirstAttribute()->Value() == str_ewe)
		{
			ewecase(input);
		}
	}		
}

xmlparse::xmlparse(char *xmlfile) {
	doc = new TiXmlDocument(xmlfile);
	bool loaded = doc->LoadFile();   //load the xml file into memory

	if(loaded) {
		parseloaded();
	}
	else {
		fprintf(stderr, "XML data file not loaded\n");
	}

}


