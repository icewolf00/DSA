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
int n1,n2;
vector<double> Pitch;
vector<double> Note;
vector<int> Answer;
double total[1000][1000];
double Distance[1000][1000];
bool used[1000][1000] = {0};

double mi(double a, double b){
	if(a < b){
		return a;
	}
	return b;
}

double running(int y, int x){
	//printf("yee\n");
	if(used[y][x] == 1){
		return total[y][x];
	}
	used[y][x] = 1;
	if(x == n1 - 1){
		total[y][x] = abs(Pitch[x] - Note[y]);
		//return total[y][x];
	}
	else if(y == n2 - 1){
		total[y][x] = abs(Pitch[x] - Note[y]) + running(y,x+1);
		//return total[y][x];
	}
	else total[y][x] = abs(Pitch[x] - Note[y]) + mi(running(y,x+1), running(y+1,x+1));
	return total[y][x];
}

int main(void){
	scanf("%d", &n1);
	double p;
	for(int i = 0; i < n1; i ++){
		scanf("%lf", &p);
		Pitch.push_back(p);
	}
	scanf("%d", &n2);
	double q;
	for(int j = 0; j < n2; j ++){
		scanf("%lf", &q);
		Note.push_back(q);
	}
    printf("%f\n",running(0,0));
    int flag = 0;
    Answer.push_back(0);
    for(int j = 0; j < n1; j ++){
    	if(flag == n2-1){
    		break;
    	}
    	if(total[flag][j + 1] > total[flag + 1][j + 1]){
    		Answer.push_back(j+1);
    		flag++;
    	}
    }
    int sizee = Answer.size();
    //printf("%d\n", sizee);
    for(int i = 0; i < sizee - 1; i ++){
    	printf("%d ", Answer[i]);
    }
    printf("%d\n", Answer[sizee - 1]);
}