#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <map>
#include <vector>
#include "tokens.h"
using namespace std;


int main( int argc, char*argv[] ){
    
    map<int, string> m;
    map<string, int> m1;
    ifstream f;
    stringstream s;
    bool vFlag = false;
    bool sFlag = false;
    bool aFlag = false;
    int filecounter = 0;
    int argCounter = 0;
    int tokenCounter = -1;
    int IDENTC = 0;
    int SCONSTC = 0;
    int lN = 0;
    int lineNumber = 0;
    Token got;
    string allids = "";
    
    for(int i = 1; i<argc; i++){
        
     string arg = argv[i];
     
        
        if(arg.at(0) == '-'){
            
            if(!((arg.compare("-v") == 0) || (arg.compare("-sum") == 0) || (arg.compare("-allids") == 0))){
                
                cout << "INVALID FLAG " << arg << endl;
                return 0;
                
            }else if(arg.compare("-v") == 0){
                
                argCounter++;
                vFlag = true;
                
                
            }else if(arg.compare("-sum") == 0){

                argCounter++;
                sFlag = true;
                
            }else if(arg.compare("-allids") == 0){
                
                argCounter++;
                aFlag = true;
                
            }   
            
            
            
        }else{
            
            filecounter++;
            
        }
    }
        
    if(filecounter>0){    
        if(filecounter>1){
            cout << "TOO MANY FILE NAMES" << endl;  
            return 0;
        }else{
            
            f.open(argv[argc-1]);
            if(!f.good()){
                
             cout << "UNABLE TO OPEN " << argv[argc-1] << endl;
                return 0;
                
            }
            
            got = getNextToken(&f, &lineNumber);

            while(true){

                tokenCounter++;

                if(got.GetTokenType() == DONE){
                    break;            
                }else if(got.GetTokenType() == SCONST){
                    SCONSTC++;
                }else if(got.GetTokenType() == IDENT){
                    IDENTC++;
                }

                if(vFlag){
                    
                    if(got.GetTokenType() == SCONST){
                        cout << got << "(" << got.GetLexeme() << ")" << endl;

                    }else if(got.GetTokenType() == IDENT){
                        cout << got << "(" << got.GetLexeme() << ")" << endl;

                    }else if(got.GetTokenType() == ICONST){
                        cout << got << "(" << got.GetLexeme() << ")" << endl;

                    }else if(got.GetTokenType() == ERR){
                            cout << "Error on line " << (got.GetLinenum())<< " (\"" << got.GetLexeme() << "\n" << ")" << endl;
                            break;
                    }else{
                        cout << got << endl;
                    }
                }

                if(aFlag){

                    if(got.GetTokenType() == IDENT){
                        m[IDENTC] = got.GetLexeme();
                    }
                }

                
                got = getNextToken(&f, &lineNumber);
                lN = got.GetLinenum();
                
            }

            if(aFlag){
                map<int, string>::iterator it;
                map<string, int>::iterator hit;

                for(it = m.begin(); it!=m.end(); it++){
                    m1[it->second] = it->first;
                }

                for(hit = m1.begin(); hit!=m1.end(); hit++){
                    allids += hit->first;
                    allids += ", ";
                }

                allids.erase((allids.size()-2));

                cout << "IDENTIFIERS: " << allids << endl;

            }

            if(sFlag){
                    
                    cout << "Total lines: " <<  lN << endl;
                    cout << "Total tokens: " << tokenCounter << endl;
                    cout << "Total identifiers: " << IDENTC << endl;
                    cout << "Total strings: " << SCONSTC << endl;
                    return 0;

                }  
                
        }
    }
    
    if(argc = 2){

        return 0;

    }else if(argCounter == 0){

        string input = "";

        while(getline(cin, input)){
            s << " " << input;

        }

        got = getNextToken(&s, &lineNumber);

        while(true){

                tokenCounter++;

                if(got.GetTokenType() == DONE){
                    break;            
                }

                if(vFlag){
                    
                    if(got.GetTokenType() == SCONST){
                        cout << got << "(" << got.GetLexeme() << ")" << endl;

                    }else if(got.GetTokenType() == IDENT){
                        cout << got << "(" << got.GetLexeme() << ")" << endl;

                    }else if(got.GetTokenType() == ICONST){
                        cout << got << "(" << got.GetLexeme() << ")" << endl;

                    }else if(got.GetTokenType() == ERR){
                            cout << "Error on line " << (got.GetLinenum())<< " (\"" << got.GetLexeme() << "\n" << ")" << endl;
                            break;
                    }else{
                        cout << got << endl;
                    }
                }

                
                got = getNextToken(&f, &lineNumber);
                lN = got.GetLinenum();
                
            }


    }
        
        
        
    if(vFlag || sFlag || aFlag){
            
    }
        
        
    
    
}
