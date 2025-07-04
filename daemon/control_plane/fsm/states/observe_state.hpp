#pragma once

#include "../base_state.hpp"
#include <memory>
#include <string>
#include <spdlog/spdlog.h>

// OBSERVE state for the ATROP FSM
class ObserveState : public BaseState {
public:
    explicit ObserveState(std::shared_ptr<spdlog::logger> logger);

    void on_enter() override;
    void on_exit() override;
    std::string name() const override { return "OBSERVE"; }

private:
    std::shared_ptr<spdlog::logger> logger_;
};
