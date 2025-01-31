#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm> 
#include <cctype>
#include <locale>
#include "Bignum.hpp"

// g++ -O3 -std=c++2a -Wall -o bignum main.cpp Bignum.cpp && ./bignum e < one.txt
// g++ -O3 -std=c++2a -Wall -o bignum main.cpp Bignum.cpp && ./bignum d < encrypt_output.txt

/* for profiling
g++ -pg -O3 -std=c++2a -Wall -o bignum main.cpp Bignum.cpp && ./bignum e < one.txt
g++ -pg -O3 -std=c++2a -Wall -o bignum main.cpp Bignum.cpp && ./bignum d < encrypt_output.txt
Analyze the profile data
gprof bignum gmon.out > [].txt 
*/


const std::string rsa_n = 
"9616540267013058477253762977293425063379243458473593816900454019721117570003248808113992652836857529658675570356835067184715201230519907361653795328462699";
const std::string rsa_e = "65537";
const std::string rsa_d =
"4802033916387221748426181350914821072434641827090144975386182740274856853318276518446521844642275539818092186650425384826827514552122318308590929813048801";

const Bignum n = Bignum(rsa_n);
const Bignum e = Bignum(rsa_e);
const Bignum d = Bignum(rsa_d);

bool iterateNum(std::string num) {
    for (size_t i = 0; i<num.length(); i++) {
        if (isdigit(num[i])) {
            continue;
        } else {
            std::cout << "Error: " << "\"" << num << "\"" << " is not an unsigned integer" << std::endl;
            return false;
        }
    }
    return true;

}

std::string convert(std::string s) {
    int d;
    std::string res;
    for (size_t i = 0; i < s.length(); i++) {
        d = static_cast<int>(s[i]);
        std::ostringstream oss;
        oss << std::setw(3) << std::setfill('0') << d;
        res += oss.str();
    }

    return res;

}

void encrypt() {
    std::vector<Bignum> res;
    std::string line;
    int line_count = 1;
    while (std::getline(std::cin, line)) {
        std::string l;
        std::string ls = std::to_string(line_count);
        if (line_count<10) {
            l = "032032" + convert(ls);
        } else if (line_count<100) {
            l = "032" + convert(ls);
        } else {
            l = convert(ls);
        }

        line_count +=1;
        std::string coded1;
        std::string coded2;
        for (size_t c = 0; c<96; c++) {
            int d;
            std::string d0;
            if (c < line.length()){
                d = static_cast<int>(line[c]);
                std::ostringstream oss;
                oss << std::setw(3) << std::setfill('0') << d;

                d0 = oss.str();
            } else {
                d0 = "032"; //space as a decimal
            }

            if (c < 48) { // 96/2
                coded1 += d0;
            } else {
                coded2 += d0;
            }
            
        }
        std::string first = l + coded1;
        std::string sec = coded2 + l;
        Bignum b1 = Bignum(first);
        Bignum b2 = Bignum(sec);
        b1.trim();
        b2.trim();
        Bignum b1_encoded = Bignum::modular(b1, e, n);
        Bignum b2_encoded = Bignum::modular(b2, e, n);
        std::cout << b1_encoded.to_string() << std::endl;
        std::cout << b2_encoded.to_string() << std::endl; //supposed to print on two separate lines?
        
    }
    
}

inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void decrypt() {
    std::string line;
    std::string prev;
    
    int count = 0; //there will always be an even number bc of how encrpyt works
    while (std::getline(std::cin, line)) {
        if (count % 2 == 0) {
            prev = line;
        } else {
            Bignum b = Bignum(prev);
            Bignum b2 = Bignum(line);

            Bignum decoded1 = Bignum::modular(b, d, n);
            Bignum decoded2 = Bignum::modular(b2, d, n);

            std::string d1_str = decoded1.to_string();
            std::string d2_str = decoded2.to_string();
            if (d1_str.length() < 153) {
                d1_str = "0" + d1_str;
            }
            if (d2_str.length() < 153) {
                d2_str = "0" + d2_str;
            }
            
            std::string s0 = d1_str + d2_str;
            std::string result;
            for (size_t i = 0; i < s0.length(); i+=3) {
                int num = std::stoi(s0.substr(i, 3));
                char ch = static_cast<char>(num);
                result += ch;
            }
            std::string final = result.substr(3, 96); //take off the line numbers
            rtrim(final);
            std::cout << final << std::endl;
        }
        count++;
    }

}

int main(int argc, char *argv[]) {
    std::string op = argv[1];

    if (op == "e") {
        encrypt(); //call encrypt helper function on the file to encrypt, double check input format
        return 0;
    } else if (op == "d") {
        decrypt();
        return 0;
    }
    
    if (argc < 4) {
        //program name counts as arg
        std::cout << "Usage:% ./bignum op number1 number2." << std::endl;
        return 1;
        // what if user forgets to put operater should it throw this since argc is 3?
    } 

    std::string num1 = argv[2];
    std::string num2 = argv[3];
    Bignum ans;
    bool a = iterateNum(num1); //TODO may have to alter control flow for error messages for part2
    bool b = iterateNum(num2);
    if (!(a && b)) {
        return 1;
    }



    if (op == "+") {
        if (argc != 4) { // 5 for ^ operator which requires an addl arg
            std::cout << "Error: +-*/% requires two numbers" << std::endl;
            return 1;
        }
        for (int i = 0; i < argc; i++) {
            if (i == 0) {
                std::cout << "bignum ";
            }
            else if (i == argc-1) {
                std::cout << argv[i] << std::endl;
            } else {
                std::cout << argv[i] << " ";
            }
        }
        ans = Bignum(num1) + Bignum(num2);
        std::cout << ans.to_string() << std::endl;

    } else if (op == "-") {
        if (argc != 4) { // 5 for ^ operator which requires an addl arg
            std::cout << "Error: +-*/% requires two numbers" << std::endl;
            return 1;
        }
        for (int i = 0; i < argc; i++) {
            if (i == 0) {
                std::cout << "bignum ";
            }
            else if (i == argc-1) {
                std::cout << argv[i] << std::endl;
            } else {
                std::cout << argv[i] << " ";
            }
        }
        ans = Bignum(num1) - Bignum(num2);
        std::cout << ans.to_string() << std::endl;

    } else if (op == "*") {
        if (argc != 4) { // 5 for ^ operator which requires an addl arg
            std::cout << "Error: +-*/% requires two numbers" << std::endl;
            return 1;
        }
        for (int i = 0; i < argc; i++) {
            if (i == 0) {
                std::cout << "bignum ";
            }
            else if (i == argc-1) {
                std::cout << argv[i] << std::endl;
            } else {
                std::cout << argv[i] << " ";
            }
        }        
        ans = Bignum(num1) * Bignum(num2);
        std::cout << ans.to_string() << std::endl;
        
    } else if (op == "/") {
        if (argc != 4) { // 5 for ^ operator which requires an addl arg
            std::cout << "Error: +-*/% requires two numbers" << std::endl;
            return 1;
        }
        for (int i = 0; i < argc; i++) {
            if (i == 0) {
                std::cout << "bignum ";
            }
            else if (i == argc-1) {
                std::cout << argv[i] << std::endl;
            } else {
                std::cout << argv[i] << " ";
            }
        }        
        ans = Bignum(num1) / Bignum(num2);
        std::cout << ans.to_string() << std::endl;
        
    } else if (op == "%") {
        if (argc != 4) { // 5 for ^ operator which requires an addl arg
            std::cout << "Error: +-*/% requires two numbers" << std::endl;
            return 1;
        }
        for (int i = 0; i < argc; i++) {
            if (i == 0) {
                std::cout << "bignum ";
            }
            else if (i == argc-1) {
                std::cout << argv[i] << std::endl;
            } else {
                std::cout << argv[i] << " ";
            }
        }
        ans = Bignum(num1) % Bignum(num2);
        std::cout << ans.to_string() << std::endl;

    } else if (op == "^") {
        if (argc != 5) { // 5 for ^ operator which requires an addl arg
            std::cout << "Error: Exponent requires three numbers" << std::endl;
            return 1;
        }
        for (int i = 0; i < argc; i++) {
            if (i == 0) {
                std::cout << "bignum ";
            }
            else if (i == argc-1) {
                std::cout << argv[i] << std::endl;
            } else {
                std::cout << argv[i] << " ";
            }
        }
        std::string num3 = argv[4];
        ans = Bignum::modular(Bignum(num1), Bignum(num2), Bignum(num3));
        std::cout << ans.to_string() << std::endl;
    }
    else {
        std::cout << "Error: " << "\"" << op << "\"" << " is not a supported operator" << std::endl;
        return 1;
    }



}