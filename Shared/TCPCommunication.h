#pragma once

typedef uint16_t tcpHeader;

enum class ConnectionStatus
{
    Disabled = 0, Connected, Reconnecting
};