/* ----------------------------------------------------------------------------
 * Copyright &copy; 2015 Dong Kim <donm93@fullerton.edu>
 * Released under the [MIT License] (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */

#include <fstream>
#include <iostream>
#include <string>

#include "point.h"

using std::ifstream;

using std::cerr;
using std::cout;
using std::endl;

using std::string;

// ----------------------------------------------------------------------------

template <typename T, const unsigned int SIZE>
void print_max(const string & filename) {

    ifstream infile(filename);


    Point<T,SIZE> p, pmax;

    try {
        infile >> pmax;
    } catch (std::exception & e) {
        cerr << "ERROR: unable to read first element (" << e.what() << ")\n";
        cerr << "  source code line: " << __LINE__ << endl;
        cerr << "  reading from: " << filename << endl;
        cerr << "  at position: " << infile.tellg() << endl;
        return;
    }
    for (;;) {
        try {
            infile >> p;
        } catch (typename Point<T,SIZE>::EmptyStreamError & e) {
            break; 
        } catch (typename Point<T,SIZE>::InvalidSymbolError & e) {
           
            cerr << "ERROR: ignoring invalid element (" << e.what() << ")\n";
            cerr << "  source code line: " << __LINE__ << endl;
            cerr << "  reading from: " << filename << endl;
            cerr << "  at position: " << infile.tellg() << endl;
            while (infile.get() != '\n');
        } catch (std::exception & e) {
            cerr << "ERROR: unable to recover (" << e.what() << ")\n";
            cerr << "  source code line: " << __LINE__ << endl;
            cerr << "  reading from: " << filename << endl;
            cerr << "  at position: " << infile.tellg() << endl;
            return;
        }
        if (p > pmax)
            pmax = p;
    }

    cout << "the point furthest from " << Point<T,SIZE>() << " in "
         << filename << " is " << pmax << "\n\n";
}

// ----------------------------------------------------------------------------

int main() {
    print_max<int,1>("../input-int-1.txt");
    print_max<int,2>("../input-int-2.txt");
    print_max<int,5>("../input-int-5.txt");

    print_max<double,2>("../input-double-2.txt");
    print_max<double,3>("../input-double-3.txt");

    print_max<int,3>("../input-int-3-bad.txt");
    print_max<int,4>("../input-int-4-very-bad.txt");

    return 0;  // success
}

