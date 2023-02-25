#include <stdio.h>
#include <stdlib.h>

int getSoldier() {
    int soldier;

    if (scanf("%d",&soldier) != 1) {
        abort();
    } else {
        return soldier;
    }
}

int main() {
    int s1,s2,s3;

    s1 = getSoldier(); 
    s2 = getSoldier();
    s3 = getSoldier();

    int array[] = {s1,s2,s3};
    // size = elements number in array[]
    int size = sizeof(array)/sizeof(array[0]); // size in bits of the array[] divided by size in bits of the array 1st elemnt 

    for(int i = 0; i < size - 1; i++) {

        for(int j = 0; j < size - 1; j++) {

            if(array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array [j+1];
                array[j+1] = temp;
            }

        }
    
    }

    // print the sorted array
    printf("%d %d %d\n", array[0],array[1],array[2]);
    

    return 0;
}