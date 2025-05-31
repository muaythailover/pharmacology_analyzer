#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <memory>
#include <set>

enum class DrugClass {
    OPIOID,
    BENZODIAZEPINE,
    STIMULANT,
    ALCOHOL,
    DEPRESSANT,
    HALLUCINOGEN,
    CANNABIS,
    INHALANT,
    SYNTHETIC
};
enum class SideEffect {
    RESPIRATORY_DEPRESSION,
    NODDING,
    DROWSINESS,
    DEATH_RISK,
    CARDIAC_ARRHYTHMIA,
    MANIA,
    HYPERTHERMIA,
    TORSADES_DE_POINTES,
    NAUSEA,
    HALLUCINATIONS
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