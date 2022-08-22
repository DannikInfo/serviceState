#include "config.h"

//DB
static std::string dbUrl;
static std::string dbUser;
static std::string dbPass;
static std::string dbName;

static std::string pointsTable;

void config::loadConfig(){
    nlohmann::json j;

    if(std::filesystem::exists("config.json")){
        std::ifstream i("config.json");
        i >> j;
        dbUrl = j["dbUrl"];
        dbUser = j["dbUser"];
        dbPass = j["dbPass"];
        dbName = j["dbName"];
        pointsTable = j["pointsTable"];

    }else
        initConfig();
}

void config::initConfig(){
    nlohmann::json j;

    j["dbUrl"] = dbUrl = "localhost";
    j["dbUser"] = dbUser = "root";
    j["dbPass"] = dbPass = "root";
    j["dbName"] = dbName = "db";
    j["pointsTable"] = pointsTable = "points";

    std::ofstream o("config.json");
    o << std::setw(4) << j << std::endl;
}

std::string config::getDBUrl() {
    return dbUrl;
}

std::string config::getDBUser() {
    return dbUser;
}

std::string config::getDBPass() {
    return dbPass;
}

std::string config::getDBName() {
    return dbName;
}

std::string config::getPointsTable() {
    return pointsTable;
}

