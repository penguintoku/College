#ifndef HOUSE
#define HOUSE
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <deque>
#include <sstream>
class House{

	public:

	//Default constructor
	House();

	//Destructor
	~House();

	//Get energyData from a file.	
	void inputEnergyData(std::string fileName);	
	void inputApplianceData(std::string fileName);

	//Copy energyData from a deque
	void inputEnergyData(const std::deque<double>& d);

	//Get priceData from a file.
	void inputPriceData(std::string fileName);
	
	//Get priceData from a file, and repeat it for x days.
	void inputPriceData(std::string fileName, int numDays);

	//Calculate the High and Low costs of the day
	void calcMinMaxAvgPrice();
	
	//Calculate the High and Low costs of the day for rtp
	//void calcMinMaxAvgPriceRTP();

	//Calculate the avg demand for a 7 day period.
	void calcAvgDemand();
	
	//Print energyData to cout.
	void outputEnergyData();	

	//Print priceData to cout.
	void outputPriceData();

	//Print Total cost for the house. Requires having called
	//calcPrice() before hand.
	void printCost();

	//Display House information for debugging.
	void displayInfo();

	//Calculate Price Data based on consumption
	void calcPrice();
	
	//Print energyData to an out file.
	void outFileEnergyData(std::string fileName);

	//Gets the name of the house.
	std::string getName();
	
	//Gets the cost for the house.
	double getCost();

	//Sets the name of the house.
	void setName(std::string n);

	//Checks if house has energy data.
	bool checkEnergy();

	//Checks if house has price data.
	bool checkPrice();

	//Charge the battery for one hour using charge rate
	double chargeBattery(double chargeRate);

	//Discharge the battery for one hour.
	double dischargeBattery(double dischargeRate);
	
	//Perform the battery algorithm for the given number of days
	void batteryBehavior();
	

	//Data Members
	std::deque<double> * applianceData;
	std::deque<double> * energyData;
	std::vector<double> * priceData;
	//std::vector<double> * RTPminPrice;
	//double RTPminPrice[56];
	//std::vector<double> * RTPmaxPrice;
	//Battery Data members
	double maxCost;
	double minCost;
	double xMax;
	double maxCapacity;
	double avgDemand;
	double avgCost;
	double capacity;	
	private:

	double batteryCap;
	std::string name;
	double cost;
	bool energy;
	bool price;
	//bool rtp;
};

#endif //HOUSE
