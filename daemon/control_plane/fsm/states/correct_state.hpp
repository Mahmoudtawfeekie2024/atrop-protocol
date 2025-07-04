#pragma once

#include "../base_state.hpp"
#include <memory>
#include <string>
#include <spdlog/spdlog.h>

// CORRECT state for the ATROP FSM
class CorrectState : public BaseState {
public:
    explicit CorrectState(std::shared_ptr<spdlog::logger> logger);

    void on_enter() override;
    void on_exit() override;
    std::string name() const override { return "CORRECT"; }

private:
    std::shared_ptr<spdlog::logger> logger_;
};
