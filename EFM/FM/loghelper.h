#pragma once
#ifndef LOGHELPER_H
#define LOGHELPER_H
#include <iostream>
static std::string getCurrentTimeStamp() {
	std::time_t now = std::time(nullptr);
	struct tm timeInfo;
	localtime_s(&timeInfo, &now);
	char timeStr[80];
	std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &timeInfo);
	return timeStr;
}
#endif