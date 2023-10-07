#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(){

    FILE *file; //declaring pointer for file
    file = fopen("payloads.txt", "r");//opening file
    if(file == NULL) //if file can not open, print file not found.
        printf("File not found.");

    //read first line in file to determine how many rows of data are in file
    int num;
    fscanf(file, "%d", &num);

    //if the initial number in the file is 0, the no payloads are in the file
    if(num == 0){
        printf("No payloads in file.");
        return 0; //end program
    }

    float **array = (float **) malloc(num * sizeof(float*));//creating 2d array using malloc

    //printing necessary parts to the screen
    printf("Payload Data:\n");
    printf("Total Mass / Grade / Ore Value\n");

        //for loop to scan values from the file into the array
        for(int i = 0; i < num; i++) {
            array[i] = (float *) malloc(3 * sizeof(float));
            fscanf(file, "%f %f", &array[i][0], &array[i][1]);

            //calculating the Ore Value
            array[i][2] = (array[i][0]*array[i][1])*8500;

            //Printing the Total mass, Grade, and Ore Value to the screen
            printf("   %.0f      %.2f    $%.0f\n", array[i][0], array[i][1], array[i][2]);
        }

        //declaring value for swaps made and new array to use in bubble sort
        int swapMade = 0;
        float *temp = (float *) malloc(3 * sizeof(float));

        //while loop for bubble sort
        while(1){
            swapMade = 0;
            for(int j = 0; j < num - 1; j++){
                if(array[j][2] < array[j+1][2]){
                    for(int m = 0; m < 3; m++) {
                     temp[m] = array[j][m];
                     array[j][m] = array[j+1][m];
                     array[j+1][m] = temp[m];
                    }
                    swapMade = 1;
                }
            }
            if(!swapMade)
                break;
        }
    free(temp);//freeing the memory of the temp array after using it

    fclose(file);//closing the payloads file

    //creating new file for the sorted values and opening it
    FILE *file2;
    file2 = fopen("ores.txt", "w");

    //printing necessary parts to the file
    fprintf(file2, "Sorted Payload Data\n");
    fprintf(file2, "Total Mass / Grade / Ore Value\n");

    //for loop to print the sorted value to the new file
    for(int i = 0; i < num; i++){
        fprintf(file2, "   %.0f      %.2f    $%.0f\n", array[i][0], array[i][1], array[i][2]);
    }

    fclose(file2);//closing the file

    //I attest to the originality of my work
}