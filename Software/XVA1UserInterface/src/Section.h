//
// Created by André Mathlener on 06/04/2021.
//

#ifndef XVA1USERINTERFACE_SECTION_H
#define XVA1USERINTERFACE_SECTION_H

#include <string>
#include "SynthParameter.h"
#include <vector>

using namespace std;

class Section {
private:
    string _name;
    vector<string> _virtualSubSectionTitles;
    vector<Section> _subSections;
    vector<SynthParameter> _parameters;

public:
    Section(string name);

    virtual ~Section();

    const string &getName() const;

    const vector<string> &getSubSectionTitles();

    const vector<Section> &getSubSections() const;

    const vector<SynthParameter> &getParameters() const;

    int getNumberOfSubSections();

    int getNumberOfPages();

    bool hasVirtualSubSections();

    Section &parameters(std::initializer_list<SynthParameter> parameters);
    Section &subSections(std::initializer_list<Section> sections);
    Section &virtualSubSectionTitles(std::initializer_list<std::string> titles);

};


#endif //XVA1USERINTERFACE_SECTION_H
