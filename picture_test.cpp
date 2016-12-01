/* Revised 120116.001
To compile use:
g++ -Wall -lpthread -o picture_test picture_test.cpp -lpigpio -lrt -std=c++14

This program is to test photo file structure and analysis.

I may use it to help the mower program with:
Location using visual references.
Georeference with sun, moon, stars...
Moving object identification and avoidance.

In JPG files 184-202 is a date and time. YYYY:MM:DD HH:MM:SS.

BMP height and width is:
Width is [19] * 256 + [18]
Height is [23] * 256 + [22]
RGB Data starts at offset [10]


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
streampos size;

int main (void)
{
  char * memblock;
  int c = 54;
  int width;
  int height;

  ifstream file ("pic.bmp", ios::in|ios::binary|ios::ate);
  if (file.is_open())
  {
    size = file.tellg();
    memblock = new char [size];
    file.seekg (0, ios::beg);
    file.read (memblock, size);
    file.close();
    width = memblock[19] * 256 + memblock[18];
    height = memblock[23] * 256 + memblock[22];
    cout << "the entire file content is in memory";
    cout << "The Size of the file is " << size  << endl;
    cout << "Width = " << width << endl;
    cout << "Height = " << height << endl;
    do {
    memblock[c] = 176;
    c += 1;
    } while  (c < 9000000);
  }
  else cout << "Unable to open file";

  ofstream outfile ("pic1.bmp" , ios::out|ios::binary);
  outfile.write (memblock,size);
  delete[] memblock;
  outfile.close();
  return 0;
}
