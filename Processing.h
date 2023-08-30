#include "Base.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <string>
#include <tuple>
#include <vector>

class Process {
public:
  void initial(std::string filename);
  void findBestSchedule(std::string filename);
  void printListOClasses();


private:
  std::vector<std::pair<
      std::string, std::vector<std::pair<std::string, std::vector<Base *>>>>>
      block;
  bool IsOverlap(std::string start1, std::string start2, std::string end1,
                 std::string end2);
  std::string MilConversion(std::string s);
  std::vector<int> getVectorIndicies(int index, std::vector<int> &maxIndicies);
  bool IsSameDate(std::string date1, std::string date2);
};
