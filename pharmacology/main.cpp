#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "core.cpp"
#include "db.h"
#include "drug.h"
#include "interaction_engine.h"

class PharmacologyProgram {
private:
    DrugDatabase database;
    InteractionAnalyzer analyzer;

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

public:
    void runInteractionCheck() {
        std::cout << "=== Pharmacology Drug Interaction Checker ===\n\n";

        std::vector<std::string> selectedDrugs;
        std::string input;

        std::cout << "Available drugs:\n";
        auto drugNames = database.getAllDrugNames();
        for (const auto& name : drugNames) {
            std::cout << "- " << name << "\n";
        }

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
};

int main() {
    PharmacologyProgram program;
    program.runInteractionCheck();
    return 0;
}
