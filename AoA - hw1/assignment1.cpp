//Sinem Elif Haseki - 150160026
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <ctype.h>
using namespace std;

class Array{
        int size;
        const char *algoType;
        const char* filename;
    public:
        int *arr;
        void mergeHalves(int start, int middle, int end);
        void sort(int start, int end);
        Array(const char* algoType, int size, const char* filename):size(size),algoType(algoType),filename(filename){
            arr = new int[size]; //create a dynamic array of requested size
            for(int i = 80; i > 0;i=i-6)
                arr[i] = i; //initialize array
            readFile(filename,algoType);
            clock_t t = clock();
            (*algoType == 'm') ? sort(0,size-1) : bubbleSort(); //if algoType is m, call merge sort function, else call bubblesort
            t = clock()-t;
            cout << "Time of execution for "<<size<<" elements: "<<float(t)/CLOCKS_PER_SEC<<" seconds for ";
            if(*algoType == 'm') cout << "merge sort"<<endl;
            else cout << "bubble sort"<<endl;
        }
        void bubbleSort();
        void writeOutput();
        void readFile(const char* filename, const char* algoType);
};

void Array::readFile(const char* filename, const char* algoType){
    ifstream file(filename);

    for(int i = 0; i<size; i++)
        file >> arr[i];
}

void Array::writeOutput(){
    ofstream file("output.txt");
    for(int i = 0; i<size; i++){
        file << arr[i] << " ";
    }


}

//BUBBLE SORT FUNCTIONS

void Array::bubbleSort(){ //bubble sorting while traversing the array
    int i = size;
    bool sorted = false;
    while(i>1 && !sorted){
        sorted=true;
        for(int j=1; j <= i-1; j++){
            if(arr[j] < arr[j-1]){
                int temp = arr[j-1];
                arr[j-1]=arr[j];
                arr[j]=temp;
                sorted = false;
            }
        }
        i--;
    }
}

//MERGE SORT FUNCTIONS
void Array::sort(int start, int end){
    int middle;
    if(start < end){
        middle = floor(start+end)/2;
        sort(start, middle); //recursively calls the first half
        sort(middle+1, end); //calls the second half
        mergeHalves(start, middle, end);
    }
}

void Array::mergeHalves(int start, int middle, int end){
    int b[size];
    int k=start, i=start, j=middle+1;
    while(k<=middle && j <= end){
        if(arr[k] <= arr[j]){
            b[i]=arr[k];
            k++;
        }
        else{
            b[i]=arr[j];
            j++;
        }
        i++;
    }
    if(k>middle){
        for(int h=j; h<=end;h++){
            b[i]=arr[h];
            i++;
        }
    }
    else{
        for(int h=k; h<=middle;h++){
            b[i]=arr[h];
            i++;
        }
    }
    for(int h=start;h<=end;h++){
        arr[h]=b[h];
    }
}

int main(int argc, char **argv){
    const char * type = argv[1];
    if (*type!='m' && *type!='b'){
        cerr << "You have entered invalid algo type!"<<endl;
        return -1;
    }
    
    Array a(argv[1],atoi(argv[2]),argv[3]);
    a.writeOutput();

    return 0;
}