// Dajja Williams
// Bankers Algorithm
// Due April 23, 2023
// Operating Systems

#include <iostream>
#include <fstream>
using namespace std;

int main(){
    int M = 3; // number of resources
    int N = 4; // number of threads
    //names for resources
    string resourceName[M]; 
    //resources available
    int resourceNumber[M]; 
    //name of threads
    string threadName[N];   
    //names of threads in order to achieve safe state
    string safeState[N];    
    //max resources needed for each thread
    int resourceMax[N][M];  
    //resources allocated per thread
    int resourceAllocated[N][M];    
    //resources needed to complete the process
    int need[N][M];         
    
    // open file and read information into variables
    fstream fin;
    fin.open("data.txt");

    for(int i=1; i<=M; i++) {
        fin >> resourceName[i-1] >> resourceNumber[i-1];
        // test output
        //cout << resourceName[i-1] << " + " << resourceNumber[i-1] << endl;
    }

    fin.ignore(1, '\n');
    fin.ignore(1, '\n');
    fin.ignore(1, '\n');

    for(int j=1; j<=N; j++){
        fin >> threadName[j-1];
        //cout << threadName[j-1];
        for(int i=1; i<=M; i++){
            fin >> resourceMax[j-1][i-1];
            //cout << " + " << resourceMax[j-1][i-1];
        }
        //cout << endl;
    }

    fin.ignore(1, '\n');
    fin.ignore(1, '\n');
    fin.ignore(1, '\n');
   
    for(int j=1; j<=N; j++){
        for(int i=1; i<=M; i++){
            fin >> resourceAllocated[j-1][i-1];
            //cout << resourceAllocated[j-1][i-1] << " ";
        }
        //cout << endl;
    }
    fin.close();
   
    // calculate the need of each process
    for(int j=1; j<=N; j++){
        for(int i=1; i<=M; i++){
            need[j-1][i-1] = resourceMax[j-1][i-1] - resourceAllocated[j-1][i-1];
            //cout << need[j-1][i-1] << " ";
        }
        //cout << endl;
    }

    // calculate the currently available resources
    for (int j=1; j<=N; j++){
        for(int i=1; i<=M; i++)
        {
            resourceNumber[i-1] -= resourceAllocated[j-1][i-1];
        }      
    }

    //bool isSafe = false;
    int queueIndex = 0;
    int loopChecks = 0;
    // check if available > need then complete process and store process in safe state
    do {
        for(int j=0; j<=N; j++){
            if(resourceNumber[0] >= need[j-1][0] && resourceNumber[1] >= need[j-1][1] && resourceNumber[2] >= need[j-1][2])
            {
                resourceNumber[0] += resourceAllocated[j-1][0];
                resourceNumber[1] += resourceAllocated[j-1][1];
                resourceNumber[2] += resourceAllocated[j-1][2];
                need[j-1][0] = 100;
                need[j-1][1] = 100;
                need[j-1][2] = 100;
                safeState[queueIndex++] = threadName[j-1];
            }
        }
        if(queueIndex > 3){
            //isSafe = true;
            cout << "A safe state is: {" << safeState[0] << ", " << safeState[1] << ", " << safeState[2] << ", " << safeState[3] << "}" << endl;
            loopChecks = N;
        }
        loopChecks++;
    } while(loopChecks < N);
    return 0;
}
