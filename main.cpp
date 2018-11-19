#include <iostream>

#include "functions.cpp"

int main(int argc, char const *argv[]){	
	
	if(argc<2){
		std::cerr << "Enter the filename";
    	exit(1);
	}
	
	RBTree t;
	
	for(Command c : Interpreter::createCommandsFromFile(argv[1])){
		
		std::cout << "##########################################" << std::endl;

		std::cout << "COMMAND: " << c.toString() << std::endl;

		RBElement* element = t.search(c.value);
	
		switch(c.operation){
			case Operation::INSERT:
				
				if(element==nullptr){
					t.insert(new RBElement(c.value,Color::BLACK));
				}

			break;
			case Operation::REMOVE:
				
				if(element!=nullptr){

					t.remove(element);	
					
					std::cout << "==================================" << std::endl;
			
					std::cout << "RBPrint:" << std::endl;
			
					std::cout << t.toStringSortKeys() << std::endl;

					std::cout << "==================================" << std::endl;
			
					std::cout << "RBCheck:" << std::endl;
			
					std::cout << t.toStringPreOrder() << std::endl;

					std::cout << "==================================" << std::endl;	
						
				}

			break;
		}

		std::cout << "##########################################" << std::endl;
		std::cout << "" << std::endl;
	}
	
	return 0;
}