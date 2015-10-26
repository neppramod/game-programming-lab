#pragma once
#ifndef GENERIC_WINDOW
#define GENERIC_WINDOW

#include <string>
using std::string;
using std::wstring;

class Logger;

class GenericWindow
{
protected:
	Logger *logger;

public:
	GenericWindow();
	virtual ~GenericWindow();

	virtual bool create() = 0;
	virtual void show() = 0;
	virtual void listenForEvents() = 0;
	virtual void exit() = 0;

	void setLogger(Logger *logger) { this->logger = logger; }
	const Logger* getLogger() const { return this->logger; }

	void log(string text, bool debug=false);
	void log(wstring text, bool debug=false);
};

#endif

