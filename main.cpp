#include <iomanip>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>


struct Process {
    int pId;
    long long startAddress;
    long long sizeMb;
    long long page;
    long long unusedMb;
};

// Sim class
using namespace std;
class MemorySim {
private:
    static const int totalPages = 100;
    static const int pageSizeMb = 160;
    static const int stAddress= 2000;

    int pages;
    long long currentAddress;
    vector<Process> processes;

public:
    // Constructor
    MemorySim() {
        pages = 0;
        currentAddress = stAddress;
        srand(time(0));
    }

    void userMemoryAllocation() {
        int pId = 1;

        while (pages < totalPages) {
            int randNum = rand() % 30 + 1;
            long long processSize = randNum * 80;
            int pages2 = ceil(((double) processSize) / pageSizeMb);

            // If there are no pages left
            if (pages + pages2 > totalPages) {
                break;
            }

            long long allocatedSpace = pages2 * pageSizeMb;
            long long unusedSpace = allocatedSpace - processSize;

            Process p;
            p.pId = pId++;
            p.startAddress = currentAddress;
            p.sizeMb = processSize;
            p.page = pages2;
            p.unusedMb = unusedSpace;

            processes.push_back(p);

            // Update memory
            pages += pages2;
            currentAddress += allocatedSpace;
        }
    }

    void print() {
        cout << left << setw(15) << "Process Id"
        << setw(25) << "Starting Memory Address"
        << setw(20) << "Process Size (Mb)"
        << setw(20) << "Unused Space (Mb)" << endl;

        cout << string(90, '-' ) << endl;

        for (auto p : processes) {
            cout << left << setw(15) << p.pId
            << setw(25) << p.startAddress
            << setw(20) << p.sizeMb
            << setw(20) << p.unusedMb << endl;
        }
    }
};


using namespace std;
int main() {
    MemorySim sim;
    sim.userMemoryAllocation();
    sim.print();
    return 0;
}