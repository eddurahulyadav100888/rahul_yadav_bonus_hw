#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  int i, limit;
  
  if (argc==1){
    printf("How many elements you want to display: ");
    scanf("%d",&limit);
  }

  if (argc==2){
    limit = atoi(argv[1]);
  }

  // first two terms
  int t1 = 0, t2 = 1;

  // third term
  int nextTerm = t1 + t2;

  // print the first two terms t1 and t2
  printf("The First %d value: %d, %d ",limit, t1, t2);

  // print 3rd to nth terms
  for (i = 3; i <= limit; ++i) {
    printf(", %d", nextTerm);
    t1 = t2;
    t2 = nextTerm;
    nextTerm = t1 + t2;
  }
  printf("\n");

  return 0;
}
