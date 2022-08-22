#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include "nlohmann/json.hpp"
#include <fstream>

class config {
public:
    static void loadConfig();
    static void initConfig();

    //DB
    static std::string getDBUrl();
    static std::string getDBUser();
    static std::string getDBPass();
    static std::string getDBName();
    static std::string getPointsTable();

};


#endif //CONFIG_H
