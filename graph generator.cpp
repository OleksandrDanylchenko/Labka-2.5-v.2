// LABKA 2.5 v.2 EDGES GENERATOR
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#define NOMINMAX
#include <Windows.h>

void putInfo();
void makeFullGR(std::ofstream&, const size_t& amountOfVertices);
void makeTrail(std::ofstream&, const size_t& amountOfVertices);
void makeTour(std::ofstream&, const size_t& amountOfVertices);
std::string getOutputFilePath();
size_t randomGenerator(size_t min, size_t max);

int main() {
	system("mode con COLS=700");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

	putInfo();

	try {
		std::string graphType = "";
		std::cout << "\nWhat type of graph do you want:" <<
			"\nFull plain (fp)" <<
			"\nOriented trail (otr)" << ", Oriented tour (oto)" << std::endl;
		while (true) {
			std::cout << ">> ";
			std::cin >> graphType;
			if (graphType != "fp" and graphType != "otr" and graphType != "oto")
				graphType.clear();
			else
				break;
		}

		unsigned char connected = ' ';
		if (graphType != "fp") {
			std::cout << "\nIs it connected? (Connected - C, Disconnected - D)" << std::endl;
			while (true) {
				std::cout << ">> ";
				std::cin >> connected;
				if (connected != 'C' and connected != 'c' and connected != 'D' and connected != 'd')
					connected = ' ';
				else
					break;
			}
		}

		int amountOfVertices = 0;
		while (true) {
			std::cout << "\nEnter how many vertices you want (<= 50000): ";
			std::cin >> amountOfVertices;
			if (amountOfVertices <= 0 or amountOfVertices > 50000) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			} else
				break;
		}

		std::ofstream outputFileS;
		while (true) {
			std::string outputFilePath = getOutputFilePath();
			outputFileS.open(outputFilePath);
			if (outputFileS.fail())
				outputFilePath.clear();
			else
				break;
		}

		if (graphType == "fp") {
			outputFileS << '1' << ' ' << amountOfVertices << std::endl;
			makeFullGR(outputFileS, amountOfVertices);
			return 0;
		}

		if (connected == 'C' or connected == 'c')
			if (graphType == "otr") {
				outputFileS << '1' << ' ' << amountOfVertices << std::endl;
				makeTrail(outputFileS, amountOfVertices);
			} else if(graphType == "oto") {
				outputFileS << '1' << ' ' << amountOfVertices << std::endl;
				makeTour(outputFileS, amountOfVertices);
			} else
				throw std::logic_error("Inappropriate type of graph");
		else {
			if (graphType == "otr" or graphType == "oto")
				outputFileS << '1' << ' ' << amountOfVertices << std::endl;
			else
				throw std::logic_error("Inappropriate type of graph");
			for (size_t i = 0; i < amountOfVertices; ++i) {
				outputFileS << randomGenerator(0, size_t(amountOfVertices) - 1) << ' '
					<< randomGenerator(0, size_t(amountOfVertices) - 1) << std::endl;
			}
		}
	} catch (const std::exception& ex) {
		std::cerr << "\n\t" << ex.what() << std::endl << std::endl;
		system("pause");
		return -1;
	}
	system("pause");
	return 0;
}

void putInfo() {
	std::cout << "#########################################\n" <<
		"# GRAPH EDGES GENERATOR 2000ULTRARANDOM #\n" <<
		"#########################################" << std::endl;
}

std::string getOutputFilePath() {
	std::string filePath = "";
	std::cout << "\nEnter the path to the output file or its name: ";
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(std::cin, filePath);
	//if file path is empty -> save the output to the out.txt in the root folder
	std::string rootFolder = "D:/Studying/Programming/LABS/Labka 2.5 v.2/Labka 2.5 text files/";
	if (filePath.empty())
		filePath = rootFolder + "out.txt";
	//if user didn't provided full adress -> create a new file in the root folder
	else if (filePath.find('\\') == std::string::npos and filePath.find('/') == std::string::npos) {
		filePath.insert(0, rootFolder); // prepend address of the root folder
		filePath.append(".txt"); // append extension of a text file
	}
	return filePath;
}

void makeFullGR(std::ofstream& ofs, const size_t& amountOfVertices) {
	for (size_t i = 0; i < amountOfVertices; ++i)
		for (size_t j = 0; j < amountOfVertices; ++j)
			if (i != j) 
				ofs << i << ' ' << j << std::endl;
}

void makeTrail(std::ofstream& ofs, const size_t& amountOfVertices) {
	std::vector<size_t> verticesArr(amountOfVertices);
	for (size_t i = 0; i < amountOfVertices; ++i)
		verticesArr[i] = i;
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(verticesArr.begin(), verticesArr.end(), g);
	size_t k = 0;
	while ((k + 1) < amountOfVertices) {
		ofs << verticesArr[k] << ' ';
		ofs << verticesArr[++k] << std::endl;
	}
}

void makeTour(std::ofstream& ofs, const size_t& amountOfVertices) {
	std::vector<size_t> verticesArr(amountOfVertices);
	for (size_t i = 0; i < amountOfVertices; ++i)
		verticesArr[i] = i;
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(verticesArr.begin(), verticesArr.end(), g);
	size_t k = 0;
	while (true) {
		ofs << verticesArr[k] << ' ';
		if ((k + 1) != amountOfVertices)
			ofs << verticesArr[++k] << std::endl;
		else {
			ofs << verticesArr[0] << std::endl;
			break;
		}
	}
}

size_t randomGenerator(size_t min, size_t max) {
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
	return dist(rng);
}