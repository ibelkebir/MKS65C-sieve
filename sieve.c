#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sieve.h"

int sieve(int targetPrime){
  if(targetPrime == 1){
    return 2;
  }
  if(targetPrime == 2){
    return 3;
  }
  int len;
  if(targetPrime > 5000){
    len = 1.31 * targetPrime * log(targetPrime);
  }else{
    len = 1.3 * targetPrime * log(targetPrime) + 10;
  }
  int* cur = calloc(len, sizeof(int));
  int i = 3;
  int j;
  int index = 6;
  while(i <= targetPrime){
    if(i == targetPrime){
      if(!(cur[index-1])){
        return index-1;
      }
      return index+1;
    }
    if(i == targetPrime - 1){
      if(cur[index-1] || cur[index+1]){
        if(!(cur[index+5])){
          return index+5;
        }
        return index+7;
      }
      return index+1;
    }
    if(!(cur[index-1])){
      for(j = 2 * (index-1); j < len; j += index - 1){
        cur[j] = 1;
      }
      i++;
    }
    if(!(cur[index+1])){
      for(j = 2 * (index+1); j < len; j += index + 1){
        cur[j] = 1;
      }
      i++;
    }
    index += 6;
  }
  return 0;
}

int fastsieve(int targetPrime){
  if(targetPrime == 1){
    return 2;
  }
  if(targetPrime == 2){
    return 3;
  }
  int len;
  if(targetPrime > 5000){
    len = 1.31 * targetPrime * log(targetPrime);
  }else{
    len = 1.3 * targetPrime * log(targetPrime) + 10;
  }
  int* cur = calloc((len * 2) / 192, sizeof(int));
  int mult3 = 1;
  int index = 5;
  int i = 3;
  int indexer;
  while(i <= targetPrime){
    indexer = (((index - (((index+1) / 3) - 1)) >> 1) & 31);
    if(i == targetPrime){
      while(cur[(index*2) / 192] & (1 << indexer)){
        mult3++;
        mult3 %= 3;
        if(mult3){
          index += 2;
        }else{
          index += 4;
          mult3++;
        }
        indexer = (((index - (((index+1) / 3) - 1)) >> 1) & 31);
      }
      return index;
    }
    if(!(cur[(index*2) / 192] & (1 << indexer))){
      for(int j = index * index; j < len; j += 2 * index){
        if(j % 3){
          indexer = ((j - (((j+1) / 3) - 1)) >> 1) & 31;
          cur[(j * 2) / 192] |= (1 << indexer);
        }
      }
      i++;
    }
    mult3++;
    mult3 %= 3;
    if(!(mult3)){
      index += 4;
      mult3++;
    }else{
      index += 2;
    }
  }
  return 0;
}

int main(){
  int i;
  //for(i = 25; i < 30; i++){
    printf("%d\n", fastsieve(4794));
  //}
  return 0;
}
