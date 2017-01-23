/* Revised 120816.001
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
  long c = 54;
  int width;
  int height;
  int h = 0, w = 0, r, g, b;
  int minr = 255, maxr = 0, ming = 255, maxg = 0, minb = 255, maxb = 0;
  long int avgr = 0, avgg = 0, avgb =0;

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
    cout << "the entire file content is in memory" << endl;
    cout << "The size of the file is " << size  << endl;
    cout << "Width = " << width << endl;
    cout << "Height = " << height << endl << endl << endl;

    for (c = 54;c+3 <= size;c = c+3)
	{r = memblock[c];
                if (minr > r) {minr = r;}
                if (maxr < r) {maxr = r;}
                avgr = avgr + r;
                        
        g = memblock[c+1];
                if (ming > g) {ming = g;}
                if (maxg < g) {maxg = g;}
                avgg = avgg + g;
        
        b = memblock[c+2];
                if (minb > b) {minb = b;}
                if (maxb < b) {maxb = b;}
                avgb = avgb + b;
        };

    avgr = avgr / width / height;
    avgg = avgg / width / height;
    avgb = avgb / width / height;
    cout << c << endl;
    cout << minr << ", " << ming << ", " << minb << endl;
    cout << maxr << ", " << maxg << ", " << maxb << endl;
    cout << avgr << ", " << avgg << ", " << avgb << endl;
    cout << h << w << endl;

//  Update memblock to change colors;
    c = 54;
    do {
    memblock[c] = r;
    c += 1;
    memblock[c] = g;
    c += 1;
    memblock[c] = b;
    c += 1;
    r += 1;
    if ( r > 255) {r = 0;};
       } while  (c < 900000);
  }

  else cout << "Unable to open file";

  ofstream outfile ("pic1.bmp" , ios::out|ios::binary);
  outfile.write (memblock,size);
  delete[] memblock;
  outfile.close();
  return 0;
}
