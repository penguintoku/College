#include "Community.h"
using namespace std;
#include <assert.h>
//Default constructor
Community::Community(){

	houseList = new list<House>;
	comData = new deque<double>;
	totalCost = 0;
}
Community::~Community(){

	delete houseList;
	delete comData;
}
//Adds a house to the community
void Community::add(House& h){

	houseList->push_front(h);

}

void Community::addHouses(int numHouses){
	int houseNum = 0;
	for(int i = 0; i < numHouses; i++)
	{
		House * temp =  new House();
		houseNum = houseList->size() + 1;
		temp->setName(to_string(houseNum));
		houseList->push_back(*temp);
	}

	stratRov = houseList->begin();
}

//Set Energy Data for a number of houses.
void Community::setEnergyData(int numHouses, string fileName){

	if(numHouses > 0)
	{
	cout << "Assigning " << fileName << " to " << numHouses << " houses." << endl;

	//Get to proper spot in list.
	auto rover = houseList->begin();
	while(rover->checkEnergy())
	{
		rover++;
	}		

	if((unsigned int)numHouses > houseList->size())
	{
		cerr << "Number of Houses in community is not enough to " <<
		"accomadate setEnergyData() parameter." << endl;
	}
	else
	{

		
		for(int i = 0;(rover != houseList->end()) && (i < numHouses); i++)
		{
		
					rover->inputEnergyData(fileName);	
					rover++;
		}
		if(rover == houseList->end())
		{
			cerr << "All houses have been assigned " <<
		"energy data. " << endl;
		}
	}
	}
}

//Set Price Data for a number of houses.
void Community::setPriceData(int numHouses, string fileName, int numDays){


	if(numHouses > 0)
	{

	cout << "Assigning " << fileName << " to " << numHouses << " houses for " << numDays << " days." << endl;
	

	//Get to proper spot in list.
	auto rover = houseList->begin();
	while(rover->checkPrice())
	{
		rover++;
	}		
	

	if((unsigned int)numHouses > houseList->size())
	{
		cerr << "Number of Houses in community is not enough to " <<
		"accomadate setPrieData() parameter." << endl;
	}
	else
	{

		if(numDays == 0)
		{
			for(int i = 0;(rover != houseList->end()) && (i < numHouses); i++)
			{
				rover->inputPriceData(fileName);	
				rover++;
			}


		}	
		else
		{
			for(int i = 0;(rover != houseList->end()) && (i < numHouses); i++)
			{
				rover->inputPriceData(fileName, numDays);	
				rover++;
			}
		}


		if(rover == houseList->end())
		{
			cerr << "All houses have been assigned " <<
		"Price data. " << endl;
		}
		
	}
	}
}

//Assign the battery strategy to a number of houses.
void Community::assignBattery(int numHouses){

	if(numHouses > 0)
	{
		cout << "Assigning batteries to " << numHouses << " houses." << endl;
		
	
		if((unsigned int)numHouses > houseList->size())
		{
			cerr << "Not enough houses in community to assign battery strategy to. Exiting. " << endl;
			exit(0);
		}
	
		for(int i = 0; stratRov != houseList->end() && i < numHouses; i++, stratRov++)
		{
			stratRov->batteryBehavior();
		}
	
		if(stratRov == houseList->end())
		{
			cout << "All houses have been assigned a strategy. " << endl;
		}
	}

}

//Get the aggregate cost
void Community::getCost(){

	for(auto rover = houseList->begin(); rover != houseList->end(); rover++)
	{
		rover->calcPrice();
		totalCost += rover->getCost();
		//rover->outputPriceData();
		//cout<<"rover house cost"<< rover->getCost()<<endl;
		//cout<<"totalCost"<< totalCost<<endl;

	}

}
//Prints out a list of all the houses names in the list.
void Community::showCommunity(){

	for(auto rover = houseList->begin(); rover != houseList->end(); rover++)
	{
		cout << rover->getName() << endl;
	}

}

//Calculates the aggregate data of all homes in the community.
void Community::energyData(){

	deque<double> *temp = new deque<double>;
	int i= 0;
	auto tRover = temp->begin();
	//Cycle through the list of houses
	for(auto hRover = houseList->begin(); hRover != houseList->end(); hRover++)
	{

		//Set the initial size of temp to whatever length the first house is.
		if(i == 0)
		{
			temp->resize(hRover->energyData->size());
			i++;
			
		}

		tRover = temp->begin();
		assert(hRover->energyData->size() == temp->size());

		//Cycle through each houses energy vector,
		//adding to the communitys data vector.
		for(auto eRover = hRover->energyData->begin(); eRover != hRover->energyData->end(); eRover++)
		{
			*tRover = *tRover + *eRover;
			tRover++;
		}
		i++;
	}
	//Put the results into the comData vector (community data member)
	comData->resize(temp->size());
	tRover = comData->begin();	
	for(auto rover = temp->begin(); rover != temp->end(); rover++)
	{
		*tRover = *rover;
		tRover++;
	}
	delete temp;
}

//Print out the aggregate community data.
void Community::printCData(){
	int i = 0;
	for(auto rover = comData->begin(); rover != comData->end(); rover++)
	{
		cout <<	"Hour " << i << ": " << *rover << " kw" << endl;
		i++;
	}
}


//Print comData to a file
void Community::outEnergyData(string fileName){
	this->energyData();
	this->getCost();
        ofstream outFile;
        outFile.open(fileName, ios::out);
        if(!outFile.good())
        {
                cerr << "Error opening out file." << endl;
        }
        else
        {
        double sum=0;

        for(auto rover = comData->begin(); rover != comData->end(); rover++)
		{
			sum+=*rover;
		}
                //set up first line
				outFile << "Total Price: $" << totalCost << endl;
				outFile << "Total Energy: " << sum << endl;
                outFile << "Hour, " << "Consumption kw" << endl;

                //Loop through file writing energy data on seperate lines.
                int i = 0;
		for(auto rover = comData->begin(); rover != comData->end(); rover++)
		{
			outFile << i << ", " << *rover << endl;
			i++;
		}
	}

}


