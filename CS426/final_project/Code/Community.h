#ifndef COMMUNITY
#define COMMUNITY
#include "House.h"
#include <list>
class Community{


	public:
		//Default Constructor
		Community();

		//Destructor
		~Community();

		//Add a house to the community
		void add(House& h);
		
		//Add a number of houses to the community.
		void addHouses(int numHouses);

		//Set Energy Data to a number of houses
		//From a file.
		void setEnergyData(int numHouses, std::string fileName);

		//Set Price data to  a number of houses 
		//From a file
		void setPriceData(int numHouses, std::string fileName, int numDays);

		//Assign the battery Algorithm to a number of houses
		void assignBattery(int numHouses);

		//Get the aggregate community cost
		void getCost();

		//Output a list of Houses in the community
		void showCommunity();

		//Create the aggregate data and store it.
		void energyData();		

		//Print out the aggregate community data.
		void printCData();

		//Print comData to an out file.
		void outEnergyData(std::string fileName);

		double totalCost;	
		std::list<House> * houseList;
		std::list<House>::iterator stratRov;

	private:
		std::deque<double> * comData;
};

#endif //COMMUNITY
