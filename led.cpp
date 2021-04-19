#include <iostream>
#include <fstream> 
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <iomanip>
	using namespace std;
string FixAdd(string element);
string FixSymbols(string element);
string FixInstructions(string element);
string FixParameter(string element);
string FixOpcode(string element);
void PrintESTAB(string Mainaddress[], string Mainsymbols[], string Maininstruction[],string Mainparameter[], string Mainopcode[], int rowNum);
void PrintObj(string Mainaddress[], string Mainsymbols[], string Mainparameter[],string Mainopcode[],int rowNum);
void StoreData(vector<char> data, vector<int> newLines, string Mainaddress[],string Mainsymbols[],string Maininstruction[],string Mainparameter[],string Mainopcode[], int *rowPtr){
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
		}
		else{
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
					next = i+1;
					restart = false;
					break;	
				}
			}
		}
					
		if(restart == true){
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
					opcode[arrayCounter] = sValue;
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
		address[i] = FixAdd(address[i]);
		symbols[i] = FixSymbols(symbols[i]);
		instruction[i] = FixInstructions(instruction[i]);
		parameter[i] = FixParameter(parameter[i]);
		opcode[i] = FixOpcode(opcode[i]);

	}
	*rowPtr = rows-1;

	for(int i = 0; i <rows; i++){
		Mainaddress[i] = address[i];
		Mainsymbols[i] = symbols[i];
		Maininstruction[i] = instruction[i];
		Mainparameter[i] = parameter[i];
		Mainopcode[i] = opcode[i];
	}	
	
}

	string FixAdd(string element){
		string replacement;
		char aChar;
		for(int i = 0; i < element.length(); i ++){
			aChar = element[i];
			if(int(aChar) != 32){
				replacement += aChar;
			}else{
				if(element[0] == element[element.length()-1]){
				replacement = " ";
				break;
				}
			}
		}
	return replacement;
}
	string FixSymbols(string element){
		string replacement;
		char aChar;
		for(int i = 0; i < element.length(); i ++){
			aChar = element[i];
			if(int(aChar) != 32){
			replacement += aChar;
			}
		}
		if(replacement.length() == 0){
			replacement  = " ";
			return replacement;
		}
	return replacement;
	}
	string FixInstructions(string element){
		string replacement;
		char aChar;
		for(int i = 0; i < element.length(); i ++){
			aChar = element[i];
			if(int(aChar) != 32){
				replacement += aChar;
			}
		}
		return replacement;
}
	string FixParameter(string element){
	string replacement;
	char aChar;
		for(int i = 0; i < element.length(); i ++){
			aChar = element[i];
			if(int(aChar) != 32){
				replacement += aChar;
			}
		}
		if(replacement.length() == 0){
			replacement  = " ";
			return replacement;
		}
	return replacement;
}
	string FixOpcode(string element){
	 string replacement;
	 char aChar;
		for(int i = 0; i < element.length(); i ++){
			aChar = element[i];
			if(int(aChar) != 32){
				replacement += aChar;
			}
		}
		if(replacement.length() == 0){
			replacement  = " ";
			return replacement;
		}
	return replacement;
 }
 
 
 void PrintESTAB(string Mainaddress[], string Mainsymbols[], string Maininstruction[],string Mainparameter[], string Mainopcode[], int rowNum, int*addPtr, int*lengthPtr, bool firstPass){
	 int finalLength;
	int bob7 = 0;
	char aChar;
	char anotherChar;
	string bob = Mainaddress[rowNum]; // length of control section
	 string bob2;
	 int toHex[4];
	 ofstream out;
	 out.open("estab", ios::out | ios::app);

	
 for(int i = 0;i < bob.length(); i ++){
	 aChar = bob[i];
	 bob2 += aChar;
	 std::stringstream b;
	b << bob2;
	int c;
	b >> std::hex >> c;
	toHex[i] = c;
	bob2 = "";
 }

 int power = 3;
 
	for(int i = 0; i < 4; i++){
		finalLength += toHex[i]*pow(16.0, power);
		power --;
	}
		finalLength+=3;
//////////////////////	
if(firstPass == true){
	string addControl = Mainaddress[0]; // addres of control section
	char aChar2;
	 string tempStr;
	 int toHex2[4];
 for(int i = 0;i < 4; i ++){
	 aChar2 = addControl[i];
	 tempStr += aChar2;
	 std::stringstream bb;
	bb << tempStr;
	int cc;
	bb >> std::hex >> cc;
	toHex2[i] = cc;
	tempStr = "";
 }
 int power2 = 3;
	for(int i = 0; i < 4; i++){
		bob7 += toHex2[i]*pow(16.0, power);
		power --;
	}
	
	//printing to the console
	 cout<<setfill(' ')<<setw(6)<<left<<Mainsymbols[0];
	  cout<<"        ";
	 cout<<"  ";
	 cout<<setfill('0')<<setw(6)<<right<<Mainaddress[0]<<"  ";
	 cout<<setfill('0')<<setw(6)<<right<<hex<<finalLength<<endl;

	 // Put these into out to put into the ESTAB:
	 out<<setfill(' ')<<setw(6)<<left<<Mainsymbols[0];
	 out<<"        ";
	 out<<"  ";
	 out<<setfill('0')<<setw(6)<<right<<Mainaddress[0]<<"  ";
	 out<<setfill('0')<<setw(6)<<right<<hex<<finalLength<<endl;

 }else{
	 bob7 = *lengthPtr + *addPtr;
	 cout<<setfill(' ')<<setw(6)<<left<<Mainsymbols[0];
	 cout<<"        ";
	 cout<<"  ";
	 cout<<setfill('0')<<setw(6)<<right<<hex<<bob7<<"  ";
	 cout<<setfill('0')<<setw(6)<<right<<hex<<finalLength<<endl;

	 // Put these into out to put into the ESTAB:
	 out<<setfill(' ')<<setw(6)<<left<<Mainsymbols[0];
	 out<<"        ";
	 out<<"  ";
	 out<<setfill('0')<<setw(6)<<right<<hex<<bob7<<"  ";
	 out<<setfill('0')<<setw(6)<<right<<hex<<finalLength<<endl;

	 
 }
	 if(Maininstruction[1] == "EXTDEF"){
		 string temp = Mainparameter[1];
		 string param;
		 if(firstPass == true){
		 for(int i = 0; i < temp.length(); i++){
			 aChar = temp[i];
			 if(int(aChar) == 44){
				 cout<<"        ";
				 cout<<setfill(' ')<<setw(6)<<left<<param;
				 cout<<"  ";

				 // Into ESTAB:
				 out<<"        ";
				 out<<setfill(' ')<<setw(6)<<left<<param;
				 out<<"  ";

				 for(int j = 0; j < rowNum; j ++){
					 if(Mainsymbols[j] == param){
						cout<<setfill('0')<<setw(6)<<right<<Mainaddress[j];
						cout<<"  "<<endl;
						// Into ESTAB:
						out<<setfill('0')<<setw(6)<<right<<Mainaddress[j];
						out<<"  "<<endl;

						param = "";
						break;
					 }  
				 }
			 }else{
			 param +=aChar;
			 } 
		 }
		 for(int i = 0; i < rowNum; i++){
			  if(Mainsymbols[i] == param){
				 cout<<"        ";
				 cout<<setfill(' ')<<setw(6)<<left<<param;
				 cout<<"  ";
				cout<<setfill('0')<<setw(6)<<right<<Mainaddress[i];
				cout<<"  "<<endl;

				// Into ESTAB:
				out<<"        ";
				out<<setfill(' ')<<setw(6)<<left<<param;
				out<<"  ";
				out<<setfill('0')<<setw(6)<<right<<Mainaddress[i];
				out<<"  "<<endl;

				param = "";
					break;
			}
		 } 
	 }else{ 
	 		 string tempADD;
			 string tempBob;
			 string tempBoby;
			 string tempADD1;
			  int toHex3[4];
			  int toHex4[4];
			  int con = 0;
	 // if it is not the first pass we need to do math
		 	for(int i = 0; i < temp.length(); i++){
			 aChar = temp[i];
			 if(int(aChar) == 44){
				 cout<<"        ";
				 cout<<setfill(' ')<<setw(6)<<left<<param;
				 cout<<"  ";

				 // Into ESTAB:
				 out<<"        ";
				 out<<setfill(' ')<<setw(6)<<left<<param;
				 out<<"  ";

				 for(int j = 0; j < rowNum; j ++){
					 if(Mainsymbols[j] == param){
						 tempADD1 = Mainaddress[j];
						 for(int k = 0; k < 4; k++){
							 anotherChar = tempADD1[k];
							 tempBoby += anotherChar;
							 std::stringstream con;
							 con << tempBoby;
							 int cVal;
							 con >>std:: hex >> cVal;
							 toHex4[k] = cVal;
							 tempBoby = "";
						 }
						int power3 = 3;
						int p;
						int s;
						int a;
						int o;
						int mathAdd;
						s =  toHex4[0]*pow(16.0, 3);
						a =  toHex4[1]*pow(16.0, 2);
						p =  toHex4[2]*pow(16.0, 1);
						o =  toHex4[3]*pow(16.0, 0);
						mathAdd = s + a + p + o;
						mathAdd+= *addPtr + *lengthPtr;
						cout<<setfill('0')<<setw(6)<<right<<mathAdd;
						cout<<"  "<<endl;
						// Into ESTAB:
						out<<setfill('0')<<setw(6)<<right<<mathAdd;
						out<<"  "<<endl;

						param = "";
						break;
					 }  
				 }
			 }else{
			 param +=aChar;
			 } 
		 }
		 
		 
		 
		 //one extdef
		 for(int i = 0; i < rowNum; i++){
			  if(Mainsymbols[i] == param){
				  	//converting the string add to a int
					tempADD = Mainaddress[i];
					for(int i = 0;i < 4; i ++){
					anotherChar = tempADD[i];
					tempBob += anotherChar;
					std::stringstream bbb;
					bbb << tempBob;
					int ccc;
					bbb>> std::hex >> ccc;
					
					toHex3[i] = ccc;
					tempBob= "";
				}
				int power3 = 3;
				int p;
				int s;
				int a;
				int o;
				int mathAdd;
				s =  toHex3[0]*pow(16.0, 3);
				a =  toHex3[1]*pow(16.0, 2);
				p =  toHex3[2]*pow(16.0, 1);
				o =  toHex3[3]*pow(16.0, 0);
				mathAdd = s + a + p + o;
				mathAdd+= *addPtr + *lengthPtr;
				 cout<<"        ";
				 cout<<setfill(' ')<<setw(6)<<left<<param;
				 cout<<"  ";
				 cout<<setfill('0')<<setw(6)<<right<<mathAdd<<endl;
				 cout<<"  "<<endl;

				// Into ESTAB:
				out<<"        ";
				out<<setfill(' ')<<setw(6)<<left<<param;
				out<<"  ";
				out<<setfill('0')<<setw(6)<<right<<mathAdd<<endl;
				out<<"  "<<endl;

				param = "";
					break;
			}
		 }
	 }
	 }
	 *addPtr = bob7;
	 *lengthPtr = finalLength;

	 out.close();
 }
 
 void PrintObj(string Mainaddress[], string Mainsymbols[], string Mainparameter[],string Mainopcode[],int rowNum){
	cout<<"H";
	 cout<<setfill(' ')<<setw(6)<<left<<Mainsymbols[0];
	 cout<<setfill('0')<<setw(6)<<left<<Mainaddress[0];
	for(int i = 0; i < rowNum; i++){
		
		
	}
 }
	int main(int argc, char* argv[]){
		ifstream listingFile;
		vector<char>data; 
		vector<int> newLines;
		bool noNewline = true;
		char fileChar;
		string Mainaddress [2000];
		string Mainsymbols [2000];
		string Maininstruction[2000];
		string Mainparameter[2000];
		string Mainopcode[2000];
		int rowNum = 0;
		int *rowPtr = &rowNum;
		int firstAdd = 0;
		int *addPtr = &firstAdd;
		int length = 0;
		int *lengthPtr = &length;
		bool firstPass;
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
			if(i == 2){
				firstPass = true;
			}else{
				firstPass = false;
			}
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
					
					StoreData(data, newLines, Mainaddress, Mainsymbols, Maininstruction, Mainparameter, Mainopcode,rowPtr); // instead of clearing it we want to put the data in the ESTAB
					data.clear();
					///start working here
					PrintESTAB(Mainaddress, Mainsymbols, Maininstruction, Mainparameter, Mainopcode,rowNum, addPtr, lengthPtr, firstPass);
					PrintObj(Mainaddress, Mainsymbols, Mainparameter, Mainopcode,rowNum);
				}
		  		data.push_back(fileChar);
			} 
	 	}		

		return 1;
  	}
