#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <Contender.h>

class DataLog
{
private:
	std::string m_name;
	std::string m_dataPath;
	std::string m_logPath;
	std::string m_dataName;
	std::string m_method;
	std::string m_params;
	std::time_t m_runTime;

	std::string DataName();
	
public:
	DataLog(std::string& dataPath, std::string& outDir, std::string method, std::string params);
	void WriteHeader();
	std::string NameGenerator();
	void LogEntry(std::string entry);

	std::vector<Point> GetPoints();
};

std::vector<Point> ReadDataFile(std::string& fPath);
