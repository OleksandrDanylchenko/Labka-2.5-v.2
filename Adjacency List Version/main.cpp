// LABKA 2.5 v.2 List
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#define NOMINMAX
#include <Windows.h>

#include "D:\Studying\Programming\LABS\Labka 2.5 v.2\Headers\vList.h"
#include "D:\Studying\Programming\LABS\Labka 2.5 v.2\Headers\grRepres.h"

void studentInfo();
void labInfo();
bool readFromFile(const std::string&, GrA&);
std::string getFilePath(char);
std::string formatTime(std::clock_t);


int main() {
	system("mode con COLS=700");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

	studentInfo();
	labInfo();
	try {
		std::cout << "\nList representation:";
		GrL grList;
		std::clock_t generalTimeList = 0;
		while (true) {
			std::string inputFilePathL = getFilePath('i');
			std::clock_t timeStart = std::clock();
			if (readFromFile(inputFilePathL, grList)) {
				std::clock_t timeEnd = std::clock();
				std::cout << "Input in list, CPU time used: " << formatTime(timeEnd - timeStart) << std::endl;
				generalTimeList += (timeEnd - timeStart);
				break;
			} else
				continue;
		}
		while (true) {
			std::string outputFilePathM = getFilePath('o');
			std::ofstream outputS;
			outputS.open(outputFilePathM);
			if (outputS.fail())
				continue;

			std::vector <VList> outVlist;
			std::clock_t timeStart = std::clock();
			grList.SCC(outVlist); // problem solving method // finds Strongly Connected Components
			std::clock_t timeEnd = std::clock();

			for (auto&& i : outVlist)
				i.output(outputS);

			std::cout << "Output in list, CPU time used: " << formatTime(timeEnd - timeStart) << std::endl;
			generalTimeList += (timeEnd - timeStart);
			std::cout << "General list processing time: " << formatTime(generalTimeList) << std::endl << std::endl;
			system("pause");
			return 0;
		}
	} catch (std::exception& ex) {
		std::cerr << "\nError occured: " << ex.what() << std::endl;
		system("pause");
		return -1;
	}
}

void studentInfo() {
	std::cout << "Laboratory work 2 - 5 v.2 Graphs Processing\n" <<
		"Group: K-14 Danilchenko Alexander" << std::endl;
}

void labInfo() {
	std::cout << "\nThis programm reads information about graph from the input file and converts it to an adjacency list" <<
				 "\nAfter that it searches strongly connected components" << std::endl;
}

std::string getFilePath(char ioVar) {
	std::string filePath = "";
	if (std::cin.bad()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	if (ioVar == 'i')
		std::cout << "\nEnter the path to the input file: ";
	else // ioVar == 'o'
		std::cout << "\nEnter the path to the output file: ";
	getline(std::cin, filePath);
	std::string rootFolder = "D:/Studying/Programming/LABS/Labka 2.5 v.2/Labka 2.5 text files/";
	if (filePath.empty() and ioVar == 'o') {
		filePath.insert(0, rootFolder);
		filePath.append("out.txt");
	} else if (filePath.find('\\') == std::string::npos and filePath.find('/') == std::string::npos) {
		filePath.insert(0, rootFolder); // prepend address of the root folder
		filePath.append(".txt"); // append extension of a text file
	}
	return filePath;
}

bool readFromFile(const std::string& inputFilePath, GrA& g) {
	std::ifstream inputS;
	inputS.open(inputFilePath);
	if (inputS.fail())
		return false;
	bool isDir; size_t n;
	inputS >> isDir >> n;
	g.setisDir(isDir);
	if (!(g.create(n)))
		return false;
	size_t i, j;
	while (inputS >> i >> j)
		g.addArc(i, j);
	return true;
}

std::string formatTime(std::clock_t time) {
	std::string resultStr = "";
	size_t sec = time / 1000;
	resultStr.append(std::to_string(sec) + "s. ");
	size_t ms = time % 1000;
	resultStr.append(std::to_string(ms) + "ms.");
	return resultStr;
}
