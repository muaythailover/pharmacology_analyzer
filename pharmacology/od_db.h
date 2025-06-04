#pragma once
#include "drug.h"
#include <unordered_map>
#include <algorithm>

enum class OverdoseRisk {
    EXTREMELY_HIGH = 90,  // 90-100% risk category
    VERY_HIGH = 75,       // 75-89% risk category  
    HIGH = 60,            // 60-74% risk category
    MODERATE = 40,        // 40-59% risk category
    LOW = 20,             // 20-39% risk category
    VERY_LOW = 10         // 10-19% risk category
};

class OverdosePotentialDatabase {
private:
    std::unordered_map<std::string, int> overdosePercentages;

public:
    OverdosePotentialDatabase() {
        initializeOverdoseRisks();
    }

    void initializeOverdoseRisks() {
        // EXTREMELY HIGH RISK (90-95%) - Synthetic opioids and dangerous combinations
        overdosePercentages["fentanyl"] = 95;
        overdosePercentages["carfentanil"] = 98;
        overdosePercentages["butane"] = 92;  // Sudden death syndrome

        // VERY HIGH RISK (75-89%) - Potent opioids and respiratory depressants
        overdosePercentages["heroin"] = 85;
        overdosePercentages["morphine"] = 78;
        overdosePercentages["oxycodone"] = 76;
        overdosePercentages["hydrocodone"] = 74;
        overdosePercentages["methadone"] = 82;  // Long half-life increases risk
        overdosePercentages["rohypnol"] = 79;   // Potent benzodiazepine
        overdosePercentages["ghb"] = 81;        // Narrow margin between high and fatal dose
        overdosePercentages["barbiturates"] = 83;
        overdosePercentages["phenobarbital"] = 80;
        overdosePercentages["secobarbital"] = 84;
        overdosePercentages["quaaludes"] = 77;

        // HIGH RISK (60-74%) - Other opioids and strong depressants
        overdosePercentages["buprenorphine"] = 65; // Partial agonist - lower risk
        overdosePercentages["codeine"] = 62;
        overdosePercentages["tramadol"] = 68;
        overdosePercentages["xanax"] = 72;
        overdosePercentages["ativan"] = 70;
        overdosePercentages["midazolam"] = 74;
        overdosePercentages["alcohol"] = 69;    // Varies greatly with tolerance
        overdosePercentages["ambien"] = 66;
        overdosePercentages["soma"] = 71;
        overdosePercentages["pregabalin"] = 63;
        overdosePercentages["toluene"] = 73;
        overdosePercentages["nitrous_oxide"] = 61; // Asphyxiation risk

        // MODERATE RISK (40-59%) - Benzodiazepines and some stimulants
        overdosePercentages["valium"] = 45;     // Longer half-life, more forgiving
        overdosePercentages["klonopin"] = 48;
        overdosePercentages["temazepam"] = 52;
        overdosePercentages["cocaine"] = 58;    // Cardiac events
        overdosePercentages["methamphetamine"] = 55;
        overdosePercentages["amphetamine"] = 51;
        overdosePercentages["mdma"] = 49;       // Hyperthermia risk
        overdosePercentages["pcp"] = 56;        // Unpredictable effects
        overdosePercentages["ketamine"] = 42;   // Relatively safe anesthetic profile
        overdosePercentages["gabapentin"] = 41;
        overdosePercentages["spice"] = 54;      // Synthetic cannabinoids
        overdosePercentages["bath_salts"] = 57;
        overdosePercentages["flakka"] = 53;

        // LOW RISK (20-39%) - Prescription stimulants and some hallucinogens
        overdosePercentages["adderall"] = 35;
        overdosePercentages["dextroamphetamine"] = 38;
        overdosePercentages["methylphenidate"] = 32;
        overdosePercentages["ritalin"] = 30;
        overdosePercentages["lsd"] = 25;        // Very low physical toxicity
        overdosePercentages["psilocybin"] = 22;
        overdosePercentages["mescaline"] = 28;
        overdosePercentages["dmt"] = 24;
        overdosePercentages["dxm"] = 36;
        overdosePercentages["2cb"] = 33;
        overdosePercentages["synthetic_cannabis"] = 39;

        // VERY LOW RISK (10-19%) - Cannabis and mild stimulants
        overdosePercentages["thc"] = 15;        // No known fatal overdose cases
        overdosePercentages["cbd"] = 12;        // Extremely safe profile
        overdosePercentages["caffeine"] = 18;   // Requires massive doses
        overdosePercentages["nicotine"] = 16;   // Difficult to achieve fatal dose through smoking
    }

    int getOverdosePercentage(const std::string& drugName) const {
        auto it = overdosePercentages.find(drugName);
        return (it != overdosePercentages.end()) ? it->second : 0;
    }

    OverdoseRisk getOverdoseRiskCategory(const std::string& drugName) const {
        int percentage = getOverdosePercentage(drugName);

        if (percentage >= 90) return OverdoseRisk::EXTREMELY_HIGH;
        if (percentage >= 75) return OverdoseRisk::VERY_HIGH;
        if (percentage >= 60) return OverdoseRisk::HIGH;
        if (percentage >= 40) return OverdoseRisk::MODERATE;
        if (percentage >= 20) return OverdoseRisk::LOW;
        return OverdoseRisk::VERY_LOW;
    }

    std::string getRiskDescription(const std::string& drugName) const {
        OverdoseRisk risk = getOverdoseRiskCategory(drugName);

        switch (risk) {
        case OverdoseRisk::EXTREMELY_HIGH:
            return "Extremely High Risk - Fatal overdose highly likely";
        case OverdoseRisk::VERY_HIGH:
            return "Very High Risk - Significant overdose potential";
        case OverdoseRisk::HIGH:
            return "High Risk - Notable overdose danger";
        case OverdoseRisk::MODERATE:
            return "Moderate Risk - Overdose possible with misuse";
        case OverdoseRisk::LOW:
            return "Low Risk - Overdose unlikely but possible";
        case OverdoseRisk::VERY_LOW:
            return "Very Low Risk - Overdose extremely rare";
        default:
            return "Unknown Risk";
        }
    }

    std::vector<std::string> getDrugsByRiskLevel(OverdoseRisk riskLevel) const {
        std::vector<std::string> drugs;
        for (const auto& pair : overdosePercentages) {
            if (getOverdoseRiskCategory(pair.first) == riskLevel) {
                drugs.push_back(pair.first);
            }
        }
        return drugs;
    }

    int calculateCombinationRisk(const std::vector<std::string>& drugs) const {
        if (drugs.empty()) return 0;

        double combinedRisk = 0.0;
        bool hasRespiratoryDepressant = false;
        bool hasStimulant = false;

        for (const std::string& drug : drugs) {
            int individualRisk = getOverdosePercentage(drug);
            combinedRisk += individualRisk * 0.01; // Convert to decimal

            // Check for dangerous combinations
            if (drug == "alcohol" || drug == "heroin" || drug == "fentanyl" ||
                drug == "xanax" || drug == "valium") {
                hasRespiratoryDepressant = true;
            }
            if (drug == "cocaine" || drug == "methamphetamine" || drug == "adderall") {
                hasStimulant = true;
            }
        }

        combinedRisk = 1.0 - std::pow(1.0 - combinedRisk, 1.3);

        if (hasRespiratoryDepressant && hasStimulant) {
            combinedRisk *= 1.4; // Speedball effect
        }

        int finalRisk = static_cast<int>(combinedRisk * 100);

        if (finalRisk < 0) {
            return 100;
        }

        return std::min(finalRisk, 99);
    }


    void addCustomDrug(const std::string& name, int overdosePercentage) {
        auto clamp = [](auto value, auto low, auto high) {
            return std::max(low, std::min(high, value));
            };
        overdosePercentages[name] = clamp(overdosePercentage, 0, 99);
    }
};
