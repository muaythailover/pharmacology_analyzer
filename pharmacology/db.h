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
        // Opioids
        addDrug("heroin", DrugClass::OPIOID,
            { SideEffect::RESPIRATORY_DEPRESSION, SideEffect::NODDING, SideEffect::DROWSINESS },
            0.5);
        addDrug("morphine", DrugClass::OPIOID,
            { SideEffect::RESPIRATORY_DEPRESSION, SideEffect::DROWSINESS },
            2.0);
        addDrug("fentanyl", DrugClass::OPIOID,
            { SideEffect::RESPIRATORY_DEPRESSION, SideEffect::DEATH_RISK },
            0.25);
        addDrug("oxycodone", DrugClass::OPIOID,
            { SideEffect::RESPIRATORY_DEPRESSION, SideEffect::DROWSINESS, SideEffect::NAUSEA },
            4.0);
        addDrug("hydrocodone", DrugClass::OPIOID,
            { SideEffect::RESPIRATORY_DEPRESSION, SideEffect::DROWSINESS },
            6.0);
        addDrug("codeine", DrugClass::OPIOID,
            { SideEffect::DROWSINESS, SideEffect::NAUSEA },
            3.0);
        addDrug("tramadol", DrugClass::OPIOID,
            { SideEffect::DROWSINESS, SideEffect::NAUSEA },
            6.0);
        addDrug("methadone", DrugClass::OPIOID,
            { SideEffect::RESPIRATORY_DEPRESSION, SideEffect::TORSADES_DE_POINTES },
            24.0);
        addDrug("buprenorphine", DrugClass::OPIOID,
            { SideEffect::RESPIRATORY_DEPRESSION, SideEffect::DROWSINESS },
            36.0);

        // Benzodiazepines
        addDrug("xanax", DrugClass::BENZODIAZEPINE,
            { SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION },
            12.0);
        addDrug("valium", DrugClass::BENZODIAZEPINE,
            { SideEffect::DROWSINESS },
            36.0);
        addDrug("ativan", DrugClass::BENZODIAZEPINE,
            { SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION },
            14.0);
        addDrug("klonopin", DrugClass::BENZODIAZEPINE,
            { SideEffect::DROWSINESS },
            30.0);
        addDrug("rohypnol", DrugClass::BENZODIAZEPINE,
            { SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION },
            18.0);
        addDrug("midazolam", DrugClass::BENZODIAZEPINE,
            { SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION },
            2.0);
        addDrug("temazepam", DrugClass::BENZODIAZEPINE,
            { SideEffect::DROWSINESS },
            8.0);

        // Stimulants
        addDrug("cocaine", DrugClass::STIMULANT,
            { SideEffect::CARDIAC_ARRHYTHMIA, SideEffect::HYPERTHERMIA },
            1.0);
        addDrug("methamphetamine", DrugClass::STIMULANT,
            { SideEffect::CARDIAC_ARRHYTHMIA, SideEffect::HYPERTHERMIA, SideEffect::TORSADES_DE_POINTES },
            12.0);
        addDrug("amphetamine", DrugClass::STIMULANT,
            { SideEffect::CARDIAC_ARRHYTHMIA, SideEffect::HYPERTHERMIA },
            8.0);
        addDrug("mdma", DrugClass::STIMULANT,
            { SideEffect::HYPERTHERMIA, SideEffect::CARDIAC_ARRHYTHMIA },
            6.0);
        addDrug("caffeine", DrugClass::STIMULANT,
            { SideEffect::CARDIAC_ARRHYTHMIA },
            4.0);
        addDrug("nicotine", DrugClass::STIMULANT,
            { SideEffect::CARDIAC_ARRHYTHMIA },
            2.0);
        addDrug("methylphenidate", DrugClass::STIMULANT,
            { SideEffect::CARDIAC_ARRHYTHMIA },
            4.0);
        addDrug("dextroamphetamine", DrugClass::STIMULANT,
            { SideEffect::CARDIAC_ARRHYTHMIA, SideEffect::HYPERTHERMIA },
            10.0);

        // Depressants
        addDrug("alcohol", DrugClass::ALCOHOL,
            { SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION },
            1.0);
        addDrug("barbiturates", DrugClass::DEPRESSANT,
            { SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION },
            8.0);
        addDrug("phenobarbital", DrugClass::DEPRESSANT,
            { SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION },
            72.0);
        addDrug("secobarbital", DrugClass::DEPRESSANT,
            { SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION },
            6.0);
        addDrug("ghb", DrugClass::DEPRESSANT,
            { SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION },
            4.0);
        addDrug("quaaludes", DrugClass::DEPRESSANT,
            { SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION },
            24.0);

        // Hallucinogens
        addDrug("lsd", DrugClass::HALLUCINOGEN,
            { SideEffect::HALLUCINATIONS, SideEffect::CARDIAC_ARRHYTHMIA },
            8.0);
        addDrug("psilocybin", DrugClass::HALLUCINOGEN,
            { SideEffect::HALLUCINATIONS, SideEffect::NAUSEA },
            4.0);
        addDrug("pcp", DrugClass::HALLUCINOGEN,
            { SideEffect::HALLUCINATIONS, SideEffect::HYPERTHERMIA, SideEffect::CARDIAC_ARRHYTHMIA },
            6.0);
        addDrug("dmt", DrugClass::HALLUCINOGEN,
            { SideEffect::HALLUCINATIONS, SideEffect::CARDIAC_ARRHYTHMIA },
            0.5);
        addDrug("mescaline", DrugClass::HALLUCINOGEN,
            { SideEffect::HALLUCINATIONS, SideEffect::NAUSEA },
            12.0);
        addDrug("ketamine", DrugClass::HALLUCINOGEN,
            { SideEffect::HALLUCINATIONS, SideEffect::RESPIRATORY_DEPRESSION },
            2.0);
        addDrug("dxm", DrugClass::HALLUCINOGEN,
            { SideEffect::HALLUCINATIONS, SideEffect::DROWSINESS },
            6.0);

        // Cannabis
        addDrug("thc", DrugClass::CANNABIS,
            { SideEffect::DROWSINESS, SideEffect::CARDIAC_ARRHYTHMIA },
            4.0);
        addDrug("cbd", DrugClass::CANNABIS,
            { SideEffect::DROWSINESS },
            6.0);
        addDrug("synthetic_cannabis", DrugClass::CANNABIS,
            { SideEffect::CARDIAC_ARRHYTHMIA, SideEffect::HYPERTHERMIA },
            2.0);

        // Inhalants
        addDrug("nitrous_oxide", DrugClass::INHALANT,
            { SideEffect::RESPIRATORY_DEPRESSION, SideEffect::DROWSINESS },
            0.25);
        addDrug("toluene", DrugClass::INHALANT,
            { SideEffect::CARDIAC_ARRHYTHMIA, SideEffect::RESPIRATORY_DEPRESSION },
            0.5);
        addDrug("butane", DrugClass::INHALANT,
            { SideEffect::CARDIAC_ARRHYTHMIA, SideEffect::DEATH_RISK },
            0.1);

        // Synthetic Drugs
        addDrug("spice", DrugClass::SYNTHETIC,
            { SideEffect::CARDIAC_ARRHYTHMIA, SideEffect::HYPERTHERMIA, SideEffect::HALLUCINATIONS },
            3.0);
        addDrug("bath_salts", DrugClass::SYNTHETIC,
            { SideEffect::HYPERTHERMIA, SideEffect::CARDIAC_ARRHYTHMIA, SideEffect::HALLUCINATIONS },
            4.0);
        addDrug("flakka", DrugClass::SYNTHETIC,
            { SideEffect::HYPERTHERMIA, SideEffect::CARDIAC_ARRHYTHMIA },
            3.0);
        addDrug("2cb", DrugClass::SYNTHETIC,
            { SideEffect::HALLUCINATIONS, SideEffect::NAUSEA },
            6.0);

        // Prescription Drugs (Misused)
        addDrug("adderall", DrugClass::STIMULANT,
            { SideEffect::CARDIAC_ARRHYTHMIA, SideEffect::HYPERTHERMIA },
            8.0);
        addDrug("ritalin", DrugClass::STIMULANT,
            { SideEffect::CARDIAC_ARRHYTHMIA },
            4.0);
        addDrug("ambien", DrugClass::DEPRESSANT,
            { SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION },
            2.5);
        addDrug("soma", DrugClass::DEPRESSANT,
            { SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION },
            8.0);
        addDrug("gabapentin", DrugClass::DEPRESSANT,
            { SideEffect::DROWSINESS },
            6.0);
        addDrug("pregabalin", DrugClass::DEPRESSANT,
            { SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION },
            6.0);

        // Set specific properties for respiratory depression
        drugs["heroin"]->setRespiratoryDepression(true);
        drugs["fentanyl"]->setRespiratoryDepression(true);
        drugs["morphine"]->setRespiratoryDepression(true);
        drugs["oxycodone"]->setRespiratoryDepression(true);
        drugs["hydrocodone"]->setRespiratoryDepression(true);
        drugs["methadone"]->setRespiratoryDepression(true);
        drugs["buprenorphine"]->setRespiratoryDepression(true);
        drugs["xanax"]->setRespiratoryDepression(true);
        drugs["ativan"]->setRespiratoryDepression(true);
        drugs["rohypnol"]->setRespiratoryDepression(true);
        drugs["midazolam"]->setRespiratoryDepression(true);
        drugs["alcohol"]->setRespiratoryDepression(true);
        drugs["barbiturates"]->setRespiratoryDepression(true);
        drugs["phenobarbital"]->setRespiratoryDepression(true);
        drugs["secobarbital"]->setRespiratoryDepression(true);
        drugs["ghb"]->setRespiratoryDepression(true);
        drugs["quaaludes"]->setRespiratoryDepression(true);
        drugs["ketamine"]->setRespiratoryDepression(true);
        drugs["nitrous_oxide"]->setRespiratoryDepression(true);
        drugs["toluene"]->setRespiratoryDepression(true);
        drugs["ambien"]->setRespiratoryDepression(true);
        drugs["soma"]->setRespiratoryDepression(true);
        drugs["pregabalin"]->setRespiratoryDepression(true);
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
