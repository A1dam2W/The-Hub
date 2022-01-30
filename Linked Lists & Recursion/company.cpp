#include "company.hpp"

#include <iostream>
#include <string>

using namespace std;

// Initializes the tracker with n students and their 1-person companies.
CompanyTracker::CompanyTracker(int n) {
    numCompanies = n;
    companies = new Company*[numCompanies];
    for (int i = 0; i < numCompanies; ++i)
        companies[i] = new Company();
}

// Deallocates all dynamically allocated memory.
CompanyTracker::~CompanyTracker() {
    for (int i = 0; i < numCompanies; i++) {
        while (companies[i]->parent != nullptr) {
            split(i);
        }
    }
    for (int j = 0; j < numCompanies; j++) {
        delete companies[j];
    }
    delete[] companies;
}

void CompanyTracker::merge(int i, int j) {
    if (withinrange(i) and withinrange(j)) {
        Company* largesti = getlargestcompany(i);
        Company* largestj = getlargestcompany(j);
        if (!inSameCompany(i, j)) {
            Company* newlargest = new Company(largesti, largestj);
            largesti->parent = newlargest;
            largestj->parent = newlargest;
        }
    }
}

void CompanyTracker::split(int i) {
    if (withinrange(i)) {
        Company* largesti = getlargestcompany(i);
        if (largesti->merge1 != nullptr and largesti->merge2 != nullptr) {
            largesti->merge1->parent = nullptr;
            largesti->merge2->parent = nullptr;
            largesti->merge1 = nullptr;
            largesti->merge2 = nullptr;
            delete largesti;
        }
    }
}

bool CompanyTracker::inSameCompany(int i, int j) {
    if (withinrange(i) and withinrange(j)) {
        Company* largesti = getlargestcompany(i);
        Company* largestj = getlargestcompany(j);
        if (largesti == largestj) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

Company* CompanyTracker::getlargestcompany(int i) {
    Company* largest = companies[i];
    while (largest->parent != nullptr) {
        largest = largest->parent;
    }
    return largest;
}

bool CompanyTracker::withinrange(int i) {
    if (i >= 0 and i < numCompanies) {
        return true;
    } else {
        return false;
    }
}
