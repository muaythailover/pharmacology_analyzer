class Drug {
private:
    std::string name;
    DrugClass drugClass;
    std::vector<SideEffect> primaryEffects;
    std::map<std::string, double> receptorAffinities;
    double halfLife;
    double peakEffectTime;
    double onsetTime;
    bool causesRespiratoryDepression;
    bool affectsCNS;
    bool masksOtherDrugs;
    double stimulantPotency;
    double depressantPotency;
    std::vector<std::string> metabolicPathways;
    double lethalDoseMin;
    double lethalDoseMax;

public:
    Drug(const std::string& drugName, DrugClass type,
        const std::vector<SideEffect>& effects, double t_half,
        double onset = 0.25, double peak = 1.0)
        : name(drugName), drugClass(type), primaryEffects(effects),
        halfLife(t_half), onsetTime(onset), peakEffectTime(peak),
        causesRespiratoryDepression(false), affectsCNS(true),
        masksOtherDrugs(false), stimulantPotency(0.0), depressantPotency(0.0),
        lethalDoseMin(0.0), lethalDoseMax(0.0) {
    }

    // All getter methods
    const std::string& getName() const { return name; }
    DrugClass getDrugClass() const { return drugClass; }
    const std::vector<SideEffect>& getPrimaryEffects() const { return primaryEffects; }
    double getHalfLife() const { return halfLife; }
    double getOnsetTime() const { return onsetTime; }
    double getPeakEffectTime() const { return peakEffectTime; }
    bool causesRespDepression() const { return causesRespiratoryDepression; }
    bool getMasksOtherDrugs() const { return masksOtherDrugs; }
    double getStimulantPotency() const { return stimulantPotency; }
    double getDepressantPotency() const { return depressantPotency; }
    double getLethalDoseMin() const { return lethalDoseMin; }
    double getLethalDoseMax() const { return lethalDoseMax; }

    // All setter methods
    void setRespiratoryDepression(bool value) { causesRespiratoryDepression = value; }
    void setMasksOtherDrugs(bool value) { masksOtherDrugs = value; }
    void setStimulantPotency(double potency) { stimulantPotency = potency; }
    void setDepressantPotency(double potency) { depressantPotency = potency; }
    void setLethalDoseRange(double min, double max) {
        lethalDoseMin = min;
        lethalDoseMax = max;
    }

    void addMetabolicPathway(const std::string& pathway) {
        metabolicPathways.push_back(pathway);
    }

    void addReceptorAffinity(const std::string& receptor, double affinity) {
        receptorAffinities[receptor] = affinity;
    }

    bool hasEffect(SideEffect effect) const {
        return std::find(primaryEffects.begin(), primaryEffects.end(), effect)
            != primaryEffects.end();
    }
};
