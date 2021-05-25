#include "Debugger.h"


Debugger* Debugger::instance = 0;

Debugger* Debugger::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new Debugger();
    }
    return instance;
}


std::string Debugger::DebugVec3(glm::vec3 a)
{
    std::string b = "X: " + std::to_string(a.x) + " -- Y: " + std::to_string(a.y) + " -- Z: " + std::to_string(a.z);
    return b;
}

void Debugger::OpenLogger()
{
	logFile = fopen(logFilePath.c_str(), "w");
	if (logFile == nullptr)
	{
		std::cout << "ENGINE::Debugger.cpp::Log file failed to load at path: " + logFilePath <<  std::endl;
	}

}

void Debugger::AppendLogger(std::string fromFile, std::string outputString)
{
	if(logFile == nullptr) return;

	std::string ty = LogTypeToString(type);

	std::string s;
	auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	s = " " + fromFile + " :: " + outputString + "\n";
	std::string t = ctime(&time);
	t.erase(std::remove(t.begin(), t.end(), '\n'), t.end());
	//time, type, string to append
	fprintf(logFile, "%s :: %s :: %s",t.c_str(), ty.c_str(), s.c_str());
}

void Debugger::CloseLogger()
{
	if(logFile == nullptr) return;
	fclose(logFile);
	std::cout << "Debugger.cpp::Log File written to: " << logFilePath << std::endl;
}

std::string Debugger::LogTypeToString(LogType t)
{
	std::string out;
	switch (t)
	{
		case LogType::INFO:
			out = "INFO";
			break;
		case LogType::WARNING:
			out = "WARNING";
			break;
		case LogType::ERROR:
			out = "ERROR";
			break;
		case LogType::ENGINE:
			out = "ENGINE";
			break;
		case LogType::ALL:
			out = "ALL";
			break;
		default:
			out = "UNKNOWN";
			break;
	}
	return out;
}




