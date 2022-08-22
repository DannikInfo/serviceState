#include <iostream>
#include <thread>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "config.h"
#include "logger.h"

int main() {
    config::loadConfig();
    sql::Driver* driver = get_driver_instance();

    while(true){
        try {
            std::unique_ptr<sql::Connection> con(
                    driver->connect(config::getDBUrl(), config::getDBUser(), config::getDBPass()));
            con->setSchema(config::getDBName());
            std::string sql = "SELECT * FROM " + config::getPointsTable();
            sql::ResultSet *rs = con->createStatement()->executeQuery(sql);
            logger::info("Start ping points...");
            while (rs->next()) {
                std::string addr = rs->getString("address");
                if (addr.empty()) continue;
                std::string cmd = "ping -c1 -s1 " + addr + "  > /dev/null 2>&1";
                int x = system(cmd.c_str());
                if (x == 0) {
                    logger::success(rs->getString("unlocalizedName") + " is online");
                    sql = "UPDATE " + config::getPointsTable() + " SET state=1, lastStateUpdate=" +
                          std::to_string(time(NULL)) + " WHERE id=" + rs->getString("id");
                } else {
                    logger::warn(rs->getString("unlocalizedName") + " maybe offline");
                    sql = "UPDATE " + config::getPointsTable() + " SET state=0, lastStateUpdate=" +
                          std::to_string(time(NULL)) + " WHERE id=" + rs->getString("id");
                }
                con->createStatement()->execute(sql);
            }
            logger::info("End ping points");
            con->close();
        }catch(...){
            logger::error("can't connect to MySQL server");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(60000));
    }
}
