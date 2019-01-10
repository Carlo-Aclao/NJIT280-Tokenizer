#include <string>
#include <cctype>
#include <map>
#include "tokens.h"

using namespace std;

Token getNextToken(istream *in, int *linenum){
    
    enum LexState{
        
        FIR,
        LET, //Letter
        QUO, //Quotation
        NUM, //Number
        OPE, //Operator 
        COM, //COMMENt
        EQQ,
        LTT,
        GTT,
        EXP,
        AND,
        ORR, 


    };

    LexState state = FIR;
    bool fQ = true;
    bool nK = true;
    string lexeme = "";
    char ch;

    while(in->get(ch)){

        if(ch=='\n'){
            (*linenum)++;
        }

        if(state == FIR){

            if(isspace(ch)){
                continue;

            }else if(isdigit(ch)){
                state = NUM;

            }else if(isalpha(ch)){
                state = LET;

            }else if(ch == '"'){
                state = QUO;
            }else if(ch == '='){
                state = EQQ;
            }else if(ch == '>'){
                state = LTT;
            }else if(ch == '<'){
                state = GTT;
            }else if(ch == '!'){
                state = EXP;
            }else if(ch == '&'){
                state = AND;
            }else if(ch == '|'){
                state = ORR;
            }else if(ch == '#'){
                state = COM;
            }else{
                state = OPE;
            }

            if(state == FIR){
                return Token(ERR, lexeme, *linenum);
            }


        }

        if(state == EQQ){

            if(ch == '='){
                if(lexeme == "="){
                    return Token(EQ, "", *linenum);
                    lexeme = "";
                    state = FIR;
                }else if(lexeme == ">"){
                    return Token(LEQ, "", *linenum);
                    lexeme = "";
                    state = FIR;
                }else if(lexeme == "<"){
                    return Token(GEQ, "", *linenum);
                    lexeme = "";
                    state = FIR;
                }
                lexeme +=ch;
            }else{
                in->putback(ch);
                return Token(ASSIGN, "", *linenum);
                lexeme = "";
                state = FIR;
            }

        }

        if(state == EXP){

            if(ch == '!'){
                lexeme +=ch;
            }else if(ch=='='){
                return Token(NEQ, "", *linenum);
                lexeme = "";
                state = FIR;
            }else{
                return Token(ERR, "", *linenum);
            }            

        }

        if(state == LTT){

            if(ch == '>'){
                lexeme +=ch;
            }else{
                return Token(LT, "", *linenum);
                in->putback(ch);
                lexeme = "";
                state = FIR;
            }

        }

        if(state == GTT){

            if(ch == '<'){
                lexeme +=ch;
            }else{
                return Token(GT, "", *linenum);
                in->putback(ch);
                lexeme = "";
                state = FIR;
            }
        }

        if(state == AND){

            if(ch='&'){
                if(lexeme=="&"){
                    return Token(LOGICAND, "", *linenum);
                    lexeme = "";
                    state = FIR;
                }
                lexeme+=ch;
            }else{
                return Token(ERR, "", *linenum);
            }
        }

        if(state == ORR){

            if(ch='|'){
                if(lexeme=="|"){
                    return Token(LOGICOR, "", *linenum);
                    lexeme = "";
                    state = FIR;
                }
                lexeme+=ch;
            }else{
                return Token(ERR, "", *linenum);
            }

        }


        if(state == LET){

            if(state == LET && isalnum(ch)){
                lexeme += ch;
                if(lexeme == "print"){
                    return Token(PRINT, lexeme, *linenum);
                    state=FIR;
                    lexeme="";
                    nK = false;
                }else if(lexeme == "if"){
                    return Token(IF, lexeme, *linenum);
                    state=FIR;
                    lexeme="";
                    nK = false;
                }else if(lexeme == "then"){
                    return Token(THEN, lexeme, *linenum);
                    state=FIR;
                    lexeme="";
                    nK = false;
                }else if(lexeme == "true"){
                    return Token(TRUE, lexeme, *linenum);
                    state=FIR;
                    lexeme="";
                    nK = false;
                }else if(lexeme == "false"){
                    return Token(FALSE, lexeme, *linenum);
                    lexeme="";
                    state=FIR;
                    nK = false;
                }
            }else if(state == LET && nK){

                if(ch=='\n'){
                    ch = ' ';
                    in->putback(ch);
                    continue;
                }
                    in->putback(ch);
                    return Token(IDENT, lexeme, *linenum);
                    state=FIR;
                    lexeme="";
                
            }


        }

        if(state == QUO){

            if(fQ){
                fQ = false;
            }else if(ch!='"' && ch!='\n'){
                lexeme += ch;
            }else if(fQ == false && ch=='"'){
                //cout << lexeme << endl;
                return Token(SCONST, lexeme, *linenum);
                lexeme = "";
                state = FIR;
            }else if(ch=='\n' && ch != '"'){
                return Token(ERR, lexeme, *linenum);
                break;
            }
            


        }

        if(state == NUM){

            //cout << "NUM" << ch << endl;
            if(state == NUM && isdigit(ch)){
                lexeme += ch;
            }else if(state == NUM){
                in->putback(ch);
                return Token(ICONST, lexeme, *linenum);
                lexeme = "";
                state = FIR;
            }

        }

        if(state == OPE){

            if(ch=='+'){
                return Token(PLUS, "", *linenum);
                lexeme = FIR;
            }else if(ch=='-'){
                return Token(MINUS, "", *linenum);
                lexeme = FIR;
            }else if(ch=='*'){
                return Token(STAR, "", *linenum);
                lexeme = FIR;
            }else if(ch=='/'){
                return Token(SLASH, "", *linenum);
                lexeme = FIR;
            }else if(ch=='('){
                return Token(LPAREN, "", *linenum);
                lexeme = FIR;
            }else if(ch==')'){
                return Token(RPAREN, "", *linenum);
                lexeme = FIR;
            }else if(ch==';'){
                return Token(SC, "", *linenum);
                lexeme = FIR;
            }

        }

        if(state == COM){

            //cout << "comment" << ch << endl;
            if(ch=='\n'){
                state=FIR;
            }
        }

    }



    return Token(DONE, "", *linenum);
        
    
}

extern ostream& operator<<(ostream& out, const Token& tok){

    const char* s = 0;
    #define PROCESS_VAL(p) case(p): s = #p; break;

    switch(tok.GetTokenType()){

        PROCESS_VAL(PLUS);
        PROCESS_VAL(MINUS);
        PROCESS_VAL(STAR);
        PROCESS_VAL(SLASH);
        PROCESS_VAL(SCONST);
        PROCESS_VAL(IF);
        PROCESS_VAL(THEN);
        PROCESS_VAL(TRUE);
        PROCESS_VAL(FALSE);
        PROCESS_VAL(PRINT);
        PROCESS_VAL(IDENT);
        PROCESS_VAL(ICONST);            
        PROCESS_VAL(ASSIGN);    
        PROCESS_VAL(EQ);
        PROCESS_VAL(NEQ);
        PROCESS_VAL(LT);    
        PROCESS_VAL(LEQ);    
        PROCESS_VAL(GT);    
        PROCESS_VAL(GEQ);
        PROCESS_VAL(LOGICAND);
        PROCESS_VAL(LOGICOR);
        PROCESS_VAL(LPAREN);
        PROCESS_VAL(RPAREN);
        PROCESS_VAL(SC);
        PROCESS_VAL(ERR);
        case DONE:
            break;



    }
#undef PROCESS_VAL

        return out << s;
    
}


