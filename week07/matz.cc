#include <math.h>
#include <cstdlib>
#include <iostream>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

void formatz(string line);
double epsilon = 0.0;

int main(int argc, char *argv[]) {
    if (argc > 1 && string(argv[1]) == "-e") {
        epsilon = fabs(strtod(argv[2], 0));
    }
    
    string line;
    while (getline(cin, line)) {
        formatz(line);
    }
}

void formatz(string line) {
    std::istringstream lstream(line) ;
    int index = 1;
    double val;
    
    while (lstream>> val)  {
        if (val > epsilon) {
            cout << index << ' ' << val << ' ';
        }
        index++;
    }
    cout << endl;
}
