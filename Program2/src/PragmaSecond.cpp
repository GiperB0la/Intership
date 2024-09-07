#include "../include/PragmaSecond.h"


void PragmaSecond::Start()
{
	while (true) {
        if (client.Connection()) {
            client.ProcessingData();
        }
        std::cout << "Waiting for connection." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}