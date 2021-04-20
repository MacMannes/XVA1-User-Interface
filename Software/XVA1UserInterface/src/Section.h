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
    explicit Section(string name);

    virtual ~Section();

    const string &getName() const;

    const vector<string> &getSubSectionTitles();

    const vector<Section> &getSubSections() const;

    const vector<SynthParameter> &getParameters() const;

    int getNumberOfSubSections();

    int getNumberOfPages();

    bool hasVirtualSubSections();

    Section &virtualSubSectionTitles(std::initializer_list<const std::string> titles);

    Section &addSubSection(const Section &section);

    Section &addParameter(const SynthParameter &parameter);

};


#endif //XVA1USERINTERFACE_SECTION_H
