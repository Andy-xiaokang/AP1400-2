#include "client.h"
#include "crypto.h"
#include <random>

Client::Client(std::string id, const Server& server) : id(id), server(&server) {
    crypto::generate_key(public_key, private_key);
}

std::string Client::get_id() const {
    return id;
}

std::string Client::get_publickey() const {
    return public_key;
}

double Client::get_wallet() {
    return server->get_wallet(id);
}

std::string Client::sign(std::string txt) const{
    return crypto::signMessage(private_key, txt);
}

bool Client::transfer_money(std::string receiver, double value) {
    std::string trx = (id + "-" + receiver + "-" + std::to_string(value));
    return server->add_pending_trx(trx, sign(trx));
}

// if the random size_t generated inappropriate the Server::mine() function
// may not work
size_t Client::generate_nonce() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(0, SIZE_MAX);
    return dis(gen);
}