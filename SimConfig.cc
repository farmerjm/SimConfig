#include "SimConfig.h"

void SimConfig::AddConfig(const std::string& fname) {
  if (fname.empty()) {
    std::cerr << "ERROR:  No file passed to config reader." << std::endl;
    return;
  }
  if (ParsedConfigs.size() != 0) {
    for (auto conf : ParsedConfigs) {
      if (fname == conf) {
        std::cerr << "ERROR: Duplicate configuration read!" << std::endl;
        return;
      }
    }
  }
  ReadConfig(fname);
}

int SimConfig::FindIndex(const std::string& varname) const {
  int index = -1;
  for (int i=0; i<vals.size(); i++) if (vals[i].first == varname) index = i;
  return index;
}

double SimConfig::GetValue(const std::string& var) {
  return std::stod(GetString(var));
}

const std::string& SimConfig::GetString(const std::string& var) {
  int index = FindIndex(var);
  if (index==-1) {
    std::cerr << "Error matching parameter!" << std::endl;
    return "ERROR_LOOKUP";
  }
  return vals[index].second;
}

void SimConfig::ReadConfig(const std::string& fname) {
  std::ifstream fin;
  fin.open(fname);
  std::string sin, split1, split2;

  while (getline(fin,sin)) {
    if (sin[0]=='#' || sin.empty()) continue;

    int len = sin.length();
    int sep=-1;
    
    for (int i=0; i<len; i++) {
      if (sin[i]=='=') {
        if (sep != -1) {
          std::cerr << "ERROR: Error parsing file!" << std::endl;
        }
        sep=i;
      }
    }

    if (sep==0) {
      std::cerr << "ERROR:  Error parsing file!" << std::endl;
    }
    split1=sin.substr(0,sep);
    split2=sin.substr(sep+1,len-sep);

    if (vals.size() != 0) {
      for (auto pair : vals) {
        if (pair.first == split1) {
          std::cerr << "ERROR:  Duplicate key: " << split1 << std::endl;
          return;
        }
      }
    }

    std::pair< std::string, std::string> pair(split1,split2);
    vals.push_back(pair);
  }
}
