#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;
int main(void){
   int n;
   double matrix[201][201] = {{0}}, ans[201][201] = {{0}}, origin[201][201] = {{0}}, product[201][201] = {{0}};
   double error = 0.000000, ratio = 0;
   cin >> n;
   for(int i = 0; i < n; i++){
       for(int j = 0; j < n; j++){
           cin >> matrix[i][j];
           origin[i][j] = matrix[i][j];
       }
   }
   for(int i = 0; i < n; i++){
       ans[i][i] = 1;
   }
   for(int i = 0; i < n; i++){
       if(matrix[i][i] < 1e-12){
           for(int down = i + 1; down < n; down++){
              if(matrix[down][i] > 1e-12){
                 for(int col = 0; col < n; col++){
                    matrix[i][col] += matrix[down][col];
                    ans[i][col] += ans[down][col];
                 }
                 break;
              }
           }
       }
       double temp = matrix[i][i];
       for(int j = 0; j < n; j++){
          matrix[i][j] /= temp;
          ans[i][j] /= temp;
       }
       for(int line = 0; line < n; line++){
          if(line == i){
             continue;
          }
          ratio = matrix[line][i];
          for(int column = 0; column < n; column++){
             ans[line][column] -= (ans[i][column]*ratio);
             matrix[line][column] -= (matrix[i][column]*ratio);
          }
       }
   }
   for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
         for(int k = 0; k < n; k++){
            product[i][j] += ans[i][k]*origin[k][j];
         }
      }
   }
   for(int i = 0; i < n; i++){
      product[i][i] -= 1;
      for(int j = 0; j < n; j++){
         product[i][j] = abs(product[i][j]);
      }
   }
   for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
         if(product[i][j] > error){
            error = product[i][j];
         }
      }
   }
   cout << error << endl;
   for(int i = 0; i < n; i++){
      for(int j = 0; j < n-1; j++){
         cout << ans[i][j] << ' ';
      }
      cout << ans[i][n-1] << endl;
   }
   return 0;
}
