#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<int> rowinput[32];
vector<int> colinput[32];
int plate[32][32]={{0}};
int row, column;

void clean(){
    for(int i = 0; i < 32; i ++){
        for(int j = 0; j < 32; j ++){
            plate[i][j] = 0;
        }
    }
}

int checkrow(int now){
    int r = now / column;
    int c = now % column;
    int count = 0;
    int place = 0;
    int flag = 0;
    if(plate[r][c] == 1){
        for(int i = 0; i < c; i ++){
            if(plate[r][i] == 1){
               count ++;
               flag = 1;
               if(count > rowinput[r][place]){
                   return -1;
               }
            }
            if(plate[r][i] == -1){
               if(flag == 1){
                   if(count != rowinput[r][place]){
                       return -1;
                   }
                   place ++;
               }
               count = 0;
               flag = 0;
            }
        }
        if(c == (column - 1)){
            if((count+1) != rowinput[r][place] || (place + 1) != rowinput[r].size()){
               return -1;
            }
        }
        if((count+1) > rowinput[r][place]){
            return -1;
        }
        return 1;
    }
    if(plate[r][c] == -1){
        for(int i = 0; i < c; i ++){
            if(plate[r][i] == 1){
               count ++;
               flag = 1;
               if(count > rowinput[r][place]){
                   return -1;
               }
            }
            if(plate[r][i] == -1){
               if(flag == 1){
                   if(count != rowinput[r][place]){
                       return -1;
                   }
                   place ++;
               }
               count = 0;
               flag = 0;
            }
        }
        if(c == (column - 1)){
            if(plate[r][c - 1] == 1){
               if((place + 1) != rowinput[r].size()){
                 return -1;
               }
            }
            else if(place != rowinput[r].size()){
               return -1;
            }
        }
        if(flag == 1){
            if(count < rowinput[r][place]){
               return -1;
            }
        }
        return 1;
    }
}

int checkcol(int now){
    int r = now / column;
    int c = now % column;
    int count = 0;
    int place = 0;
    int flag = 0;
    if(plate[r][c] == 1){
        for(int i = 0; i < r; i ++){
            if(plate[i][c] == 1){
               count ++;
               flag = 1;
               if(count > colinput[c][place]){
                   return -1;
               }
            }
            if(plate[i][c] == -1){
               if(flag == 1){
                   if(count != colinput[c][place]){
                       return -1;
                   }
                   place ++;
               }
               count = 0;
               flag = 0;
            }
        }
        if(r == (row - 1)){
            if((count+1) != colinput[c][place] || (place + 1) != colinput[c].size()){
               return -1;
            }
        }
        if((count+1) > colinput[c][place]){
            return -1;
        }
        return 1;
    }
    else if(plate[r][c] == -1){
        for(int i = 0; i < r; i ++){
            if(plate[i][c] == 1){
               count ++;
               flag = 1;
               if(count > colinput[c][place]){
                   return -1;
               }
            }
            if(plate[i][c] == -1){
               if(flag == 1){
                   if(count != colinput[c][place]){
                       return -1;
                   }
                   place ++;
               }
               count = 0;
               flag = 0;
            }
        }
        if(r == (row - 1)){
            if(plate[r - 1][c] == 1){
               if((place + 1) != colinput[c].size()){
                 return -1;
               }
            }
            else if(place != colinput[c].size()){
               return -1;
            }
        }
        if(flag == 1){
            if(count != colinput[c][place]){
               return -1;
            }
        }
        return 1;
    }
}

int find(int now){
    if(now == row * column && checkrow(now-1)==1 && checkcol(now-1)==1){
        return 1;
    }
    int r = now / column;
    int c = now % column;
    plate[r][c] = 1;
    if(checkrow(now) == 1 && checkcol(now) == 1){
        if(find(now + 1)){
            return 1;
        }
    }
    plate[r][c] = -1;
    if(checkrow(now) == 1 && checkcol(now) == 1){
        if(find(now + 1)){
            return 1;
        }
    }
    //plate[r][c] = 0;
    return 0;
}

int ReadInt(int *x) {
    char c;
    while((c = getchar()) < '-'){
    	if(c == EOF){
    		return 0;
    	}
      if(c == 10){
        return 3;
      }
    }
    *x = c - '0';
    while((c = getchar()) >= '0'){
    	*x = (*x << 3) + (*x << 1) + c-'0';
    }
    if(c == ' '){
    	return 2;
    }
    return 1;
}

int main(void){
	  //scanf("%d%d\n", &row, &column);
    string s1;
    getline(cin, s1);
    int tempp;
    istringstream input(s1);
    input >> row;
    input >> column;
    for(int i = 0; i < row; i ++){
        string s;
        getline(cin, s);
        int tempinput;
        istringstream input(s);
        while(input >> tempinput){
            rowinput[i].push_back(tempinput);
        }
    }
    for(int i = 0; i < column; i ++){
        string s;
        getline(cin, s);
        int tempinput;
        istringstream input(s);
        while(input >> tempinput){
            colinput[i].push_back(tempinput);
        }
    }
	  /*for(int i = 0; i < row; i ++){
		  int temp1, temp2;
		  while ((temp1 = ReadInt(&temp2)) > 0){
          if(temp1 == 3){
            break;
          }
        	if(temp1 == 1){
        	  	rowinput[i].push_back(temp2);
        		  break;
        	}
          if(temp1 == 2){
          		rowinput[i].push_back(temp2);
          }
      }
	  }
	  for(int i = 0; i < column; i ++){
		   int temp1, temp2;
		   while ((temp1 = ReadInt(&temp2)) > 0){
          if(temp1 == 3){
            break;
          }
         	if(temp1 == 1){
        		colinput[i].push_back(temp2);
        		break;
        	}
        	if(temp1 == 2){
        		colinput[i].push_back(temp2);
        	}
       }
	  }*/
    clean();
    if(find(0) == 1){
        for(int i = 0; i < row; i ++){
            for(int j = 0; j < column; j ++){
                if(plate[i][j] == 0 || plate[i][j] == -1){
                    printf(".");
                }
                if(plate[i][j] == 1){
                    printf("#");
                }
            }
            printf("\n");
        }
    }
    return 0;
}