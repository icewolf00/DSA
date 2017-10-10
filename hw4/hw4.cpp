#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

typedef struct{
    int bidID;
    int clientID;
    int action;
    int price;
    int shareCount;
}stock;

struct cmp0{ 
    bool operator() (stock a, stock b ){ 
        if( a.price == b.price ){ 
        	return a.bidID > b.bidID;
        	//return a.price < b.price;
        }
        return a.price < b.price; } 
};//maxheap

struct cmp1{ 
    bool operator() (stock a, stock b ){ 
        if( a.price == b.price ){ 
        	return a.bidID > b.bidID;
        	//return a.price > b.price;
        }
        return a.price > b.price; } 
};//minheap

int transID = 0;
vector<stock> forbuy;
vector<stock> forsell;
vector<int> record;

void trans(){
	if(forbuy.size() == 0 || forsell.size() == 0){
		return;
	}
	stock buy = forbuy.front();
	stock sell = forsell.front();
	while(forbuy.size() != 0 && forsell.size() != 0 && buy.price >= sell.price){
		while(record[buy.bidID] == 0 || buy.shareCount == 0){
			pop_heap(forbuy.begin(), forbuy.end(), cmp0());
		    forbuy.pop_back();
		    if(forbuy.size() == 0){
		    	break;
		    }
		    buy = forbuy.front();
		}
		while(record[sell.bidID] == 0 || sell.shareCount == 0){
			pop_heap(forsell.begin(), forsell.end(), cmp1());
		    forsell.pop_back();
		    if(forsell.size() == 0){
		    	break;
		    }
		    sell = forsell.front();
		}
        if(forbuy.size() == 0 || forsell.size() == 0 || buy.price < sell.price){
        	break;
        }
        if(buy.shareCount > sell.shareCount){
		    printf("%d\t%d\t%d\t%d\t%d\n",transID,buy.clientID,sell.clientID,sell.price,sell.shareCount);
	     	pop_heap(forsell.begin(), forsell.end(), cmp1());
	    	forsell.pop_back();
		    forbuy.front().shareCount -= sell.shareCount;
		    transID ++;
		    if(forsell.size() == 0 || forbuy.size() == 0){
		    	break;
		    }
		    buy = forbuy.front();
	        sell = forsell.front();
	    }
	    else if(buy.shareCount < sell.shareCount){
		    printf("%d\t%d\t%d\t%d\t%d\n",transID,buy.clientID,sell.clientID,sell.price,buy.shareCount);
		    pop_heap(forbuy.begin(), forbuy.end(), cmp0());
		    forbuy.pop_back();
	    	forsell.front().shareCount -= buy.shareCount;
	    	transID ++;
	    	if(forsell.size() == 0 || forbuy.size() == 0){
		    	break;
		    }
	    	buy = forbuy.front();
	        sell = forsell.front();
	    }
	    else if(buy.shareCount == sell.shareCount){
	    	printf("%d\t%d\t%d\t%d\t%d\n",transID,buy.clientID,sell.clientID,sell.price,buy.shareCount);
	    	pop_heap(forsell.begin(), forsell.end(), cmp1());
	       	forsell.pop_back();
	    	pop_heap(forbuy.begin(), forbuy.end(), cmp0());
	    	forbuy.pop_back();
    		transID ++;
    		if(forsell.size() == 0 || forbuy.size() == 0){
		    	break;
		    }
    		buy = forbuy.front();
	        sell = forsell.front();
	    }
	}
}

int main(void){
	stock a;
	while(scanf("%d%d%d%d%d",&a.bidID,&a.clientID,&a.action,&a.price,&a.shareCount) != EOF){
		record.push_back(1);
		if(a.action == 0){
			forbuy.push_back(a);
			push_heap(forbuy.begin(),forbuy.end(),cmp0());
			trans();
		}
		if(a.action == 1){
			forsell.push_back(a);
			push_heap(forsell.begin(),forsell.end(),cmp1());
			trans();
		}
		if(a.action == 2){
			record[a.price] = 0;
			trans();
		}
	}
}