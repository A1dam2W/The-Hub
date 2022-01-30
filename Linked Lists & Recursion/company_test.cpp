#include "company.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
    CompanyTracker test1{10};  // normal merge
    test1.merge(1, 2);
    bool answer1 = test1.inSameCompany(1, 2);
    cout << answer1 << " ";

    CompanyTracker test2{10};  // merge the largest company 2 is in, make sure getlargestcompany works properly
    test2.merge(1, 2);
    test2.merge(2, 3);
    bool answer2 = test2.inSameCompany(3, 2);
    cout << answer2 << " ";

    CompanyTracker test3{10};  // try if getlargest work properly
    test3.merge(1, 2);
    test3.merge(3, 4);
    test3.merge(1, 3);
    bool answer3 = test3.inSameCompany(1, 3);
    cout << answer3 << " ";

    CompanyTracker test4{10};  // merge doesn't do anything
    test4.merge(1, 1);
    bool answer4 = test4.inSameCompany(1, 1);
    cout << answer4 << " ";

    CompanyTracker test5{10};  // merge doesn't do anything & merge doesn't SegFaultfor numbers smaller than range
    test5.merge(-1, 1);
    bool answer5 = test5.inSameCompany(-1, 1);
    cout << answer5 << " ";

    CompanyTracker test6{10};  // merge also checks j is within range
    test6.merge(1, -1);
    bool answer6 = test6.inSameCompany(1, -1);
    cout << answer6 << " ";

    CompanyTracker test7{10};  // merge doesn't do anything & merge doesn't SegFault for numbers bigger than range
    test7.merge(15, 1);
    bool answer7 = test7.inSameCompany(15, 1);
    cout << answer7 << " ";

    CompanyTracker test8{10};  // merge doesn't do anything & merge doesn't SegFault for numbers bigger than range
    test8.merge(1, 15);
    bool answer8 = test8.inSameCompany(1, 15);
    cout << answer8 << " ";

    CompanyTracker test9{100000};  // test for big numbers
    test9.merge(346, 2355);
    bool answer9 = test9.inSameCompany(346, 2355);
    cout << answer9 << " ";

    CompanyTracker test10{100000};  // show that merge works properly,specifically it doesn't put every company under
                                    // the same big company
    test10.merge(346, 2355);
    test10.merge(234, 12343);
    test10.merge(37, 15);
    bool answer10 = test10.inSameCompany(346, 15);
    cout << answer10 << " ";

    CompanyTracker test11{10};  // repeatedly calling split wouldn't generate error
    test11.merge(1, 3);
    test11.split(1);
    test11.split(1);
    bool answer11 = test11.inSameCompany(1, 3);
    cout << answer11 << " ";

    CompanyTracker test12{10};  // split out of range, won't crash
    test12.split(10000);
    bool answer12 = test12.inSameCompany(0, 1);
    cout << answer12 << " ";

    CompanyTracker test13{10};  // normal split
    test13.merge(1, 2);
    test13.split(1);
    bool answer13 = test13.inSameCompany(2, 1);
    cout << answer13 << " ";

    CompanyTracker test14{10};  // split doesn't attack indiscriminately
    test14.merge(1, 2);
    test14.split(10);
    bool answer14 = test14.inSameCompany(2, 1);
    cout << answer14 << " ";

    CompanyTracker test15{10};  // correct sub-companies are generated, namely 1 and 4 isn't in the same company
    test15.merge(1, 2);
    test15.merge(2, 3);
    test15.merge(3, 4);
    test15.split(1);
    bool answer15 = test15.inSameCompany(4, 1);
    cout << answer15 << " ";

    CompanyTracker test16{10};  // negative number split wouldn't generate error
    test16.split(-1);
    bool answer16 = test16.inSameCompany(1, 2);
    cout << answer16 << " ";

    CompanyTracker test17{10};  // initially the companies are separatedly created
    bool answer17 = test17.inSameCompany(1, 2);
    cout << answer17 << " ";

    CompanyTracker test18{10};  // inSameCompany returns true for same inputs
    bool answer18 = test18.inSameCompany(1, 1);
    cout << answer18 << " ";

    CompanyTracker test19{10};  // inSameCompany doesn't crash when index out of range
    bool answer19 = test19.inSameCompany(1, -1);
    cout << answer19 << " ";

    CompanyTracker test20{10};  // check in c++ language, array[10] is the 11st number, output 0, thus prove the
                                // correctness of the for loop
    test20.merge(0, 10);
    bool answer20 = test20.inSameCompany(0, 10);
    cout << answer20 << " ";

    CompanyTracker test21{10};  // repeated merge provide correct results
    test21.merge(0, 9);
    test21.merge(0, 9);
    bool answer21 = test21.inSameCompany(0, 9);
    cout << answer21 << " ";

    CompanyTracker test22{10};  // different split if given more subcompanies
    test22.merge(0, 1);
    test22.merge(1, 2);
    test22.merge(2, 3);
    test22.split(1);
    test22.split(1);
    bool answer22 = test22.inSameCompany(1, 2);  // first split 3, then 2, output 0
    cout << answer22 << endl;

    return 0;
}
