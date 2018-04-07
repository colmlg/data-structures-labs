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

    explicit RowEntry(int column, double value) {
        this->column = column;
        this->value = value;
    }
};

using Row = list<RowEntry>;
using Matrix = vector<Row>;

Matrix readMatrix();
Row readLine(string line);
void print(const Matrix& matrix);
Matrix transposeMatrix(const Matrix& matrix);
Matrix multiplyMatrices(const Matrix& first, const Matrix& second, Matrix& result);
double multiplyRows(Row first, Row second);

int transposedRowCount = 0;

int main(int argc, char *argv[]) {
    Matrix sparseMatrix = readMatrix();
    Matrix resultMatrix(sparseMatrix.size());
    
    multiplyMatrices(sparseMatrix, sparseMatrix, resultMatrix);
    print(resultMatrix);
}

inline Matrix readMatrix() {
    Matrix matrix;
    string line;
    int rowCount = 0;
    while (getline(cin, line)) {
        rowCount++;
        matrix.push_back(readLine(line));
    }

    if (rowCount > transposedRowCount) {
        transposedRowCount = rowCount;
    }

    return matrix;
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

Matrix transposeMatrix(const Matrix& matrix) {
    Matrix transposed(transposedRowCount);
    for (int r = 0; r < matrix.size(); r++) {
        for (RowEntry entry : matrix[r]) {
            int newRow = entry.column - 1;
            entry.column = r + 1;
            transposed[newRow].push_back(entry);
        }
    }
    return transposed;
}

Matrix multiplyMatrices(const Matrix& first, const Matrix& second, Matrix& result) {
    Matrix secondT = transposeMatrix(second);
    for(int row = 0; row < first.size(); row++) {
        for(int column = 0; column < secondT.size(); column++) {
            double value = multiplyRows(first[row], secondT[column]);
            if (value == 0) {
                continue;
            }
            result[row].push_back(RowEntry(column + 1, value));
        }
    }
}

double multiplyRows(Row first, Row second) {
    double result = 0.0;
    Row::iterator firstPos = first.begin();
    Row::iterator secondPos = second.begin();
        
    while(firstPos != first.end() && secondPos != second.end()) {
        if(firstPos->column == secondPos->column) {
            result += (firstPos->value * secondPos->value);
            firstPos++;
            secondPos++;            
        } else if (firstPos->column > secondPos->column) {
            secondPos++;
        } else { // if (firstPos->column < secondPos->column)
            firstPos++;
        }
    }
    
    return result;
}
