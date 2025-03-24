#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <icmpapi.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Iphlpapi.lib")


std::mutex cout_mutex;
std::atomic<int> total_sent(0);
std::atomic<int> total_received(0);
std::atomic<long long> total_time(0);

void ping(const std::string& target, int num_pings) {
    HANDLE icmp = IcmpCreateFile();
    if (icmp == INVALID_HANDLE_VALUE) {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cerr << "Failed to create ICMP handle\n";
        return;
    }

    char send_data[32] = "ping test";
    DWORD reply_size = sizeof(ICMP_ECHO_REPLY) + sizeof(send_data);
    std::vector<char> reply_buffer(reply_size);
    sockaddr_in dest_addr{};
    dest_addr.sin_family = AF_INET;
    inet_pton(AF_INET, target.c_str(), &dest_addr.sin_addr);

    int sent = 0, received = 0;
    long long time_sum = 0;

    for (int i = 0; i < num_pings; ++i) {
        auto start = std::chrono::steady_clock::now();
        DWORD result = IcmpSendEcho(icmp, dest_addr.sin_addr.s_addr, send_data, sizeof(send_data), nullptr,
                                    reply_buffer.data(), reply_size, 1000);
        auto end = std::chrono::steady_clock::now();

        sent++;
        if (result > 0) {
            received++;
            long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            time_sum += duration;
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "[Thread " << std::this_thread::get_id() << "] Ping to " << target
                      << " successful, time: " << duration << " ms\n";
        }
    }

    IcmpCloseHandle(icmp);
    total_sent += sent;
    total_received += received;
    total_time += time_sum;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <hostname/IP> <THREADS> <Pings per thread>\n";
        return 1;
    }

    std::string target = argv[1];
    int num_threads = std::stoi(argv[2]);
    int num_pings = std::stoi(argv[3]);

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(ping, target, num_pings);
    }

    for (auto& t : threads) {
        t.join();
    }

    int lost = total_sent - total_received;
    double loss_percentage = (total_sent > 0) ? (lost * 100.0 / total_sent) : 0.0;
    double avg_time = (total_received > 0) ? (total_time / static_cast<double>(total_received)) : 0.0;

    std::cout << "\n--- Ping Statistics for " << target << " ---\n";
    std::cout << "Packets: Sent = " << total_sent
              << ", Received = " << total_received
              << ", Lost = " << lost
              << " (" << loss_percentage << "% loss)\n";
    std::cout << "Average Response Time: " << avg_time << " ms\n";

    return 0;
}
