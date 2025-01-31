#include "Bignum.hpp"

#include <vector>
#include <iostream>

Bignum::Bignum() : value(std::vector<int>{0}) {}

Bignum::Bignum(std::string num)
{
    for (size_t i = 0; i < num.size(); ++i)
    {
        value.insert(value.begin(), num[i] - '0'); // convert char to int
    }
}

Bignum Bignum::operator+(const Bignum &other) const
{
    Bignum result;
    size_t this_size = value.size();
    size_t other_size = other.value.size();
    size_t max_size = std::max(this_size, other_size);
    int carry = 0;

    result.value.reserve(max_size + 1);

    for (size_t i = 0; i < max_size; i++)
    {
        int digit1 = (i < this_size) ? value[i] : 0;
        int digit2 = (i < other_size) ? other.value[i] : 0;
        int sum = digit1 + digit2 + carry;
        // std::cout << "sum of " << digit1 << "+" << digit2 << "+" << carry << "=" << sum << std::endl;

        result.value.push_back(sum % 10);
        // std::cout << result << std::endl;
        carry = sum / 10;
    }
    if (carry == 1)
    {
        // result.value[max_size-1] += 1;
        result.value.push_back(1);
        // std::cout << "last carry" << std::endl;
    }
    // truncate 0 at end
    result.value.erase(result.value.begin());
    result.value.shrink_to_fit();

    return result;
}

Bignum Bignum::binaryAdd(Bignum &other) 
{
    Bignum result;
    size_t this_size = value.size();
    size_t other_size = other.value.size();
    size_t max_size = std::max(this_size, other_size);
    int carry = 0;
    // std::cout << "max size: " << max_size << std::endl;
    //  can insert zeros into a copy? is this inefficient tho?
    result.value.reserve(max_size + 1);

    for (size_t i = 0; i < max_size; i++)
    {
        int digit1 = (i < this_size) ? value[i] : 0;
        int digit2 = (i < other_size) ? other.value[i] : 0;
        int sum = digit1 + digit2 + carry;
        // std::cout << "sum of " << digit1 << "+" << digit2 << "+" << carry << "=" << sum << std::endl;

        result.value.push_back(sum % 2);
        // std::cout << result << std::endl;
        carry = sum / 2;
    }
    if (carry == 1)
    {
        // result.value[max_size-1] += 1;
        result.value.push_back(1);
        // std::cout << "last carry" << std::endl;
    }
    // truncate 0 at end
    result.value.erase(result.value.begin());
    result.value.shrink_to_fit();

    return result;
}

Bignum Bignum::operator-(const Bignum &other)
{ 
    Bignum thisCopy = *this;
    thisCopy.trim();
    if (thisCopy < other)
    {   
        //std::cout << thisCopy.to_string() << " is less than " << other_fordebugging.to_string() << std::endl;
        std::cout << "Unsupported: Negative number" << std::endl;
        return Bignum();
    }
    else if (*this == other)
    {
        return Bignum();
    }

    Bignum result;
    size_t this_size = thisCopy.value.size();
    size_t other_size = other.value.size();
    size_t max_size = std::max(this_size, other_size);
    for (size_t i = 0; i < max_size; i++)
    {
        int digit1 = thisCopy.value[i];
        int digit2 = (i < other_size) ? other.value[i] : 0;
        int dif = digit1 - digit2;
        if (dif < 0)
        {
            int j = 1;
            dif = (digit1 + 10) - digit2;
            while (thisCopy.value[i + j] == 0)
            {
                thisCopy.value[i + j] = 9;
                j++;
            }
            thisCopy.value[i + j] = thisCopy.value[i + j] - 1;
        }
        result.value.push_back(dif);
    }
    // truncate 0 at end
    result.value.erase(result.value.begin());
    result.value.shrink_to_fit();
    result.trim();
    return result;
}


int Bignum::pow(int x, unsigned int p)
{
  if (p == 0) return 1;
  if (p == 1) return x;
  
  int tmp = pow(x, p/2);
  if (p%2 == 0) return tmp * tmp;
  else return x * tmp * tmp;
}

Bignum Bignum::div_helper(const Bignum& other, const bool div) const {
    if (other==Bignum()) {
        std::cout << "Error: Divide by zero" << std::endl;
        return Bignum(); 
    }
    // dividing a number by a bigger number should result in 0
    if (*this < other) {
        return Bignum();
    }
    Bignum remainder = *this;
    Bignum quotient = Bignum("0");
    Bignum ten = Bignum("10");

    std::vector<Bignum> multiples;
    multiples.push_back(other);
    std::vector<Bignum> tens; 
    //other idea for optimization is instead of multiplying by 10, do exponential 2, 4, 8, 16, 32...
    Bignum temp = other;
    Bignum multiple = Bignum("1");
    tens.push_back(multiple);
    while ((temp * ten) <= remainder) {
        temp = temp * ten;
        multiple = multiple * ten;
        multiples.push_back(temp);
        tens.push_back(multiple);
    }
    
    while (other <= remainder) {
        for (size_t i = 0; i < multiples.size(); i++) {
          if (!(multiples[i] <= remainder)) {
            temp = multiples[i-1];
            multiple = tens[i-1];
            break;
          } if (i == multiples.size()-1) {
            temp = multiples[i];
            multiple = tens[i];
          }
        }

        // subtract and increment quotient
        remainder = remainder - temp;
        quotient = quotient + multiple;
    }
    if (div) {
        quotient.trim();
        return quotient;
    } else {
        remainder.trim();
        return remainder;
    }

}

Bignum Bignum::operator/(const Bignum& other) const {
    return div_helper(other, true);

}


Bignum Bignum::operator%(const Bignum& other) const {
    if (*this < other) {
        return *this;
    }
    return div_helper(other, false);

}


void Bignum::trim()
{
    if (value.size() == 1)
    {
        return; // don't want to trim singular 0
    }
    while (value.size() > 1 && value.back() == 0)
    {
        value.pop_back();
    }

    value.shrink_to_fit();
}



// should only be called when n < 10
Bignum Bignum::mult_helper(const Bignum& b, int n)
{ 
    Bignum res;
    int carry = 0;
    for (size_t i = 0; i < b.value.size(); i++)
    {
        int val = b.value[i] * n + carry;
        res.value.push_back(val % 10);

        carry = val / 10;
    }

    if (carry > 0)
    {
        res.value.push_back(carry);
    }
    // truncate 0 at end
    res.value.erase(res.value.begin());
    res.value.shrink_to_fit();

    return res;
}


Bignum Bignum::operator*(const Bignum &other) const
{   
    if (*this == Bignum() || other == Bignum()) {
        return Bignum();
    }
    Bignum result;
    size_t this_size = value.size();
    size_t other_size = other.value.size();
    size_t min_size;
    bool larger; // whether this bignum is larger than other (in terms of size, not value)
    if (this_size < other_size)
    {
        min_size = this_size;
        larger = false;
    }
    else
    {
        min_size = other_size;
        larger = true;
    }
    std::vector<Bignum> rows; // rows to be added together
    for (size_t i = 0; i < min_size; i++)
    {
        Bignum row;
        if (larger)
        {
            row = mult_helper(*this, other.value[i]);
        }
        else
        {
            row = mult_helper(other, value[i]);
        }
        for (size_t j = 0; j < i; j++)
        {
            row.value.insert(row.value.begin(), 0);
        }
        rows.push_back(row);
    } 
    // add together all the rows
    if (rows.size() == 1) {
        return rows[0];
    }
    Bignum acc = rows[0];
    for (size_t k = 1; k < rows.size(); k++) {
        acc = acc + rows[k];
    }
    //std::cout << "final ans: " << acc.to_string() << std::endl;
    acc.trim();
    //std::cout << "mult answer: " << acc.to_string() << std::endl;
    return acc;

}

Bignum Bignum::modular(const Bignum& a, const Bignum& b, const Bignum& c) {

    if (c == Bignum("1")) {
        return Bignum();
    }
    Bignum result("1"); 
    Bignum x = a % c;
    Bignum e = b;  //copy exponent for iteration

    while (!(e <= Bignum("0"))) {
        if (e % Bignum("2") == Bignum("1")) {
            result = (result * x) % c;
        }
        e = e / Bignum("2");
        x = (x * x) % c; 
    }

    return result;
}


bool Bignum::operator<(const Bignum &other) const
{
    if (value.size() < other.value.size())
    {
        return true;
    }
    else if (value.size() > other.value.size())
    {
        return false;
    }
    else
    {
        for (size_t i = value.size(); i-- > 0;) {
            if (value[i] < other.value[i]) {
                return true;
            } else if (value[i] > other.value[i])
            {
                return false;
            }

        }
        return false;
        
    }
}

bool Bignum::operator<=(const Bignum &other) const {
    if (*this < other) {
        return true;
    } else if (*this == other) {
        return true;
    } else {
        return false;
    }
}

bool Bignum::operator==(const Bignum &other) const
{
    if (value.size() != other.value.size())
    {
        return false;
    }
    else
    {
        for (size_t i = 0; i < value.size(); i++)
        {
            if (value[i] != other.value[i])
            {
                return false;
            }
        }
    }
    return true;
}

std::string Bignum::to_string() const
{
    std::string res = "";
    for (size_t i = value.size(); i-- > 0;)
    {
        res += std::to_string(value[i]);
    }
    // std::cout << res << std::endl;
    return res;
}
