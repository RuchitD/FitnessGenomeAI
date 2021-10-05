#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <limits.h>
using namespace std;
/* HOW TO USE: EDIT MAKEPOP IN MAIN TO CHANGE THE SIZE OF THE CREATED SETS
CHANGE GA(X)(Y) WITH X BEING POPULATION SIZE AND Y BEING GENERATION TO YOUR PREFERENCE
FOR ME I  */
#define cities 9
int poparray[10][9]; 
int newpop[10][9];
int TSP[9][9] = {        { 0, 0, 0, 0, 0 ,0, 0, 0, 0},
                         { 2, 0, 0, 0, 0 ,0, 0, 0, 0},
                         { 11, 13, 0, 0, 0 ,0, 0, 0, 0},
                         { 3, 10, 5, 0, 0 ,0, 0, 0, 0},
                         { 18, 5, 19, 6, 0 ,0, 0, 0, 0},
                         { 14, 3, 21, 4, 12 ,0, 0, 0, 0},
                         { 20, 8, 2, 12, 6 ,19, 0, 0, 0},
                         { 12, 20, 5, 15, 9 ,7, 21, 0, 0},
                         { 5, 17, 8, 1, 7 ,4, 13, 6, 0} };
int fitness(int row) { //fitness function
    int total = 0;
    int fv;
    int sv;
    int temp;
    int destination = poparray[row - 1][0];
    for (int i = 0; i < 8; i++) {
        fv = poparray[row - 1][i];
        //  cout << "fv is " << fv << "\n";
        sv = poparray[row - 1][i + 1];
        // cout << "sv is " << sv << "\n";
        if (sv > fv) {
            temp = fv;
            fv = sv;
            sv = temp;
        }
        total += TSP[fv - 1][sv - 1];
        // cout << "total is " << total << "\n" <<" new added distance is " << TSP[fv-1][sv-1] << "\n" ;


    }
    if (sv > destination) {
        temp = destination;
        destination = sv;
        sv = temp;
    }
        //cout << "starting point is " << destination << "\n";
       // cout << "last stop is " << sv << "\n";
       // cout << "Current Total is " << total;
        total = total + TSP[sv - 1][destination];
       // cout << "New total is " << total;

        // cout << "total is " << total;
        return total;

    
}// fitness function
void makepop(int population);//makepopfunction this 
void mutate(int row1) { //mutation function works by activating only is math.random rolls less than 5/100 it then swaps the 1st and the 6th element of the item in newpop
    int temp = newpop[row1][0];
    int temp2 = newpop[row1][5];
    newpop[row1][0] = temp2;
    newpop[row1][5] = temp;
   // cout << "Mutation has occured";
}
void reproduce(int row1, int row2) { //reproduction function
  
    int genelength = 9;
    int parent[9] = { poparray[row2][0], poparray[row2][1], poparray[row2][2],poparray[row2][3], poparray[row2][4], poparray[row2][5],poparray[row2][6], poparray[row2][7], poparray[row2][8] }; 
    int child[9] = {};                           
    int gene[3] = { poparray[row1][0], poparray[row1][1], poparray[row1][2] };                    
    int pos = 3;

    //std::cout << "Printing Child:" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        child[i] = gene[i]; 
      // std::cout << child[i] << " ";
    }

    for (int i = 0; i < genelength; i++)
    {
        int gene_exists = false;
        for (int g = 0; g < 3; g++)
        {
            if (gene[g] == parent[i])
                gene_exists = true;
        }

        if (!gene_exists) {
            child[pos++] = parent[i];
            //std::cout << parent[i] << " ";
        }
    }
    for (int i = 0; i < 9; i++) {
        newpop[row1][i] = child[i];
    }





    
};
void ga(int population, int generation) {//THIS IS THE MAIN GENETIC ALGORITHIM FUNCTION 
    int mutationnumber = 5;
    int temparray[9];
    int bestfitness;
    int fittemp = 0;
    for (int i = 0; i < generation; i++) {
        for (int j = 0; j < population - 1; j++) {
            if (fitness(j) < fitness(j + 1)) {
                fittemp = fitness(j);
                for (int i = 0; i < 9; i++) {
                    temparray[i] = poparray[j][i];
                }

            }
            else if (fitness(j + 1) < fitness(j)) {
                fittemp = fitness(j + 1);
                for (int i = 0; i < 9; i++) {
                    temparray[i] = poparray[j + 1][i];
                }
            }

           // cout << "fitness of the current value is" << fitness(j);
            reproduce(j, j + 1);
            if (rand() % 100 <= mutationnumber) {
                mutate(j);


            }

        }
        for (int k = 0; k < population - 1; k++) {
            for (int l = 0; l < 9; l++) {
                poparray[k][l] = newpop[k][l];
            }
        }
    }
    bestfitness = fittemp;
    cout << "For " << generation << " generations, and For a population of " << population << "\n";
    cout << "The fitness value was " << bestfitness << "\n";
    cout << "For State of ";
    for (int i = 0; i < 9; i++)
    {

        std::cout << temparray[i] << " ";



    }
}

int main()
{

    
    
    
    makepop(10);
    ga(6, 7);
    ga(3, 5);
    ga(4, 2);
    ga(5, 4);
    ga(6, 8);
    ga(7, 9);
    ga(8, 10);
    ga(9, 22);
    ga(10, 3);
    ga(10, 5);
    
    
   
}

void makepop(int population) { //makepop function This function populates an array with the amount of statesets
    int rows = population;
    for (int j = 0; j < rows; j++) {
        int nums[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        std::random_shuffle(nums, nums + 9);
       // cout << "\n";
        for (int i = 0; i < 9; i++) {
            poparray[j][i] = nums[i];
           // cout << poparray[j][i] << ",";
        }
    }
    
}