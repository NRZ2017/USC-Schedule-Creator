#include "Processing.h"

using namespace std;

void Process::initial(string filename) {
  bool found = false;
  bool foundType = false;
  string prevName;
  ifstream ifile(filename);
  if (ifile.fail()) {
    cout << "Invalid filename" << endl;
    return;
  }
  string tempType, tempName, tempDate, tempStarttime, tempEndtime;
  while (ifile >> tempType >> tempName >> tempDate >> tempStarttime >>
         tempEndtime) {
    for (unsigned i = 0; i < block.size(); i++) {
      if (block[i].first.compare(tempName) == 0) {
        for (unsigned j = 0; j < block[i].second.size(); j++) {
          // cout << "tempType: " << tempType << endl;
          // cout << "Second: " <<block[i].second[j].first << endl;
          if (block[i].second[j].first == tempType) {
            // cout << "hit!" << endl;
            foundType = true;
            block[i].second[j].second.push_back(
                new Base(tempDate, tempStarttime, tempEndtime));
            break;
          }
        }
        // cout << "foundType: " << foundType << endl;
        if (!foundType) {
          block[i].second.push_back({tempType, vector<Base *>()});
          block[i].second.back().second.push_back(
              new Base(tempDate, tempStarttime, tempEndtime));
        }
        found = true;
        foundType = false;
        break;
      }
    }
    if (!found) {
      block.push_back({tempName, vector<pair<string, vector<Base *>>>()});
      block.back().second.push_back({tempType, vector<Base *>()});
      block.back().second.back().second.push_back(
          new Base(tempDate, tempStarttime, tempEndtime));
    }
    found = false;
  }
}

void Process::printListOClasses() {
  for (unsigned i = 0; i < block.size(); i++) {
    for (unsigned j = 0; j < block[i].second.size(); j++) {
      for (unsigned k = 0; k < block[i].second[j].second.size(); k++) {
        cout << block[i].second[j].first << " ";
        cout << block[i].first << " ";
        cout << block[i].second[j].second[k]->getDates() << " ";
        cout << block[i].second[j].second[k]->getstartTime() << " ";
        cout << block[i].second[j].second[k]->getendTime() << " ";
        cout << endl;
      }
      cout << "\n" << endl;
    }
  }
}

string Process::MilConversion(string s) {
  string ret = "";
  if (s[s.size() - 2] == 'A' || s[s.size() - 2] == 'a') {
    string temp = s.substr(0, 2);
    int time = stoi(temp);
    if (time == 12) {
      ret = "00:";
      ret += s.substr(3, 5);
    } else {
      ret = s.substr(0, s.size() - 2);
    }
  } else {
    string temp = s.substr(0, 2);
    int time = stoi(temp);
    if (time == 12) {
      ret = s.substr(0, s.size() - 2);
      return ret;
    }
    time += 12;
    if (time == 24) {
      ret = ret + "00" + s.substr(2, 6);
    }
    ret = ret + to_string(time) + s.substr(2, 6);
  }
  return ret;
}

bool Process::IsOverlap(string start1, string start2, string end1,
                        string end2) {
  start1 = MilConversion(start1);
  start2 = MilConversion(start2);
  end1 = MilConversion(end1);
  end2 = MilConversion(end2);
  int tempStart1Hour = stoi(start1.substr(0, 2));
  int tempStart1Minutes = stoi(start1.substr(3, 2));
  int tempStart2Hour = stoi(start2.substr(0, 2));
  int tempStart2Minutes = stoi(start2.substr(3, 2));
  int tempEnd1Hour = stoi(end1.substr(0, 2));
  int tempEnd1Minutes = stoi(end1.substr(3, 2));
  int tempEnd2Hour = stoi(end2.substr(0, 2));
  int tempEnd2Minutes = stoi(end2.substr(3, 2));

  // cout << "start1 == start2: " << start1.compare(start2) << endl;
  // cout << "end1 == end2: " << end1.compare(end2) << endl;
  // cout << "start1Hour: " << tempStart1Hour << endl;
  // cout << "start1Minutes: " << tempStart1Minutes << endl;
  // cout << "start2Hour: " << tempStart2Hour << endl;
  // cout << "start2Minutes: " << tempStart2Minutes << endl;
  // cout << "end1Hour: " << tempEnd1Hour << endl;
  // cout << "end1Minutes: " << tempEnd1Minutes << endl;
  // cout << "end2Hour: " << tempEnd2Hour << endl;
  // cout << "end2Minutes: " << tempEnd2Minutes << endl;

  int tempStart1 = tempStart1Hour * 60 + tempStart1Minutes;
  int tempStart2 = tempStart2Hour * 60 + tempStart2Minutes;
  int tempEnd1 = tempEnd1Hour * 60 + tempEnd1Minutes;
  int tempEnd2 = tempEnd2Hour * 60 + tempEnd2Minutes;
  return tempStart1 <= tempEnd2 && tempEnd1 >= tempStart2;
}

void Process::findBestSchedule(string filename) { 
  ofstream ofile(filename + ".txt");
  bool works = true;
  int count = 0;
  for (unsigned i = 0; i < block.size(); i++) {
    count += block[i].second.size();
  }
  vector<int> maxIndex(count);
  count = 0;
  for (unsigned i = 0; i < block.size(); i++) {
    for (unsigned j = 0; j < block[i].second.size(); j++) {
      // cout << "i: " << i << endl;
      // cout << "ret: " << block[i].second[j].second.size() << endl;
      maxIndex[count] = block[i].second[j].second.size();
      count++;
    }
  }

  long long total = 1;
  for (unsigned i = 0; i < maxIndex.size(); i++) {
    // cout << maxIndex[i] << endl;
    total *= maxIndex[i];
  }

  for (long long i = 0; i < total; i++) {
    works = true;
    int h = 0;
    vector<int> indicies = getVectorIndicies(i, maxIndex);
    vector<tuple<string, string, string, string, string>> check(
        indicies.size());
    // for (unsigned j = 0; j < indicies.size(); j++) {
    for (unsigned z = 0; z < block.size(); z++) {
      // cout << "size: " << block[z].second.size() << endl;
      for (unsigned x = 0; x < block[z].second.size(); x++) {
        // cout << block[z].second.size() << endl;
        // cout << "j: " << j << endl;
        // cout << "z: " << z << endl;
        // cout << "h: " << h << endl;
        // cout << "x: " << x << endl;
        // cout << indicies[h] << endl;
        // cout << block[z].second[x].second[indicies[h]]->getstartTime() <<
        // endl; cout << block[z].second[x].second[indicies[h]]->getendTime() <<
        // endl; cout << block[z].second[x].second[indicies[h]]->getDates() <<
        // endl;
        get<0>(check[h]) =
            block[z].second[x].second[indicies[h]]->getstartTime();
        get<1>(check[h]) = block[z].second[x].second[indicies[h]]->getendTime();
        get<2>(check[h]) = block[z].second[x].second[indicies[h]]->getDates();
        get<3>(check[h]) = block[z].first;
        get<4>(check[h]) = block[z].second[x].first;
        h++;
      }
    }
    // get<0>(check[j]) = block[j].second[indicies[j]]->getstartTime();
    // get<1>(check[j]) = block[j].second[indicies[j]]->getendTime();
    // get<2>(check[j]) = block[j].second[indicies[j]]->getDates();
    // }

    h = 0;

    // cout << "start" << endl;
    // cout << check.size() << endl;

    // for(unsigned x = 0; x < check.size(); x++) {
    //   cout << get<0>(check[x]) << endl;
    //   cout << get<1>(check[x]) << endl;
    //   cout << get<2>(check[x]) << endl;
    // }

    // cout << "end" << endl;

    for (unsigned k = 0; k < check.size(); k++) {
      for (unsigned z = k + 1; z < check.size(); z++) {
        // cout << "start1: " << get<0>(check[k]) << endl;
        //   cout << "start2: " << get<0>(check[z]) << endl;
        //   cout << "end1: " << get<1>(check[k]) << endl;
        //   cout << "end2: " << get<1>(check[z]) << endl;
        if (IsOverlap(get<0>(check[k]), get<0>(check[z]), get<1>(check[k]),
                      get<1>(check[z]))) {
          if (IsSameDate(get<2>(check[k]), get<2>(check[z]))) {
            // cout << "date1: " << get<2>(check[k]) << " ";
            // cout << "date2: " << get<2>(check[z]) << endl;
            works = false;
            goto loopend;
          }
        }
      }
      if (!works)
        goto loopend;
    }
  loopend:;
    // cout << works << endl;
    if (works) {
      for (unsigned l = 0; l < check.size(); l++) {
        ofile << get<4>(check[l]) << " ";
        ofile << get<3>(check[l]) << " ";
        ofile << get<2>(check[l]) << " ";
        ofile << get<0>(check[l]) << " ";
        ofile << get<1>(check[l]) << endl;
      }
      ofile << endl;
    }
  }
}

vector<int> Process::getVectorIndicies(int index, vector<int> &maxIndicies) {
  vector<int> ret(maxIndicies.size());
  for (unsigned i = 0; i < ret.size(); i++) {
    ret[i] = 0;
  }
  for (int i = 0; i < index; i++) {
    ret.back() += 1;
    for (unsigned j = maxIndicies.size() - 1; j > 0; j--) {
      if (ret[j] >= maxIndicies[j]) {
        ret[j] = 0;
        ret[j - 1] += 1;
      } else {
        break;
      }
    }
  }
  return ret;
}

bool Process::IsSameDate(string date1, string date2) {
  if (date1.size() > date2.size()) {
    if (date1.find(date2) == string::npos) {
      return false;
    }
    return true;
  } else {
    if (date2.find(date1) == string::npos) {
      return false;
    }
    return true;
  }
}