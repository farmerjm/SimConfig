#ifndef SIMCONFIG_H
#define SIMCONFIG_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
class SimConfig {

  public:
    SimConfig() {}
    ~SimConfig() {};

    void AddConfig(const std::string& fname);

    double GetValue(const std::string& var);
    const std::string& GetString(const std::string& var); 

    static SimConfig& Instance() {
      static SimConfig conf;
      return conf;
    }

  private:
 
    void ReadConfig(const std::string& fname);
    int FindIndex(const std::string& varname) const;

    std::vector<std::string> ParsedConfigs;
    std::vector< std::pair <std::string, std::string> > vals;


};

#endif
