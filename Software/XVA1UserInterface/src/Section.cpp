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
    this->subSectionTitles = subSectionTitles;
    this->parameters = parameters;
}

const string &Section::getName() const {
    return name;
}

const vector<string> &Section::getSubSectionTitles() const {
    return subSectionTitles;
}

const vector<SynthParameter> &Section::getParameters() const {
    return parameters;
}

int Section::getCurrentSubSection() const {
    return currentSubSection;
}

int Section::getNumberOfSubSections() {
    if (numberOfSubSections < 0) {
        numberOfSubSections = subSectionTitles.size();
    }

    return numberOfSubSections;
}

int Section::getCurrentPage() const {
    return currentPage;
}

int Section::getNumberOfPages()  {
    if (numberOfPages < 0) {
        numberOfPages = (parameters.size() + 8 - 1) / 8;
    }

    return numberOfPages;
}
