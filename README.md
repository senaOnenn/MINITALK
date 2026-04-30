# 💬 Minitalk - Bit-stream Communication via UNIX Signals

Minitalk is a small-scale data exchange system developed as part of the 42 curriculum. The project demonstrates asynchronous communication between a client and a server using only **UNIX signals** (SIGUSR1 and SIGUSR2).

## 🕹️ Project Overview
The system consists of two distinct programs:
*   **Server:** Once launched, it displays its Process ID (PID) and remains in a listening state to reconstruct incoming messages bit by bit.
*   **Client:** Communicates with the server by converting a given string into a sequence of bits and transmitting them using signals.

## 🛠️ Technical Stack
*   **Language:** C
*   **System Calls:** `kill()`, `sigaction()`, `pause()`, `getpid()`
*   **Concepts:** Bitwise operations, signal handling, and process synchronization.

## 🚀 Key Features
*   **Robust Signal Handling:** Uses `sigaction` for reliable signal management across different Unix environments.
*   **Bitwise Protocol:** Sends each character as a series of 8 bits (SIGUSR1 for 0, SIGUSR2 for 1).
*   **Efficiency:** Designed to handle strings of varying lengths with minimal latency.
*   **Error Prevention:** Displays clear PIDs to ensure the client targets the correct process.

## 📂 Project Structure
*   `server.c`: Main server logic for receiving signals and printing characters.
*   `client.c`: Main client logic for string-to-bit conversion and transmission.
*   `utils_client.c`: Helper functions specifically for the client side.
*   `minitalk.h`: Global header containing necessary includes and prototypes.
*   `minitalk-Tester/`: External testing suite used to verify the stability of the communication.
*   `Makefile`: Build script to compile both `client` and `server` executables.

## 💻 How to Run

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/senaOnenn/MINITALK.git](https://github.com/senaOnenn/MINITALK.git)
    cd MINITALK
    ```

2.  **Compile the project:**
    ```bash
    make
    ```

3.  **Launch the Server:**
    ```bash
    ./server
    ```
    *Take note of the PID printed in the terminal.*

4.  **Send a Message:**
    In a separate terminal, use the client with the server's PID:
    ```bash
    ./client [SERVER_PID] "Your message here"
    ```

---
*Developed as part of the 42 Türkiye Software Engineering Program.*
