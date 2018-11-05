#include <vector>
#include <sstream>
#include <iterator>
#include <fstream>

#include "include/Command.cpp"
#include "include/RBTree.cpp"

namespace Reader{

	std::vector<std::string> readfile(std::string filename){

		std::vector<std::string> v;
		std::ifstream inFile;
		std::string sLine;

		inFile.open(filename);

		if (!inFile) {
    		std::cerr << "Unable to open file " + filename;
    		exit(1);   
		}

		while (!inFile.eof()){
			getline(inFile, sLine);
			v.push_back(sLine);
		}

		inFile.close();

		return v;
	}
}

namespace Interpreter{

	std::vector<std::string> split(std::string str){

		std::vector<std::string> cont;

    	std::istringstream iss(str);
    	std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(cont));
		
		return cont;
	}

	std::vector<Command> createCommands(std::vector<std::string> commands){

		std::vector<Command> instructions;

		for(std::string line : commands){

			if(line==""){
				break;
			}

			std::vector<std::string> words = split(line);

			if(words.size()<2){
				std::cout << "Bad formatted instruction" << std::endl;
			}else{

				Operation operation;

				if(words[1]=="0"){
					operation=Operation::REMOVE;
				}else{
					if(words[1]=="1"){
						operation=Operation::INSERT;
					}else{
						std::cout << "Bad formatted instruction" << std::endl;
					}
				}

				instructions.push_back(Command(words[0],operation));
			}

		}

		return instructions;
	}

	std::vector<Command> createCommandsFromFile(std::string filename){
		return createCommands(Reader::readfile(filename));
	}
}