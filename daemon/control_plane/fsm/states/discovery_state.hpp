#pragma once

#include "../base_state.hpp"
#include <memory>
#include <string>
#include <spdlog/spdlog.h>

// DISCOVERY state for the ATROP FSM
class DiscoveryState : public BaseState {
public:
    explicit DiscoveryState(std::shared_ptr<spdlog::logger> logger);

    void on_enter() override;
    void on_exit() override;
    std::string name() const override { return "DISCOVERY"; }

private:
    std::shared_ptr<spdlog::logger> logger_;
};
