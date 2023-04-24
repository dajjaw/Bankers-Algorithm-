# Bankers-Algorithm-
Implement Banker's algorithm that is explained in the deadlock slides. To make entering the data easy; create a file that of four parts, each part is separated with the symbol #.

The first part is the resources available where you write the resource name and the number available of that resource in each line. resource name is a string.
The second part is the threads name (string type) with numbers separated by space, these numbers represent the maximum number of resources the process uses during its execution.
The third part is the allocation matrix, that shows the number of resources allocated to each thread.
Here is an example of a file data.txt:

A 5
B 21
C 18
#
P0 0 0 1
P1 1 7 5
P2 2 3 5
P3 0 6 5
#
0 0 1
1 0 0
1 3 5
0 6 3
#
The first part in the data.txt includes three resources A, B and C with their maximum available resource.
The second part in the data.txt includes four threads P0, P1, P2 and P3 with their maximum requested resources.
The third part in the data.txt is the allocation matrix that shows for each thread; the number of resources allocated.
You need to declare variables to store the current availability resources and the resources needed for each thread.

You need to define a input file stream variable:
T = 4 // number of threads
R = 3 // number of resources
string resourceNames[R]; // store resource names
int maxResource[R]; // store maximum resources in the system
string threadsName[T]; // threads names
int resourcesRequested[T][R]; // resources requested for each thread
int resourceAllocated[T][R]; // allocated resources for each thread
int neededResources[T][R]; // This matrix is computed to show the needed resources for each thread
int currentAvailResources[R]; // This a computed array of the number of resources available.

In addition, you need to declare a file stream:
ifstream fin;
you open the file:
fin.open("data.txt");

You read the file:
fin >> resourceName[i] << resourceNumber[i];  for i=1, ..., R
fin >> threadName[i]; for i = 1, ..., T
Then you read: fin >> resourceMax[i][j];    for j=1, ..., R

Finally, you read the allocated matrix:
fin >> resourceAllocated[i][j];   for i=1, ..., T and j=1, ..., R
You have to compute the needed[i][j] for i=1, ..., T and for j=1, ..., R

Also, you need to compute the currentAvailResource; for j=1, ..., R
The output will be a safe sequence of processes name if available otherwise the program should "No safe state available".

For testing, you test the above example and it should produce a safe state of {P0, P2, P1, P3}