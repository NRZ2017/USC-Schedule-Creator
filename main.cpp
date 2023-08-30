#include "Processing.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
  string input;
  bool loaded = false;
  Process x;

  while(true) {
    cout << "Welcome. Please select one of the following options" << endl;
    cout << "1 - Load class file" << endl;
    cout << "2 - Print all classes" << endl;
    cout << "3 - Display all possible schedules" << endl;
    cout << "4 - Quit" << endl;
    cin >> input;
    if(input == "1") {
      cout << "Please enter a filename for imported file" << endl;
      cin >> input;
        x.initial(input);
      loaded = true;
    }
    else if(input == "2") {
      if(loaded) {
        x.printListOClasses();
      }
      else {
        cout << "Did not load in a class list!" << endl;
      }
    }
    else if(input == "3") {
      if(loaded) {
      cout << "Please enter a filename for the exported file" << endl;
      cin >> input;
      x.findBestSchedule(input);
      }
      else {
        cout << "Did not load in a class list!" << endl;
      }
    }
    else if(input == "4") {return 0;}
    else { cout << "invliad input, try again" << endl;
          cout << endl;}
  }

  // cout << x.IsOverlap("8:00am", "3:00pm", "2:20pm", "5:00pm") << endl;
  // x.printListOClasses();
  // x.findBestSchedule();
  // vector<int> y = {1,4,3,2,2};
  // long long p = 1;
  // for (int& x : y) p *= x;
  // vector<int> ret;
  // for(int i = 0; i < p; i++) {
  //   ret = x.getVectorIndicies(i, y);
  //   for(unsigned i = 0; i < ret.size(); i++) {
  //     cout << ret[i] << " ";
  //   }
  //   cout << endl;
  // }

  return 0;
}
