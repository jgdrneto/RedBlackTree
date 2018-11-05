#ifndef _COMMAND_
#define _COMMAND_

#include <string>

typedef enum Operation{
        REMOVE,
        INSERT
}Operation;


std::string getNameOfOperation(Operation operation){
	
	std::string value;

	switch(operation){
		case Operation::REMOVE :
			value = "REMOVE";
		break;
		case Operation::INSERT:
			value = "INSERT";
		break;
	}

	return value;
}

class Command{
public:
	std::string value;
	Operation operation;
	
	Command(std::string nValue,Operation nOperation) : value(""), operation(Operation::INSERT){
		this->value = nValue;
		this->operation = nOperation;
	}

	std::string toString(){
		return "( " + value + ", " + getNameOfOperation(this->operation) + " )";  
	}

};

#endif