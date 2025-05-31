#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <algorithm>

// Enhanced drug database with comprehensive profiles
class DrugDatabase {
private:
    std::map<std::string, std::unique_ptr<Drug>> drugs;

public:
    DrugDatabase() {
        initializeDrugs();
    }

    void initializeDrugs() {
        // === OPIOIDS ===

        // Fentanyl - Extremely potent, short-acting synthetic opioid
        auto fentanyl = std::make_unique<Drug>("fentanyl", DrugClass::OPIOID,
            { SideEffect::RESPIRATORY_DEPRESSION, SideEffect::DEATH_RISK, SideEffect::NODDING },
            0.5, 0.08, 0.25); // Half-life: 30min, Onset: 5min, Peak: 15min
        fentanyl->setRespiratoryDepression(true);
        fentanyl->setDepressantPotency(15.0);
        fentanyl->setMasksOtherDrugs(false);
        fentanyl->addMetabolicPathway("CYP3A4");
        fentanyl->addReceptorAffinity("mu-opioid", 0.95);
        fentanyl->setLethalDoseRange(0.002, 0.01); // 2-10mg
        drugs["fentanyl"] = std::move(fentanyl);

        // Carfentanil - Veterinary opioid, extremely dangerous
        auto carfentanil = std::make_unique<Drug>("carfentanil", DrugClass::OPIOID,
            { SideEffect::RESPIRATORY_DEPRESSION, SideEffect::DEATH_RISK },
            7.7, 0.1, 0.5);
        carfentanil->setRespiratoryDepression(true);
        carfentanil->setDepressantPotency(25.0);
        carfentanil->addMetabolicPathway("CYP3A4");
        carfentanil->addReceptorAffinity("mu-opioid", 0.98);
        carfentanil->setLethalDoseRange(0.00002, 0.0001); // 0.02-0.1mg
        drugs["carfentanil"] = std::move(carfentanil);

        // Heroin - Classic street opioid
        auto heroin = std::make_unique<Drug>("heroin", DrugClass::OPIOID,
            { SideEffect::RESPIRATORY_DEPRESSION, SideEffect::NODDING, SideEffect::DROWSINESS },
            0.5, 0.1, 0.5);
        heroin->setRespiratoryDepression(true);
        heroin->setDepressantPotency(8.0);
        heroin->addMetabolicPathway("CYP2D6");
        heroin->addReceptorAffinity("mu-opioid", 0.85);
        heroin->setLethalDoseRange(0.075, 0.375); // 75-375mg
        drugs["heroin"] = std::move(heroin);

        // Morphine - Medical opioid standard
        auto morphine = std::make_unique<Drug>("morphine", DrugClass::OPIOID,
            { SideEffect::RESPIRATORY_DEPRESSION, SideEffect::DROWSINESS },
            3.0, 0.5, 1.0);
        morphine->setRespiratoryDepression(true);
        morphine->setDepressantPotency(6.0);
        morphine->addMetabolicPathway("UGT2B7");
        morphine->addReceptorAffinity("mu-opioid", 0.80);
        morphine->setLethalDoseRange(0.2, 1.0); // 200mg-1g
        drugs["morphine"] = std::move(morphine);

        // Oxycodone - Common prescription opioid
        auto oxycodone = std::make_unique<Drug>("oxycodone", DrugClass::OPIOID,
            { SideEffect::RESPIRATORY_DEPRESSION, SideEffect::DROWSINESS },
            4.5, 0.5, 1.5);
        oxycodone->setRespiratoryDepression(true);
        oxycodone->setDepressantPotency(5.5);
        oxycodone->addMetabolicPathway("CYP3A4");
        oxycodone->addMetabolicPathway("CYP2D6");
        oxycodone->addReceptorAffinity("mu-opioid", 0.75);
        oxycodone->setLethalDoseRange(0.08, 0.4); // 80-400mg
        drugs["oxycodone"] = std::move(oxycodone);

        // Tramadol - Atypical opioid with SNRI properties
        auto tramadol = std::make_unique<Drug>("tramadol", DrugClass::OPIOID,
            { SideEffect::SEIZURE, SideEffect::SEROTONIN_SYNDROME, SideEffect::DROWSINESS },
            6.3, 1.0, 2.0);
        tramadol->setRespiratoryDepression(false);
        tramadol->setDepressantPotency(2.0);
        tramadol->setStimulantPotency(1.5); // SNRI effects
        tramadol->addMetabolicPathway("CYP2D6");
        tramadol->addReceptorAffinity("mu-opioid", 0.30);
        tramadol->addReceptorAffinity("serotonin", 0.40);
        tramadol->addReceptorAffinity("norepinephrine", 0.35);
        tramadol->setLethalDoseRange(2.0, 8.0); // 2-8g
        drugs["tramadol"] = std::move(tramadol);

        // === STIMULANTS ===

        // Methamphetamine - Long-acting, highly neurotoxic
        auto methamphetamine = std::make_unique<Drug>("methamphetamine", DrugClass::STIMULANT,
            { SideEffect::CARDIAC_ARRHYTHMIA, SideEffect::HYPERTHERMIA, SideEffect::TORSADES_DE_POINTES },
            12.0, 0.5, 3.0);
        methamphetamine->setStimulantPotency(9.0);
        methamphetamine->setMasksOtherDrugs(true);
        methamphetamine->addMetabolicPathway("CYP2D6");
        methamphetamine->addMetabolicPathway("CYP3A4");
        methamphetamine->addReceptorAffinity("dopamine", 0.90);
        methamphetamine->addReceptorAffinity("norepinephrine", 0.85);
        methamphetamine->addReceptorAffinity("serotonin", 0.60);
        methamphetamine->setLethalDoseRange(0.2, 1.5); // 200mg-1.5g
        drugs["methamphetamine"] = std::move(methamphetamine);

        // Cocaine - Short-acting, cardiotoxic
        auto cocaine = std::make_unique<Drug>("cocaine", DrugClass::STIMULANT,
            { SideEffect::CARDIAC_ARRHYTHMIA, SideEffect::HYPERTHERMIA, SideEffect::SEIZURE },
            1.0, 0.08, 0.5);
        cocaine->setStimulantPotency(7.5);
        cocaine->setMasksOtherDrugs(true);
        cocaine->addMetabolicPathway("CYP3A4");
        cocaine->addMetabolicPathway("pseudocholinesterase");
        cocaine->addReceptorAffinity("dopamine", 0.85);
        cocaine->addReceptorAffinity("sodium_channel", 0.70);
        cocaine->setLethalDoseRange(0.5, 1.4); // 500mg-1.4g
        drugs["cocaine"] = std::move(cocaine);

        // Amphetamine - Medium duration stimulant
        auto amphetamine = std::make_unique<Drug>("amphetamine", DrugClass::STIMULANT,
            { SideEffect::CARDIAC_ARRHYTHMIA, SideEffect::HYPERTHERMIA },
            8.0, 0.75, 2.0);
        amphetamine->setStimulantPotency(6.0);
        amphetamine->addMetabolicPathway("CYP2D6");
        amphetamine->addReceptorAffinity("dopamine", 0.75);
        amphetamine->addReceptorAffinity("norepinephrine", 0.80);
        amphetamine->setLethalDoseRange(0.5, 5.0); // 500mg-5g
        drugs["amphetamine"] = std::move(amphetamine);

        // MDMA - Empathogenic stimulant
        auto mdma = std::make_unique<Drug>("mdma", DrugClass::STIMULANT,
            { SideEffect::HYPERTHERMIA, SideEffect::SEROTONIN_SYNDROME, SideEffect::CARDIAC_ARRHYTHMIA },
            8.0, 0.5, 2.0);
        mdma->setStimulantPotency(5.0);
        mdma->addMetabolicPathway("CYP2D6");
        mdma->addMetabolicPathway("CYP3A4");
        mdma->addReceptorAffinity("serotonin", 0.90);
        mdma->addReceptorAffinity("dopamine", 0.60);
        mdma->addReceptorAffinity("norepinephrine", 0.70);
        mdma->setLethalDoseRange(0.5, 2.0); // 500mg-2g
        drugs["mdma"] = std::move(mdma);

        // === BENZODIAZEPINES ===

        // Alprazolam (Xanax) - Short-acting, high potency
        auto alprazolam = std::make_unique<Drug>("alprazolam", DrugClass::BENZODIAZEPINE,
            { SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION },
            12.0, 0.5, 1.5);
        alprazolam->setDepressantPotency(7.0);
        alprazolam->addMetabolicPathway("CYP3A4");
        alprazolam->addReceptorAffinity("GABA-A", 0.85);
        alprazolam->setLethalDoseRange(10.0, 50.0); // 10-50mg (alone)
        drugs["alprazolam"] = std::move(alprazolam);

        // Diazepam (Valium) - Long-acting
        auto diazepam = std::make_unique<Drug>("diazepam", DrugClass::BENZODIAZEPINE,
            { SideEffect::DROWSINESS },
            36.0, 1.0, 2.0);
        diazepam->setDepressantPotency(4.0);
        diazepam->addMetabolicPathway("CYP3A4");
        diazepam->addMetabolicPathway("CYP2C19");
        diazepam->addReceptorAffinity("GABA-A", 0.80);
        diazepam->setLethalDoseRange(50.0, 200.0); // 50-200mg (alone)
        drugs["diazepam"] = std::move(diazepam);

        // Clonazepam (Klonopin) - Long-acting, high potency
        auto clonazepam = std::make_unique<Drug>("clonazepam", DrugClass::BENZODIAZEPINE,
            { SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION },
            30.0, 1.0, 4.0);
        clonazepam->setDepressantPotency(6.5);
        clonazepam->addMetabolicPathway("CYP3A4");
        clonazepam->addReceptorAffinity("GABA-A", 0.88);
        clonazepam->setLethalDoseRange(20.0, 80.0); // 20-80mg (alone)
        drugs["clonazepam"] = std::move(clonazepam);

        // Lorazepam (Ativan) - Intermediate-acting
        auto lorazepam = std::make_unique<Drug>("lorazepam", DrugClass::BENZODIAZEPINE,
            { SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION },
            14.0, 1.0, 2.0);
        lorazepam->setDepressantPotency(5.5);
        lorazepam->addMetabolicPathway("UGT");
        lorazepam->addReceptorAffinity("GABA-A", 0.82);
        lorazepam->setLethalDoseRange(30.0, 120.0); // 30-120mg (alone)
        drugs["lorazepam"] = std::move(lorazepam);

        // === ALCOHOL ===

        // Ethanol - Legal depressant
        auto alcohol = std::make_unique<Drug>("alcohol", DrugClass::ALCOHOL,
            { SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION },
            1.0, 0.25, 1.0);
        alcohol->setDepressantPotency(4.0);
        alcohol->setMasksOtherDrugs(false);
        alcohol->addMetabolicPathway("ADH");
        alcohol->addMetabolicPathway("CYP2E1");
        alcohol->addReceptorAffinity("GABA-A", 0.50);
        alcohol->addReceptorAffinity("NMDA", 0.40);
        alcohol->setLethalDoseRange(300.0, 500.0); // 300-500mg/dL BAC
        drugs["alcohol"] = std::move(alcohol);

        // === BARBITURATES ===

        // Phenobarbital - Long-acting barbiturate
        auto phenobarbital = std::make_unique<Drug>("phenobarbital", DrugClass::DEPRESSANT,
            { SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION },
            72.0, 1.0, 4.0);
        phenobarbital->setDepressantPotency(8.0);
        phenobarbital->setRespiratoryDepression(true);
        phenobarbital->addMetabolicPathway("CYP2C19");
        phenobarbital->addReceptorAffinity("GABA-A", 0.75);
        phenobarbital->setLethalDoseRange(6.0, 10.0); // 6-10g
        drugs["phenobarbital"] = std::move(phenobarbital);

        // Secobarbital - Short-acting barbiturate
        auto secobarbital = std::make_unique<Drug>("secobarbital", DrugClass::DEPRESSANT,
            { SideEffect::DROWSINESS, SideEffect::RESPIRATORY_DEPRESSION, SideEffect::DEATH_RISK },
            28.0, 0.5, 2.0);
        secobarbital->setDepressantPotency(9.0);
        secobarbital->setRespiratoryDepression(true);
        secobarbital->addMetabolicPathway("CYP2C19");
        secobarbital->addReceptorAffinity("GABA-A", 0.80);
        secobarbital->setLethalDoseRange(2.0, 5.0); // 2-5g
        drugs["secobarbital"] = std::move(secobarbital);

        // === HALLUCINOGENS ===

        // LSD - Classic psychedelic
        auto lsd = std::make_unique<Drug>("lsd", DrugClass::HALLUCINOGEN,
            { SideEffect::CARDIAC_ARRHYTHMIA },
            5.0, 0.5, 3.0);
        lsd->setStimulantPotency(2.0);
        lsd->addMetabolicPathway("CYP2D6");
        lsd->addReceptorAffinity("5-HT2A", 0.95);
        lsd->setLethalDoseRange(0.2, 1.0); // 200μg-1mg (theoretical)
        drugs["lsd"] = std::move(lsd);

        // Psilocybin - Magic mushrooms
        auto psilocybin = std::make_unique<Drug>("psilocybin", DrugClass::HALLUCINOGEN,
            {},
            2.5, 0.5, 2.0);
        psilocybin->addMetabolicPathway("alkaline_phosphatase");
        psilocybin->addReceptorAffinity("5-HT2A", 0.85);
        psilocybin->setLethalDoseRange(17.0, 280.0); // Very high LD50
        drugs["psilocybin"] = std::move(psilocybin);

        // === DISSOCIATIVES ===

        // Ketamine - NMDA antagonist
        auto ketamine = std::make_unique<Drug>("ketamine", DrugClass::DISSOCIATIVE,
            { SideEffect::RESPIRATORY_DEPRESSION },
            2.5, 0.25, 1.0);
        ketamine->setDepressantPotency(3.0);
        ketamine->addMetabolicPathway("CYP3A4");
        ketamine->addMetabolicPathway("CYP2B6");
        ketamine->addReceptorAffinity("NMDA", 0.85);
        ketamine->setLethalDoseRange(4.0, 11.0); // 4-11mg/kg
        drugs["ketamine"] = std::move(ketamine);

        // PCP - Dangerous dissociative
        auto pcp = std::make_unique<Drug>("pcp", DrugClass::DISSOCIATIVE,
            { SideEffect::HYPERTHERMIA, SideEffect::CARDIAC_ARRHYTHMIA },
            21.0, 0.5, 2.0);
        pcp->setStimulantPotency(4.0);
        pcp->addMetabolicPathway("CYP3A4");
        pcp->addReceptorAffinity("NMDA", 0.90);
        pcp->addReceptorAffinity("dopamine", 0.40);
        pcp->setLethalDoseRange(0.2, 1.0); // 200mg-1g
        drugs["pcp"] = std::move(pcp);

        // === NOVEL PSYCHOACTIVE SUBSTANCES ===

        // Synthetic Cathinones (Bath Salts)
        auto mephedrone = std::make_unique<Drug>("mephedrone", DrugClass::STIMULANT,
            { SideEffect::HYPERTHERMIA, SideEffect::CARDIAC_ARRHYTHMIA, SideEffect::SEROTONIN_SYNDROME },
            2.0, 0.25, 1.0);
        mephedrone->setStimulantPotency(6.5);
        mephedrone->addMetabolicPathway("CYP2D6");
        mephedrone->addReceptorAffinity("dopamine", 0.70);
        mephedrone->addReceptorAffinity("serotonin", 0.75);
        mephedrone->setLethalDoseRange(0.5, 2.0); // 500mg-2g
        drugs["mephedrone"] = std::move(mephedrone);

        // Synthetic Cannabinoids (K2/Spice)
        auto jwh018 = std::make_unique<Drug>("jwh-018", DrugClass::HALLUCINOGEN,
            { SideEffect::SEIZURE, SideEffect::CARDIAC_ARRHYTHMIA },
            6.0, 0.1, 0.5);
        jwh018->addMetabolicPathway("CYP1A2");
        jwh018->addReceptorAffinity("CB1", 0.90);
        jwh018->setLethalDoseRange(0.01, 0.1); // 10-100mg
        drugs["jwh-018"] = std::move(jwh018);

        // === RESEARCH CHEMICALS ===

        // 25I-NBOMe - Dangerous hallucinogen
        auto nbome = std::make_unique<Drug>("25i-nbome", DrugClass::HALLUCINOGEN,
            { SideEffect::SEIZURE, SideEffect::HYPERTHERMIA, SideEffect::CARDIAC_ARRHYTHMIA, SideEffect::DEATH_RISK },
            5.0, 0.5, 2.0);
        nbome->setStimulantPotency(3.0);
        nbome->addMetabolicPathway("CYP2D6");
        nbome->addReceptorAffinity("5-HT2A", 0.95);
        nbome->setLethalDoseRange(0.0005, 0.002); // 0.5-2mg
        drugs["25i-nbome"] = std::move(nbome);

        // 2C-B - Phenethylamine psychedelic
        auto twocb = std::make_unique<Drug>("2c-b", DrugClass::HALLUCINOGEN,
            { SideEffect::HYPERTHERMIA },
            8.0, 1.0, 3.0);
        twocb->setStimulantPotency(2.5);
        twocb->addMetabolicPathway("CYP2D6");
        twocb->addReceptorAffinity("5-HT2A", 0.80);
        twocb->setLethalDoseRange(0.2, 1.0); // 200mg-1g
        drugs["2c-b"] = std::move(twocb);
    }

    // Database access methods
    Drug* getDrug(const std::string& name) {
        auto it = drugs.find(name);
        return (it != drugs.end()) ? it->second.get() : nullptr;
    }

    std::vector<std::string> getAllDrugNames() const {
        std::vector<std::string> names;
        for (const auto& pair : drugs) {
            names.push_back(pair.first);
        }
        std::sort(names.begin(), names.end());
        return names;
    }

    std::vector<std::string> getDrugsByClass(DrugClass drugClass) const {
        std::vector<std::string> names;
        for (const auto& pair : drugs) {
            if (pair.second->getDrugClass() == drugClass) {
                names.push_back(pair.first);
            }
        }
        std::sort(names.begin(), names.end());
        return names;
    }

    std::vector<std::string> searchDrugs(const std::string& searchTerm) const {
        std::vector<std::string> matches;
        std::string lowerSearchTerm = searchTerm;
        std::transform(lowerSearchTerm.begin(), lowerSearchTerm.end(),
            lowerSearchTerm.begin(), ::tolower);

        for (const auto& pair : drugs) {
            std::string lowerDrugName = pair.first;
            std::transform(lowerDrugName.begin(), lowerDrugName.end(),
                lowerDrugName.begin(), ::tolower);

            if (lowerDrugName.find(lowerSearchTerm) != std::string::npos) {
                matches.push_back(pair.first);
            }
        }

        std::sort(matches.begin(), matches.end());
        return matches;
    }

    void displayDrugInfo(const std::string& drugName) const {
        auto it = drugs.find(drugName);
        if (it == drugs.end()) {
            std::cout << "Drug '" << drugName << "' not found in database.\n";
            return;
        }

        const Drug* drug = it->second.get();
        std::cout << "\n=== " << drug->getName() << " ===\n";
        std::cout << "Class: " << drugClassToString(drug->getDrugClass()) << "\n";
        std::cout << "Half-life: " << drug->getHalfLife() << " hours\n";
        std::cout << "Onset: " << drug->getOnsetTime() << " hours\n";
        std::cout << "Peak: " << drug->getPeakEffectTime() << " hours\n";
        std::cout << "Respiratory Depression: " << (drug->causesRespDepression() ? "Yes" : "No") << "\n";
        std::cout << "Stimulant Potency: " << drug->getStimulantPotency() << "/10\n";
        std::cout << "Depressant Potency: " << drug->getDepressantPotency() << "/10\n";
        std::cout << "Masks Other Drugs: " << (drug->getMasksOtherDrugs() ? "Yes" : "No") << "\n";

        auto effects = drug->getPrimaryEffects();
        if (!effects.empty()) {
            std::cout << "Primary Effects: ";
            for (size_t i = 0; i < effects.size(); ++i) {
                std::cout << effectToString(effects[i]);
                if (i < effects.size() - 1) std::cout << ", ";
            }
            std::cout << "\n";
        }

        std::cout << "Lethal Dose Range: " << drug->getLethalDoseMin() << " - "
            << drug->getLethalDoseMax() << " mg\n";
    }

    void displayAllDrugs() const {
        std::cout << "\n=== COMPLETE DRUG DATABASE ===\n";

        std::vector<DrugClass> classes = {
            DrugClass::OPIOID, DrugClass::STIMULANT, DrugClass::BENZODIAZEPINE,
            DrugClass::ALCOHOL, DrugClass::DEPRESSANT, DrugClass::HALLUCINOGEN,
            DrugClass::DISSOCIATIVE
        };

        for (DrugClass drugClass : classes) {
            auto drugsInClass = getDrugsByClass(drugClass);
            if (!drugsInClass.empty()) {
                std::cout << "\n## " << drugClassToString(drugClass) << "S\n";
                for (const auto& drugName : drugsInClass) {
                    std::cout << "- " << drugName << "\n";
                }
            }
        }

        std::cout << "\nTotal drugs in database: " << drugs.size() << "\n";
    }

private:
    std::string drugClassToString(DrugClass drugClass) const {
        switch (drugClass) {
        case DrugClass::OPIOID: return "OPIOID";
        case DrugClass::STIMULANT: return "STIMULANT";
        case DrugClass::BENZODIAZEPINE: return "BENZODIAZEPINE";
        case DrugClass::ALCOHOL: return "ALCOHOL";
        case DrugClass::DEPRESSANT: return "DEPRESSANT";
        case DrugClass::HALLUCINOGEN: return "HALLUCINOGEN";
        case DrugClass::DISSOCIATIVE: return "DISSOCIATIVE";
        default: return "UNKNOWN";
        }
    }

    std::string effectToString(SideEffect effect) const {
        switch (effect) {
        case SideEffect::DROWSINESS: return "Drowsiness";
        case SideEffect::RESPIRATORY_DEPRESSION: return "Respiratory Depression";
        case SideEffect::CARDIAC_ARRHYTHMIA: return "Cardiac Arrhythmia";
        case SideEffect::TORSADES_DE_POINTES: return "Torsades de Pointes";
        case SideEffect::NODDING: return "Nodding";
        case SideEffect::HYPERTHERMIA: return "Hyperthermia";
        case SideEffect::SEIZURE: return "Seizure";
        case SideEffect::DEATH_RISK: return "Risk of Death";
        case SideEffect::SEROTONIN_SYNDROME: return "Serotonin Syndrome";
        default: return "Unknown Effect";
        }
    }
};
