#include "tnahpch.h"
#include "Debugger.h"

namespace tnah {

	tnah::Debugger* tnah::Debugger::instance = 0;

	tnah::Debugger* tnah::Debugger::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new Debugger();
		}
		return instance;
	}

	std::string tnah::Debugger::RP3DVec3ToString(rp3d::Vector3 p)
	{
		std::string s = "X: " + std::to_string(p.x) + " -- Y: " + std::to_string(p.y) + " -- Z: " + std::to_string(p.z);
		return s;
	}


	std::string tnah::Debugger::DebugVec3(glm::vec3 a)
	{
		std::string b = "X: " + std::to_string(a.x) + " -- Y: " + std::to_string(a.y) + " -- Z: " + std::to_string(a.z);
		return b;
	}

	glm::vec3 tnah::Debugger::ConvertPlayerToTerrainPosition(glm::vec3 playerPosition, float terrainSize, float vertexHeight)
	{
		float worldx, worldz, worldToTerrainScaleFactor;
		worldToTerrainScaleFactor = terrainSize / 409.0f;
		worldx = playerPosition.x * worldToTerrainScaleFactor;
		worldz = playerPosition.z * worldToTerrainScaleFactor;
		glm::vec3 terrainPos = glm::vec3(worldx, vertexHeight, worldz);
		return terrainPos;
	}

	void tnah::Debugger::OpenLogger()
	{
		errno_t err;
#if _WIN32
		if ((err = fopen_s(&logFile, logFilePath.c_str(), "w") != 0))
		{
			std::cout << "ENGINE::Debugger.cpp::Log file failed to load at path: " + logFilePath << std::endl;
		}
#elif __APPLE__

		logFile = fopen(logFilePath.c_str(), "w");
		if (logFile == nullptr)
		{
			std::cout << "ENGINE::Debugger.cpp::Log file failed to load at path: " + logFilePath << std::endl;
		}
#endif
	}

	void tnah::Debugger::AppendLogger(std::string fromFile, std::string outputString)
	{
		if (logFile == nullptr) return;

		std::string ty = LogTypeToString(type);

		std::string s, t;
		auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		s = " " + fromFile + " :: " + outputString + "\n";
#if _WIN32
		char buffer[256];
		t = ctime_s(buffer, 256, &time);
#elif _APPLE_
		t = ctime(&time);
#endif
		t.erase(std::remove(t.begin(), t.end(), '\n'), t.end());
		//time, type, string to append
		fprintf(logFile, "%s :: %s :: %s", t.c_str(), ty.c_str(), s.c_str());
	}

	void tnah::Debugger::CloseLogger()
	{
		if (logFile == nullptr) return;
		fclose(logFile);
		std::cout << "Debugger.cpp::Log File written to: " << logFilePath << std::endl;
	}

	std::string tnah::Debugger::LogTypeToString(LogType t)
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
		case LogType::ERR:
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




}