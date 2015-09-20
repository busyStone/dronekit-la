#ifndef ANALYZER_ATTITUDE_ESTIMATE_DIVERGENCE_H
#define ANALYZER_ATTITUDE_ESTIMATE_DIVERGENCE_H

/*
 * analyzer_attitude_estimate_divergence
 *
 */

#include "analyzer.h"

class Analyzer_Attitude_Estimate_Divergence_Result : public Analyzer_Result_Period {
public:
    Analyzer_Attitude_Estimate_Divergence_Result() :
        Analyzer_Result_Period()
        { }

    void set_name(const std::string name) { _name = name; }
    std::string name() { return _name; }

    void set_max_delta(const double delta) { _max_delta = delta; }
    const double max_delta() { return _max_delta; }

    void set_delta_threshold(const double delta) { _delta_threshold = delta; }
    const double delta_threshold() { return _delta_threshold; }

    void to_json(Json::Value &root) const override;
private:
    std::string _name = "";

    double _max_delta;
    double _delta_threshold;
};

class Analyzer_Attitude_Estimate_Divergence : public Analyzer {

public:

    Analyzer_Attitude_Estimate_Divergence(AnalyzerVehicle::Base *&vehicle, Data_Sources &data_sources) :
	Analyzer(vehicle,data_sources)
    { }

    const std::string name() const override { return "Attitude Estimate Divergence"; }
    const std::string description() const override {
        return "This test will FAIL if various craft's attitude estimates diverge";
    }

    void evaluate_estimate(
        std::string name,
        AnalyzerVehicle::Attitude attitude,
        AnalyzerVehicle::Attitude estimate);
    void evaluate() override;

    void end_of_log(const uint32_t packet_count);

private:

    // FIXME: magic numbers!
    const double attitude_max_delta_roll_pitch_fail = 10.0f;
    const double attitude_max_delta_roll_pitch_warn = 5.0f;
    const uint64_t delta_time_threshold = 500000;

    void open_result(std::string name, double delta);
    void update_result(std::string name, double delta);
    void close_result(std::string name);
    std::map<const std::string, Analyzer_Attitude_Estimate_Divergence_Result*> _result;
};

#endif
