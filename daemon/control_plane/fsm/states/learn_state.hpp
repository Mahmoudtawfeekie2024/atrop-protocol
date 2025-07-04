#pragma once

#include "../base_state.hpp"
#include <memory>
#include <string>
#include <spdlog/spdlog.h>

// LEARN state for the ATROP FSM
class LearnState : public BaseState {
public:
    explicit LearnState(std::shared_ptr<spdlog::logger> logger);

    void on_enter() override;
    void on_exit() override;
    std::string name() const override { return "LEARN"; }

private:
    std::shared_ptr<spdlog::logger> logger_;
};
