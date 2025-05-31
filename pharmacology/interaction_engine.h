#pragma once

#include <algorithm>
#include <vector>

class InteractionAnalyzer {
private:
    std::map<std::pair<DrugClass, DrugClass>, std::vector<ComplexInteractionEffect>> complexInteractionMatrix;

    void initializeComplexInteractions() {
        // Fentanyl + Methamphetamine - Critical masking interaction
        addComplexInteraction(DrugClass::OPIOID, DrugClass::STIMULANT, {
            {
                SideEffect::RESPIRATORY_DEPRESSION,
                InteractionSeverity::LETHAL,
                InteractionMechanism::MASKING,
                0.75,
                "Fentanyl's depressant effects mask methamphetamine's stimulant warning signs, leading to false sense of safety",
                0.5, // Onset within 30 minutes
                4.0, // Duration 4 hours
                {"Confusion", "Slurred speech", "Pinpoint pupils"},
                {"Sudden agitation", "Hyperthermia", "Cardiac arrhythmia"},
                true,
                "Monitor for delayed stimulant toxicity after opioid effects subside. Naloxone may unmask dangerous stimulant levels."
            },
            {
                SideEffect::CARDIAC_ARRHYTHMIA,
                InteractionSeverity::MAJOR,
                InteractionMechanism::DELAYED_ONSET,
                0.65,
                "When fentanyl wears off (shorter half-life), accumulated methamphetamine causes sudden stimulant overdose symptoms",
                2.0, // Delayed onset after 2 hours
                6.0,
                {"Mild tachycardia", "Restlessness"},
                {"Severe tachycardia", "Hyperthermia", "Psychosis", "Seizures"},
                true,
                "Requires extended monitoring. Stimulant toxicity may emerge 2-4 hours after initial presentation."
            },
            {
                SideEffect::HYPERTHERMIA,
                InteractionSeverity::MAJOR,
                InteractionMechanism::DELAYED_ONSET,
                0.60,
                "Methamphetamine's thermogenic effects become apparent as opioid sedation diminishes",
                1.5,
                8.0,
                {"Mild temperature elevation", "Sweating"},
                {"Dangerous hyperthermia >104°F", "Dehydration", "Organ failure"},
                true,
                "Active cooling measures may be needed. Monitor core temperature closely."
            }
            });

        // Cocaine + Fentanyl - Different masking pattern
        addComplexInteraction(DrugClass::STIMULANT, DrugClass::OPIOID, {
            {
                SideEffect::RESPIRATORY_DEPRESSION,
                InteractionSeverity::LETHAL,
                InteractionMechanism::MASKING,
                0.80,
                "Cocaine's stimulant effects mask early signs of fentanyl-induced respiratory depression",
                0.25,
                2.0,
                {"Euphoria masking sedation", "Normal alertness despite opioid use"},
                {"Sudden respiratory failure", "Cyanosis", "Loss of consciousness"},
                true,
                "Cocaine's shorter duration than fentanyl creates dangerous window of unmasked opioid toxicity"
            },
            {
                SideEffect::CARDIAC_ARRHYTHMIA,
                InteractionSeverity::MAJOR,
                InteractionMechanism::SYNERGISTIC,
                0.70,
                "Opposing cardiovascular effects create unstable cardiac rhythm patterns",
                0.5,
                4.0,
                {"Irregular heartbeat", "Chest discomfort"},
                {"Ventricular arrhythmias", "Cardiac arrest"},
                true,
                "Requires cardiac monitoring. Both pro-arrhythmic and anti-arrhythmic effects present."
            }
            });

        // Alcohol + Stimulants - Masking intoxication
        addComplexInteraction(DrugClass::ALCOHOL, DrugClass::STIMULANT, {
            {
                SideEffect::DEATH_RISK,
                InteractionSeverity::MAJOR,
                InteractionMechanism::MASKING,
                0.55,
                "Stimulants mask alcohol intoxication, leading to dangerous overconsumption and alcohol poisoning",
                1.0,
                6.0,
                {"False sobriety", "Continued drinking despite high BAC"},
                {"Sudden collapse", "Respiratory depression", "Hypothermia"},
                true,
                "Patient may appear sober despite lethal blood alcohol levels. Check BAC regardless of apparent alertness."
            }
            });

        // Multiple CNS Depressants - Synergistic respiratory depression
        addComplexInteraction(DrugClass::BENZODIAZEPINE, DrugClass::OPIOID, {
            {
                SideEffect::RESPIRATORY_DEPRESSION,
                InteractionSeverity::LETHAL,
                InteractionMechanism::SYNERGISTIC,
                0.90,
                "Benzodiazepines and opioids synergistically depress respiratory drive through different mechanisms",
                0.5,
                8.0,
                {"Drowsiness", "Slowed breathing", "Confusion"},
                {"Respiratory rate <8/min", "Cyanosis", "Unresponsiveness"},
                true,
                "May require multiple naloxone doses. Flumazenil contraindicated if seizure history present."
            },
            {
                SideEffect::NODDING,
                InteractionSeverity::MAJOR,
                InteractionMechanism::SYNERGISTIC,
                0.85,
                "Combined sedation creates characteristic 'nodding' with increased fall risk and aspiration danger",
                0.75,
                6.0,
                {"Mild sedation", "Head drooping"},
                {"Complete loss of postural control", "Aspiration risk"},
                false,
                "Position patient to prevent aspiration. Monitor airway patency."
            }
            });

        // Pharmacokinetic interactions - CYP450 competition
        addComplexInteraction(DrugClass::STIMULANT, DrugClass::STIMULANT, {
            {
                SideEffect::TORSADES_DE_POINTES,
                InteractionSeverity::MAJOR,
                InteractionMechanism::PHARMACOKINETIC,
                0.45,
                "Multiple stimulants compete for CYP3A4 metabolism, prolonging QT interval and increasing arrhythmia risk",
                2.0,
                12.0,
                {"Palpitations", "Mild QT prolongation"},
                {"Polymorphic ventricular tachycardia", "Sudden cardiac death"},
                true,
                "Monitor ECG for QT prolongation. Avoid other QT-prolonging medications."
            }
            });
    }

    void addComplexInteraction(DrugClass drug1, DrugClass drug2,
        const std::vector<ComplexInteractionEffect>& effects) {
        auto key1 = std::make_pair(drug1, drug2);
        auto key2 = std::make_pair(drug2, drug1);
        complexInteractionMatrix[key1] = effects;
        complexInteractionMatrix[key2] = effects;
    }

public:
    AdvancedInteractionAnalyzer() {
        initializeComplexInteractions();
    }

    std::vector<ComplexInteractionEffect> analyzeComplexInteraction(const Drug& drug1, const Drug& drug2) {
        auto key = std::make_pair(drug1.getDrugClass(), drug2.getDrugClass());
        auto it = complexInteractionMatrix.find(key);

        std::vector<ComplexInteractionEffect> effects;
        if (it != complexInteractionMatrix.end()) {
            effects = it->second;
        }

        // Add dynamic analysis based on drug properties
        effects = enhanceWithDynamicAnalysis(drug1, drug2, effects);

        return effects;
    }

private:
    std::vector<ComplexInteractionEffect> enhanceWithDynamicAnalysis(
        const Drug& drug1, const Drug& drug2,
        std::vector<ComplexInteractionEffect> baseEffects) {

        // Analyze half-life differences for masking effects
        double halfLifeDiff = std::abs(drug1.getHalfLife() - drug2.getHalfLife());
        if (halfLifeDiff > 2.0) { // Significant difference in duration
            if ((drug1.getDrugClass() == DrugClass::OPIOID && drug2.getDrugClass() == DrugClass::STIMULANT) ||
                (drug1.getDrugClass() == DrugClass::STIMULANT && drug2.getDrugClass() == DrugClass::OPIOID)) {

                // Determine which drug has shorter half-life
                bool opioidShorter = (drug1.getDrugClass() == DrugClass::OPIOID && drug1.getHalfLife() < drug2.getHalfLife()) ||
                    (drug2.getDrugClass() == DrugClass::OPIOID && drug2.getHalfLife() < drug1.getHalfLife());

                if (opioidShorter) {
                    ComplexInteractionEffect delayedStimulant = {
                        SideEffect::HYPERTHERMIA,
                        InteractionSeverity::MAJOR,
                        InteractionMechanism::DELAYED_ONSET,
                        0.70,
                        "Short-acting opioid wears off before longer-acting stimulant, causing delayed stimulant toxicity",
                        std::max(drug1.getHalfLife(), drug2.getHalfLife()),
                        6.0,
                        {"Increasing restlessness", "Rising heart rate"},
                        {"Severe hyperthermia", "Agitation", "Potential seizures"},
                        true,
                        "Extended monitoring required for delayed stimulant emergence"
                    };
                    baseEffects.push_back(delayedStimulant);
                }
            }
        }

        // Analyze masking potential based on drug properties
        if ((drug1.getMasksOtherDrugs() || drug2.getMasksOtherDrugs()) &&
            drug1.getDrugClass() != drug2.getDrugClass()) {

            ComplexInteractionEffect maskingEffect = {
                SideEffect::DEATH_RISK,
                InteractionSeverity::MAJOR,
                InteractionMechanism::MASKING,
                0.60,
                "One drug masks the intoxication signs of the other, leading to dangerous overconsumption",
                0.5,
                4.0,
                {"False sense of sobriety", "Continued drug use"},
                {"Sudden onset of severe toxicity", "Rapid deterioration"},
                true,
                "Assess for masked intoxication regardless of apparent alertness level"
            };
            baseEffects.push_back(maskingEffect);
        }

        return baseEffects;
    }
};