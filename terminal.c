#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(void){
  int m[15][15];
  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 15; j++) {
      m[i][j] = ' ';
    }
  }
  for (int i = 0; i < 15; i++) {
    m[0][i] = '#'; // Borda superior
    m[14][i] = '#'; // Borda inferior
    m[i][0] = '#'; // Borda esquerda
    m[i][14] = '#'; // Borda direita
  }
  for(int i = 0;i<15;i++){
    for(int j = 0;j<15;j++){
     printf("%c", m[i][j]);
    }
    printf("\n"); // Nova linha ao final de cada linha do array
  }
  return 0;
}