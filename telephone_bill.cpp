#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

//named constants
const int base = 50;
const float perMin = 0.20;

int main()
{
	std::string name,addr,city,state, letter;
	int pin,min,amount,dollars,quaters,temp,sub,dimes,nickels,pennies;
	double owed;
	int ch;
	//menu options
	std::cout<<"Welcome to the Cellular Telephone System"<<endl<<endl;
	std::cout<<"1- Process Telephone Bill"<<endl;
	std::cout<<"2- Translate Phone Word"<<endl<<endl;
	std::cout<<"Enter your choice:\t";
	std::cin>>ch;
	cin.ignore();
	switch(ch){
		case 1:
		std::cout<<"Enter the name of Customer:\t";
		std::getline(std::cin,name);
		cin.clear();
		std::cout<<"Enter Street Address:\t";
		std::getline(std::cin,addr);
		cin.clear();
		std::cout<<"Enter City:\t";
		std::getline(std::cin,city);
		cin.clear();
		std::cout<<"Enter state:\t";
		std::getline(std::cin,state);
		cin.clear();
		std::cout<<"Enter zip code:\t";
		std::cin>>pin;
		std::cout<<"Enter the number of minutes used:\t";
		std::cin>>min;
		//new rates
		if(min<50){
			owed = base;
		}
		else{
			owed = base;
			min= min -50;
			owed+=(double)min*perMin;
		}
		// owed=(double)min*0.20;
		std::cout<<endl<<name<<"\n"<<addr<<"\n"<<city<<","<<state<<"\n"<<pin<<endl<<"Amount Owed:"<<owed<<endl;
		std::cout<<"Enter the amount received from customer:\t";
		std::cin>>amount;
		temp=owed*100;
		//check if customer paid more
		if(amount>temp){
			sub=amount-temp;
			dollars=sub/100;
			quaters=(sub-dollars*100)/25;
			dimes=(sub-dollars*100-quaters*25)/10;
			nickels=(sub-dollars*100-quaters*25-dimes*10)/5;
			pennies=(sub-dollars*100-quaters*25-dimes*10-nickels*5);
			std::cout<<"Denomination\tNumber\nDollars\t\t\t"<<dollars<<"\nQuaters\t\t\t"<<quaters<<"\nDimes\t\t\t"<<dimes<<"\nNickels\t\t\t"<<nickels<<"\nPennies\t\t\t"<<pennies<<"\n";
		}
		else if(amount<temp)
			std::cout<<"Customer owes more."<<endl;
		else
			std::cout<<"No change to be returned. Exact amount paid."<<endl;
		break;
		case 2:
		//get letter
		std::cout<<"Enter a single letter:\t";
		std::getline(std::cin,letter);
		//check length
		if(letter.length()==1){
			//convert to uppercase
			transform(letter.begin(), letter.end(), letter.begin(), ::toupper);
			if(letter.compare("A")==1 || letter.compare("B")==1 || letter.compare("C")==1)
				std::cout<<"The corresponding phone digit is "<<2<<endl;
			else if(letter.compare("D")==1 || letter.compare("E")==1 || letter.compare("F")==1)
				std::cout<<"The corresponding phone digit is "<<3<<endl;
			else if(letter.compare("G")==1 || letter.compare("H")==1 || letter.compare("I")==1)
				std::cout<<"The corresponding phone digit is "<<4<<endl;
			else if(letter.compare("K")==1 || letter.compare("L")==1)
				std::cout<<"The corresponding phone digit is "<<5<<endl;
			else if(letter.compare("M")==1 || letter.compare("N")==1 || letter.compare("O")==1)
				std::cout<<"The corresponding phone digit is "<<6<<endl;
			else if(letter.compare("P")==1 || letter.compare("Q")==1 || letter.compare("R")==1 || letter.compare("S")==1)
				std::cout<<"The corresponding phone digit is "<<7<<endl;
			else if(letter.compare("T")==1 || letter.compare("U")==1 || letter.compare("V")==1)
				std::cout<<"The corresponding phone digit is "<<8<<endl;
			else if(letter.compare("W")==1 || letter.compare("X")==1 || letter.compare("Y")==1 || letter.compare("Z")==1)
				std::cout<<"The corresponding phone digit is "<<9<<endl;
			else
				std::cout<<"Invalid character entered."<<endl;
		}
		else
			std::cout<<"Too many characters entered."<<endl;
		break;
		default:
		std::cout<<"Invalid choice given.";
	}
	
	return 0;
}