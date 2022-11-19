#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;

double tLane_Q_time;

struct var {
	
	double no_costumers;
	double cItems, no_pack;
	string pref_pack, pref_payment;
	double idle;
	
};
var scanningData(string line)
{
	
	// parse data-line, using [space] as delimiter
	// source: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
	
	size_t pos = 0;
	size_t npos = -1;
	string spacing = " ";
	string data[10] = {""};
	int data_index = 0;
	while ((pos = line.find(spacing))!= npos && (pos = line.find(spacing))!=4) {  
	    
	   	data[data_index] = line.substr(0,pos);
		line.erase(0, pos + spacing.length());
	    data_index++;
	    
	}
	data[data_index] = line;
	// setting the data
	stringstream ss;
	var temp;
	for (int i = 0; i <10; i++) {
		string d = *(data + i);
		if (i == 0 || i == 2 ) {
			ss << d;
			if (i == 0) {
				ss >> temp.cItems;
			} else if (i == 2) {
				ss >> temp.no_pack;
			}
			ss.clear();
			ss.str("");
		}
			
		else if (i == 1) {
			temp.pref_pack = d;
		}
		else if(i ==3 ){
			temp.pref_payment =d;
		}
	
	}
	return temp;
}

void getData(var n, int i){
	
	/*   display the data of the costumers   */
	
	cout<<"Costumer#"<<i+1<<endl;
	cout<<"No.of Cart Items             : "<<n.cItems<<endl;
	cout<<"Preferred Packaging          : "<<n.pref_pack<<endl;
	if(n.pref_pack == "box"){		
		cout<<"Number of boxes              : "<<n.no_pack<<endl;
	}
	else if(n.pref_pack == "bag"){
		cout<<"Number of bags               : "<<n.no_pack<<endl;
	}
	cout<<"Preferred Payment Method     : ";
	
		if(n.pref_payment == "digital"){		
			cout<<"digital"<<endl;	  
		}
		else if(n.pref_payment == "cash e"){
			cout<<"cash (exact)"<<endl;	
		}
		else if(n.pref_payment == "cash ne"){
			cout<<"cash (not exact)"<<endl;	
		}
			
}

void computation(var c, int i){
	
	/*  declaration of variable for computation */
	
	double dec_time=c.cItems * 0.5;
	double scan_time=c.cItems * 0.5;
	
	double pack_time;
	if(c.pref_pack =="box"){
		double box =10;
		pack_time = (c.cItems*0.5) + (c.no_pack*box);
	}
	else if(c.pref_pack =="bag"){
		double bag= 5;
		pack_time = (c.cItems*0.5)+ (c.no_pack*bag);
	}
	
	double pay_time;
	if(c.pref_payment == "digital"){
		pay_time=15;
	}
	else if(c.pref_payment == "cash e"){
		pay_time =15;
	}
	else if(c.pref_payment == "cash ne"){
		pay_time =20;
	}
	
	double recpt_print_time = (c.cItems *0.3) + 2;
	c.idle =(i>0) ?3:0;
	double tCostumer_Q_time = (dec_time+scan_time) + pack_time + pay_time + recpt_print_time + c.idle;
	
	cout << "Total De-Carting Time        : "<<dec_time<<endl;
	cout<< "Total Scanning Time          : "<<scan_time<<endl;
	cout<< "Total Packing Time           : "<<pack_time<<endl;
	cout<< "Total Paying Time            : "<<pay_time<<endl;
	cout<< "Total Receipt Printing Time  : "<<recpt_print_time<<endl;
	cout<< "Idle Time                    : "<<c.idle<<endl;
	cout<< "Total Customer-Queue Time    : "<<tCostumer_Q_time<<endl;
	tLane_Q_time +=tCostumer_Q_time;
	
}
 
 
 
int main ()
{
	// Open the input file
	ifstream in("inputfile.txt");
	if (!in.is_open()) {
		cout << "Cannot open file!!!" ;
		exit(1);
	}
	// Read the record size
	int T;
	char c;
	in >> T;
	cout<<"No.of Costumers: "<<T<<endl;
	cout<<"============================================"<<endl;
	int i=0;
	// instanstiate queue
	var list[T];
	string line;
	// For each succeeding lines of strings...
	while (getline(in, line)) {
		
		if (line.length() > 0) {	
			// Parse data and store to list
			list[i] = scanningData(line);
			// Print costumers data
			getData(list[i],i);			
			cout<<"--------------------------------------------"<<endl;
			computation(list[i],i);
			
			if(T-1!=i){
				cout<<"++++++++++++++++++++++++++++++++++++++++++++"<<endl;
				i++;
			}
			else{
				cout<<"============================================"<<endl;
			}				
		}
		
	}
	cout<<"Total Lane Queue Time        : "<<tLane_Q_time<<endl;

	return 0;
}

