#include <iostream>
#include <fstream> 
#include <vector>
#include <string>
#include <sstream>
	using namespace std;
  
void Print(vector<char> data, vector<int> newLines){
	// convert the characers to either a string or an int then create the ESTAB
	
	string address [2000];
	string symbols [2000];
	string instruction[2000];
	string parameter[2000];
	string opcode[2000];
	char charValue;
	stringstream streamValue;	
	string sValue;
	int arrSize;
	// printing the file
	//for(int i  = 0; i < int(data.size()-1); i++){
	//	cout << char(data[i]);
	//}

		for(int i  = 0; i < data.size()-1; i++){// saving the spots where there is a space in this file
			if(int(data[i]) == 10){
			newLines.push_back(i);
			}
	}
	
	int newlineFound = 0;
	int acounter = 0;
	int next = 0;
	int setI = 0;
	int rows = 0;
	bool lastOP = false;
	bool restart = false;
	bool foundLine = false;
	bool asteriskFound = false;
	int arrayCounter = 0;
	int fileSize = 0;
	int line = 0;
//	string test = "25B0";
while(fileSize != data.size()-1){
	acounter = 0;
	rows++;
	//address
	for(int i = setI; i < data.size()-1;i++){
		if(int(data[i]) == 46){ //found a comment
		i = newLines[newlineFound];	// jump to the next line
		newlineFound++;
		}else{
			if(acounter < 7){ 
				charValue = char(data[i]); //storing the char
				sValue += charValue;
				acounter ++;
				
			}
			if(acounter == 7 ){	
					address[arrayCounter] = sValue;
					//cout<<"address is "<<address[arrayCounter]<<endl;
					next = i+1;
					break;
			
			}
		}
	}
	
	////symbol
	sValue = "";
	acounter = 0;
	for(int i = next; i < data.size()-1; i++){
		if(int(data[i]) == 46){ //found a comment
		i = newLines[newlineFound];	// jump to the next line
		newlineFound++;
		}else{
			if(acounter < 7){ 
				charValue = char(data[i]); //storing the char
				if(charValue == '*'){
					asteriskFound = true;
				}
				sValue += charValue; 
				acounter ++;	
			}
			if(acounter == 7 ){	
					symbols[arrayCounter] = sValue;
				//	cout<<"symbols is "<<symbols[arrayCounter]<<endl;
					next = i+1;
					break;
			}
		}
	}
////instruciton
	sValue = "";
	acounter = 0;
	for(int i = next; i < data.size()-1; i++){
		if(int(data[i]) == 46){ //found a comment
			i = newLines[newlineFound];	// jump to the next line
			newlineFound++;
		}else if(int(data[i+1]) == 10){
			instruction[arrayCounter] = sValue;
			//cout<<"instruction: "<<instruction[arrayCounter]<<endl;
			i = newLines[newlineFound];	// jump to the next line
			newlineFound++;
			next = i+1;
			foundLine = true;
			break;
		}
		else{
			if(acounter < 9){ 
				charValue = char(data[i]); //storing the char
				sValue += charValue; 
				acounter ++;	
			}
			if(acounter == 9){	
					instruction[arrayCounter] = sValue;
					//cout<<"instruction is"<<instruction[arrayCounter]<<endl;
					next = i+1;
					break;
			}
		}
	}
	if(foundLine == true){lastOP = true;}
	else{
		// parameter	
		sValue = "";
		acounter = 0;
		for(int i = next; i < data.size()-1; i++){
			if(int(data[i]) == 46){ //found a comment
				parameter[arrayCounter] = sValue;
				//cout<<"parameter is "<<parameter[arrayCounter]<<endl;
				i = newLines[newlineFound];	// jump to the next line
				newlineFound++;
				next = i+1;
				restart = true;
				opcode[arrayCounter] = " ";
				//cout<<"opcode NO: "<<opcode[arrayCounter]<<endl;
				break;
			}
			else if (int(data[i+1]) == 10){
				//cout << "next character the line ends"<<endl;
				parameter[arrayCounter] = sValue;
				//cout<<"parameter: "<<parameter[arrayCounter]<<endl;
				i = newLines[newlineFound];	// jump to the next line
				newlineFound++;
				next = i+1;
				restart = true;
				opcode[arrayCounter] = " ";
				//cout<<"opcode NO: "<<opcode[arrayCounter]<<endl;
				break;
			}
			else{
				if(acounter < 25){ 
					charValue = char(data[i]); //storing the char
					sValue += charValue; 
					acounter ++;	
				}
				if(acounter == 25){	// if the counter reaches 25
					parameter[arrayCounter] = sValue;
					//	cout<<"parameter NORMAL: "<<parameter[arrayCounter]<<endl;
					next = i+1;
					restart = false;
					break;	
				}
			}
		}
					
		//if(hasObjectCode == false){break;}
		if(restart == true){
			//cout<<"restart is true"<<endl;
		}
		else if(lastOP){
			//cout<<"lastOp was reached"<<endl;
			sValue = "";
			acounter = 0;
			for(int i = next; i <= data.size(); i++){
				if(acounter < 10){
					charValue = char(data[i]); //storing the char
					sValue += charValue; 
					acounter ++;
				}
				if(i == data.size()){
					opcode[arrayCounter] = sValue;
					//cout<<"opcode is "<<opcode[arrayCounter]<<endl;
					//cout<<i<<endl;
					arrSize = i;
					break;
				}
			}
			break;
		}
		else if(asteriskFound){
			sValue = "";
			acounter = 0;
			for(int i = next; i <= data.size(); i++){
				if(acounter < 10){
					charValue = char(data[i]); //storing the char
					sValue += charValue; 
					acounter ++;
				}
				if(i == data.size()){
					opcode[arrayCounter] = sValue;
					//cout<<"opcode is "<<opcode[arrayCounter]<<endl;
					arrSize = i;
					break;
				}
			}
			break;
		}
		else{
		
			//cout<<"entered the end"<<endl;
		
			// opcode
			sValue = "";
			acounter = 0;
			for(int i = next; i < data.size()-1; i++){
				if(int(data[i]) == 46){ //found a comment
					opcode[arrayCounter] = sValue;
					//cout<<"opcode is "<<opcode[arrayCounter]<<endl;
					i = newLines[newlineFound];	// jump to the next line
					newlineFound++;
					restart = true;
					next = i+1;
					break;
				}
				else if(int(data[i+1]) == 10){ // newline found
					//	cout<< "reached the end of the line"<<endl;
					opcode[arrayCounter] = sValue;
					//	cout<<"opcode is "<<opcode[arrayCounter]<<endl;
					i = newLines[newlineFound];	// jump to the next line
					newlineFound++;
					restart = true;
					next = i+1;
					break;
				}
				else{
					if(acounter < 13){ 
						charValue = char(data[i]); //storing the char
						sValue += charValue; 
						acounter ++;	
					}
					if(acounter == 13){	
						opcode[arrayCounter] = sValue;
						//cout<<"opcode is "<<opcode[arrayCounter]<<endl;
						next = i+1;
						break;
					}
				}
			}
		}
	}	
	foundLine = false; 
	arrayCounter++;
	sValue = "";
	setI = next;
	fileSize = next;
	line ++;

}

	for(int i = 0; i <rows; i ++){
		cout<<address[i]<<" " << symbols[i]<<" "<<instruction[i]<<" "<<parameter[i]<<" "<<opcode[i]<<" "<<endl;
	}

//CONVERTING A STRING TO ITS HEX VALUE REPRESENTATION			
//	std::string a = "001A";
//	std::stringstream b;
//	b << a;
//	int c;
//	b >> std::hex >> c;
//	std::cout << c; 
//CONVERTING A STRING TO ITS HEX VALUE REPRESENTATION	

}
	int main(int argc, char* argv[]){
		ifstream listingFile;
		vector<char>data; 
		vector<int> newLines;
		bool noNewline = true;
		char fileChar;
	    
		// cheking if a listing file is provided
		if(argc < 2){
			cout<<"No listing files were provided."<< endl;  
			cout<<"Terminating program."<< endl; 
	  	return(-1);
		}
	
		//opening the listing files
		//only currently only reading one file
	 	for(int i = 2; i <= argc; i++){
			noNewline = true;
			listingFile.open(argv[i-1]);
			
			// while it is true it runs	 
			// While the line is being read and no new line is found, the while loop runs.
			while(noNewline){
				fileChar = listingFile.get();

				/* Columns 0-7:   Address
				 * Columns 8-15:  Symbols
				 * Columns 16-24: Instructions
				 * Columns 25-50: Parameters
				 * Columns 51-58: Instruction code
				 *
				 * Columns that are vital to creating the object file: 
				 * Symbols, Instructions, Instruction Code
				 *
				 * Columns that are vital to creating the ESTAB:
				 * Address, Instructions, Parameters, 
				 */

				if(listingFile.eof()){
					noNewline = false; // ending the while loop
					listingFile.close();// closing the current file
					
					Print(data, newLines); // instead of clearing it we want to put the data in the ESTAB
					data.clear();
				}
		  		data.push_back(fileChar);
			} 
	 	}		

		return 1;
  	}
