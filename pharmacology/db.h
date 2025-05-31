#pragma once
#include "drug.h"

class DrugDatabase {
private:
    std::map<std::string, std::unique_ptr<Drug>> drugs;
    
public:
    DrugDatabase() {
        initializeDrugs();
    }
    
    void initializeDrugs() {
        // Opioids[1]
        addDrug("heroin", DrugClass::OPIOID, 
                {SideEffect::RESPIRATORY_DEPRESSION, SideEffect::NODDING, SideEffect::DROWSINESS}, 
                0.5);
        addDrug("morphine", DrugClass::OPIOID, 
                {SideEffect::RESPIRATORY_DEPRESSION, SideEffect::DROWSINESS}, 
                2.0);
        addDrug("fentanyl", DrugClass::OPIOID, 
                {SideEffect::RESPIRATORY_DEPRESSION, SideEffect::DEATH_RISK}, 
                0.25);
        
        // Benzodiazepines[1]
        addDrug("xanax", DrugClass::BENZODIAZEPINE, 
                {SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION}, 
                12.0);
        addDrug("valium", DrugClass::BENZODIAZEPINE, 
                {SideEffect::DROWSINESS}, 
                36.0);
        
        // Stimulants[1]
        addDrug("cocaine", DrugClass::STIMULANT, 
                {SideEffect::CARDIAC_ARRHYTHMIA, SideEffect::HYPERTHERMIA}, 
                1.0);
        addDrug("methamphetamine", DrugClass::STIMULANT, 
                {SideEffect::CARDIAC_ARRHYTHMIA, SideEffect::HYPERTHERMIA, SideEffect::TORSADES_DE_POINTES}, 
                12.0);
        
        // Depressants[1]
        addDrug("alcohol", DrugClass::ALCOHOL, 
                {SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION}, 
                1.0);
        addDrug("barbiturates", DrugClass::DEPRESSANT, 
                {SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION}, 
                8.0);
        
        // Set specific properties
        drugs["heroin"]->setRespiratoryDepression(true);
        drugs["fentanyl"]->setRespiratoryDepression(true);
        drugs["morphine"]->setRespiratoryDepression(true);
    }
    
    void addDrug(const std::string& name, DrugClass drugClass, 
                 const std::vector<SideEffect>& effects, double halfLife) {
        drugs[name] = std::make_unique<Drug>(name, drugClass, effects, halfLife);
    }
    
    Drug* getDrug(const std::string& name) {
        auto it = drugs.find(name);
        return (it != drugs.end()) ? it->second.get() : nullptr;
    }
    
    std::vector<std::string> getAllDrugNames() const {
        std::vector<std::string> names;
        for (const auto& pair : drugs) {
            names.push_back(pair.first);
        }
        return names;
    }
};
