#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "storestruct.h"
#include "mylexer.h"
using namespace std;

Mylexer::Mylexer(){
    string KeyWord[14]={"if","else","for","while","main","int","string","char","int","double","return","void","printf","include"};
}

void Mylexer::readfile(string filename){
    ifstream infile;

    infile.open(filename, ios::in); // open file 

    if (!infile) {
    cerr << "unable to open file" << endl;
    }

    string line;
    while (getline(infile, line)) { 
        
        store.push_back(vector<Tokens>()); // add an empty vector
        Mylexer::scan(line);
        cout << line << endl;
    
    
    }
        infile.close(); 

}

bool Mylexer::IsLetter(char ch){
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
        return true;
    }
	return false;
}  


bool Mylexer::IsDigit(char ch){
    if (ch >= '0'&&ch <= '9'){
        return true;
    }
	return false;
}




void Mylexer::scan(string info){
    int pos = 0 ;
    if(pos<info.size()){
        if(info[pos] == ' '){
		    symbol = -2;
		    pos++;
	    }else if(IsNumber(info,pos)){
            if(symbol!=0) symbol = typeInteger;
        }
    }
   
}  

bool Mylexer::IsNumber(string inf,int pos){
    tokenvalue = ""; 

    while (IsDigit(inf[pos])||inf[pos]=='.') {
        tokenvalue.push_back(inf[pos]);
        if(inf[pos]=='.') symbol = typeDouble;
        if(pos<inf.size()) pos++;  
    }

    if(pos<inf.size()&&inf[pos]==' '){
        return true;
    }else{
        if(pos==inf.size() && IsDigit(inf[pos])) return true;
    } 
    symbol = 0;
    return false;   
}






std::vector<std::vector<Tokens>> Mylexer::ReturnToken(){
    

	 
}