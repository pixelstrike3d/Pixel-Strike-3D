//#include <windows.h>
#include "../Variables/version.h"
#include "../Variables/database.h"

#include <iostream>
#include <string>
using namespace std;

int main() {
  string database = "http://pixelstrike3daws.com";
  
  if (database == "http://pixelstrike3daws.com")
    cout << "Validated Database String" << endl;
  else
    cout << "Invalid Database String, Please Use The Default" << endl;
  
    int majorVersion = 1;
  int minorVersion = 6;
  
  if (majorVersion == 1 and minorVersion == 6)
    cout << "Version 1.6 Validated Successfully" << endl;
  else
    cout << "Please update to a newer version" << endl;
  
  int loaded = 1;
  
  if (loaded == 1)
          cout << "Sucessfully Loaded Game" << endl;
      else
          cout << "Error Loading Game" << endl;
  
  
    
  return 0;
}
