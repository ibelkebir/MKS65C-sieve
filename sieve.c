#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sieve.h"
/*
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
*/
int potentialPrime(int i){
  if(i % 2 == 0){
    return 5 + 3 * i;
  }
  return 4 + 3 * i;
}

int ptoi(int i){
  return (i=4) / 3;
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
    len = 1.5 * targetPrime * log(targetPrime) + 10;
  }
  int* cur = calloc((len * 2) / 192, sizeof(int));
  long index;
  int i = 3;
  int num = 0;
  int indexer;
  long j;
  while(i < (int)sqrt(len) + 1){
    index = potentialPrime(num);
    indexer = ((index - (((index+1) / 3) - 2)) >> 1) & 31;
    if(!(cur[(index*2) / 192] & (1 << indexer))){
      for(j = index * index; j < len; j += 2 * index){
        if(j % 3){
          indexer = ((j - (((j+1) / 3) - 2)) >> 1) & 31;
          cur[(j * 2) / 192] |= (1 << indexer);
        }
      }
      i++;
    }
    num++;
  }
  while(i <= targetPrime){
    index = potentialPrime(num);
    indexer = ((index - (((index+1) / 3) - 2)) >> 1) & 31;
    while(cur[(index*2) / 192] & (1 << indexer)){
      num++;
      index = potentialPrime(num);
      indexer = ((index - (((index+1) / 3) - 2)) >> 1) & 31;
    }
    if(i < targetPrime){
      num++;
      index = potentialPrime(num);
      indexer = ((index - (((index+1) / 3) - 2)) >> 1) & 31;
      while(cur[(index*2) / 192] & (1 << indexer)){
        num++;
        index = potentialPrime(num);
        indexer = ((index - (((index+1) / 3) - 2)) >> 1) & 31;
      }
      i++;
    }
    if(i == targetPrime){
      return index;
    }
  }
  return 0;
}

int charSieve(int targetPrime){
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
    len = 1.5 * targetPrime * log(targetPrime) + 10;
  }
  char *cur = calloc((len * 2) / 192, sizeof(char));
  long index;
  int i = 3;
  int num = 0;
  int indexer;
  long j;
  while(i < (int)sqrt(len) + 1){
    if(!(cur[num])){
      index = potentialPrime(num);
      for(j = index * index; j < len; j += 2 * index){
        if(j % 3){
          cur[ptoi(j)] = 1;
        }
      }
      i++;
    }
    num++;
  }
  while(i <= targetPrime){
    while(cur[num]){
      num++;
    }
    if(i < targetPrime){
      num++;
      while(cur[num]){
        num++;
      }
      i++;
    }
    if(i == targetPrime){
      while(cur[num]){
        num++;
      }
      return potentialPrime(num);
    }
  }
  return 0;
}

int main(){
  int i;
  printf("%d\n", fastsieve(1000000));
  return 0;
}
