#include <iostream>

#include "functions.cpp"

void testes(){
	RBElement element1("raiz",Color::BLACK);
    RBElement element2("opa2",Color::RED);

    element1.left =  new RBElement("esquerda",Color::BLACK);
    element1.right =  new RBElement("direita",Color::BLACK);
    
    element1.left->left = new RBElement("esqueda2",Color::BLACK);
    element1.left->parent = &element1;


    element1.right->right = new RBElement("direita2",Color::BLACK);
    element1.right->right->right = new RBElement("direita3",Color::BLACK);

    std::cout << element1.toString() << std::endl;
    std::cout << element2.toString() << std::endl;
    std::cout << element1.left->toString() << std::endl;
}

int main(int argc, char const *argv[]){	
	
	if(argc<2){
		std::cerr << "Enter the filename";
    	exit(1);
	}

	RBTree t;
	/*
	for(Command c : Interpreter::createCommandsFromFile(argv[1])){
		
		RBElement* element = rbtree.search(c.value);

		switch(c.operation){
			case Operation::INSERT:
				
				if(element==nullptr){
					t.insert(new RBElement(c.value,Color::BLACK));
				}

			break;
			case Operation::REMOVE:
				
				if(element!=nullptr){

				}

			break;
		}

		std::cout << c.toString() << std::endl;
	}
	*/
	
	RBElement no("c",Color::BLACK);
	RBElement no2("adc",Color::BLACK);
	RBElement no3("abc",Color::BLACK);
	RBElement no4("d",Color::BLACK);
	
	//e.left = new RBElement("a", Color::RED);
	//e.right = new RBElement("p", Color::RED);

	t.insert(&no);

	std::cout << "inseriu no1" << std::endl;

	t.insert(&no2);

	std::cout << "inseriu no2" << std::endl;

	t.insert(&no3);

	std::cout << "inseriu no3" << std::endl;

	t.insert(&no4);

	std::cout << "inseriu no4" << std::endl;

	std::cout << "Impressão da árvore" << std::endl;

	//std::cout << no3.toString() << std::endl;

	std::cout << t.toStringPreOrder() << std::endl;

	std::cout << "===========================" << std::endl;


	std::cout << t.printSortKeys() << std::endl;
	
	/*
	t.remove(&no);

	std::cout << "remove no1" <<std::endl;

	//std::cout << no2.toString() << std::endl;

	std::cout << t.toStringPreOrder() << std::endl;
	*/
	return 0;
}