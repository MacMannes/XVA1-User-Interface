//
// Created by André Mathlener on 06/04/2021.
//

#include "Section.h"

Section::Section(const string &name) : name(name) {}

Section::Section(string name, vector<SynthParameter> parameters) {
    this->name = name;
    this->parameters = parameters;
}

Section::Section(string name, vector<Section> subSections) {
    this->name = name;
    this->subSections = subSections;
    this->parameters = {};
}

Section::Section(string name, vector<string> subSectionTitles, vector<SynthParameter> parameters) {
    this->name = name;
    this->virtualSubSectionTitles = subSectionTitles;
    this->parameters = parameters;
}

const string &Section::getName() const {
    return name;
}

const vector<string> &Section::getSubSectionTitles() {
    if (virtualSubSectionTitles.size() == 0 && subSections.size() > 0) {
        for (auto &section : subSections) {
            virtualSubSectionTitles.push_back(section.getName());
        }
    }

    return virtualSubSectionTitles;
}

const vector<SynthParameter> &Section::getParameters() const {
    return parameters;
}

int Section::getNumberOfSubSections() {
    if (subSections.size() > 0) {
        return subSections.size();
    } else if (virtualSubSectionTitles.size() > 0) {
        return virtualSubSectionTitles.size();
    }

    return 0;
}

int Section::getNumberOfPages() {
    return (parameters.size() + 8 - 1) / 8;;
}

const vector<Section> &Section::getSubSections() const {
    return subSections;
}

bool Section::hasVirtualSubSections() {
    return virtualSubSectionTitles.size() > 0 && subSections.size() == 0;
}
