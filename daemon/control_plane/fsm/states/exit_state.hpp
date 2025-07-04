#pragma once

#include "../base_state.hpp"
#include <memory>
#include <string>
#include <spdlog/spdlog.h>

// EXIT state for the ATROP FSM
class ExitState : public BaseState {
public:
    explicit ExitState(std::shared_ptr<spdlog::logger> logger);

    void on_enter() override;
    void on_exit() override;
    std::string name() const override { return "EXIT"; }

private:
    std::shared_ptr<spdlog::logger> logger_;
};
