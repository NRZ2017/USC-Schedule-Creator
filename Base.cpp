#include "Base.h"

using namespace std;

Base::Base(string Dates, string Starttime, string Endtime) {
  dates = Dates;
  startTime = Starttime;
  endTime = Endtime;
}

string Base::getendTime() { return endTime; }

string Base::getstartTime() { return startTime; }

string Base::getDates() { return dates; }
