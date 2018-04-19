#include <math.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>

using std::list;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class RowEntry {
public:
    int column;
    double value;

    RowEntry(int column, double value) {
        this->column = column;
        this->value = value;
    }
};

typedef list<RowEntry> Row;
typedef vector<Row> Matrix;

void readMatrix(Matrix& matrix);
Row readLine(string line);
void print(const Matrix& matrix);
void transposeMatrix(const Matrix& matrix, Matrix& transposed);
void multiplyMatrices(const Matrix& first, const Matrix& second, Matrix& result);
double multiplyRows(const Row& first, const Row& second);
Matrix createIdentityMatrix(const int size);
double dotProd(const Row& r1, const Row& r2);


int transposedRowCount = 0;

int main(int argc, char *argv[]) {

    
    if(argc < 2) {
        cout << "Illegal exponent; exiting." << endl;
        return 1;
    }
    
    std::istringstream ss(argv[1]);
    int power;
    if (!(ss >> power) || power < 0) {
        cout << "Illegal exponent; exiting." << endl;
        return 1;
    }

    Matrix sparseMatrix;
    readMatrix(sparseMatrix);
    
    if(power == 0) {
        print(createIdentityMatrix(sparseMatrix.size()));
        return 0;
    }
    
    if(power == 1) {
        print(sparseMatrix);
        return 0;
    }
    
    Matrix resultMatrix;
    multiplyMatrices(sparseMatrix, sparseMatrix, resultMatrix);

    for (int j = 2; j < power; j++) {
        Matrix newResult;
        multiplyMatrices(sparseMatrix, resultMatrix, newResult);
        resultMatrix = newResult;
    }

    print(resultMatrix);

    return 0;
}

 void readMatrix(Matrix& matrix) {
    string line;
    int rowCount = 0;
    while (getline(cin, line)) {
        rowCount++;
        matrix.push_back(readLine(line));
    }

    if (rowCount > transposedRowCount) {
        transposedRowCount = rowCount;
    }
}

inline Row readLine(string line) {
    Row row;
    std::istringstream lstream(line);
    int column;
    double value;

    while (lstream >> column >> value) {
        row.push_back(RowEntry(column, value));
        if (column > transposedRowCount) {
            transposedRowCount = column;
        }
    }
    return row;
}

void print(const Matrix& matrix) {
    for (Row row : matrix) {
        for (RowEntry entry : row) {
            cout << entry.column << ' ' << entry.value << ' ';
        }
        cout << endl;
    }
}

void transposeMatrix(const Matrix& matrix, Matrix& transposed) {
    for (int r = 0; r < matrix.size(); r++) {
        for (RowEntry entry : matrix[r]) {
            int newRow = entry.column - 1;
            entry.column = r + 1;
            transposed[newRow].push_back(entry);
        }
    }
}

void multiplyMatrices(const Matrix& first, const Matrix& second, Matrix& result) {
    result.clear();
    for (int i = 0; i < first.size(); i++) {
      Row row;
      result.push_back(row);
    }

    Matrix secondT(transposedRowCount);
    transposeMatrix(second, secondT);
    
    for (int row = 0; row < first.size(); row++) {
        for (int column = 0; column < secondT.size(); column++) {
            double value = multiplyRows(first[row], secondT[column]);
            if (value == 0) {
                continue;
            }
            result[row].push_back(RowEntry(column + 1, value));
        }
    }
}

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

double multiplyRows(const Row& first, const Row& second) {
    double result = 0.0;
    Row::const_iterator firstPos = first.begin();
    Row::const_iterator secondPos = second.begin();
    
    Row::const_iterator firstEnd = first.end();
    Row::const_iterator secondEnd = second.end();


    while (true) {
        int targetCol = MAX(firstPos->column, secondPos->column);
        while(firstPos->column < targetCol && firstPos != firstEnd)
            firstPos++;

        if(firstPos == firstEnd) break;
	
        while(secondPos->column < targetCol && secondPos != secondEnd)
            secondPos++;

        if(secondPos == secondEnd) break;
	
        if (firstPos->column == secondPos->column) {
            result += (firstPos->value * secondPos->value);
            firstPos++;
            if(firstPos == firstEnd) break;
        }
    }
    
    return result;
}

Matrix createIdentityMatrix(const int size) {
    Matrix identity = Matrix(size);
    
    for(int i = 0; i < size; i++) {
        identity[i].push_back(RowEntry((i + 1), 1));
    }
    return identity;
}
