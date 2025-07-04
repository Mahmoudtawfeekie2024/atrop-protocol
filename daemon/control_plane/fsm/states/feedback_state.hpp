#pragma once

#include "../base_state.hpp"
#include <memory>
#include <string>
#include <spdlog/spdlog.h>

// FEEDBACK state for the ATROP FSM
class FeedbackState : public BaseState {
public:
    explicit FeedbackState(std::shared_ptr<spdlog::logger> logger);

    void on_enter() override;
    void on_exit() override;
    std::string name() const override { return "FEEDBACK"; }

private:
    std::shared_ptr<spdlog::logger> logger_;
};
