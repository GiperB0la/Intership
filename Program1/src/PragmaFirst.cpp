#include "../include/PragmaFirst.h"


void PragmaFirst::Start()
{
	std::thread Thread1(&ThreadFirst::WorkThreadFirst, &ThreadFirstObject, std::ref(WorkThreadFirstFlag), std::ref(mt), std::ref(cv), std::ref(dataFlag), std::ref(buffer));
	std::thread Thread2(&ThreadSecond::WorkThreadSecond, &ThreadSecondObject, std::ref(WorkThreadSecondFlag), std::ref(mt), std::ref(cv), std::ref(dataFlag), std::ref(buffer), SocketObject);

	Thread1.join();
	Thread2.join();
}