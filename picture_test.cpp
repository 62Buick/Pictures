/* Revised 113016.001
To compile use:
g++ -Wall -lpthread -o picture_test picture_test.cpp -lpigpio -lrt -std=c++14

This program is to test photo file structure and analysis.

I may use it to help the mower program with:
Location using visual references.
Georeference with sun, moon, stars...
Moving object identification and avoidance.

In JPG files 184-202 is a date and time. YYYY:MM:DD HH:MM:SS.

BMP height and width is:
Width is [20] * 256 + [19]
Height is [24] * 256 + [23]
RGB Data starts at offset [11]


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
  int c = 0;
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
    cn = memblock[c];
    lint = cn;
    cout << lint << ", ";
    c += 1;
    cn = memblock[c];
    lint = cn;
    cout << lint << ", ";
    c += 1;
    cn = memblock[c];
    lint = cn;
    cout << lint << endl;
    c += 1;
    } while  (c < 200);

    delete[] memblock;
  }
  else cout << "Unable to open file";
  return 0;
}
