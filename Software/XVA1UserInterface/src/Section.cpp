//
// Created by André Mathlener on 06/04/2021.
//

#include "Section.h"

Section::Section(string name) : _name(name) {}

const string &Section::getName() const {
    return _name;
}

const vector<string> &Section::getSubSectionTitles() {
    if (_virtualSubSectionTitles.size() == 0 && _subSections.size() > 0) {
        for (auto &section : _subSections) {
            _virtualSubSectionTitles.push_back(section.getName());
        }
    }

    return _virtualSubSectionTitles;
}

const vector<SynthParameter> &Section::getParameters() const {
    return _parameters;
}

int Section::getNumberOfSubSections() {
    if (_subSections.size() > 0) {
        return _subSections.size();
    } else if (_virtualSubSectionTitles.size() > 0) {
        return _virtualSubSectionTitles.size();
    }

    return 0;
}

int Section::getNumberOfPages() {
    return (_parameters.size() + 8 - 1) / 8;;
}

const vector<Section> &Section::getSubSections() const {
    return _subSections;
}

bool Section::hasVirtualSubSections() {
    return _virtualSubSectionTitles.size() > 0 && _subSections.size() == 0;
}

Section::~Section() {
    _virtualSubSectionTitles.clear();
    _parameters.clear();
    _subSections.clear();
}

Section &Section::virtualSubSectionTitles(const std::initializer_list<const std::string> titles) {
    for (const auto &title : titles) {
        _virtualSubSectionTitles.push_back(title);
    }
    return *this;
}

Section &Section::addSubSection(const Section &section) {
    _subSections.push_back(section);
    return *this;
}

Section &Section::addParameter(const SynthParameter &parameter) {
    _parameters.push_back(parameter);
    return *this;
}
