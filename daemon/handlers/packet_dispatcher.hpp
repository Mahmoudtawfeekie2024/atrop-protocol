#pragma once
#include <string>
#include <unordered_map>

// Simple packet header structure
struct PacketHeader {
    std::string message_id;
    std::string type;
    std::string source;
    std::string destination;
    int sequence;
};

// ATROP Packet Dispatcher
class PacketDispatcher {
public:
    PacketDispatcher();
    bool dispatch(const std::unordered_map<std::string, std::string>& packet);

    // Parses header fields from a packet (simple map-based for demonstration)
    static bool parse_header(const std::unordered_map<std::string, std::string>& packet, PacketHeader& header);

private:
    // Helper to route based on type
    void route_packet(const PacketHeader& header, const std::unordered_map<std::string, std::string>& packet);
};
