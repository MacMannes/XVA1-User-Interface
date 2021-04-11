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
    vector<string> virtualSubSectionTitles = {};
    vector<SynthParameter> parameters;

    int currentSubSection = 0;

public:
    Section(string name, vector<SynthParameter> parameters);
    Section(string name, vector<string> titles, vector<SynthParameter> parameters);

    const string &getName() const;

    const vector<string> &getSubSectionTitles() const;

    const vector<SynthParameter> &getParameters() const;

    int getNumberOfSubSections();

    int getNumberOfPages();


};


#endif //XVA1USERINTERFACE_SECTION_H
