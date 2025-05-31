#include <vector>

class InteractionAnalyzer {
private:
    std::map<std::pair<DrugClass, DrugClass>, std::vector<InteractionEffect>> interactionMatrix;

    void initializeInteractionMatrix() {
        // Depressant + Depressant combinations (high risk)[1]
        addInteraction(DrugClass::DEPRESSANT, DrugClass::DEPRESSANT, {
            {SideEffect::RESPIRATORY_DEPRESSION, InteractionSeverity::MAJOR, 0.85,
             "Synergistic CNS depression leading to respiratory failure"},
            {SideEffect::DROWSINESS, InteractionSeverity::MAJOR, 0.95,
             "Extreme sedation and loss of consciousness"},
            {SideEffect::DEATH_RISK, InteractionSeverity::LETHAL, 0.35,
             "High risk of fatal overdose"}
            });

        // Opioid + Benzodiazepine (extremely dangerous)[1]
        addInteraction(DrugClass::OPIOID, DrugClass::BENZODIAZEPINE, {
            {SideEffect::RESPIRATORY_DEPRESSION, InteractionSeverity::LETHAL, 0.90,
             "Severe respiratory depression - frequent cause of overdose deaths"},
            {SideEffect::NODDING, InteractionSeverity::MAJOR, 0.80,
             "Characteristic opioid nodding intensified"},
            {SideEffect::DEATH_RISK, InteractionSeverity::LETHAL, 0.45,
             "Extremely high fatality risk"}
            });

        // Alcohol + Opioids[1]
        addInteraction(DrugClass::ALCOHOL, DrugClass::OPIOID, {
            {SideEffect::RESPIRATORY_DEPRESSION, InteractionSeverity::LETHAL, 0.88,
             "Alcohol potentiates opioid respiratory depression"},
            {SideEffect::DROWSINESS, InteractionSeverity::MAJOR, 0.92,
             "Severe sedation and impaired consciousness"},
            {SideEffect::DEATH_RISK, InteractionSeverity::LETHAL, 0.40,
             "High risk of fatal respiratory failure"}
            });

        // Stimulant + Depressant (masking effects)
        addInteraction(DrugClass::STIMULANT, DrugClass::DEPRESSANT, {
            {SideEffect::CARDIAC_ARRHYTHMIA, InteractionSeverity::MAJOR, 0.65,
             "Opposing effects on cardiovascular system"},
            {SideEffect::DEATH_RISK, InteractionSeverity::MAJOR, 0.25,
             "Masked intoxication leading to overdose"}
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
    }

    void addInteraction(DrugClass drug1, DrugClass drug2,
        const std::vector<InteractionEffect>& effects) {
        auto key1 = std::make_pair(drug1, drug2);
        auto key2 = std::make_pair(drug2, drug1);
        interactionMatrix[key1] = effects;
        interactionMatrix[key2] = effects;
    }

public:
    InteractionAnalyzer() {
        initializeInteractionMatrix();
    }

    std::vector<InteractionEffect> analyzeInteraction(const Drug& drug1, const Drug& drug2) {
        auto key = std::make_pair(drug1.getDrugClass(), drug2.getDrugClass());
        auto it = interactionMatrix.find(key);

        if (it != interactionMatrix.end()) {
            return it->second;
        }

        return {}; // No specific interaction found
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
