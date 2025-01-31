#include "Bignum.hpp"
#include <iostream>
#include <cassert>
#include <memory>

//g++ -std=c++2a -Wall -o test test.cpp Bignum.cpp && ./test

Bignum n0 = Bignum("398");
Bignum n1 = Bignum("347");
Bignum n2 = Bignum("888");
Bignum n3 = Bignum("1289");
Bignum n4 = Bignum("12489083249032845823424");
Bignum n5 = Bignum("458349500");
Bignum n7 = Bignum("1002");
Bignum n8 = Bignum("7555");
Bignum n9 = Bignum("45");

void testToString() {
    Bignum n1 = Bignum("347");
    Bignum n2 = Bignum("888");
    Bignum n3 = Bignum("1289");
    Bignum n4 = Bignum("12489083249032845823424");

    assert(n1.to_string() == "347");
    assert(n2.to_string() == "888");
    assert(n3.to_string() == "1289");
    assert(n4.to_string() == "12489083249032845823424");

}

void testAdd() {


    Bignum n6 = Bignum("916699000");

    //carry over
    Bignum res = n1 + n1;
    //std::cout << "test case 1: " << res.to_string() << std::endl;
    assert(res.to_string() == "694");


    // carry over in biggest digit
    //assert(n1+n2 == Bignum("1235"));
    //std::cout << "test case 2: " << (n1+n2).to_string() << std::endl;
    assert((n1+n2).to_string() == "1235");

    // numbers of different length
    //std::cout << "test case 3: " << (n1+n3).to_string() << std::endl;
    assert((n1+n3).to_string() == "1636");

    //number ending in zeros
    Bignum res3 = n2 + n5;
    assert(res3.to_string() == "458350388");

    // result ending in zeros
    Bignum res4 = n8 + n9;
    assert(res4.to_string() == "7600");

    // large number
    Bignum res5 = n5 + n5;
    //std::cout << "large number test case: " << res5.to_string() << std::endl;
    assert(res5.to_string() == n6.to_string());

}

void testSub() {
    // basic case of same number of digits
    Bignum res1 = n2 - n1;
    std::cout << res1.to_string() << std::endl;
    assert(res1.to_string() == "541");
    
    // A-B but B>A
    Bignum res3 = n2-n3;
    assert(res3.to_string() == "0");

    // case of diff number of digits
    Bignum res2 = n3-n2;
    std::cout << res2.to_string() << std::endl;
    assert(res2.to_string() == "401");

    // multiple borrows (zeros in a row)
    Bignum res4 = n7-n0;
    assert(res4.to_string() == "604");

    //subtract number from itself
    Bignum res5 = n5-n5;
    std::cout << res5.to_string() << std::endl;
    assert(res5.to_string() == "0");

    //big number


}

void testlt() {
    // nums of same length, is lt
    assert(n1<n2);

    // nums of diff length, is lt
    assert(n2<n3);

    // nums of diff length, is not lt
    assert(!(n8<n9));

    //nums are equal
    assert(!(n4<n4));
}

void testMultHelper() {
    Bignum a = Bignum("123");
    Bignum b = Bignum("859");
    Bignum c = Bignum("604");
    Bignum n3_ = Bignum("1289"); //mutability problem if using n3 after it must
    // have been mutated in previous method. should be ok in actual application

    // ordinary case
    Bignum res1 = Bignum::mult_helper(a, 8);
    // mult by 1
    Bignum res2 = Bignum::mult_helper(b, 1);
    // size of result grows
    Bignum res3 = Bignum::mult_helper(c, 9);
    //
    Bignum res4 = Bignum::mult_helper(n3_, 8);
    std::cout << "n3_: " << n3_.to_string() << std::endl;

    assert(res1.to_string() == "984");
    assert(res2.to_string() == "859");
    assert(res3.to_string() == "5436");
    assert(res4.to_string() == "10312");
}

void testMult() {
    Bignum a = Bignum("123");
    Bignum b = Bignum("19");
    Bignum c = Bignum("604");

    Bignum n2 = Bignum("888");
    Bignum n3 = Bignum("1289");
    Bignum n8 = Bignum("7555");
    Bignum n9 = Bignum("45");

    // ordinary case
    Bignum res1 = a*b;

    //
    Bignum res2 = n2*n3;
    Bignum res3 = n8*n9;

    assert(res1.to_string() == "2337");
    assert(res2.to_string() == "1144632");
    assert(res3.to_string() == "339975");

}

// void testDivHelper() {
//     Bignum eight = Bignum("8");
//     Bignum forty8 = Bignum("48");
//     Bignum twelve = Bignum("12");

//     std::cout << "in div helper test" << std::endl;
    

//     Bignum res1 = Bignum::div_helper(twelve, eight);
//     Bignum res2 = Bignum::div_helper(forty8, eight);
//     //Bignum res3 = Bignum::div_helper(twelve, eight);

//     std::cout << res1.to_string() << " should be 1" << std::endl;
//     std::cout << res2.to_string() << " should be 6" << std::endl;


// }

void testDiv() {
    Bignum one289 = Bignum("1289");
    Bignum eight = Bignum("8");
    Bignum one44 = Bignum("144");
    Bignum twelve = Bignum("12");
    Bignum five500 = Bignum("5500");
    Bignum hundred = Bignum("100");
    Bignum n = Bignum("157987");
    Bignum h = Bignum("2469");

    Bignum bad = Bignum("25553025");
    Bignum c = Bignum("10201");

    Bignum subtract = Bignum("50525");
    assert(Bignum() == subtract-subtract);
    assert(Bignum() == subtract * Bignum()); //anything times 0 is 0
    //Bignum dividend2("1000000000000000123");
    //Bignum divisor2("999999000000099999");
    std::cout << "in div test before";

    Bignum res1 = one289 / eight;
    std::cout << "in div test";
    Bignum res2 = one44 / twelve;
    Bignum res3 = five500 / hundred;
    Bignum res4 = n / h;
    Bignum res5 = bad / c;

    Bignum dividend1("1234567890123456789012345678901234567890");
    Bignum divisor1("987654321");
    Bignum expected1 = Bignum("1249999988734374999015820312399");
    Bignum res6 = dividend1 / divisor1;

    

    std::cout << res1.to_string() << ", expected: " << "161" << std::endl;
    std::cout << res2.to_string() << ", expected: " << "12" << std::endl;
    std::cout << res3.to_string() << ", expected: " << "55" << std::endl;
    std::cout << res4.to_string() << ", expected: " << "63" << std::endl;
    std::cout << res5.to_string() << ", expected: " << "2504" << std::endl;
    assert(res6.to_string() == "1249999988734374999015820312399");
    std::cout << res6.to_string() << ", expected: " << "1249999988734374999015820312399" << std::endl;

}

void testMod() {
    Bignum one289 = Bignum("1289");
    Bignum eight = Bignum("8");
    Bignum one44 = Bignum("144");
    Bignum twelve = Bignum("12");
    Bignum twenty9 = Bignum("29");
    Bignum thirteen = Bignum("13");
    Bignum big = Bignum("21867849431");

    Bignum res1 = one289 % eight;
    Bignum res2 = one44 % twelve;
    Bignum res3 = twenty9 % thirteen;
    Bignum res4 = big % twenty9;

    // when a < b for a % b
    Bignum res5 = eight % twelve;

    std::cout << res1.to_string() << ", expected: " << "1" << std::endl;
    std::cout << res2.to_string() << ", expected: " << "0" << std::endl;
    std::cout << res3.to_string() << ", expected: " << "3" << std::endl;
    std::cout << res4.to_string() << ", expected: " << "14" << std::endl;
    std::cout << res5.to_string() << ", expected: " << "8" << std::endl;

}

void testModular() {
    Bignum one289 = Bignum("1289");
    Bignum eight = Bignum("8");
    Bignum one44 = Bignum("144");
    Bignum twelve = Bignum("12");
    Bignum twenty3 = Bignum("23");
    Bignum thirteen = Bignum("13");
    Bignum sixteen = Bignum("16");
    Bignum two = Bignum("2");

    Bignum a = Bignum("2345");
    Bignum b = Bignum("6789");
    Bignum c = Bignum("10201");

    Bignum res0 = Bignum::modular(two, thirteen, twenty3);
    Bignum res1 = Bignum::modular(eight, twenty3, twelve);
    Bignum res2 = Bignum::modular(one289, thirteen, thirteen);
    Bignum res3 = Bignum::modular(one44, twelve, sixteen);
    Bignum res4 = Bignum::modular(a, b, c);

    std::cout << res0.to_string() << ", expected: " << "4" << std::endl;
    std::cout << res1.to_string() << ", expected: " << "8" << std::endl;
    std::cout << res2.to_string() << ", expected: " << "2" << std::endl;
    std::cout << res3.to_string() << ", expected: " << "0" << std::endl;
    std::cout << res4.to_string() << ", expected: " << "4829" << std::endl;

}

void testBinaryAdd() {

    Bignum thirteen = Bignum("1101");
    Bignum ten = Bignum("1010");
    Bignum three = Bignum("11");
    //Bignum on = Bignum("1010");

    Bignum res1 = thirteen.binaryAdd(ten);
    Bignum res2 = three.binaryAdd(ten);

    std::cout << res1.to_string() << ", expected: " << "10111" << std::endl;
    std::cout << res2.to_string() << ", expected: " << "1101" << std::endl;

}

void testTrim() {
    std::cout << "trim test" << std::endl;
    Bignum zeros = Bignum("00000");
    zeros.trim();
    std::cout << zeros.to_string() << std::endl;

}

void findBug() {
    Bignum a = Bignum("2345");
    Bignum b = Bignum("6789");
    Bignum c = Bignum("10201");

    Bignum five055 = Bignum("5055");
    Bignum x_ = five055 * five055;
    Bignum x = x_ % c;
    std::cout << "5055*5055 is " << x_.to_string() << " should be 25553025" <<std::endl;
    std::cout << "x is " << x.to_string() << " should be 9721" <<std::endl;

    //Bignum res4 = Bignum::modular(a, b, c);
}

void test_modulus(const Bignum& dividend, const Bignum& divisor, const Bignum& expected) {
    Bignum result = dividend % divisor;
    if (result == expected) {
        std::cout << "Test passed!" << std::endl;
    } else {
        std::cout << "Test failed. Expected " << expected.to_string() 
                  << ", got " << result.to_string() << std::endl;
    }
}

void run_test_cases() {
    // Test 1: Large Dividend and Small Divisor
    Bignum dividend1("1234567890123456789012345678901234567890");
    Bignum divisor1("987654321");
    Bignum expected1 = Bignum("792341811");
    test_modulus(dividend1, divisor1, expected1);

    // Test 2: Large Dividend and Divisor, Close in Size
    Bignum dividend2("10000000000000000000000000000000000000123");
    Bignum divisor2("9999999999999999999999999999999999999999");
    Bignum expected2 = Bignum("124");
    test_modulus(dividend2, divisor2, expected2);

    // Test 3: Large Prime Numbers
    Bignum dividend3("982451653");  // 50 millionth prime number
    Bignum divisor3("961748927");  // Another large prime number
    Bignum expected3 = Bignum("20702726");
    test_modulus(dividend3, divisor3, expected3);

    // // Test 4: Powers of 10
    // Bignum dividend4("1000000000000000000000");  // 10^21
    // Bignum divisor4("9999");
    // Bignum expected4 = dividend4 % divisor4;
    // test_modulus(dividend4, divisor4, expected4);

    // // Test 5: Power Residue
    // Bignum dividend5("expected result of 2^1024 - 1");
    // Bignum divisor5("expected result of 2^512 - 1");
    // Bignum expected5 = dividend5 % divisor5;
    // test_modulus(dividend5, divisor5, expected5);

    // // Test 6: Random Large Numbers
    // Bignum dividend6("92340293840238402384023840238402384023");
    // Bignum divisor6("2384023840238402384");
    // Bignum expected6 = dividend6 % divisor6;
    // test_modulus(dividend6, divisor6, expected6);

    // Test 7: Edge Case: Dividend Equals Divisor
    Bignum dividend7("999999999999999999999999999999999999");
    Bignum divisor7("999999999999999999999999999999999999");
    test_modulus(dividend7, divisor7, Bignum());

    // Test 8: Edge Case: Divisor Larger Than Dividend
    Bignum dividend8("54321");
    Bignum divisor8("123456789012345678901234567890");
    Bignum expected8("54321");
    test_modulus(dividend8, divisor8, expected8);

    // // Test 9: One Large, One Small Number
    // Bignum dividend9("987654321987654321987654321987654321987654321");
    // Bignum divisor9("2");
    // Bignum expected9("expected result for dividend9 % divisor9");
    // test_modulus(dividend9, divisor9, expected9);

    // // Test 10: Boundary Case: Large Even and Odd Numbers
    // Bignum dividend10("1000000000000000000000000000000000000000000000000001");  // 10^50 + 1
    // Bignum divisor10("1000000000000000000000000000000000000000000000000001");  // 10^25 + 1
    // Bignum expected10("expected result for dividend10 % divisor10");
    // test_modulus(dividend10, divisor10, expected10);
}

int main() {
    // testToString();
    // testAdd();
    // testSub();
    // testlt();
    // testMultHelper();
    // testMult();
    //testDivHelper();
    testDiv();
    testMod();
    //testTrim();
    //testBinaryAdd();
    testModular();
    //findBug();
    //run_test_cases();


}
