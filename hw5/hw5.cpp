#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <locale>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
vector<vector<string>> Dict;  //133784
//vector<string> Dict[133790];
//vector<int> countt;

int inDict(string &str1){
    unsigned long hashnum = 5381;
    int size1 = str1.size();
    for(int i = 0; i < size1; i++){
        hashnum = ((hashnum << 5) + hashnum) + str1[i];
    }
    int size2 = Dict[hashnum % 1339107].size();
    for(int j = 0; j < size2; j++){
        if(str1 == Dict[hashnum % 1339107][j]){
            return 1;
        }
    }
    return 0;
}

void Insert(string &str2, vector<string> &sugg, vector<string> &toprint, int act){
    int size = str2.size();
    if(act == 1){
        for(int i = 0; i <= size; i++){
            for(int j = 'a'; j <= 'z'; j ++){
                str2.insert(i, 1, j);
                sugg.push_back(str2);
                if(inDict(str2)){
                    toprint.push_back(str2);
                }
                str2.erase(i, 1);
            }
        }
    }
    if(act == 2){
        for(int i = 0; i <= size; i++){
            for(int j = 'a'; j <= 'z'; j ++){
                str2.insert(i, 1, j);
                if(inDict(str2)){
                    toprint.push_back(str2);
                }
                str2.erase(i, 1);
            }
        }
    }
    
}

void Delete(string &str3, vector<string> &sugg, vector<string> &toprint, int act){
    string temp;
    int size = str3.size();
    if(act == 1){
        for(int i = 0; i < size; i ++){
            temp = str3;
            temp.erase(i, 1);
            if(inDict(temp)){
                toprint.push_back(temp);
            }
            sugg.push_back(temp);
        }
    }
    if(act == 2){
        for(int i = 0; i < size; i ++){
            temp = str3;
            temp.erase(i, 1);
            if(inDict(temp)){
                toprint.push_back(temp);
            }
        }
    }
}

void Substitute(string &str4, vector<string> &sugg, vector<string> &toprint, int act){
    string temp;
    int size = str4.size();
    if(act == 1){
        for(int i = 0; i < size; i ++){
            for(int j = 'a'; j <= 'z'; j ++){
                temp = str4;
                temp[i] = j;
                if(inDict(temp)){
                    toprint.push_back(temp);
                }
                sugg.push_back(temp);
            }
        }
    }
    if(act == 2){
        for(int i = 0; i < size; i ++){
            for(int j = 'a'; j <= 'z'; j ++){
                temp = str4;
                temp[i] = j;
                if(inDict(temp)){
                    toprint.push_back(temp);
                }
            }
        }
    }
}

void Transpose(string &str5, vector<string> &sugg, vector<string> &toprint, int act){
    string temp;
    int size = str5.size();
    if(act == 1){
        for(int i = 0; i < size - 1; i ++){
            temp = str5;
            string temp2;
            temp2[0] = str5[i];
            temp[i] = temp[i + 1];
            temp[i + 1] = temp2[0];
            if(inDict(temp)){
                toprint.push_back(temp);
            }
            sugg.push_back(temp);
        }
    }
    if(act == 2){
        for(int i = 0; i < size - 1; i ++){
            temp = str5;
            string temp2;
            temp2[0] = str5[i];
            temp[i] = temp[i + 1];
            temp[i + 1] = temp2[0];
            if(inDict(temp)){
                toprint.push_back(temp);
            }
        }
    }
    
}

void hashh(string &strrr){
    unsigned long hashnum = 5381;
    int size = strrr.size();
    for(int i = 0; i < size; i++){
        hashnum = ((hashnum << 5) + hashnum) + strrr[i]; //*33
    }
    Dict[hashnum % 1339107].push_back(strrr);
    //countt[hashnum % 133784]++;
}

int main(void){
    Dict.resize(1339107, vector<string>(0));
    FILE *fp = fopen("/tmp2/dsa2016_hw5/cmudict-0.7b","rb");
    char readinn[128];
    while(fgets(readinn, 128, fp) != NULL){
        istringstream input(readinn);
        string tohash;
        input >> tohash;
        int size3 = tohash.size();
        for(int i = 0; i < size3; i++){
            tohash[i] = tolower(tohash[i]);
        }
        hashh(tohash);
    }
    fclose(fp);
    char fromio[128];
    while(fgets(fromio, 128, stdin) != NULL){
            istringstream input1(fromio);
            string toact;
            input1 >> toact;
            printf("%s ==>",toact.c_str());
            if(inDict(toact)){
                printf(" OK\n");
            }
            else{
                vector<string> sugg;
                vector<string> toprint;
                Insert(toact, sugg, toprint, 1);
                Delete(toact, sugg, toprint, 1);
                Substitute(toact, sugg, toprint, 1);
                Transpose(toact, sugg, toprint, 1);
                sort(sugg.begin(), sugg.end());
                std::vector<string>::iterator it;
                it = std::unique (sugg.begin(), sugg.end());
                sugg.resize(distance(sugg.begin(), it));
                int size = sugg.size();
                for(int i = 0; i < size; i++){
                    string sssss = sugg[i];
                    Insert(sssss, sugg, toprint, 2);
                    Delete(sssss, sugg, toprint, 2);
                    Substitute(sssss, sugg, toprint, 2);
                    Transpose(sssss, sugg, toprint, 2);
                }
                sort(toprint.begin(), toprint.end());
                it = std::unique (toprint.begin(), toprint.end());
                toprint.resize(distance(toprint.begin(), it));
                int size4 = toprint.size();
                for(int i = 0; i < size4; i++){
                    printf(" %s", toprint[i].c_str());
                }
                if(size4 == 0){
                    printf(" NONE");
                }
                printf("\n");
            }
    }
}