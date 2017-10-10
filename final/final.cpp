#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <locale>
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct unknown
{
    string x;
    int freq;
    unknown(){}
    unknown(string s, int fr){
        x = s;
        freq = fr;
    }
    bool operator == (const unknown temp) const{
        return (x == temp.x) &&
               (freq == temp.freq);
    }
}Unknown;

typedef struct uunit
{
    vector<Unknown> a;
}Unit;

bool cmp(Unknown a, Unknown b){
    if(a.freq != b.freq){
        return a.freq > b.freq;
    }
    return a.x < b.x;
}

vector<Unit> Dict;
string Preposition[20] = {"of","to","in","for","with","on","at","by","from","up","about","than","after","before","down","between","under","since","without","near"};

int inhash(string &str1, int &freq){
    unsigned long hashnum = 5381;
    int size1 = str1.size();
    for(int i = 0; i < size1; i++){
        hashnum = ((hashnum << 5) + hashnum) + str1[i];
    }
    int nnn = hashnum % 13391077;
    int size2 = Dict[nnn].a.size();
    for(int j = 0; j < size2; j++){
        if(str1 == Dict[nnn].a[j].x){
            freq = Dict[nnn].a[j].freq; 
            return 1;
        }
    }
    return 0;
}

void nonPreposition(vector<string> &todo, vector<Unknown> &Answer){
    int size1 = todo.size();
    vector<vector<string>> sugg;
    for(int i = 0; i <= size1; i ++){
        for(int j = 0; j < 20; j ++){
            todo.insert(todo.begin() + i, Preposition[j]);
            sugg.push_back(todo);
            Unknown temp2;
            temp2.x = todo[0];
            for(int k = 1; k < size1 + 1; k ++){
                temp2.x += " ";
                temp2.x += todo[k];
            }
            if(inhash(temp2.x, temp2.freq) == 1){
                Answer.push_back(temp2);
            }
            todo.erase(todo.begin() + i);
        }
    }
    int size3 = sugg.size();
    for(int i = 0; i < size3; i ++){
        int size4 = sugg[i].size();
        for(int j = 0; j <= size4; j ++){
            for(int k = 0; k < 20; k ++){
                sugg[i].insert(sugg[i].begin() + j, Preposition[k]);
                Unknown temp2;
                temp2.x = sugg[i][0];
                for(int l = 1; l < size4 + 1; l ++){
                    temp2.x += " ";
                    temp2.x += sugg[i][l];
                }
                if(inhash(temp2.x, temp2.freq) == 1){
                    Answer.push_back(temp2);
                }
                sugg[i].erase(sugg[i].begin() + j);
            }
        }
    }
}

void Recursion(vector<vector<string>> &sugg, int prenow, int ssize, vector<vector<string>> &test, vector<string> &todo, int now, vector<int> &preloc, vector<Unknown> &Answer){
    if(now == ssize){
        //printf("yes\n");
        int size8 = test.size();
        for(int i = 0; i < size8; i ++){
            int newsize = test[i].size();
            /*if(newsize > 5){
                continue;
            }*/
            Unknown yesss;
            yesss.x = test[i][0];
            if(newsize >= 2){
                if(test[i][0] == ""){
                    yesss.x += test[i][1];
                    for(int j = 2; j < newsize; j ++){
                        if(test[i][j] != ""){
                            yesss.x += " ";
                            yesss.x += test[i][j];
                        }
                    }
                }
                else{
                    for(int j = 1; j < newsize; j ++){
                        if(test[i][j] != ""){
                            yesss.x += " ";
                            yesss.x += test[i][j];
                        }
                    }
                }
            }
            if(inhash(yesss.x, yesss.freq) == 1){
                Answer.push_back(yesss);
            }
        }
        return;
    }
    if(now == 0){
        if(preloc[now] == 1){
            vector<string> tempp;
            tempp.resize(0);
            int siize = sugg[0].size();
            int endpoint = now;
            int flag = 0;
            for(int i = now; i < preloc.size(); i ++){
                if(preloc[i] == 0){
                    endpoint = i;
                    flag = 1;
                    break;
                }
            }
            for(int i = 0; i < siize; i ++){
                tempp.push_back(sugg[0][i]);
                test.push_back(tempp);
                tempp.pop_back();
            }
            if(flag == 0){
                Recursion(sugg, prenow + 1, ssize, test, todo, preloc.size(), preloc, Answer);
            }
            else{
                Recursion(sugg, prenow + 1, ssize, test, todo, endpoint, preloc, Answer);
            }
               
        }
        else if(preloc[now] == 0){
            vector<string> tempp;
            tempp.resize(0);
            tempp.push_back(todo[now]);
            test.push_back(tempp);
            Recursion(sugg, prenow, ssize, test, todo, now + 1, preloc, Answer);
        }
    }
    else if(preloc[now] == 1){
        int endpoint1 = now;
        int flag = 0;
        for(int i = now; i < preloc.size(); i ++){
            if(preloc[i] == 0){
                endpoint1 = i;
                flag = 1;
                break;
            }
        }
        int size9 = test.size();
        int sizze = sugg[prenow].size();
        for(int i = 0; i < size9; i ++){
            vector<string> teemp;
            teemp.resize(0);
            for(int k = 0; k < test[i].size(); k ++){
                teemp.push_back(test[i][k]);
            }
            for(int j = 0; j < sizze; j ++){
                teemp.push_back(sugg[prenow][j]);
                test.push_back(teemp);
                teemp.pop_back();
            }
        }
        for(int i = 0; i < size9; i ++){
            test.erase(test.begin());
        }
        if(flag == 0 && endpoint1 == now){
            Recursion(sugg, prenow + 1, ssize, test, todo, preloc.size(), preloc, Answer);
        }
        else if(now == endpoint1){
            Recursion(sugg, prenow + 1, ssize, test, todo, now + 1, preloc, Answer);
        }
        else{
            Recursion(sugg, prenow + 1, ssize, test, todo, endpoint1, preloc, Answer);
        }
    }
    else if(preloc[now] == 0){
        int size7 = test.size();
        for(int i = 0; i < size7; i ++){
            test[i].push_back(todo[now]);
        }
        Recursion(sugg, prenow, ssize, test, todo, now + 1, preloc, Answer);
    }
}

void Insert(vector<vector<string>> &sugg, vector<vector<string>> &newPrepo, int &sizee){
    for(int i = 0; i < sizee; i ++){
        int size6 = newPrepo[i].size();
        for(int j = 0; j <= size6; j ++){
            for(int k = 0; k < 20; k ++){
                newPrepo[i].insert(newPrepo[i].begin() + j, Preposition[k]);
                string temp2;
                temp2 = newPrepo[i][0];
                for(int l = 1; l < size6 + 1; l ++){
                    temp2 += " ";
                    temp2 += newPrepo[i][l];
                }
                sugg[i].push_back(temp2);
                newPrepo[i].erase(newPrepo[i].begin() + j);
            }
        }
    }
}

void Delete(vector<vector<string>> &sugg, vector<vector<string>> &newPrepo, int &sizee){
    for(int i = 0; i < sizee; i ++){
        vector<string> temp = newPrepo[i];
        int size1 = newPrepo[i].size();
        for(int j = 0; j < size1; j ++){
            newPrepo[i].erase(newPrepo[i].begin() + j);
            string temp2;
            if(newPrepo[i].size() == 0){
                sugg[i].push_back("");
            }
            else{
                temp2 = newPrepo[i][0];
                for(int l = 1; l < size1 - 1; l ++){
                    temp2 += " ";
                    temp2 += newPrepo[i][l];
                }
                sugg[i].push_back(temp2);
            }
            newPrepo[i] = temp;
        }
        newPrepo[i] = temp;
    }
}

void Substitute(vector<vector<string>> &sugg, vector<vector<string>> &newPrepo, int &sizee){
    for(int i = 0; i < sizee; i ++){
        vector<string> temp = newPrepo[i];
        int size2 = newPrepo[i].size();
        for(int j = 0; j < size2; j ++){
            for(int k = 0; k < 20; k ++){
                newPrepo[i][j] = Preposition[k];
                string temp2;
                temp2 = newPrepo[i][0];
                for(int l = 1; l < size2; l ++){
                    temp2 += " ";
                    temp2 += newPrepo[i][l];
                }
                sugg[i].push_back(temp2);
                newPrepo[i] = temp;
            }
            newPrepo[i] = temp;
        }
        newPrepo[i] = temp;
    }
}

void isPreposition(vector<string> &todo, vector<Unknown> &Answer, vector<int> &preloc, vector<vector<string>> &newPrepo){
    int sizee = newPrepo.size();
    vector<vector<string>> sugg;
    sugg.resize(sizee, vector<string>(0));
    Insert(sugg, newPrepo, sizee);
    Delete(sugg, newPrepo, sizee);
    Substitute(sugg, newPrepo, sizee);
    int ssize = todo.size();
    vector<vector<string>> test;
    test.resize(0, vector<string>(0));
    Recursion(sugg, 0, ssize, test, todo, 0, preloc, Answer);
}

void hashh(Unknown &todict){
    unsigned long hashnum = 5381;
    int size = todict.x.size();
    for(int i = 0; i < size; i++){
        hashnum = ((hashnum << 5) + hashnum) + todict.x[i]; //*33
    }
    Dict[hashnum % 13391077].a.push_back(todict);
}

int toread(FILE *fp, int Number){
    char readinn[256] = {'\0'};
    while(fgets(readinn, 256, fp) != NULL){
        int n1 = strlen(readinn);
        int brokepoint = 0;
        for(int i = 0;; i ++){
            if(readinn[i] == '\t'){
                brokepoint = i;
                break;
            }
        }
        string tohash;
        tohash.assign(readinn, 0, brokepoint);
        int frequ = 0;
        for(int i = brokepoint + 1; readinn[i] != '\n'; i ++){
            frequ = frequ * 10 + (readinn[i] - '0'); 
        }
        Unknown temp;
        temp.x = tohash;
        temp.freq = frequ;
        hashh(temp);
    }
}

int main(void){
    Dict.resize(13391077);
    FILE *fp1 = fopen("/tmp2/dsa2016_project/2gm.small.txt","rb");
    FILE *fp2 = fopen("/tmp2/dsa2016_project/3gm.small.txt","rb");
    FILE *fp3 = fopen("/tmp2/dsa2016_project/4gm.small.txt","rb");
    FILE *fp4 = fopen("/tmp2/dsa2016_project/5gm.small.txt","rb");
    toread(fp1, 2);
    toread(fp2, 3);
    toread(fp3, 4);
    toread(fp4, 5);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    char fromio[200] = {'\0'};
    while(fgets(fromio, 200, stdin) != NULL){
        istringstream input1(fromio);
        vector<string> todo;
        vector<int> preloc;
        vector<Unknown> sugg;
        string temp1 = "";
        int node = 0;
        int counter = 0;
        while(input1 >> temp1){
            preloc.push_back(0);
            for(int i = 0; i < 20; i ++){
                if(temp1 == Preposition[i]){
                    counter ++;
                    preloc.pop_back();
                    preloc.push_back(1);
                    break;
                }
            }
            todo.push_back(temp1);
        }
        vector<Unknown> Answer;
        Unknown temp3;
        temp3.x = todo[0];
        int size5 = todo.size();
        for(int j = 1; j < size5; j ++){
            temp3.x += " ";
            temp3.x += todo[j];
        }
        string s1 = temp3.x;
        if(inhash(temp3.x, temp3.freq) == 1){
            Answer.push_back(temp3);
        }
        if(counter == 0){
            nonPreposition(todo, Answer);
        }
        
        else{
            vector<vector<string>> newPrepo;
            int size6 = preloc.size();
            for(int i = 0; i < size6; i ++){
                if(preloc[i] == 1){
                    vector<string> ttemp;
                    ttemp.push_back(todo[i]);
                    while(preloc[i+1] == 1 && i+1 < size6){
                        ttemp.push_back(todo[i+1]);
                        i ++;
                    }
                    newPrepo.push_back(ttemp);
                }
            }
            isPreposition(todo, Answer, preloc, newPrepo);
        }
        sort(Answer.begin(), Answer.end(), cmp);
        int newlength = unique(Answer.begin(), Answer.end()) - Answer.begin();
        Answer.resize(newlength);
        if(newlength > 10){
            newlength = 10;
        }
        printf("query: %s\n", s1.c_str());
        printf("output: %d\n", newlength);
        for(int j = 0; j < newlength; j ++){
            printf("%s\t%d\n", Answer[j].x.c_str(), Answer[j].freq);
        }
    }
    return 0;
}