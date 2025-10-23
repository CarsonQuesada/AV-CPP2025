#pragma once
#include <atomic>
#include <thread>

#include "TCPServer.h"
#include "Shared/Message.h"
#include "ThreadSafeQueue.h"

enum class ServerConnectionState {
    Disconnected,
    Listening,
    Connected
};

class VehicleServer
{
public:
    VehicleServer();
    ~VehicleServer();

    bool start();
    bool start(std::atomic_bool& cancelConnectFlag);
    void disconnect();

    inline std::optional<Message> tryRecvMsg() { return receiveQueue.tryPop(); }
    inline Message waitRecvMsg() { return receiveQueue.waitAndPop(); }
    inline void sendMsg(Message msg) { sendQueue.push(msg); }
    inline ServerConnectionState getConnectionState() { return connectionState.load(); }

private:
    void runReceive();
    void runTransmit();
    void runRegularUpdate();
    void runSupervisor();
    void startWorkerThreads();
    void stopWorkerThreads();
    bool performHandshake();
    void signalDisconnect();

    std::thread receiveThread, transmitThread, updateThread, supervisorThread;

    std::atomic<bool> stopFlag{true};
    std::atomic<bool> shutdownFlag{false};
    std::atomic<bool> reconnectRequested{false};
    std::atomic<ServerConnectionState> connectionState{ServerConnectionState::Disconnected};

    TCPServer server;
    ThreadSafeQueue<Message> receiveQueue;
	ThreadSafeQueue<Message> sendQueue;
};