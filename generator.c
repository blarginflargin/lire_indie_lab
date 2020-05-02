#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <string.h>


//Function Prototypes
void getDimensions(void);
void giveAnswer(bool blocks, int value);
bool checkUse(int argc, char *command);
float recurSum(int N, float blockLength);

//Global Variables
float blockHeight;
float blockLength;
bool blocks = false;




//Returns 1 on improper usage and 0 otherwise
int main(int argc, char *argv[]) {


    if (checkUse(argc, argv[1]) == false) {
        return 1;
    }
    

    getDimensions();
    
    
    giveAnswer(blocks, strtof(argv[2], NULL));


    return 0;
}




//Ensures proper command line usage and also determines the desired output from the user
bool checkUse(int argc, char *command) {
    if (argc < 3) {
        printf("\n\n\nINPUT ERROR: TOO FEW TERMS \nEXPECTED FORM: './lireGenerator getBlocks Length' or ./lireGenerator getLength Blocks'\n\n\n\n");
        return false;
    }
    else if (argc > 3) {
        printf("\n\n\nINPUT ERROR: TOO MANY TERMS \nEXPECTED FORM: './lireGenerator getBlocks Length' or ./lireGenerator getLength Blocks'\n\n\n\n");
        return false;
    }

    
    if (strncmp(command, "getBlocks", 15) != 0 && strncmp(command, "getLength", 15) != 0) {
        printf("\n\n\nINPUT ERROR: IMPROPER COMMAND GIVEN \nEXPECTED FORM: './lireGenerator getBlocks Length' or ./lireGenerator getLength Blocks'\n\n\n\n");
        return false;
    }

    if (strncmp(command, "getBlocks", 15) == 0) {
        blocks = true;
    }
    
    return true;
}





//Prompts user for command line inputs of length and height and stores them as floats 
void getDimensions(void) {
    float strHeight;
    float strLength;
    
    printf("\n\n\nInput Block Height:\n");
    scanf("%f", &strHeight);

    printf("Input Block Length:\n");
    scanf("%f", &strLength);

    blockHeight = (float) strHeight;
    blockLength = (float) strLength;
}




//Picks which output is wanted, calculates the appropriate value, and prints it to the terminal
void giveAnswer(bool blocks, int value) {
    if (blocks == false) {
        int blockNum = value + 0.5;
        float overhang = recurSum(value, blockLength);

        printf("\n\n\nThe resulting tower will extend %f cm and be %f cm tall\n\n\n\n", overhang, blockHeight*blockNum);
    }
    else { 
        float goalLength = value;
        float curLength = 0;
        int blocksNeeded = 0;
        do {
            curLength = recurSum(blocksNeeded, blockLength);
            blocksNeeded++;
        } while (curLength < goalLength);
        
        blocksNeeded--;

        printf("\n\n\nThe resulting tower requires %d blocks and be %f cm tall\n\n\n\n", blocksNeeded, blockHeight*blocksNeeded);


    }
}





//Recursive calculation for the series that represents max overhang
float recurSum(int N, float blockLength) {
    if (N > 1) {
        return (blockLength/2/N) + recurSum((N - 1), blockLength);
    }
    else if (N == 1) {
        return blockLength/2/N;
    }
    else {
        return (float) 0;
    }
}