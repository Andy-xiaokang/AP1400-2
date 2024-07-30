#ifndef SERVER_H
#define SERVER_H

#include <map>
#include "client.h"
extern std::vector<std::string> pending_trxs;
// 循环依赖问题: 在某些情况下，两个或多个头文件相互包含时，会导致循环依赖。
// 在这种情况下，前向声明可以打破循环依赖，因为前向声明只需要知道类名，而不需要完整的类定义。
class Client;

class Server
{

public:
    Server();
    std::shared_ptr<Client> add_client(std::string id);
    std::shared_ptr<Client> get_client(std::string id) const;
    double get_wallet(std::string id) const;
    static bool parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value) ;
    bool add_pending_trx(std::string trx, std::string signature) const;
    size_t mine();
    friend void show_wallets(const Server& server);

private:
    std::map<std::shared_ptr<Client>, double> clients;
};


#endif //SERVER_H