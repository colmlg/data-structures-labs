#include <math.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <list>

using std::list;
using std::cin;
using std::cout;
using std::endl;
using std::string;

class RowEntry {
public:
    double value;
    int index;
    RowEntry(double value, int index) {
        this->value = value;
        this->index = index;
    }
};

list<RowEntry> formatz(string line);
void printList(list< list<RowEntry> > matrix);
double epsilon = 0.0;


int main(int argc, char *argv[]) {
    if (argc > 1 && string(argv[1]) == "-e") {
        epsilon = fabs(strtod(argv[2], 0));
    }
    list< list<RowEntry> > matrix;
    string line;
    while (getline(cin, line)) {
        matrix.push_back(formatz(line));
    }
    printList(matrix);
}

list<RowEntry> formatz(string line) {
    list<RowEntry> row;
    std::istringstream lstream(line) ;
    int index = 1;
    double val;
    while (lstream>> val)  {
        if (val > epsilon) {
            RowEntry entry = RowEntry(val, index);
            row.push_back(entry);
        }
        index++;
    }
    return row;
}

void printList(list< list<RowEntry> > matrix) {
    for(list<RowEntry> row : matrix) {
        for(RowEntry entry : row) {
            cout << entry.index << ' ' << entry.value << ' ';
        }
        cout << endl;
    }
}
