#pragma once

#include "../base_state.hpp"
#include <memory>
#include <string>
#include <spdlog/spdlog.h>

// INIT state for the ATROP FSM
class InitState : public BaseState {
public:
    explicit InitState(std::shared_ptr<spdlog::logger> logger);

    void on_enter() override;
    void on_exit() override;
    std::string name() const override { return "INIT"; }

private:
    std::shared_ptr<spdlog::logger> logger_;
};
