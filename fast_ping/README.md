
fping Documentation
=================================

`fping` is an optimized multi-threaded ping tool written in C++. It uses Windows ICMP APIs to ping a specified host and prints ping statistics.
It is designed for maximum efficiency and minimal system resource usage by avoiding external processes

Features
--------

*   Parallel ping requests using threads
*   Direct ICMP usage to avoid system command overhead
*   Calculates and prints packet loss percentage and average response time
*   Thread-safe output with mutex locking



Usage
-----

To use fping, compile the code and run it with the following arguments:

    fping.exe 

*   **hostname/IP**: The target hostname or IP address to ping.
*   **THREADS**: The number of threads to use for pinging (parallel requests).
*   **Pings per thread**: The number of pings each thread will perform.

Example Command
---------------

    fping.exe google.com 4 10

Output
------

After running the command, the tool will print individual ping results from each thread and, at the end, a summary including:

*   Total packets sent
*   Total packets received
*   Packet loss percentage
*   Average response time (in milliseconds)

Dependencies
------------

*   Windows SDK (for ICMP API and network functionality)
*   Standard C++ 17 libraries (threading, atomic operations, etc.)