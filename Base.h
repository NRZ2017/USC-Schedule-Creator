#include <iostream>
#include <string>

class Base {
public:
  Base(std::string dates, std::string Starttime, std::string Endtime);
  std::string getstartTime();
  std::string getendTime();
  std::string getDates();

private:
  std::string startTime;
  std::string endTime;
  std::string dates;
};
