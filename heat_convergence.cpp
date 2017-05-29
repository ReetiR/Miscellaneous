#include <iostream>
#include <cmath> 

using namespace std;

const int NROWS= 10;
const int NCOLS= 10;

//display function
void display(double temp[][NCOLS]){
	int i, j;
	for(i=0; i<NROWS; i++){
		for(j=0; j<NCOLS; j++)
			std::cout<<temp[i][j]<<" ";
		std::cout<<"\n";
	}
}

int main(){
	double temp[NROWS][NCOLS], old[NROWS][NCOLS];
	double temp_top, temp_right, temp_bottom, temp_left, temp_init;
	int i, j;
	double conv_criterion;
	bool steady;
	std::cout<<"Enter temperature for top:\t";
	std::cin>>temp_top;
	std::cout<<"Enter temperature for right:\t";
	std::cin>>temp_right;
	std::cout<<"Enter temperature for bottom:\t";
	std::cin>>temp_bottom;
	std::cout<<"Enter temperature for left:\t";
	std::cin>>temp_left;
	for(i=0; i<NCOLS; i++){
		temp[0][i]=temp_top;
		temp[NROWS-1][i]= temp_bottom;
	}
	for(i=1; i<NROWS-1; i++){
		temp[i][0]= temp_left;
		temp[i][NCOLS-1]= temp_right;
	}
	std::cout<<"Enter initial temperature:\t";
	std::cin>>temp_init;
	for(i=1; i<NROWS-1; i++){
		for(j=1; j<NCOLS-1; j++)
			temp[i][j]= temp_init;
	}
	display(temp);
	std::cout<<"Enter convergence criterion:\t";
	std::cin>>conv_criterion;
	//convergence loop
	do{
		steady = 1;
		for(i=0; i<NROWS; i++){
			for(j=0; j<NCOLS; j++)
				old[i][j]=temp[i][j];
		}
		for(i=1; i<NROWS-1; i++){
			for(j=1; j<NCOLS-1; j++)
				temp[i][j]=0.25*(old[i-1][j]+old[i+1][j]+old[i][j-1]+old[i][j+1]);
				if(std::abs(temp[i][j]-old[i][j])>conv_criterion)
					steady= 0;
		}
	} while(steady== 0);
	display(temp);
	return 0;
}