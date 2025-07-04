#pragma once

#include "../base_state.hpp"
#include <memory>
#include <string>
#include <spdlog/spdlog.h>

// ENFORCE state for the ATROP FSM
class EnforceState : public BaseState {
public:
    explicit EnforceState(std::shared_ptr<spdlog::logger> logger);

    void on_enter() override;
    void on_exit() override;
    std::string name() const override { return "ENFORCE"; }

private:
    std::shared_ptr<spdlog::logger> logger_;
};
