#include <math.h>
#include <cstdlib>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

void readMatrix (int numberOfRows, int numberOfColumns, double **array);
void formatz (int numberOfRows, int numberOfColumns, double **array);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Not enough arguments!" << endl;
        exit(1);
    }
    
    int matrixRows = atoi(argv[1]);  
    int matrixColumns = atoi(argv[2]);

    double ** inMatrix = new double*[matrixRows]; //Reserve space for the incoming matrix
    for(int i = 0; i < matrixRows; i++) {
        inMatrix[i] = new double[matrixColumns];
    }
    
    readMatrix(matrixRows, matrixColumns, inMatrix);
    formatz(matrixRows, matrixColumns, inMatrix);

    
}

// read from standard in to this array, row by row
//  for a total of r x c entries;
//  WARNING: space for array must have been reserved beforehand
void readMatrix(int numberOfRows, int numberOfColumns, double **array) {
    for (int i = 0; i < numberOfRows; i++) {
        for (int j = 0; j < numberOfColumns; j++) {
            cin >> array[i][j];
        }
    }
}

void formatz(int numberOfRows, int numberOfColumns, double **array) {
    cout << numberOfRows << endl;
    int totalNonZeroEntries = 0;
    for (int i = 0; i < numberOfRows; i++) {
        int rowNonZeroEntries = 0;
        for (int j = 0; j < numberOfColumns; j++) {
            if (array[i][j] != 0) {
                totalNonZeroEntries++;
                rowNonZeroEntries++;
            }
        }
        
        cout << rowNonZeroEntries << ' ';
        
        for (int j = 0; j < numberOfColumns; j++) {
            if (array[i][j] != 0) {
                cout << j + 1 << ' ' << array[i][j] << ' ';
            }
        }
        
        cout << endl;
    }
    
    cout << totalNonZeroEntries << endl;
}
