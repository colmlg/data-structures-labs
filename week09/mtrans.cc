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
void printList(vector< list<RowEntry> > matrix);
double epsilon = 0.0;

int main(int argc, char *argv[]) {
    if (argc > 1 && string(argv[1]) == "-e") {
        epsilon = fabs(strtod(argv[2], 0));
    }
    vector< list<RowEntry> > matrix;
    string line;
    while (getline(cin, line)) {
        matrix.push_back(readLine(line));
    }
    printList(matrix);
    vector< list<RowEntry> > transposed = transposeMatrix(matrix);
    printList(transposed);

}

list<RowEntry> readLine(string line) {
    list<RowEntry> row;
    std::istringstream lstream(line);
    double column, value;
    while (lstream >> column >> value) {
        row.push_back(RowEntry(column, value));
    }
    return row;
}

vector< list<RowEntry> > transposeMatrix(vector< list<RowEntry> > matrix) {
    vector< list<RowEntry> > transposed(20);
    for (int r = 0; r < matrix.size(); r++) {
        for (RowEntry entry : matrix[r]) {
            int newRow = entry.column;
            entry.column = r + 1;
            transposed[newRow].push_back(entry);
        }
    }
    return transposed;
}

void printList(vector< list<RowEntry> > matrix) {
    for (list<RowEntry> row : matrix) {
        for (RowEntry entry : row) {
            cout << entry.column << ' ' << entry.value << ' ';
        }
        cout << endl;
    }
}
