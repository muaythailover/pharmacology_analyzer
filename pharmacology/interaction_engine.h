#include <vector>
#include <map>
#include <set>

class InteractionAnalyzer {
private:
    std::map<std::pair<DrugClass, DrugClass>, std::vector<InteractionEffect>> interactionMatrix;
    std::map<std::string, std::vector<InteractionEffect>> specificDrugInteractions;

    void initializeInteractionMatrix() {
        // Depressant + Depressant combinations (high risk)
        addInteraction(DrugClass::DEPRESSANT, DrugClass::DEPRESSANT, {
            {SideEffect::RESPIRATORY_DEPRESSION, InteractionSeverity::MAJOR, 0.85,
             "Synergistic CNS depression leading to respiratory failure"},
            {SideEffect::DROWSINESS, InteractionSeverity::MAJOR, 0.95,
             "Extreme sedation and loss of consciousness"},
            {SideEffect::DEATH_RISK, InteractionSeverity::LETHAL, 0.35,
             "High risk of fatal overdose"}
            });

        // Opioid + Benzodiazepine (extremely dangerous)
        addInteraction(DrugClass::OPIOID, DrugClass::BENZODIAZEPINE, {
            {SideEffect::RESPIRATORY_DEPRESSION, InteractionSeverity::LETHAL, 0.90,
             "Severe respiratory depression - frequent cause of overdose deaths"},
            {SideEffect::NODDING, InteractionSeverity::MAJOR, 0.80,
             "Characteristic opioid nodding intensified"},
            {SideEffect::DEATH_RISK, InteractionSeverity::LETHAL, 0.45,
             "Extremely high fatality risk"}
            });

        // Opioid + Opioid (additive effects)
        addInteraction(DrugClass::OPIOID, DrugClass::OPIOID, {
            {SideEffect::RESPIRATORY_DEPRESSION, InteractionSeverity::MAJOR, 0.80,
             "Additive respiratory depression"},
            {SideEffect::NODDING, InteractionSeverity::MAJOR, 0.85,
             "Intensified sedation and nodding"},
            {SideEffect::DEATH_RISK, InteractionSeverity::MAJOR, 0.30,
             "Increased overdose risk"}
            });

        // Alcohol + Opioids
        addInteraction(DrugClass::ALCOHOL, DrugClass::OPIOID, {
            {SideEffect::RESPIRATORY_DEPRESSION, InteractionSeverity::LETHAL, 0.88,
             "Alcohol potentiates opioid respiratory depression"},
            {SideEffect::DROWSINESS, InteractionSeverity::MAJOR, 0.92,
             "Severe sedation and impaired consciousness"},
            {SideEffect::DEATH_RISK, InteractionSeverity::LETHAL, 0.40,
             "High risk of fatal respiratory failure"}
            });

        // Alcohol + Benzodiazepines
        addInteraction(DrugClass::ALCOHOL, DrugClass::BENZODIAZEPINE, {
            {SideEffect::RESPIRATORY_DEPRESSION, InteractionSeverity::MAJOR, 0.75,
             "Combined CNS depression"},
            {SideEffect::DROWSINESS, InteractionSeverity::MAJOR, 0.90,
             "Severe sedation"},
            {SideEffect::DEATH_RISK, InteractionSeverity::MAJOR, 0.25,
             "Risk of respiratory failure"}
            });

        // Stimulant + Depressant (masking effects)
        addInteraction(DrugClass::STIMULANT, DrugClass::DEPRESSANT, {
            {SideEffect::CARDIAC_ARRHYTHMIA, InteractionSeverity::MAJOR, 0.65,
             "Opposing effects on cardiovascular system"},
            {SideEffect::DEATH_RISK, InteractionSeverity::MAJOR, 0.25,
             "Masked intoxication leading to overdose"}
            });

        // Stimulant + Opioid
        addInteraction(DrugClass::STIMULANT, DrugClass::OPIOID, {
            {SideEffect::CARDIAC_ARRHYTHMIA, InteractionSeverity::MODERATE, 0.55,
             "Cardiovascular stress from stimulant"},
            {SideEffect::DEATH_RISK, InteractionSeverity::MAJOR, 0.20,
             "Masked respiratory depression"}
            });

        // Multiple stimulants
        addInteraction(DrugClass::STIMULANT, DrugClass::STIMULANT, {
            {SideEffect::CARDIAC_ARRHYTHMIA, InteractionSeverity::MAJOR, 0.75,
             "Additive cardiovascular stress"},
            {SideEffect::TORSADES_DE_POINTES, InteractionSeverity::MAJOR, 0.30,
             "QT prolongation and dangerous arrhythmias"},
            {SideEffect::HYPERTHERMIA, InteractionSeverity::MAJOR, 0.60,
             "Dangerous hyperthermia especially with physical activity"}
            });

        // Hallucinogen + Stimulant
        addInteraction(DrugClass::HALLUCINOGEN, DrugClass::STIMULANT, {
            {SideEffect::CARDIAC_ARRHYTHMIA, InteractionSeverity::MAJOR, 0.70,
             "Combined cardiovascular stress"},
            {SideEffect::HYPERTHERMIA, InteractionSeverity::MAJOR, 0.55,
             "Increased risk of hyperthermia"},
            {SideEffect::HALLUCINATIONS, InteractionSeverity::MAJOR, 0.85,
             "Intensified and unpredictable hallucinations"}
            });

        // Hallucinogen + Depressant
        addInteraction(DrugClass::HALLUCINOGEN, DrugClass::DEPRESSANT, {
            {SideEffect::RESPIRATORY_DEPRESSION, InteractionSeverity::MODERATE, 0.45,
             "Potential respiratory depression"},
            {SideEffect::HALLUCINATIONS, InteractionSeverity::MAJOR, 0.75,
             "Altered and potentially dangerous hallucinations"}
            });

        // Hallucinogen + Hallucinogen
        addInteraction(DrugClass::HALLUCINOGEN, DrugClass::HALLUCINOGEN, {
            {SideEffect::HALLUCINATIONS, InteractionSeverity::MAJOR, 0.90,
             "Unpredictable and intense hallucinations"},
            {SideEffect::CARDIAC_ARRHYTHMIA, InteractionSeverity::MODERATE, 0.50,
             "Combined cardiovascular effects"}
            });

        // Cannabis interactions (generally mild but can potentiate)
        addInteraction(DrugClass::CANNABIS, DrugClass::DEPRESSANT, {
            {SideEffect::DROWSINESS, InteractionSeverity::MODERATE, 0.70,
             "Enhanced sedation"},
            {SideEffect::RESPIRATORY_DEPRESSION, InteractionSeverity::MODERATE, 0.35,
             "Mild potentiation of respiratory depression"}
            });

        addInteraction(DrugClass::CANNABIS, DrugClass::STIMULANT, {
            {SideEffect::CARDIAC_ARRHYTHMIA, InteractionSeverity::MODERATE, 0.45,
             "Mixed cardiovascular effects"}
            });

        // Inhalant interactions (dangerous with most substances)
        addInteraction(DrugClass::INHALANT, DrugClass::DEPRESSANT, {
            {SideEffect::RESPIRATORY_DEPRESSION, InteractionSeverity::LETHAL, 0.85,
             "Severe respiratory depression"},
            {SideEffect::DEATH_RISK, InteractionSeverity::LETHAL, 0.50,
             "High risk of sudden death"}
            });

        addInteraction(DrugClass::INHALANT, DrugClass::STIMULANT, {
            {SideEffect::CARDIAC_ARRHYTHMIA, InteractionSeverity::LETHAL, 0.80,
             "Dangerous cardiac arrhythmias"},
            {SideEffect::DEATH_RISK, InteractionSeverity::LETHAL, 0.45,
             "Risk of sudden cardiac death"}
            });

        // Synthetic drug interactions (unpredictable)
        addInteraction(DrugClass::SYNTHETIC, DrugClass::STIMULANT, {
            {SideEffect::HYPERTHERMIA, InteractionSeverity::MAJOR, 0.75,
             "Severe hyperthermia risk"},
            {SideEffect::CARDIAC_ARRHYTHMIA, InteractionSeverity::MAJOR, 0.70,
             "Unpredictable cardiovascular effects"}
            });

        addInteraction(DrugClass::SYNTHETIC, DrugClass::DEPRESSANT, {
            {SideEffect::RESPIRATORY_DEPRESSION, InteractionSeverity::MAJOR, 0.65,
             "Unpredictable respiratory effects"},
            {SideEffect::DEATH_RISK, InteractionSeverity::MAJOR, 0.35,
             "Unknown interaction profile"}
            });
    }

    void addInteraction(DrugClass drug1, DrugClass drug2,
        const std::vector<InteractionEffect>& effects) {
        auto key1 = std::make_pair(drug1, drug2);
        auto key2 = std::make_pair(drug2, drug1);
        interactionMatrix[key1] = effects;
        interactionMatrix[key2] = effects;
    }

    // Helper function to get drug class interactions
    std::vector<InteractionEffect> getClassInteraction(DrugClass class1, DrugClass class2) {
        auto key = std::make_pair(class1, class2);
        auto it = interactionMatrix.find(key);
        return (it != interactionMatrix.end()) ? it->second : std::vector<InteractionEffect>{};
    }

public:
    InteractionAnalyzer() {
        initializeInteractionMatrix();
    }

    std::vector<InteractionEffect> analyzeInteraction(const Drug& drug1, const Drug& drug2) {
        // Get base class interaction
        std::vector<InteractionEffect> effects = getClassInteraction(
            drug1.getDrugClass(), drug2.getDrugClass());

        // Apply drug-specific modifiers
        modifyEffectsForSpecificDrugs(effects, drug1, drug2);

        return effects;
    }

    std::vector<InteractionEffect> analyzeMultipleInteractions(const std::vector<Drug>& drugs) {
        std::vector<InteractionEffect> allEffects;

        for (size_t i = 0; i < drugs.size(); ++i) {
            for (size_t j = i + 1; j < drugs.size(); ++j) {
                auto effects = analyzeInteraction(drugs[i], drugs[j]);
                allEffects.insert(allEffects.end(), effects.begin(), effects.end());
            }
        }

        return consolidateEffects(allEffects);
    }

private:
    void modifyEffectsForSpecificDrugs(std::vector<InteractionEffect>& effects,
        const Drug& drug1, const Drug& drug2) {
        std::string name1 = drug1.getName();
        std::string name2 = drug2.getName();

        // PCP + Oxycodone specific interaction (very dangerous)
        if ((name1 == "pcp" && name2 == "oxycodone") ||
            (name2 == "pcp" && name1 == "oxycodone")) {

            // Add/modify existing effects
            bool foundRespDep = false, foundMania = false, foundDeathRisk = false;

            for (auto& effect : effects) {
                if (effect.effect == SideEffect::RESPIRATORY_DEPRESSION) {
                    effect.probability = std::min(1.0, effect.probability * 1.8);
                    effect.severity = InteractionSeverity::LETHAL;
                    effect.description = "PCP's NMDA antagonism potentiates oxycodone respiratory depression";
                    foundRespDep = true;
                }
                if (effect.effect == SideEffect::DEATH_RISK) {
                    effect.probability = std::min(1.0, effect.probability * 2.0);
                    effect.severity = InteractionSeverity::LETHAL;
                    foundDeathRisk = true;
                }
            }

            // Add new effects if not present
            if (!foundRespDep) {
                effects.push_back({ SideEffect::RESPIRATORY_DEPRESSION, InteractionSeverity::LETHAL, 0.75,
                    "PCP's NMDA antagonism dangerously potentiates oxycodone respiratory depression" });
            }
            if (!foundMania) {
                effects.push_back({ SideEffect::MANIA, InteractionSeverity::MAJOR, 0.65,
                    "PCP can trigger manic episodes, especially dangerous with opioid euphoria" });
            }
            if (!foundDeathRisk) {
                effects.push_back({ SideEffect::DEATH_RISK, InteractionSeverity::LETHAL, 0.55,
                    "Extremely high risk due to respiratory depression and unpredictable PCP effects" });
            }

            // Add dissociative effects
            effects.push_back({ SideEffect::HALLUCINATIONS, InteractionSeverity::MAJOR, 0.85,
                "Intense dissociative effects combined with opioid sedation" });
        }

        // PCP with any depressant is dangerous
        if ((name1 == "pcp" && isDepressant(drug2)) ||
            (name2 == "pcp" && isDepressant(drug1))) {
            for (auto& effect : effects) {
                if (effect.effect == SideEffect::RESPIRATORY_DEPRESSION) {
                    effect.probability = std::min(1.0, effect.probability * 1.4);
                    effect.severity = InteractionSeverity::MAJOR;
                    effect.description = "PCP's complex CNS effects dangerously interact with depressants";
                }
            }

            // Add mania risk for PCP + any depressant
            bool foundMania = false;
            for (const auto& effect : effects) {
                if (effect.effect == SideEffect::MANIA) {
                    foundMania = true;
                    break;
                }
            }
            if (!foundMania) {
                effects.push_back({ SideEffect::MANIA, InteractionSeverity::MAJOR, 0.45,
                    "PCP can trigger manic/psychotic episodes when combined with depressants" });
            }
        }

        // Fentanyl interactions are more dangerous
        if (name1 == "fentanyl" || name2 == "fentanyl") {
            for (auto& effect : effects) {
                if (effect.effect == SideEffect::RESPIRATORY_DEPRESSION ||
                    effect.effect == SideEffect::DEATH_RISK) {
                    effect.probability = std::min(1.0, effect.probability * 1.5);
                    if (effect.severity < InteractionSeverity::LETHAL) {
                        effect.severity = static_cast<InteractionSeverity>(
                            static_cast<int>(effect.severity) + 1);
                    }
                }
            }
        }

        // Oxycodone with CYP2D6/CYP3A4 inhibitors (based on search results)
        if ((name1 == "oxycodone" && isCYPInhibitor(name2)) ||
            (name2 == "oxycodone" && isCYPInhibitor(name1))) {
            for (auto& effect : effects) {
                if (effect.effect == SideEffect::RESPIRATORY_DEPRESSION ||
                    effect.effect == SideEffect::DEATH_RISK) {
                    effect.probability = std::min(1.0, effect.probability * 1.3);
                    effect.description += " - Enhanced by CYP enzyme inhibition";
                }
            }
        }

        // Oxycodone with alcohol/benzos is particularly risky
        if ((name1 == "oxycodone" && (name2 == "alcohol" || isDrugClass(drug2, DrugClass::BENZODIAZEPINE))) ||
            (name2 == "oxycodone" && (name1 == "alcohol" || isDrugClass(drug1, DrugClass::BENZODIAZEPINE)))) {
            for (auto& effect : effects) {
                if (effect.effect == SideEffect::DEATH_RISK) {
                    effect.probability = std::min(1.0, effect.probability * 1.2);
                }
            }
        }
    }

private:
    bool isCYPInhibitor(const std::string& drugName) {
        // Common CYP2D6/CYP3A4 inhibitors that interact with oxycodone
        std::set<std::string> cypInhibitors = {
            "fluoxetine", "paroxetine", "sertraline", "clarithromycin",
            "erythromycin", "ketoconazole", "itraconazole", "ritonavir"
        };
        return cypInhibitors.find(drugName) != cypInhibitors.end();
    }


    bool isDepressant(const Drug& drug) {
        return drug.getDrugClass() == DrugClass::DEPRESSANT ||
            drug.getDrugClass() == DrugClass::OPIOID ||
            drug.getDrugClass() == DrugClass::BENZODIAZEPINE ||
            drug.getDrugClass() == DrugClass::ALCOHOL;
    }

    bool isDrugClass(const Drug& drug, DrugClass targetClass) {
        return drug.getDrugClass() == targetClass;
    }

    std::vector<InteractionEffect> consolidateEffects(std::vector<InteractionEffect>& effects) {
        std::map<SideEffect, InteractionEffect> consolidated;

        for (const auto& effect : effects) {
            auto it = consolidated.find(effect.effect);
            if (it == consolidated.end()) {
                consolidated[effect.effect] = effect;
            }
            else {
                // Combine probabilities and take highest severity
                it->second.probability = std::min(1.0,
                    it->second.probability + effect.probability * 0.5);
                if (effect.severity > it->second.severity) {
                    it->second.severity = effect.severity;
                    it->second.description = effect.description;
                }
            }
        }

        std::vector<InteractionEffect> result;
        for (const auto& pair : consolidated) {
            result.push_back(pair.second);
        }

        return result;
    }
};
