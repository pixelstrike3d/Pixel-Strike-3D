//#include <windows.h>
#include "../Variables/version.h"
#include "../Variables/database.h"

#include <iostream>
#include <string>
using namespace std;

int main() {
  int loaded = 0
      
  if (majorVersion == 1 and minorVersion == 6 and database == "http://pixelstrike3daws.com")
        loaded = 1
      else
        loaded = 0
          
  if (loaded == 1)
          cout << "Sucessfully Loaded Game" << endl;
      else
          cout << "Error Loading Game" << endl;
  
  
    
  return 0;
}
