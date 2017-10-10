#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
int tree[124];
int n = 0;
void preorder(int index){
    if(index >= n){
       return;
    }
    if(tree[index] != -1){
    	printf("%d ", tree[index]);
    }
    preorder(2*index);
    preorder((2*index)+1);
}
void inorder(int index){
    if(index >= n){
       return;
    }
    inorder(2*index);
    if(tree[index] != -1){
    	printf("%d ", tree[index]);
    }
    inorder((2*index)+1);
}
void postorder(int index){
    if(index >= n){
       return;
    }
    postorder(2*index);
    postorder((2*index)+1);
    if(tree[index] != -1){
    	printf("%d ",tree[index]);
    }
}

int main(void){
    while(scanf("%d", &tree[n])==1){
    	n++;
    }
    preorder(1);
    printf("\n");
    inorder(1);
    printf("\n");
    postorder(1);
	return 0;
}