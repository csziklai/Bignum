#pragma once

#include <string>
#include <vector>


class Bignum
{
public:
    Bignum(); //initialize to hold 0
    Bignum(std::string num);

    std::vector<int> value;

    bool check();
    void trim();
    static Bignum mult_helper(const Bignum& b, int n);
    Bignum div_helper(const Bignum& other, const bool div) const;
    static int pow(int x, unsigned int p);
    Bignum operator+(const Bignum& other) const;
    Bignum operator-(const Bignum& other);
    Bignum operator*(const Bignum& other) const;
    Bignum operator/(const Bignum& other) const;
    Bignum operator%(const Bignum& other) const;
    static Bignum modular(const Bignum& a, const Bignum& b, const Bignum& c);
    Bignum binaryAdd(Bignum& other);

    bool operator==(const Bignum& other) const;
    //bool operator!=(const Bignum& other) const;
    bool operator<(const Bignum& other) const;
    bool operator>(const Bignum& other) const;
    bool operator<=(const Bignum& other) const;
    //bool operator>=(const Bignum& other) const;

    std::string to_string() const;



    
private:

};