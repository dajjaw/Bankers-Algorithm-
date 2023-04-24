// Dajja Williams
// Bankers Algorithm
// Due Sunday 23, 2023
// Operating Systems


#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fstream>  
using namespace std;

const int maxProcesses = 100;
const int maxResources = 100;
int processesRead; //resources
int resourcesRead;
string resourceName[maxResources];
string processName[maxProcesses];
int resourceAmount[maxResources];
int processResourceMax[maxProcesses][maxResources];
int allocated[maxProcesses][maxResources];
int need[maxProcesses][maxResources];
int available[maxResources];
bool processCompleted[maxProcesses];

void safeState(){
    // need = processmax - resource allocated
    for (int i=0; i<processesRead; i++){
        for(int j= 0; j< resourcesRead; j++){
            need[i][j] = processResourceMax[i][j]- allocated[i][j];
        }
    }
    // available =max - sum(allocated)
    for(int i=0; i<resourcesRead; i++){
        int s=0;
        for(int j=0; j< processesRead; j++){
            s += allocated[j][i];
        }
        available[i]= resourceAmount[i]-s;
        cout << available[i] << " ";
    }
    cout << endl;
    bool change = true;
    int completeProcessesCount = 0;
    int safeSequence[maxProcesses];
    int top = 0;
    bool processComplete = true;
    while(change){
        change = false;
        for(int i=0;i<processesRead; i++){
            if (processCompleted[i]) continue;
            processComplete = true;
            for(int j=0;j<resourcesRead; j++){
                if (need[i][j]>available[j]){
                    processComplete = false;
                    break;         
                 }
            }
            if (processComplete){
                processCompleted[i] = true;
                change = true;
                completeProcessesCount++;
                for(int j=0;j<resourcesRead; j++){
                    available[j]+= allocated[i][j];
                }
                safeSequence[top++]= i;
            }
        }
    }
    if (completeProcessesCount == processesRead){
        cout << "Safe state available: ";
        for (int i = 0; i< processesRead; i++){
            cout<<safeSequence[i];
        }
        cout << endl;
    }
    else {
        cout << "No safe state available \n";
    }
}

int main(){
    ifstream fin;

   fin.open("data.txt");

   for(int i=0; i<100;i++){
   fin >> resourceName[i];
   if (resourceName[i] == "#"){
       resourcesRead = i;
        break;
   }
   fin>>resourceAmount[i];
   }
   for(int i= 0; i<resourcesRead; i++){
       cout<<resourceName[i]<< resourceAmount[i]<< endl;
   }
   for(int i=0; i<100; i++){
       fin >> processName[i];
       if(processName[i]=="#"){
           processesRead = i;
          break;
       }
      for(int j = 0; j<resourcesRead; j++){
          fin >> processResourceMax[i][j];
      }
   }
   for(int i= 0; i<processesRead; i++){
       cout << processName[i] << " ";
       for(int j=0; j<resourcesRead; j++){
           cout << processResourceMax[i][j] << " ";
       }
       cout << endl;
   }

   string p;

   for(int i=0;i<processesRead; i++){
               for (int k= 0; k<resourcesRead; k++){
                   fin>> allocated[i][k];
               }
           }

    for(int i= 0; i<processesRead; i++){
       cout << processName[i] << " ";
       for(int j=0; j<resourcesRead; j++){
           cout << allocated[i][j] << " ";
       }
       cout << endl;
       for (int i= 0; i<maxProcesses; i++){
           processCompleted[i] = false;
       }
   }
   
   safeState();
}
