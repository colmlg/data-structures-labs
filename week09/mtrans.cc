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

list<RowEntry> readLine(string line);
vector< list<RowEntry> > transposeMatrix(vector< list<RowEntry> > matrix);
void print(vector< list<RowEntry> > matrix);
int transposedRowCount = 0;

int main(int argc, char *argv[]) {
    vector< list<RowEntry> > matrix;
    string line;
    int rowCount = 0;
    while (getline(cin, line)) {
        rowCount++;
        matrix.push_back(readLine(line));
    }

    if (rowCount > transposedRowCount) {
        transposedRowCount = rowCount;
    }
    vector< list<RowEntry> > transposed = transposeMatrix(matrix);
    print(transposed);
}

list<RowEntry> readLine(string line) {
    list<RowEntry> row;
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

vector< list<RowEntry> > transposeMatrix(vector< list<RowEntry> > matrix) {
    vector< list<RowEntry> > transposed(transposedRowCount);
    for (int r = 0; r < matrix.size(); r++) {
        for (RowEntry entry : matrix[r]) {
            int newRow = entry.column - 1;
            entry.column = r + 1;
            transposed[newRow].push_back(entry);
        }
    }
    return transposed;
}

void print(vector< list<RowEntry> > matrix) {
    for (list<RowEntry> row : matrix) {
        for (RowEntry entry : row) {
            cout << entry.column << ' ' << entry.value << ' ';
        }
        cout << endl;
    }
}
