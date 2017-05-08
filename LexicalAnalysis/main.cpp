//
//  main.cpp
//  LexicalAnalysis
//
//  Created by Daisy Tang on 17/5/7.
//  Copyright © 2017年 Daisy Tang. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <streambuf>

using namespace std;
const int START = 1;
const int DONE = 15;
const int ERROR = 16;


int main(int argc, const char * argv[]) {
    // 读入文件到buffer
    string testFile[3] = {"test1.txt", "test2.txt", "test3.txt"};
    
    
    string outFile = "tokenOut.txt";
    ofstream out(outFile);
    cout.rdbuf(out.rdbuf());
    
    for (int i = 0; i<3; i++) {
        ifstream in(testFile[i]);
        stringstream buffer;
        buffer << in.rdbuf();
        if (!in) {
            cout << testFile[i] << ": file not found" << endl << endl;
            continue;
        }
        
        cout << "File: " << testFile[i] << ": " << endl << endl;
        int lineNo = 0; // 行号
        
        // 读入行
        string line;
        while (getline(buffer,line)) {
            lineNo++;
            cout <<"Line: " << lineNo << endl;
            
            int pos = 0;
            int state = START;
            char next;
            bool rollback = false;
            while (pos < line.length()) {
                string token = "";
                string info = "";
                while (state >= START && state < DONE && pos < line.length()) {
                    if (!rollback) {
                        next = line[pos];
                        pos++;
                    }else{
                        rollback = false;
                    }
                    //                cout << next;
                    //                cout << state;
                    //                cout << rollback;
                    
                    switch (state) {
                        case START:
                            if(isdigit(next)){
                                state = 3;
                                token += next;
                                break;
                            }
                            if (isalpha(next)) {
                                state = 6;
                                token += next;
                                break;
                            }
                            switch (next) {
                                case ':':
                                    state = 9;
                                    token += next;
                                    break;
                                case '=':
                                    state = 11;
                                    token += next;
                                    break;
                                case '-':
                                    state = 14;
                                    token += next;
                                    break;
                                case '+':
                                    state = 13;
                                    token += next;
                                    break;
                                case ';':
                                case '{':
                                case '}':
                                    state = DONE;
                                    token += next;
                                    break;
                                case ' ':
                                case '\t':
                                case '\r':
                                case '\n':
                                    break;
                                default:
                                    state = ERROR;
                                    info = "Ungood Symbol";
                                    break;
                            }
                            break;
                            
                        case 2:
                            break;
                            
                        case 3:
                            if(isdigit(next)){
                                state = 3;
                                token += next;
                            }
                            else if (next=='.') {
                                state = 4;
                                token += next;
                            }else{
                                state = ERROR;
                                info = "Decimal parse error";
                                continue;
                            }
                            break;
                            
                        case 4:
                            if(isdigit(next)){
                                state = 5;
                                token += next;
                            }else{
                                state = ERROR;
                                info = "Decimal parse error";
                                continue;
                            }
                            break;
                        case 5:
                            if (isdigit(next)) {
                                token += next;
                                break;
                            }else{
                                state = DONE;
                                rollback = true;
                            }
                            break;
                            
                        case 6:
                            if (next == '_') {
                                state = 7;
                                token += next;
                            }else if (isdigit(next)||isalpha(next)) {
                                state = 8;
                                token += next;
                            }else{
                                state = DONE;
                                rollback = true;
                            }
                            break;
                            
                        case 7:
                            if (isdigit(next)||isalpha(next)) {
                                state = 8;
                                token += next;
                            }else {
                                state = ERROR;
                                info = "Identifier parse error";
                            }
                            break;
                            
                        case 8:
                            if (isdigit(next)||isalpha(next)) {
                                state = 6;
                                token += next;
                            }else if(next == '_') {
                                state = 7;
                                token += next;
                            }else {
                                state = DONE;
                                rollback = true;
                            }
                            break;
                            
                        case 9:
                            if (next == ':') {
                                state = 10;
                                token += next;
                            }else{
                                state = DONE;
                                rollback = true;
                            }
                            break;
                            
                        case 10:
                            state = DONE;
                            rollback = true;
                            break;
                            
                        case 11:
                            if (next == '>') {
                                state = 12;
                                token += next;
                            }else
                                state = ERROR;
                            info = "Symbol spell error";
                            break;
                            
                        case 12:
                            state = DONE;
                            rollback = true;
                            break;
                            
                        case 13:
                            if (isdigit(next)) {
                                state = 3;
                                token += next;
                            }else if(next == '='){
                                state = 11;
                                token += next;
                            }else{
                                state = ERROR;
                                info = "Symbol spell error";
                            }
                            break;
                            
                        case 14:
                            if (isdigit(next)) {
                                state = 3;
                                token += next;
                            }else if(next == '>'){
                                state = 12;
                                token += next;
                            }else{
                                state = ERROR;
                                info = "Symbol spell error";
                            }
                            break;
                            
                        default:
                            break;
                    }
                }
                if (state == DONE) {
                    cout << token << endl;
                    token = "";
                    state = START;
                }else if(state == ERROR) {
                    cout << "Line " << lineNo << " Error:" << endl
                    << info << " when parsing { " << next << " }" << endl;
                    break;
                }
            }
        }
        
        cout <<"Line: " << ++lineNo << " EOF" << endl << endl;
        
    }
        return 0;
}
