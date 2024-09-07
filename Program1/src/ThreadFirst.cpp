#include "../include/ThreadFirst.h"


void ThreadFirst::WorkThreadFirst(bool WorkThreadSecondFlag, std::mutex& mt, std::condition_variable& cv, bool& dataFlag, std::string& buffer)
{
	std::string str;
	while (WorkThreadSecondFlag) {
		std::cout << "Input: ";
		std::getline(std::cin, str);
		std::unique_lock<std::mutex> ul(mt);

		if (WorkingWithStringObj.CheckingString(str)) {
			buffer = std::move(str);
			dataFlag = true;
			cv.notify_one();
			cv.wait(ul, [&dataFlag] { return !dataFlag; });
		}
		else {
			std::cout << "Invalid string." << std::endl;
		}
	}
}