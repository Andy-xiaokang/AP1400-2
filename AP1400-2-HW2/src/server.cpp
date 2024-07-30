#include "server.h"
#include <iostream>
#include <random>
#include <regex>
#include "crypto.h"

// global variables should be defined in the source file
std::vector<std::string> pending_trxs;

Server::Server() {
    clients = {};
}

std::string randomInt() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);
    return std::to_string(dis(gen));
}

std::shared_ptr<Client> Server::add_client(std::string id) {
    for (auto client : clients) {
        if (client.first->get_id() == id) {
            id += (randomInt() + randomInt() + randomInt() + randomInt());
        }
    }
    std::shared_ptr<Client> client_ptr = std::make_shared<Client>(id, *this);
    clients[client_ptr] = 5;
    return client_ptr;
}

std::shared_ptr<Client> Server::get_client(std::string id) const {
    for (auto [client_ptr, coins] : clients) {
        if (client_ptr->get_id() == id) return client_ptr;
    }
    return nullptr;
}

double Server::get_wallet(std::string id) const {
    for (auto [client_ptr, coins]: clients) {
        if (client_ptr->get_id() == id) return coins;
    }
    return 0.0;
}

bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value) {
    std::regex pattern(R"((\w+)-(\w+)-(\d+\.\d+))");
//    std::regex pattern("(\\w+)-(\\w+)-(\\d+\\.\\d+)");
    std::smatch match;
    if (!std::regex_search(trx, match, pattern)) throw std::runtime_error("transaction not in format");
    if (match[0] != trx) throw std::runtime_error("transaction not in format");
    sender = match[1];
    receiver = match[2];
    value = std::stod(match[3]);
    return true;
}

bool Server::add_pending_trx(std::string trx, std::string signature) const{
    std::string sender, receiver; double coins;
    parse_trx(trx, sender, receiver, coins);
    auto sender_ptr = get_client(sender);
    auto receiver_ptr = get_client(receiver);
    if (sender_ptr == nullptr || receiver_ptr == nullptr) {
        return false;
    }
    bool authentic = crypto::verifySignature(sender_ptr->get_publickey(), trx, signature);
    if (authentic && clients.at(sender_ptr) >= coins) {
        pending_trxs.push_back(trx);
        return true;
    }
    return false;
}

size_t Server::mine() {
    std::string mempool{};
    for (std::string trx : pending_trxs) {
        mempool += trx;
    }
    bool successful = false;
    size_t nounce = 0;
    while (!successful) {
        for (auto& [client_ptr, coins] : clients) {
            nounce = client_ptr->generate_nonce();
            std::string final_string = mempool + std::to_string(nounce);
            std::string hash{crypto::sha256(final_string)};
            if (hash.substr(0, 10).find("000") != std::string::npos) {
                clients[client_ptr] += 6.25;
                successful = true;
                break;
            }
        }
    }
    for (std::string trx : pending_trxs) {
        std::string sender, receiver; double coins;
        parse_trx(trx, sender, receiver, coins);
        clients.at(get_client(sender)) -= coins;
        clients.at(get_client(receiver)) += coins;
    }
    pending_trxs.clear();
    return nounce;
}

void show_wallets(const Server& server)
{
    std::cout << std::string(20, '*') << std::endl;
    for(const auto& client: server.clients)
        std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
    std::cout << std::string(20, '*') << std::endl;
}