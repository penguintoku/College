#include "House.h"
using namespace std;

#define ELOSS		.80
#define SURCHARGE 	3
#define T 		1


//Default Constructor
House::House(){
	
	energyData = new deque<double>;
	priceData = new vector<double>;
	applianceData = new deque<double>;
	//RTPminPrice=new vector<double>;
	//RTPmaxPrice=new vector<double>;
	energy = false;
	price = false;
	maxCost = 0;
	minCost = 0;
	xMax = 0;
	maxCapacity = 0;
	avgDemand = 0;
	avgCost = 0;
	capacity = 0;
	//rtp=false;

}

House::~House(){

	delete energyData;
	delete priceData;
	//delete RTPminPrice;
	//delete RTPmaxPrice;
}
//Input Energy Consumption Data from a file.
void House::inputEnergyData(string fileName){
	int i = 0;
//	cout << "-- inputEnergyData function call --" << endl;
	//Initialize needed variables.
	int firstTime = 0;
	double sum = 0;
	string kw, hour, tempHour, line;
	size_t hPosit = 0, dPosit = 0;	
	ifstream inFile(fileName);
	//Skip the first line, since it contains meaningless data.
	getline(inFile, line);
	//Loop through file until not good.
	//i < 80640 for 56 days.
	//i < 10140 for 7 days.
	while(inFile.good() && i < 80640)
	{
		if(getline(inFile, line))
		{
			//Get position of energy data
			dPosit = line.find(",");
			
			//Get the current hour being worked with.
			hPosit = line.find(":");
			tempHour = line.substr(hPosit-2, 2);
			//Option 1: first run through. Store hour which will be
			//compared against tempHour each line through.
			if(!firstTime)
			{
				hour = line.substr(hPosit-2, 2);
				firstTime++;
				kw = line.substr(dPosit+1, 11);
			
				//Add energy data to sum.
				const char * temp;
				temp = kw.c_str();
				sum+= atof(temp);
			}
			//Option 2: working with same hour, add data to sum.
			else if(hour.compare(tempHour) == 0)
			{
				kw = line.substr(dPosit+1, 11);
			
                                const char * temp;
                                temp = kw.c_str();
                                sum+= atof(temp);
			}
			//Option 3: Change in hour- Store sum into next spot of 
			//energyData vector data member, reset sum, and increment hour.
			else if(hour.compare(tempHour) != 0)
			{
				sum = sum/60;
				energyData->push_front(sum);
				sum = 0;
				hour = tempHour;
			}
			
		}
		i++;

	}	

	inFile.close();
	energy = true;
	this->calcAvgDemand();
	//added
	//this->outputEnergyData();
}

void House::inputEnergyData(const std::deque<double>& d){

	*energyData = d;

}
//note for the RTP files since we don't need to loop call this one and not the other
void House::inputPriceData(string fileName){
	//char *comfile=(char *)(fileName.c_str());
	//if(strstr(comfile,"rtp.csv")!= NULL){
	//rtp=true;
	//}
//	cout << "--inputPriceData function call--" << endl;
	//Initialize variables and streams.
        ifstream inFile(fileName);
       	stringstream ss; 
	string line, data;
	size_t pos;
	//Skip the first line, since it contains meaningless data.
        getline(inFile, line);
	
        //Loop through file until not good.
        while(inFile.good())
        {
                if(getline(inFile, line))
                {
			pos = line.find(",") + 2;	
			data = line.substr(pos);
                        const char * temp;
			temp = data.c_str();
			priceData->push_back(atof(temp));
		
		}
	}
	//if(rtp){
	////calculate minmax prices and avgprice for rtp
	//}
	this->calcPrice();
	price = true;
}
/*	This function inputs price data from a file, and loops it to
*	be numDays long. It also calls the calcPrice and calcMinMaxPrice
*	functions at the end.
*/
void House::inputPriceData(string fileName, int numDays){

	this->inputPriceData(fileName);
	vector<double> tempData;
	tempData = *priceData;
	

	for(int i = 0; i < numDays-1; i++)
	{

		priceData->insert(priceData->end(), tempData.begin(), tempData.end());
	
	}

	this->calcPrice();
	this->calcMinMaxAvgPrice();
}

/*Compute min and max of price range*/
void House::calcMinMaxAvgPrice(){

	double tempMin = 1000;
	double tempMax=  0;
	double sum = 0;
	auto rover = priceData->begin();
	for(int i = 0; i < 24; i++)
	{
		if(*rover < tempMin)
			tempMin = *rover;
	
		else if(*rover > tempMax)
			tempMax = *rover;
		
		sum += *rover;
		rover++;
	}

	maxCost = tempMax;
	minCost = tempMin;
	avgCost = sum/24;
}
//calculate RTP min/max pricing
/*
void House::calcMinMaxAvgPriceRTP(){
double dailySum = 0;
	double hourlySum = 0;
	double dailymin=0;
	double dailymax=0;
	
	int i = 0;
	int j = 0;
	auto minRTP=RTPminPrice->begin();
	auto maxRTP=RTPmaxPrice->begin();
	// we will calculate avgCost based on first 7 days
	for(auto dRover = priceData->begin(); dRover!= priceData->end(); dRover += 24)
	{
		for(auto hRover = dRover; hRover != priceData->end() && j < 24; hRover++)
		{	if(j==0){
			dailymin=*hRover;
			dailymax=*hRover;
			}
			else{
			if(dailymin>*hRover){
			dailymin=*hRover;
			}
			else if(dailymax<*hRover){
			dailymax=*hRover;
			}
			}
			hourlySum += *hRover;
			j++;
		}
		(*RTPminPrice).push_back(dailymin);
		(*RTPmaxPrice).push_back(dailymax);
		cout<<"minprice: "<<dailymin<<endl;
		cout<<"maxprice: "<<dailymax<<endl;
		//minRTP++;
		//maxRTP++;
		j = 0;
		if(i<7){
		dailySum += hourlySum;
		}
		hourlySum = 0;
		i++;
	}
	cout<<"i: "<<i<<endl;
	avgCost=dailySum/7/24;
	cout<<"avgCost: "<<avgCost<<endl;
}
*/

//Calculate the avg demand for a 7 day period.
void House::calcAvgDemand(){

	double dailySum = 0;
	double hourlySum = 0;
	int i = 0;
	int j = 0;
	for(auto dRover = energyData->begin(); dRover!= energyData->end() && i < 7; dRover += 24)
	{
		for(auto hRover = dRover; hRover != energyData->end() && j < 24; hRover++)
		{
			hourlySum += *hRover;
			j++;
		}
		j = 0;
		dailySum += hourlySum;
		hourlySum = 0;
		i++;
	}
	
	avgDemand = dailySum/7/24;
	maxCapacity = avgDemand/2*24;
	xMax = maxCapacity/8;
	//changed
	//capacity = maxCapacity;
	//don't start with a charged battery
	capacity = 0;
}
//Print energy data to cout.
void House::outputEnergyData(){
int i = 0;
	ofstream outFile;
        outFile.open("houseenergy.csv", ios::out);
        if(!outFile.good())
        {
                cerr << "Error opening out file." << endl;
        }
        else
        {
	
	for(auto rover = energyData->begin(); rover != energyData->end(); rover++)
	{
		
		cout << "Hour " << i << ": " << *rover << " kw" << endl;
		i++;
		//print out to a file
		outFile <<*rover<<endl;
	
		}

}
}


//Print price data to cout.
void House::outputPriceData(){

	int i = 0;	
	
	for(auto rover = priceData->begin(); rover != priceData->end(); rover++)
	{
		
		cout << "Hour " << i << ": " << *rover << "$/kwH" << endl;
		i++;
	}
		

}

void House::printCost(){

	cout << "The total cost for " << name << " is: $" << cost << endl;

}

//Display house information.
void House::displayInfo(){
	
		cout << '\n' << endl;
		cout << "House " << this->getName() << endl;
                cout << "Max/min Cost amounts: " << this->maxCost << ", " <<
                this->minCost << endl;
                cout << "Average Cost per hour and avg demand: " << this->avgCost <<
                ", " << this->avgDemand << endl;
                cout << "Max Battery capacity and charging rate: " << this->maxCapacity <<
                ", " << this->xMax << endl;
                cout << "Current battery capacity : " << this->capacity << endl;
                cout << '\n' << '\n'  << endl;
}

//Calculate price per day based on consumption.
void House::calcPrice(){

	double 	sum = 0,
		pTemp = 0, 
		eTemp = 0,
		temp = 0;
	auto pRover = priceData->begin();
	auto eRover = energyData->begin();
	for(int i = 0; eRover != energyData->end() && pRover != priceData->end() ; i++)
	{
		//Store the price and energy values
		pTemp = *pRover;
		eTemp = *eRover;
		//Calculate the hourly cost and store the aggregate data
		temp = pTemp * eTemp;
		sum += temp;
		//Increment the rovers
		pRover++;
		eRover++;
		
	}
	cost = sum;

}


//Print energy data to a file.
void House::outFileEnergyData(string fileName){
	
	ofstream outFile;
	outFile.open(fileName, ios::out);
	if(!outFile.good())
	{
		cerr << "Error opening out file." << endl;
	}
	else
	{
		//set up first line
		outFile << "Hour, " << "Consumption kw/h" << endl;

		//Loop through file writing energy data on seperate lines.
		int i = 0;
        	for(auto rover = energyData->begin(); rover != energyData->end(); rover++)
        	{
			outFile << i << ", " << *rover << endl;
			i++;
		}
	}
}

string House::getName(){

	return name;
}

double House::getCost(){

	return cost;
}

void House::setName(string n){

	name = n;
}

bool House::checkEnergy(){

	if(energy)
		return true;
	else
		return false;
}

bool House::checkPrice(){
	
	if(price)
		return true;
	else
		return false;

}

//Charge the battery one hour.
double House::chargeBattery(double chargeRate){
		
	double tempCapacity = capacity;
	double totalChargeHour = 0;

//	cout << "-- in CHARGE battery function with a charge rate of: " << chargeRate << endl;
	if(chargeRate < 0){
	chargeRate = 0;
	}
	//Make sure charge rate is not above xMax
	else if(chargeRate > xMax)
	{
		chargeRate = xMax;
	}

	if(capacity < maxCapacity)
	{
		//right here
		if(chargeRate==xMax){
		//add 1/8 of maxCapacity
		capacity+=xMax;
		}
		else{
			capacity += chargeRate*ELOSS;
			//was capacity+=chargeRate; before
		}
		//end changes

		//Check to make sure capacity is less
		//than the maxCapacity.
		if(capacity > maxCapacity)
		capacity = maxCapacity;

		
	totalChargeHour = capacity - tempCapacity;
				
	}
	else
	{
		capacity = maxCapacity;
	}
//	cout << "leaving with a capacity of : " << capacity << endl;
	return totalChargeHour;

}

double House::dischargeBattery(double dischargeRate){

	double tempCapacity = capacity;
	double totalChargeHour = 0;
//	cout << "-- In DIScharge battery function with a discharge rate of :" << dischargeRate << endl;
	
	//Check to make sure discharge rate is appropriate.
	if(dischargeRate < 0)
	dischargeRate = 0;
	else if(dischargeRate > xMax)
	dischargeRate = xMax;	


	//Make sure capacity is above 0
	if(capacity > 0)
	{		// not discharging enough from battery! WHen we return this mount do the energy converison there! changeed
			//capacity -= dischargeRate*ELOSS;
			capacity -= dischargeRate;
		
		//Make sure capacity is above 0, and assign
		//Correct return value to totalChargeHour
		if(capacity < 0)
		{
			capacity = 0;
			totalChargeHour = tempCapacity;
		}
		else
		totalChargeHour = tempCapacity - capacity;
	
	}
	else
	capacity = 0;
	
//	cout << "leaving with a capacity of : " << capacity << endl;

	return totalChargeHour;
}

void House::batteryBehavior(){
	
	
	int length = energyData->size();
	double chargeAmount = 0;
	double chargeRate = 0, dischargeRate = 0;
	//cout <<"MAxcapacity: "<< maxCapacity<<endl;
	//cout<<"XMax: "<<xMax<<endl;
	int x=0;
	for(int i = 0; i < length; i++)			//right here
	{
		//Cases 1&2: price is low.
		if(priceData->at(i) <= avgCost)
		{
			//Case 1: price is low, and 
			//demand is low
			if(energyData->at(i) <= avgDemand)
			{	
				//greedily charge at max rate if inequality is true
				if((xMax*ELOSS*maxCost*T)-(xMax*minCost*T) > xMax*SURCHARGE)
				{
					chargeAmount = chargeBattery(xMax);
					//cout <<"Case 1: "<<xMax<<endl;
					//cout <<"Chargeamount "<<chargeAmount<<endl;
				}
				//otherwise charge at rate to sustain avgDemand
				else
				{
					if(x<8){
					//cout<<"capacity before"<<capacity<<endl;
					}
					chargeRate = avgDemand - energyData->at(i);
					chargeAmount = chargeBattery(chargeRate);
					/*if(x<8){
					cout <<"Case2: "<<chargeRate<<endl;
					cout <<"Chargeamount "<<chargeAmount<<endl;
					cout<<"capacity after"<<capacity<<endl;
					cout<<"maxprice: "<<maxCost<<endl;
					cout<<"minprice: "<<minCost<<endl;
					}
					*/
				
				}

				//Add the energy data amount charged.
				//added
				double actamt=chargeAmount/ELOSS;
				energyData->at(i) += actamt;
				if(x<8){
				//cout <<"actamount "<<actamt<<endl;
				}
				//energyData->at(i) += chargeAmount;
			}
			//Case 2: price is low, and 
			//demand is high
			else
			{
				//greedily charge at max rate if inequality is true
				if((xMax*ELOSS*maxCost*T)-(xMax*minCost*T) > xMax*SURCHARGE)
				{
					chargeAmount = chargeBattery(xMax);
					//added
					double actamt=chargeAmount/ELOSS;
					energyData->at(i) += actamt;
					/*
					cout <<"actamount "<<actamt<<endl;
					cout <<"Case 3: "<<xMax<<endl;
					cout <<"Chargeamount "<<chargeAmount<<endl;
					*/
				}
				//otherwise discharge at rate to sustain avgDemand
				else
				{
					if(x<8){
					//cout<<"capacity before"<<capacity<<endl;
					}
					dischargeRate = energyData->at(i) - avgDemand;
					//actually want to get discharge energy back so /eLoss
					//changed
					double actDisRate=dischargeRate/ELOSS;
					chargeAmount = dischargeBattery(actDisRate);
					//SO the amount returned as chargeAMount now equals the amount discharge from the battery without the eloss
					double actenergy=chargeAmount*ELOSS;
					energyData->at(i) -= actenergy;
					/*
					if(x<8){
					cout <<"Case 4: "<<dischargeRate<<endl;
					cout <<"actDisamount "<<actDisRate<<endl;
					cout <<"Chargeamount "<<chargeAmount<<endl;
					cout <<"actenergy "<<actenergy<<endl;
					cout<<"capacity after"<<capacity<<endl;
					cout<<"maxprice: "<<maxCost<<endl;
					cout<<"minprice: "<<minCost<<endl;
					}
					*/
					
				}

			}

		}
		//Cases 3&4, price is high.
		else
		{
			//Case 3, price is high, and
			//demand is low
			if(energyData->at(i) <= avgDemand)
			{
				//If inequality holds up, discharge at max rate
				//might not have enough energy in battery
				if((xMax*ELOSS*maxCost*T)-(xMax*minCost*T) > xMax*SURCHARGE)
				{	//ask for 1/8 of maxcharging rate which means we will have whatever we get back*ELOSS amount
					chargeAmount = dischargeBattery(xMax);
					double actenergy=chargeAmount*ELOSS;
					energyData->at(i) -= actenergy;
					//cout <<"Case 5: "<<xMax<<endl;
					//cout <<"Chargeamount "<<chargeAmount<<endl;
					//cout <<"actenergy "<<actenergy<<endl;
				}
				//otherwise do nothing
				else
				{
				if(x<8){
				//cout <<"Case 6: "<<endl;
				}
				}

			}
			//Case 4, price is high, and
			//demand is high
			else
			{

				//if inequality holds up, discharge at max rate
				//might not have enough energy in battery
				if((xMax*ELOSS*maxCost*T)-(xMax*minCost*T) > xMax*SURCHARGE)
				{
					chargeAmount = dischargeBattery(xMax);
					double actenergy=chargeAmount*ELOSS;
					energyData->at(i) -= actenergy;
					/*
					cout <<"Case 7: "<<xMax<<endl;
					cout <<"Chargeamount "<<chargeAmount<<endl;
					cout <<"actenergy "<<actenergy<<endl;
					*/
				}
				//otherwise discharge at a rate to sustain avgDemand
				else
				{	
					dischargeRate = energyData->at(i) - avgDemand;
					//actually want to get discharge energy back so /eLoss
					//changed
					double actDisRate=dischargeRate/ELOSS;
					chargeAmount = dischargeBattery(actDisRate);
					//SO the amount returned as chargeAMount now equals the amount discharge from the battery without the eloss
					double actenergy=chargeAmount*ELOSS;
					energyData->at(i) -= actenergy;
					/*
					if(x<8){
					cout <<"Case 8: "<<dischargeRate<<endl;
					cout <<"actDisamount "<<actDisRate<<endl;
					cout <<"Chargeamount "<<chargeAmount<<endl;
					cout <<"actenergy "<<actenergy<<endl;
					cout<<"maxprice: "<<maxCost<<endl;
					cout<<"minprice: "<<minCost<<endl;
					}
					*/
				}
			}

		}	
			x++;
			//reset variables
			chargeAmount = 0;
			chargeRate = 0;
			dischargeRate = 0;
	}
	//cout <<"avgdemand "<<avgDemand<<endl;
	//cout <<"avgcost "<<avgCost<<endl;

}
