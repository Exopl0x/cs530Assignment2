#include <iostream>
#include <fstream> 
#include <vector>
  using namespace std;
  

  int main(int argc, char* argv[]){
	 ifstream listingFile;
	 vector<char>data; 
	  bool noNewline = true;
	  char fileChar;
	  
	  // cheking if a listing file is provided
	  if(argc < 2){
		cout<<"No listing files were provided"<< endl;  
	  return(-1);
	}
	
	//opening the listing files
	 for(int i = 2; i <= argc; i++){
		 listingFile.open(argv[i-1]);
	// while it is true it runs	 
		 while(noNewline){
		   fileChar = listingFile.get();
//*********************************************	
// 		this if keeps track of the newline/carriage returns
//		what we could do is take a note at every index that there is a 13 or 10
		//  if(int(fileChar) == 13|| int(fileChar) == 10){
			  //13  == carrige return
			  //10 == new line
		//		noNewline = false;
				
		//  }else{
		//		data.push_back(fileChar);
		//		noNewline = true;
		//  }
//**********************************************
	// cheking if we have reached the end of the file
		if(listingFile.eof()){
			noNewline = false; // ending the while loop
		}
		  	data.push_back(fileChar);
		 } 
	 }		

	// printing the file
	for(int i  = 0; i < int(data.size()-1); i++){
	cout << char(data[i]);
	}
	cout << endl;
	return 1;
  }