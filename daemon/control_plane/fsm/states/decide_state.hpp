#pragma once

#include "../base_state.hpp"
#include <memory>
#include <string>
#include <spdlog/spdlog.h>

// DECIDE state for the ATROP FSM
class DecideState : public BaseState {
public:
    explicit DecideState(std::shared_ptr<spdlog::logger> logger);

    void on_enter() override;
    void on_exit() override;
    std::string name() const override { return "DECIDE"; }

private:
    std::shared_ptr<spdlog::logger> logger_;
};
