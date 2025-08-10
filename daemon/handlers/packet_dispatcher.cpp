#include "packet_dispatcher.hpp"
#include "discovery_handler.hpp"
#include "decision_handler.hpp"
#include "correction_handler.hpp"
#include "observation_handler.hpp"
#include "../../common/logger.hpp"

PacketDispatcher::PacketDispatcher() {}

bool PacketDispatcher::parse_header(const std::unordered_map<std::string, std::string>& packet, PacketHeader& header) {
    // Required fields: message_id, type, source, destination, sequence
    try {
        header.message_id = packet.at("message_id");
        header.type = packet.at("type");
        header.source = packet.at("source");
        header.destination = packet.at("destination");
        header.sequence = std::stoi(packet.at("sequence"));
        return true;
    } catch (std::exception& e) {
        Logger::error("PacketDispatcher: header parsing error: " + std::string(e.what()));
        return false;
    }
}

bool PacketDispatcher::dispatch(const std::unordered_map<std::string, std::string>& packet) {
    PacketHeader header;
    if (!parse_header(packet, header)) {
        Logger::error("PacketDispatcher: invalid/corrupt packet dispatch aborted.");
        return false;
    }

    Logger::info("PacketDispatcher: dispatching packet type: " + header.type + " (id=" + header.message_id + ")");
    try {
        route_packet(header, packet);
    } catch (std::exception& exc) {
        Logger::error("PacketDispatcher: dispatch error for type '" + header.type + "': " + exc.what());
        return false;
    }
    return true;
}

void PacketDispatcher::route_packet(const PacketHeader& header, const std::unordered_map<std::string, std::string>& packet) {
    std::string type = header.type;
    std::transform(type.begin(), type.end(), type.begin(), ::tolower);
    if (type == "discovery") {
        handle_discovery_packet(packet);
    } else if (type == "decision") {
        handle_decision_packet(packet);
    } else if (type == "correction") {
        handle_correction_packet(packet);
    } else if (type == "observation" || type == "telemetry") {
        handle_observation_packet(packet);
    } else {
        Logger::warning("PacketDispatcher: Unknown message type '" + type + "'");
        throw std::runtime_error("Unknown message type");
    }
}
