/* machine learning lab 3 for cs 235
* John Ellis
* 11/10/21 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <list>

using namespace std;

int main(int argc, char* argv[]){

    vector<string> tokens;
    set<string> unique;
    string fileName = argv[1];
    string fileName2;
    ifstream file1(fileName);
    ifstream file2;
    string text, line, line1, line2;
    string cleanLine;
    string cleanText;


    /**************** remove .txt ****************/

    string tmp = "";
    for(int i = 0; i < fileName.length() - 4; i++){
        tmp += fileName[i];
    }
    fileName = tmp;

    if(argc > 2){
        fileName2 = argv[2];
        file2.open(fileName2);

        tmp = "";
        for(int i = 0; i < fileName2.length() - 4; i++){
            tmp += fileName2[i];
        }
        fileName2 = tmp;
    }

    int k;
    while(getline(file1, cleanLine)){
        k = 0;
        for(auto &c : cleanLine){
            k += 1;
            if((c == '.') && k > 30){
                cleanText += c;
                cleanText += ' ';
                cleanText += "\n";
                k = 0;
            
            } else if(c == '.'){
                cleanText += c;
                cleanText += ' ';

            } else if(c == '\n'){
                cleanText += ' ';
                cleanText += c;

            } else{cleanText += c;}
        } cleanText += ' ';
    }
    file1.close();
    ofstream outClean(fileName + "_mod.txt");
    outClean << cleanText;
    outClean.close();


    if(argc > 2){
        cleanLine = "";
        cleanText = "";
        while(getline(file2, cleanLine)){
            k = 0;
            for(auto &c : cleanLine){
                k += 1;
                if((c == '.') && k > 30){
                    cleanText += c;
                    cleanText += ' ';
                    cleanText += "\n";
                    k = 0;
                
                } else if(c == '.'){
                    cleanText += c;
                    cleanText += ' ';

                } else if(c == '\n'){
                    cleanText += ' ';
                    cleanText += c;

                } else{cleanText += c;}
                
            } cleanText += ' ';
        }
        file2.close();
        outClean.open(fileName2 + "_mod.txt");
        outClean << cleanText;
        outClean.close();
    }


    /**************** remove blank lines and if 2 speeches mash ****************/
    file1.open(fileName + "_mod.txt");

    if(argc > 2){
        file2.open(fileName2 + "_mod.txt");

        while(!file1.eof() && !file2.eof()){
            getline(file1, line1);
            if (!line1.empty() && line1.find_first_not_of(' ') != std::string::npos){
                text += line1;
                if(text[text.length() - 1] != ' '){text += ' ';}
            }
            getline(file2, line2);
            if (!line2.empty() && line2.find_first_not_of(' ') != std::string::npos){
                text += line2;
                if(text[text.length() - 1] != ' '){text += ' ';}
            }
        }
        file2.close();
        fileName += '_' + fileName2;

    } else{
        while(getline(file1, line1)) {            
            if (!line1.empty() && line1.find_first_not_of(' ') != std::string::npos){
                text += line1;
            }
        }
    }

    file1.close();

    //cout << "\n\n"<< text << "\n\n";

    
    
    /**************** put mixed speeches into file ****************/

    ofstream out;
    if(argc > 2){
        out.open(fileName + "_comb.txt");
    } else{out.open(fileName + "_mod.txt");}
    out << text;
    out.close();
    
    /******** populate tokens vector without punctuation ********/

    ifstream file;
    if(argc > 2){
        file.open(fileName + "_comb.txt");
    } else{file.open(fileName + "_mod.txt");}
    while(getline(file, line)){
        istringstream iss(line);
        string token;
        while(iss >> token){
            //string nopunct = "";
            // for(auto &c : token){
            //     if(isalpha(c) && c != ' '){
            //         nopunct += c;
            //     }
            // }
            if(token != " ." && token != " . " && token != ". " && token != "." && token != "  " && token != "-" && token != "\"" && token != " \"" && token != "\'" && token != ".." && token != "  " && token != " \" " && token != "\"  "){
                tokens.push_back(token);
                unique.insert(token);
            }
        }  
    }
    cout << "Number of words " << tokens.size() << endl;
    cout << "Number of unique words " << unique.size() << endl;

    /**************** make a txt of the set ****************/
    
    ofstream setFile(fileName + "_set.txt");
    for(set<string>::iterator it = unique.begin(); it != unique.end(); it++){
        setFile << *it << ' ';
    }
    setFile.close();


    /**************** make a txt of the vector ****************/

    setFile.open(fileName + "_tokens.txt");
    for(vector<string>::iterator it = tokens.begin(); it != tokens.end(); it++){
        setFile << *it << ' ';
    }
    setFile.close();


    /**************** vetor values go to a map ****************/

    // setFile.open(fileName + "_map.txt");
    // map<string, string> kartaOrd;
    // string last = *tokens.begin();
    // for(vector<string>::iterator it = tokens.begin() + 1; it != tokens.end(); it++){
    //     //setFile << last << ": " << *it << endl;
    //     kartaOrd[last] = *it;
    //     last = *it;
    // }
    // for(map<string, string>::iterator it = kartaOrd.begin(); it != kartaOrd.end(); it++){
    //     setFile << it->first << " & " << it->second << ';' << endl;
    // }
    // setFile.close();

    // string state = "";
    // for(int i = 0; i < 100; i++){
    //     cout << kartaOrd[state] << " ";
    //     state = kartaOrd[state];
    // }
    // cout << endl;

    // map<string, vector<string> > kartaOrdBest;
    // string state = "";
    // for(vector<string>::iterator it=tokens.begin(); it !=tokens.end(); it++) {
    //     kartaOrdBest[state].push_back(*it);
    //     state = *it;
    // }

    // srand(time(NULL));

    // state = "";
    // for (int i = 0; i < 200; i++) {
    //     int ind = rand() % kartaOrdBest[state].size();
    //     cout << kartaOrdBest[state][ind] << " ";
    //     state = kartaOrdBest[state][ind];
    // }
    // cout << endl;
    
    map<list<string>, vector<string>> kartaOrd;
    list<string> state;
    int m = 4;
    for (int i = 0; i < m; i++) {
        state.push_back("");
    }
                
    for (vector<string>::iterator it=tokens.begin(); it!=tokens.end(); it++) {
        kartaOrd[state].push_back(*it);
        state.push_back(*it);
        state.pop_front();
    }
    ofstream finalSpeech(fileName + "_final.txt");
    state.clear();
    for (int i = 0; i < m; i++) {
        state.push_back("");
    }

    string ending;
    int lengthSpeech;
    lengthSpeech = stoi(argv[3]);

    if(lengthSpeech > tokens.size()){
        lengthSpeech = tokens.size()*0.3;
    }
    if(lengthSpeech > 0.85*tokens.size()){
        lengthSpeech *= 0.5;
    }
    if(lengthSpeech*2 > 0.8*tokens.size()){
        lengthSpeech *= 0.5;
    }
    

    for (int i = 0; i < lengthSpeech; i++) {
        //srand(time(NULL));
        int ind = rand() % kartaOrd[state].size();
        if(i > lengthSpeech - 40){
            ending = kartaOrd[state][ind];
            if(ending[ending.length() -1] == '.'){
                finalSpeech << kartaOrd[state][ind] << " ";
                state.push_back(kartaOrd[state][ind]);
                state.pop_front();
                break;
            }
        }
        finalSpeech << kartaOrd[state][ind]<<" ";
        state.push_back(kartaOrd[state][ind]);
        state.pop_front();
    }
    
    for (int i = 0; i < lengthSpeech; i++) {
        //srand(time(NULL));
        int ind = rand() % kartaOrd[state].size();
        if(i > lengthSpeech - 40){
            ending = kartaOrd[state][ind];
            if(ending[ending.length() -1] == '.'){
                finalSpeech << kartaOrd[state][ind];
                break;
            }
        }
        finalSpeech << kartaOrd[state][ind]<<" ";
        state.push_back(kartaOrd[state][ind]);
        state.pop_front();
    }

    finalSpeech.close();

    // fstream clean(fileName + "_final.txt");

    // string bean;
    // string green;
    // string finalCleaned;
    // while(!clean.eof()){
    //     clean >> bean >> green;
    //     if(bean != green){
    //         finalCleaned += bean + ' ' + green + " ";
    //     }
    // }
    // clean.close();
    // clean.open(fileName + "_final.txt");
    // clean << finalCleaned;
    // clean.close();

    return 0;
}