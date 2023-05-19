
#ifndef Vault_cpp
#define Vault_cpp

#include "Vault.hpp"

Vault::Vault() {
    this->balance = 0;
}

Vault::Vault(int startBal) {
    this->balance = startBal;
}

Vault::~Vault() {}

bool Vault::operator==(const Vault& r) {
    return this->balance == r.balance;
}

bool Vault::operator!=(const Vault& r) {
    return this->balance != r.balance;
}

bool Vault::operator<(const Vault& r) {
    return this->balance < r.balance;
}

bool Vault::operator>(const Vault& r) {
    return this->balance > r.balance;
}

bool Vault::operator<=(const Vault& r) {
    return this->balance <= r.balance;
}

bool Vault::operator>=(const Vault& r) {
    return this->balance >= r.balance;
};
#endif
