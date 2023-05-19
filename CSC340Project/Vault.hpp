

#ifndef Vault_hpp
#define Vault_hpp

class Vault {
public:
    Vault();
    Vault(int startBal);
    ~Vault();
    
    bool operator==(const Vault& r);
    bool operator!=(const Vault& r);
    bool operator<(const Vault& r);
    bool operator>(const Vault& r);
    bool operator<=(const Vault& r);
    bool operator>=(const Vault& r);
    
private:
    int balance;
    friend std::ostream& operator<<(std::ostream& os, const Vault& v) {
        os << "Vault with balance: " << v.balance;
        return os;
    }
};
#include "Vault.cpp"
#endif /* Vault_hpp */
