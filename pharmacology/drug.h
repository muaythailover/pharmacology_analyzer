#pragma once
#include <string>

class Drug {
private:
    std::string name;
    DrugClass drugClass;
    std::vector<SideEffect> primaryEffects;
    std::map<std::string, double> receptorAffinities;
    double halfLife;
    bool causesRespiratoryDepression;
    bool affectsCNS;

public:
    Drug(const std::string& drugName, DrugClass type,
        const std::vector<SideEffect>& effects, double t_half)
        : name(drugName), drugClass(type), primaryEffects(effects),
        halfLife(t_half), causesRespiratoryDepression(false), affectsCNS(true) {
    }

    // Getters
    const std::string& getName() const { return name; }
    DrugClass getDrugClass() const { return drugClass; }
    const std::vector<SideEffect>& getPrimaryEffects() const { return primaryEffects; }
    double getHalfLife() const { return halfLife; }
    bool causesRespDepression() const { return causesRespiratoryDepression; }

    // Setters for specific properties
    void setRespiratoryDepression(bool value) { causesRespiratoryDepression = value; }
    void addReceptorAffinity(const std::string& receptor, double affinity) {
        receptorAffinities[receptor] = affinity;
    }

    bool hasEffect(SideEffect effect) const {
        return std::find(primaryEffects.begin(), primaryEffects.end(), effect)
            != primaryEffects.end();
    }
};
