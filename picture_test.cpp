/* Revised 112216.001
To compile use:
g++ -Wall -lpthread -o picture_test picture_test.cpp -lpigpio -lrt -std=c++14

This program is to test photo file structure and analysis.

I may use it to help the mower program with:
Location using visual references.
Georeference with sun, moon, stars...
Moving object identification and avoidance.

In BMP files 184-202 is a date and time. YYYY:MM:DD HH:MM:SS.

*/

#include <iostream>
#include <fstream>
#include <pigpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <ratio>
#include <chrono> // For time controls.

using namespace std;
using namespace std::chrono;
long int lint; 
char * pEnd;
char cn;

int main (void)
{
  streampos size;
  char * memblock;
  int c = 18;
  char kchar;

  ifstream file ("pic.bmp", ios::in|ios::binary|ios::ate);
  if (file.is_open())
  {
    size = file.tellg();
    memblock = new char [size];
    file.seekg (0, ios::beg);
    file.read (memblock, size);
    file.close();
    cout << "the entire file content is in memory";
    cout << "The Size of the file is " << size  << endl;
    cin >> kchar;
    do {
    c += 1;
    cn = memblock[c];
    lint = cn;
    cout << c << ", "<< cn << ", "<<lint<< endl;
    } while  (c < 22);

    delete[] memblock;
  }
  else cout << "Unable to open file";
  return 0;
}
