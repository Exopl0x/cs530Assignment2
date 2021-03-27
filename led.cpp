#include <iostream>
#include <fstream> 
#include <vector>
  using namespace std;
  int main(int argc, char* argv[]){
     ifstream listingFile;
     vector<char>data; 
      bool noNewline = true;
      char nl;
      
      if(argc < 2){
        cout<<"No listing files were provided"<< endl;  
      return(-1);
    }
    
    
    // right now it reads until there is a newline or return
    // what we could do is take a note at every index that there is a 13 or 10 
    // so then we are creating the ESTAB we know where the end of the row is
     for(int i = 2; i <= argc; i++){
         listingFile.open(argv[i-1]);
         // while it is true it runs
         while(noNewline){
           nl = listingFile.get();
           //cout<<int(nl)<<endl;
            //cout << "NEWLINE"<<endl;
          if(int(nl) == 13|| int(nl) == 10){
              //13  == carrige return
              //10 == new line
                noNewline = false;
                
          }else{
                data.push_back(nl);
                noNewline = true;
          }
         } 
     }        
     
    for(int i  = 0; i < int(data.size()); i++){
    cout << char(data[i]);
    }
    cout << endl;
    return 1;

  }