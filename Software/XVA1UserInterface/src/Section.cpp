//
// Created by André Mathlener on 06/04/2021.
//

#include "Section.h"

Section::Section(string name, vector<SynthParameter> parameters) {
    this->name = name;
    this->parameters = parameters;
}

Section::Section(string name, vector<string> subSectionTitles, vector<SynthParameter> parameters) {
    this->name = name;
    this->virtualSubSectionTitles = subSectionTitles;
    this->parameters = parameters;
}

const string &Section::getName() const {
    return name;
}

const vector<string> &Section::getSubSectionTitles() const {
    return virtualSubSectionTitles;
}

const vector<SynthParameter> &Section::getParameters() const {
    return parameters;
}

int Section::getNumberOfSubSections() {
    if (virtualSubSectionTitles.size() > 0) {
        return virtualSubSectionTitles.size();
    }
}

int Section::getNumberOfPages()  {
    return (parameters.size() + 8 - 1) / 8;;
}
