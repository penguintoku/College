#include "House.h"
#include "Community.h"
#include <cstdlib>
#include <cstring>
#include <sstream>
using namespace std;

void readConfigFile();
Community *a1 = new Community();

int main(){

/*	House * a = new House();
	a->inputEnergyData("18.csv");
	a->inputPriceData("rtp.csv");
	a->calcPrice();	
	cout << "The cost is : $" << a->getCost() << endl;
*/	readConfigFile();
	//a1->getCost();
	a1->outEnergyData("zzz.csv");	
	delete a1;
	return 0;
}

	/*
	*	Reads a config File in the following form: Number of Houses is the first line, followed
	*	by x lines stating how many houses to assign , and which energy data plan. The end
	*	of energy data reading is signaled by a "!", then x lines of #of houses followed with which
	*	price plan file, which is ended with "@". Next is how many houses to assign the battery strategy, ended
	*	with a "#", and next is how many houses to assign appliance strategy, ended with "$".
	*/
void readConfigFile(){
	

	//Initialize needed streams and variables.
	string temp, line, excl = "!", at = "@", pound = "#", dollar = "$";
	int energyBool=0, priceBool = 0, batteryBool = 0, applianceBool = 0, houseNum = 0, tempHouseNum = 0, i = 0, numDays = 0;
	stringstream ss;
	ifstream inFile("config.txt");
	
	//Assign the number of houses requested	
	getline(inFile, line);
	houseNum=atoi(line.c_str());
	cout << "Number of Houses: " << houseNum << endl;
	a1->addHouses(houseNum);

	while(getline(inFile, line))
        {
		if(!energyBool)
		{
			//if not, check for symbol
			if(line == excl)
			{
				cout << "EnergyBool val set to 1." << endl;
				energyBool = 1;
			}
			//if symbol hasnt been read, do accordingly.
			else
			{	//use a stringstream to parse commands
				ss << line;
				i = 0;
				while(ss.good())
				{
					//First part of line: #of houses
					if(i ==	0)
					ss >> tempHouseNum;
 
					//Second part of line: Energy Data fileName
					else if(i == 1)
					{
						ss >> temp;
						break;
					}
					i++;
				}	
				//Clear the stream and call the energy function.
				ss.clear();
				a1->setEnergyData(tempHouseNum, temp);
			}
		}
		else if(!priceBool)
		{
                        //if not, check for symbol
                        if(line == at)
                        {
                        
				cout << "PriceBool val set to 1." << endl;
				priceBool = 1;
                        }
			//if symbol hasnt been read, do accordingly.
			else
			{
				ss << line;
				i = 0;
				while(ss.good())
				{
					//First part of line: # of houses
					if(i ==	0)
						ss >> tempHouseNum;
					
					//Second part of line: Price Data fileName
					else if(i == 1)
					{
						ss >> temp;
			
					}

					if(temp == "rtp.csv")
					{
						cerr << "Num days not needed, breaking" << endl;
						break;
					}
					//Third part of line: num Days to assign price data
					else if(i == 2)
					{
						ss >> numDays;			
						break;
					}
					i++;
				}	
				if(temp == "rtp.csv"){
				a1->setPriceData(tempHouseNum, temp, 0);
				//reset temp
				ss.clear();
				temp="null";
				}
				else
				{
					ss.clear();
					a1->setPriceData(tempHouseNum, temp, numDays);			
				}
			}
		}
		else if(!batteryBool)
		{
			//if not, check for symbol
			if(line == pound)
			{
				cout << "BatteryBool val set to 1." << endl;
				batteryBool = 1;
			}
			//If symbol hasnt been read, proceed with applying strategies.
			else
			{
				ss << line;
				cout << "Assigning the battery strategy to " << line << " houses, for " <<
				numDays << " days. " << endl;
				a1->assignBattery(atoi(line.c_str()));
				ss.clear();

			}
			
		}
		else if(!applianceBool)
		{
			//if not, check for symbol
			if(line == dollar)
			{
				cout << "ApplianceBool val set to 1." << endl;
				applianceBool = 1;
			}
			
		}
		
	}
	


}
