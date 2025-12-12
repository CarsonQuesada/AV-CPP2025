#pragma once

// VehicleClient.h
// Manages TCP connection to the vehicle server, sending and receiving messages.
// 
// Reqirements:
// - Shared/Keys.h configured with the server's IP and port.
// 
// Current Issues:
// - Initial handshake does not send anything. Max speed may not be set on first
//   connect. Current solution is to just set these paramters when you reconnect
// - Some messages are not handled at all (e.g., ErrorMessage).
//
// Notes:
// - Thread safety is ensured via atomic variables and mutexes where necessary.
// - Uses a recieve thread and a transmit thread to handle communication. Receive 
//   thread handles auto reconnect attempt when a disconnect is detected.

#include <atomic>
#include <thread>
#include <mutex>
#include <optional>

#include "TCPClient.h"
#include "Shared/Message.h"
#include "ThreadSafeQueue.h"

enum class ClientConnectionState {
    Disconnected,
    Connecting,
    Connected,
    Reconnecting
};

enum class ConnectionType { None, Local, Remote };

class VehicleClient
{
public:
    VehicleClient();
    ~VehicleClient();

    bool connectLocally();
    bool connectRemotely();
    bool reconnect(); // Only use if there was a previous connection
    void disconnect();

    inline ClientConnectionState getConnectionState() const noexcept {
        return connectionState.load(std::memory_order_acquire);
    }
    inline ConnectionType getConnectionType() const noexcept {
        return currConnectionType.load(std::memory_order_acquire);
    }
    inline bool isConnected() const noexcept {
        return getConnectionState() == ClientConnectionState::Connected;
    }
    inline void cancelConnectAttempt() noexcept {
        const auto s = connectionState.load(std::memory_order_acquire);
        if (s == ClientConnectionState::Connecting || s == ClientConnectionState::Reconnecting) {
            cancelConnect.store(true, std::memory_order_release);
        }
    }

    inline std::optional<Message> tryRecvMsg() { return receiveQueue.tryPop(); }
    inline Message waitRecvMsg() { return receiveQueue.waitAndPop(); }
    inline void sendMsg(Message&& msg) { sendQueue.push(std::move(msg)); }
    inline void sendMsg(const Message& msg) { sendQueue.push(msg); }
    inline double getConnectionSpeed() { return pingRTTms.load(); } // Returns connection speed as a double in ms

private:
    bool onConnect();
    void stop();
    bool connect(const std::string& ipAddr, const int port);
    
    void startWorkerThreads();
    void stopWorkerThreads();
    void runReceive();
    void runTransmit();
    void runRegularUpdate();

    bool performHandshake();
    void onServerDisconnect();
    uint64_t getCurrentTimeNs(); // For ping messages


    TCPClient client;
    ThreadSafeQueue<Message> sendQueue;
	ThreadSafeQueue<Message> receiveQueue;
    std::mutex threadStartMutex;
    std::thread receiveThread;
    std::thread transmitThread;
    std::thread updateThread;

    std::atomic<bool> stopFlag{false};
    std::atomic<bool> shutdownFlag{false};
    std::atomic<ClientConnectionState> connectionState{ClientConnectionState::Disconnected};
    std::atomic<bool> cancelConnect{false};
    std::atomic<double> pingRTTms{0.0};

    std::atomic<ConnectionType> lastConnectionType{ConnectionType::None};
    std::atomic<ConnectionType> currConnectionType{ConnectionType::None};
    std::thread connectionThread;
};