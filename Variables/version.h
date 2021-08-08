#include <iostream>
#include <string>
using namespace std;

int main() {
  int majorVersion = 1;
  int minorVersion = 6;
  
  if (majorVersion == 1 and minorVersion == 6)
    cout << "Version 1.6 Validated Successfully" << endl;
  else
    cout << "Please update to a newer version" << endl;
    
  return 0;
}
