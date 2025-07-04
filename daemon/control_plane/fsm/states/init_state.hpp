#pragma once

#include "../base_state.hpp"
#include <memory>
#include <spdlog/logger.h>

// Initialization State for ATROP FSM
// Handles entry and exit logic for the INIT state.
class InitState : public BaseState {
public:
    explicit InitState(std::shared_ptr<spdlog::logger> logger);

    void on_enter() override;
    void on_exit() override;
    std::string name() const override { return "INIT"; }

private:
    std::shared_ptr<spdlog::logger> logger_;
};
