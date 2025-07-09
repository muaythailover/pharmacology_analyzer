#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "core.cpp"
#include "db.h"
#include "drug.h"
#include "interaction_engine.h"

#include <ranges>

#include "od_db.h"

class PharmacologyProgram {
private:
    DrugDatabase database;
    InteractionAnalyzer analyzer;
    OverdosePotentialDatabase overdoseDB;  

    std::string severityToString(InteractionSeverity severity) {
        switch (severity) {
        case InteractionSeverity::MINOR: return "MINOR";
        case InteractionSeverity::MODERATE: return "MODERATE";
        case InteractionSeverity::MAJOR: return "MAJOR";
        case InteractionSeverity::LETHAL: return "LETHAL";
        default: return "UNKNOWN";
        }
    }

    std::string effectToString(SideEffect effect) {
        switch (effect) {
        case SideEffect::DROWSINESS: return "Drowsiness";
        case SideEffect::RESPIRATORY_DEPRESSION: return "Respiratory Depression";
        case SideEffect::CARDIAC_ARRHYTHMIA: return "Cardiac Arrhythmia";
        case SideEffect::TORSADES_DE_POINTES: return "Torsades de Pointes";
        case SideEffect::NODDING: return "Nodding";
        case SideEffect::HYPERTHERMIA: return "Hyperthermia";
        case SideEffect::DEATH_RISK: return "Risk of Death";
        case SideEffect::NAUSEA: return "Nausea";
        case SideEffect::HALLUCINATIONS: return "Hallucinations";
        case SideEffect::MANIA: return "Mania or hypomania";
        default: return "Unknown Effect";
        }
    }

    void displayMenu() {
        std::cout << "\n=== PHARMACOLOGY ANALYSIS SYSTEM ===\n";
        std::cout << "Please select an option:\n";
        std::cout << "1. Drug Interaction Analyzer\n";
        std::cout << "2. Overdose Possibility Assessment\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice (1-3): ";
    }

    void displayAvailableDrugs() {
        std::cout << "\nAvailable drugs:\n";
        auto drugNames = database.getAllDrugNames();
        int count = 0;
        for (const auto& name : drugNames) {
            std::cout << name;
            if (++count % 5 == 0) {
                std::cout << "\n";
            }
            else {
                std::cout << ", ";
            }
        }
        if (count % 5 != 0) std::cout << "\n";
    }

public:
    void runInteractionCheck() {
        std::cout << "\n=== DRUG INTERACTION ANALYZER ===\n";

        std::vector<std::string> selectedDrugs;
        std::string input;

        displayAvailableDrugs();

        std::cout << "\nEnter drug names (separated by spaces): ";
        std::getline(std::cin, input);

        // Parse input
        std::istringstream iss(input);
        std::string drugName;
        std::vector<Drug> drugs;

        while (iss >> drugName) {
            Drug* drug = database.getDrug(drugName);
            if (drug) {
                drugs.push_back(*drug);
                selectedDrugs.push_back(drugName);
            }
            else {
                std::cout << "Warning: Drug '" << drugName << "' not found.\n";
            }
        }

        if (drugs.size() < 2) {
            std::cout << "Please enter at least 2 valid drugs for interaction analysis.\n";
            return;
        }

        analyzeAndDisplayResults(drugs, selectedDrugs);
    }

    void runOverdoseAssessment() {
        std::cout << "\n=== OVERDOSE POSSIBILITY ASSESSMENT ===\n";

        std::vector<std::string> selectedDrugs;
        std::string input;

        displayAvailableDrugs();

        std::cout << "\nEnter drug names for overdose assessment (separated by spaces): ";
        std::getline(std::cin, input);

        // Parse input
        std::istringstream iss(input);
        std::string drugName;

        while (iss >> drugName) {
            Drug* drug = database.getDrug(drugName);
            if (drug) {
                selectedDrugs.push_back(drugName);
            }
            else {
                std::cout << "Warning: Drug '" << drugName << "' not found.\n";
            }
        }

        if (selectedDrugs.empty()) {
            std::cout << "Please enter at least 1 valid drug for overdose assessment.\n";
            return;
        }

        analyzeOverdoseRisk(selectedDrugs);
    }

    void run() {
        int choice;
        std::string input;

        while (true) {
            displayMenu();
            std::getline(std::cin, input);

            try {
                choice = std::stoi(input);
            }
            catch (const std::exception&) {
                choice = 0; 
            }

            switch (choice) {
            case 1:
                runInteractionCheck();
                break;
            case 2:
                runOverdoseAssessment();
                break;
            case 3:
                std::cout << "Thank you for using the Pharmacology Analysis System!\n";
                return;
            default:
                std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
                break;
            }

            std::cout << "\nPress Enter to continue...";
            std::getline(std::cin, input);
        }
    }

private:
    void analyzeAndDisplayResults(const std::vector<Drug>& drugs,
        const std::vector<std::string>& drugNames) {
        std::cout << "\n=== INTERACTION ANALYSIS RESULTS ===\n";
        std::cout << "Analyzing combination of: ";
        for (size_t i = 0; i < drugNames.size(); ++i) {
            std::cout << drugNames[i];
            if (i < drugNames.size() - 1) std::cout << " + ";
        }
        std::cout << "\n\n";

        auto effects = analyzer.analyzeMultipleInteractions(drugs);

        if (effects.empty()) {
            std::cout << "No specific dangerous interactions found in database.\n";
            return;
        }

        // Sort by severity
        std::ranges::sort(effects,
                          [](const InteractionEffect& a, const InteractionEffect& b) {
                              return a.severity > b.severity;
                          });

        bool hasLethalRisk = false;
        bool hasMajorRisk = false;

        for (const auto& effect : effects) {
            if (effect.severity == InteractionSeverity::LETHAL) hasLethalRisk = true;
            if (effect.severity == InteractionSeverity::MAJOR) hasMajorRisk = true;

            std::cout << "   Severity: " << severityToString(effect.severity) << "\n";
            std::cout << "   Probability: " << (effect.probability * 100) << "%\n";
            std::cout << "   Description: " << effect.description << "\n\n";
        }

        // Risk assessment summary
        std::cout << "=== RISK ASSESSMENT ===\n";
        if (hasLethalRisk) {
            std::cout << "   EXTREME DANGER: This combination has LETHAL potential.\n";
            std::cout << "   Immediate medical supervision required.\n";
        }
        else if (hasMajorRisk) {
            std::cout << "   HIGH RISK: This combination poses significant health risks.\n";
            std::cout << "   Medical consultation strongly recommended.\n";
        }
        else {
            std::cout << "   MODERATE RISK: Monitor for side effects.\n";
        }
    }

    void analyzeOverdoseRisk(const std::vector<std::string>& drugNames) {
        std::cout << "\n=== OVERDOSE RISK ANALYSIS ===\n";

        if (drugNames.size() == 1) {
            // Single drug analysis
            const std::string& drugName = drugNames[0];
            int overdosePercentage = overdoseDB.getOverdosePercentage(drugName);
            std::string riskDescription = overdoseDB.getRiskDescription(drugName);

            std::cout << "Drug: " << drugName << "\n";
            std::cout << "Overdose Risk Percentage: " << overdosePercentage << "%\n";
            std::cout << "Risk Level: " << riskDescription << "\n\n";

            // Additional safety information
            displaySafetyRecommendations(drugName, overdosePercentage);

        }
        else {
            // Multiple drug combination analysis
            std::cout << "Analyzing combination of: ";
            for (size_t i = 0; i < drugNames.size(); ++i) {
                std::cout << drugNames[i];
                if (i < drugNames.size() - 1) std::cout << " + ";
            }
            std::cout << "\n\n";

            // Individual drug risks
            std::cout << "Individual Drug Risks:\n";
            for (const std::string& drugName : drugNames) {
                int percentage = overdoseDB.getOverdosePercentage(drugName);
                std::cout << "  " << drugName << ": " << percentage << "% risk\n";
            }

            // Combined risk calculation
            int combinedRisk = overdoseDB.calculateCombinationRisk(drugNames);
            std::cout << "\nCombined Overdose Risk: " << combinedRisk << "%\n";

            // Risk category for combination
            std::string combinedDescription = getCombinedRiskDescription(combinedRisk);
            std::cout << "Combined Risk Level: " << combinedDescription << "\n\n";

            displayCombinationWarnings(drugNames, combinedRisk);
        }
    }

    void displaySafetyRecommendations(const std::string& drugName, int riskPercentage) {
        std::cout << "=== SAFETY RECOMMENDATIONS ===\n";

        if (riskPercentage >= 90) {
            std::cout << "   CRITICAL WARNING: Extremely high overdose risk!\n";
            std::cout << "   - Never use without medical supervision\n";
            std::cout << "   - Have naloxone (Narcan) immediately available\n";
            std::cout << "   - Consider addiction treatment resources\n";
        }
        else if (riskPercentage >= 75) {
            std::cout << "   HIGH RISK WARNING:\n";
            std::cout << "   - Use extreme caution with dosing\n";
            std::cout << "   - Never use alone - have someone present\n";
            std::cout << "   - Keep emergency contacts readily available\n";
        }
        else if (riskPercentage >= 60) {
            std::cout << "   MODERATE-HIGH RISK:\n";
            std::cout << "   - Start with lower doses\n";
            std::cout << "   - Avoid mixing with other substances\n";
            std::cout << "   - Monitor for adverse effects\n";
        }
        else if (riskPercentage >= 40) {
            std::cout << "   MODERATE RISK:\n";
            std::cout << "   - Follow prescribed dosages carefully\n";
            std::cout << "   - Be aware of tolerance changes\n";
        }
        else {
            std::cout << "   LOWER RISK:\n";
            std::cout << "   - Still exercise caution with dosing\n";
            std::cout << "   - Monitor for unexpected reactions\n";
        }
    }

    void displayCombinationWarnings(const std::vector<std::string>& drugNames, int combinedRisk) {
        std::cout << "=== COMBINATION WARNINGS ===\n";

        // Check for specific dangerous combinations
        bool hasOpioid = false;
        bool hasBenzo = false;
        bool hasAlcohol = false;
        bool hasStimulant = false;

        for (const std::string& drug : drugNames) {
            Drug* drugPtr = database.getDrug(drug);
            if (drugPtr) {
                if (drugPtr->getDrugClass() == DrugClass::OPIOID) hasOpioid = true;
                if (drugPtr->getDrugClass() == DrugClass::BENZODIAZEPINE) hasBenzo = true;
                if (drugPtr->getDrugClass() == DrugClass::ALCOHOL) hasAlcohol = true;
                if (drugPtr->getDrugClass() == DrugClass::STIMULANT) hasStimulant = true;
            }
        }

        if ((hasOpioid && hasBenzo) || (hasOpioid && hasAlcohol) || (hasBenzo && hasAlcohol)) {
            std::cout << "   LETHAL COMBINATION DETECTED!\n";
            std::cout << "   - Respiratory depression risk extremely high\n";
            std::cout << "   - This combination is responsible for majority of overdose deaths\n";
            std::cout << "   - Seek immediate medical help if experiencing breathing difficulties\n";
        }

        if (hasStimulant && (hasOpioid || hasBenzo || hasAlcohol)) {
            std::cout << "   DANGEROUS SPEEDBALL COMBINATION!\n";
            std::cout << "   - Masking effects can lead to unexpected overdose\n";
            std::cout << "   - Cardiac stress significantly increased\n";
        }

        if (combinedRisk >= 80) {
            std::cout << "   EMERGENCY PREPAREDNESS ESSENTIAL:\n";
            std::cout << "   - Have naloxone (Narcan) immediately available\n";
            std::cout << "   - Ensure someone trained in overdose response is present\n";
            std::cout << "   - Know emergency contact numbers\n";
        }
    }

    std::string getCombinedRiskDescription(int combinedRisk) {
        if (combinedRisk >= 90) return "Extremely High Risk - Life Threatening";
        if (combinedRisk >= 75) return "Very High Risk - Dangerous Combination";
        if (combinedRisk >= 60) return "High Risk - Significant Danger";
        if (combinedRisk >= 40) return "Moderate Risk - Exercise Caution";
        if (combinedRisk >= 20) return "Low-Moderate Risk - Monitor Closely";
        return "Lower Risk - Still Requires Caution";
    }
};

int main() {
    PharmacologyProgram program;
    program.run();
    std::cin.get();
    return 0;
}
