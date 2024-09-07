#include "../include/ThreadSecond.h"


void ThreadSecond::WorkThreadSecond(bool WorkThreadFirstFlag, std::mutex& mt, std::condition_variable& cv, bool& dataFlag, std::string& buffer, Socket* SocketObject)
{
	while (WorkThreadFirstFlag) {
		std::unique_lock<std::mutex> ul(mt);
		cv.wait(ul, [&dataFlag] { return dataFlag; });

		std::string data = std::move(buffer);
		dataFlag = false;

		ul.unlock();

		std::cout << "Data: " << data << std::endl;
		int sum = 0;
		for (char ch : data) {
			if (isdigit(ch)) {
				sum += (ch - '0');
			}
		}
		std::cout << "Sum: " << sum << std::endl << std::endl;

		SocketObject->sendData(std::to_string(sum));

		cv.notify_one();
	}
}