#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <memory>
#include <set>

enum class DrugClass {
    STIMULANT,
    DEPRESSANT,
    OPIOID,
    HALLUCINOGEN,
    BENZODIAZEPINE,
    ALCOHOL,
    DISSOCIATIVE
};

enum class SideEffect {
    DROWSINESS,
    RESPIRATORY_DEPRESSION,
    CARDIAC_ARRHYTHMIA,
    TORSADES_DE_POINTES,
    NODDING,
    HYPERTHERMIA,
    SEIZURE,
    DEATH_RISK,
    SEROTONIN_SYNDROME
};

enum class InteractionSeverity {
    MINOR,
    MODERATE,
    MAJOR,
    LETHAL
};

enum class InteractionMechanism {
    SYNERGISTIC,           // Effects add together
    ANTAGONISTIC,          // Effects oppose each other
    MASKING,              // One drug hides effects of another
    DELAYED_ONSET,        // Effects appear after one drug wears off
    PHARMACOKINETIC,      // Metabolism interference
    RECEPTOR_COMPETITION, // Competing for same receptors
    SENSITIZATION        // Increased sensitivity to effects
};

struct ComplexInteractionEffect {
    SideEffect effect;
    InteractionSeverity severity;
    InteractionMechanism mechanism;
    double probability;
    std::string description;
    double onsetTimeHours;
    double durationHours;
    std::vector<std::string> warningSignsEarly;
    std::vector<std::string> warningSignsLate;
    bool requiresSpecialTreatment;
    std::string treatmentNotes;
};


struct InteractionEffect {
    SideEffect effect;
    InteractionSeverity severity;
    double probability;
    std::string description;
};