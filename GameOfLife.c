/*
This program takes input and prints the universe plays the game Conway's game of Life and prints generations
as outputs. It follows all the rules of the game.The rules for the Game of Life are simple. 
The universe consists of a two-dimensional matrix of cells with each cell being alive or dead.
For each generation every cell determines its next phase of life as follows:
If the cell is alive:
it dies if it has 0, 1, 4 or more living neighbours (starvation), or
it lives if it has 2 or 3 living neighbours (balance).
If the cell is dead:
it springs to life if it has exactly 3 neighbours (procreation).
A cycle occurs as soon as the state of the universe of the latest generation is the same as a previous generation. You should be able to see that once this occurs the Game of Life will repeat the intermediate generations forever.
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

#ifdef NDEBUG
  #define PRINT_VALUE 10
#else 
  #define PRINT_VALUE 0  
#endif  

#define INPUT_LENGTH 80
#define NUM_ROWS 60
#define NUM_COLS 60
#define MAX_GEN 251 

typedef struct GENERATION {
        char gUniverse[NUM_ROWS][NUM_COLS];//Array to store the universe
        int arrayNUM[2];//To store the number of rows and columns in a particular universe, since it is 2D Array so 2 numbers only
        char caseName[100];//keeping the case name stored here
    } generation;



int main(void){
    
    //VARIABLES    
    char input[INPUT_LENGTH];//A string for reading from input
    generation history[MAX_GEN];//Keeping track of previous generations
    generation storeInputs[20];//making universes from inputs       
    
    int row=0;//To record number of rows copied in the universe
    int  element=0;//To record number of elements to put in arrayNUM
    char *next;//For strtok purposes
    int count=0;//To record how many time while loop is called during the input process
    int deadNeighbours=0;//keeping count of dead neighbours for fun
    int aliveNeighbours=0;//keeping count for alive neighbours
    int countG=0;//Keeping count of generations
    int countG2=0;//Helper for countG2
    int counterC=0;//Helper variable to find a circle
    int confirmCycle=0;//varible to confirm cycle
    int storeInputCount=0;//storing count of input
    int inputNumber=0;//number of inputs
    int printHelper=0;//helper variable for print
    int countPrint=0;//helper variable for print
    int inputNumberHelper=1;//helper variable for inputNumber


    
  
       while(fgets(input,INPUT_LENGTH,stdin)!=NULL){
            
/*
Takes inputs from fgets. If the charcter is * it prints that line and and uses fgets again
to read the next line. it uses strtok to separate the numbers(assuming there are numbers
in the second line) and stores it to arrayNUM which by the way only
stores 2 elements. It then starts a while loop where it reads the next line until row number matches
the first element in arrayNUM and stores the data in the storeInput array. We assume fgets is not null
*/
        
            //Assuming the first character of any
            //universe is *.                              
            if(strrchr(input,'*')!=0){          
                 inputNumber++;
                 storeInputCount++;
                 strcpy(storeInputs[storeInputCount].caseName,input);                 
                 //count=0;  
                 row=0; 
                 element=0;                        
             }//if
            
            //Finding the number of rows and columns respectively 
            //by reading the numbers in the 2nd line

            fgets(input,INPUT_LENGTH,stdin);             
            next = strtok(input," ");

            while(next!=NULL){
                    assert(next!=NULL);
                    
                    if(element<2){
                    storeInputs[storeInputCount].arrayNUM[element]=atoi(next);
                }//if
                    next=strtok(NULL," ");               
                    element++;
                }//while
            
            
           //Putting all other data in the universe
            while(row<storeInputs[storeInputCount].arrayNUM[0]){
                assert(row<storeInputs[storeInputCount].arrayNUM[0]);
                count++;
                fgets(input,INPUT_LENGTH,stdin);
                strcpy(storeInputs[storeInputCount].gUniverse[row],input);
                row++;
                }//if
         
           
  while(inputNumberHelper<=inputNumber){
/*
Here it takes the searches for 'X' and ''and replaces it with '*' and '.'
inputNumber is the array index and inputNumberHelper increases to work with 
elements in the next index of the array
*/    
    //Creating the universe
    assert(inputNumberHelper<=inputNumber);    
    for(int i=0;i<storeInputs[inputNumberHelper].arrayNUM[0]; i++){
        for(int j=0; j<storeInputs[inputNumberHelper].arrayNUM[1]; j++){
            if(storeInputs[inputNumberHelper].gUniverse[i][j]=='X'){
                storeInputs[inputNumberHelper].gUniverse[i][j]='*';
            }//if
            else{
              storeInputs[inputNumberHelper].gUniverse[i][j]='.';          
            }//else
        }//for(j)
      }//for(i)

/*
Borders the top and side with - and | and prints the output
with '.' meaning dead cells and '*' means alive cell
*/
    //Printing the universe    
    printf("\n%sGeneration 0:\n",storeInputs[inputNumberHelper].caseName);
    for(int k=0;k<storeInputs[inputNumberHelper].arrayNUM[0];k++){
       
       if(k==0 ){
           printf("+");
           int temp=0;
           assert(temp<storeInputs[inputNumberHelper].arrayNUM[1]);
           while(temp<storeInputs[inputNumberHelper].arrayNUM[1]){
           printf("%c",'-');
           temp++;
           }//while
           printf("+\n");
       }//if
       int temp=0;
       printf("|");
       assert(temp<storeInputs[inputNumberHelper].arrayNUM[1]);
       while (temp<storeInputs[inputNumberHelper].arrayNUM[1])
       {   
           printf("%c",storeInputs[inputNumberHelper].gUniverse[k][temp]);            
           temp++;
           if(temp==(storeInputs[inputNumberHelper].arrayNUM[1])){
               printf("|\n");
           }//if
       }//while
        if(k==storeInputs[inputNumberHelper].arrayNUM[0]-1){
            printf("+");
           int temp=0;
           assert(temp<storeInputs[inputNumberHelper].arrayNUM[1]);
           while(temp<storeInputs[inputNumberHelper].arrayNUM[1]){
           printf("%c",'-');
           temp++;
           }//while
           printf("+\n");
        }//if
    }//for
  
   confirmCycle=0;
   countG=0;
   assert(confirmCycle<1);
   while(confirmCycle<1 ){
    generation g;
/*
Stores the previous universe by reading all the elements in the array input
and stores it to history
*/    
    //storing the previous universe
    for(int x=0; x<storeInputs[inputNumberHelper].arrayNUM[0]; x++){
        for (int y=0; y<storeInputs[inputNumberHelper].arrayNUM[1]; y++){
            g.gUniverse[x][y]=storeInputs[inputNumberHelper].gUniverse[x][y];
        }
    }
    history[countG]=g;
    
/*
Checks for a cycles. It basically searches for all the elements
in one generations and compares it with all the previous ones
CounterC counts when one element is same as another element in the
same index in ther other generations. When CounterC is equal to row*col
that means all the elements are same and therefore a cycle is found and confirmCycle
is set to when. confirmCycle is also 1 when there is no cycle found but the generation 
number is equal to MAX_GEN
*/

    //Checking if the previous generation is same as new generation   
    countG2=countG-1;  
    
    while (countG2>0)
    {
        counterC=0;
        for(int a=0; a<storeInputs[inputNumberHelper].arrayNUM[0]; a++){
        for(int b=0; b<storeInputs[inputNumberHelper].arrayNUM[1]; b++){
            if(history[countG].gUniverse[a][b]==history[countG2].gUniverse[a][b]){
            counterC++;
            
    }//if
        }//for(b)
       }//for(a)
       if(counterC==(storeInputs[inputNumberHelper].arrayNUM[0]*storeInputs[inputNumberHelper].arrayNUM[1])){
            
            confirmCycle=1;
            if(confirmCycle>0){
            printf("Found a cycle between generation %d and generation %d\n",countG2,countG);
            
            }
       }//if
       else if(countG==MAX_GEN-1)
       {
           confirmCycle=1;
       }
       
       countG2--;
    }
    countG++;
    printHelper=countG;
      
/*
Checks how many alive and dead neigbours each cell has by looking over all the elements close to 
it i.e. it checks for elements at immediate top,down,left,right and diagonal ones also. It then follows
the regular game rules.
*/

    //checking neighbours for each cell and doing the game
    for(int m=0;m<storeInputs[inputNumberHelper].arrayNUM[0]; m++){
        for(int n=0; n<storeInputs[inputNumberHelper].arrayNUM[1]; n++){

        //checking neighboursfor alive cells  
        if(g.gUniverse[m][n]=='*'){
            deadNeighbours=0;    //bound checking required  
            aliveNeighbours=-1;//to avoid including itself
                for(int r=-1; r<2; r++){
                   for(int s=-1; s<2; s++){
                        if((g.gUniverse[m+r][n+s])=='.'){
                        deadNeighbours++;
                        
               }//if
               else if((g.gUniverse[m+r][n+s])=='*'){
                        aliveNeighbours++;
               }//else if
                   }//for(s)
               }//for(r)

              
             if(aliveNeighbours == 0 || aliveNeighbours==1 || aliveNeighbours >=4){
                 storeInputs[inputNumberHelper].gUniverse[m][n]='.';   
                 
                }
                else if(aliveNeighbours == 2 || aliveNeighbours == 3){
                     storeInputs[inputNumberHelper].gUniverse[m][n]='*';                  
                }                      
           
        }//if
        //checking neighbours for dead cells
        else if(g.gUniverse[m][n]=='.'){
            deadNeighbours=-1;//to avoid including itself      
            aliveNeighbours=0;
                for(int r=-1; r<2; r++){
                   for(int s=-1; s<2; s++){                        
                if((g.gUniverse[m+r][n+s])=='*'){
                        aliveNeighbours++;
                }// if
                else if((g.gUniverse[m+r][n+s])=='.'){
                        deadNeighbours++;                        
                }//else if
                   }//for(s)
                }//for(r)
        
                if(aliveNeighbours == 3 ){
                 storeInputs[inputNumberHelper].gUniverse[m][n]='*';               
                }//if    
        
            }//else if
        }//for(n)
    }//for(m)
      
   }//while history

/*
Prints the generations the same way it did with printing universe.
However if NDEBUG is applied it only prints the last 10 generations
*/    
    //Printing generations
     if(PRINT_VALUE==10){
     if(printHelper<11){
         countPrint=0;
     }
     else{
     countPrint=printHelper-11;
     }
    }
    assert(countPrint<printHelper-1);
    while(countPrint<printHelper-1){
        countPrint++;
    printf("Generation %d: \n",countPrint);
    for(int k=0;k<storeInputs[inputNumberHelper].arrayNUM[0];k++){
       if(k==0 ){
           printf("+");
           int temp=0;
           assert(temp<storeInputs[inputNumberHelper].arrayNUM[1]);
           while(temp<storeInputs[inputNumberHelper].arrayNUM[1]){
           printf("%c",'-');
           temp++;
           }//while
           printf("+\n");
        }//if
       int temp=0;
       printf("|");
       assert(temp<storeInputs[inputNumberHelper].arrayNUM[1]);
       while (temp<storeInputs[inputNumberHelper].arrayNUM[1])
        {   
           printf("%c",history[countPrint].gUniverse[k][temp]);            
           temp++;
            if(temp==(storeInputs[inputNumberHelper].arrayNUM[1])){
               printf("|\n");
            }//if
        }//while
            if(k==storeInputs[inputNumberHelper].arrayNUM[0]-1){
                printf("+");
                int temp=0;
                    assert(temp<storeInputs[inputNumberHelper].arrayNUM[1]);
                    while(temp<storeInputs[inputNumberHelper].arrayNUM[1]){
                        printf("%c",'-');
                        temp++;
                    }//while
           printf("+\n");
            }//if
        }//for
    }//while count print
    countPrint=0;
inputNumberHelper++;

}//while(inputnumber)  
 
}//while
    return 0;
}//main
