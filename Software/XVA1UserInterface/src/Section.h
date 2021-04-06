//
// Created by André Mathlener on 06/04/2021.
//

#ifndef XVA1USERINTERFACE_SECTION_H
#define XVA1USERINTERFACE_SECTION_H

#include <string>
#include "SynthParameter.h"

using namespace std;

class Section {
private:
    string name;
    vector<string> subSectionTitles = {};
    vector<SynthParameter> parameters;

    int currentSubSection = 1;
    int numberOfSubSections = -1;

    int currentPage = 1;
    int numberOfPages = -1;

public:
    Section(string name, vector<SynthParameter> parameters);
    Section(string name, vector<string> titles, vector<SynthParameter> parameters);

    const string &getName() const;

    const vector<string> &getSubSectionTitles() const;

    const vector<SynthParameter> &getParameters() const;

    int getCurrentSubSection() const;

    int getNumberOfSubSections();

    int getCurrentPage() const;

    int getNumberOfPages();


};


#endif //XVA1USERINTERFACE_SECTION_H
