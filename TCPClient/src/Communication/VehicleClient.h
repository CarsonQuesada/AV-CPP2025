#pragma once
#include <atomic>
#include <thread>

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

    inline ClientConnectionState getConnectionState() { return connectionState; }
    inline void cancelConnectAttempt() {
        if (connectionState == ClientConnectionState::Connecting || connectionState == ClientConnectionState::Reconnecting)
        cancelConnect.store(true); 
    }

    inline std::optional<Message> tryRecvMsg() { return receiveQueue.tryPop(); }
    inline Message waitRecvMsg() { return receiveQueue.waitAndPop(); }
    inline void sendMsg(Message msg) { sendQueue.push(msg); }
    inline double getConnectionSpeed() { return pingRTTms.load(); } // Returns connection speed as a double in ms

private:
    bool start();
    void stop();
    bool connect(const std::string& ipAddr);
    void startWorkerThreads();
    void stopWorkerThreads();
    void runSupervisor();
    void runReceive();
    void runTransmit();
    void runRegularUpdate();
    bool performHandshake();
    uint64_t getCurrentTimeNs(); // For ping messages


    TCPClient client;
    ThreadSafeQueue<Message> sendQueue;
	ThreadSafeQueue<Message> receiveQueue;
    std::mutex threadStartMutex;
    std::thread supervisorThread;
    std::thread receiveThread;
    std::thread transmitThread;
    std::thread updateThread;

    std::atomic<bool> reconnectRequested = false;
    std::atomic<bool> stopFlag = true;
    std::atomic<bool> shutdownFlag = false;
    std::atomic<ClientConnectionState> connectionState = ClientConnectionState::Disconnected;
    std::atomic<bool> cancelConnect = false;
    std::atomic<double> pingRTTms;

    std::atomic<ConnectionType> lastConnectionType = ConnectionType::None;
    std::thread connectionThread;
};