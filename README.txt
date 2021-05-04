# GameOfLife
This program runs the Conway's Game Of Life. This is a simple text-based game where 
you put put the first generation of input and as output the rest of the generations prints
in the console. 

The rules for the Game of Life are simple. 
The universe consists of a two-dimensional matrix of cells with each cell being alive or dead. 
For each generation every cell determines its next phase of life as follows:
If the cell is alive:
it dies if it has 0, 1, 4 or more living neighbours (starvation), or
it lives if it has 2 or 3 living neighbours (balance).
If the cell is dead:
it springs to life if it has exactly 3 neighbours (procreation).
A cycle occurs as soon as the state of the universe of the latest generation is the same as a previous generation.
You should be able to see that once this occurs the Game of Life will repeat the intermediate generations forever.

To learn more about the game and its rules visit:
https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

________________________________________________________________________________________________________________________

                    COMPLETE THE FOLLOWING STEPS TO RUN THE GAME USING YOUR CONSOLE
________________________________________________________________________________________________________________________
1.COMPILING THE FILE

If you are using clang compiler, compile the file using the following command:

clang -Wall GameOfLife.c -o GameOfLife

If you are using gcc compiler, compile the file using the following command:

gcc -Wall GameOfLife.c -o GameOfLife
________________________________________________________________________________________________________________________
2. RUNNING THE FILE

Run the application using the following command if you are using LINUX or MAC Machine:

./GameOfLife

Run the application using the following command if you are using WINDOWS:

GameOfLife
________________________________________________________________________________________________________________________
3.PUTTING THE 1ST GENERATION

Using the format in the sampleinput.txt put your first generation. For example,

*Case #1
10 20
                    
                    
                    
       X            
        X           
      XXX           
                    
                    
                    
                    

Hit Enter. Next generations should be printed out in the console as shown the sampleOutput.txt

_________________________________________________________________________________________________________________________
4.PRINTING THE ONLY LAST 10 GENERATIONS

If you only want to print the last 10 generations use the follwing command to compile:

With clang compiler:

clang -Wall -DNDEBUG GameOfLife.c -o GameOfLife

With gcc compiler:

gcc -Wall -DNDEBUG GameOfLife.c -o GameOfLife

And run the game using the step 2 and 3.

__________________________________________________________________________________________________________________________
5.PLAY GAME USING INPUT FILE

./GameOfLife < input.txt > output.txt

__________________________________________________________________________________________________________________________

ENJOY!


