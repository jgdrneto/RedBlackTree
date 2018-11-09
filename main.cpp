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
	
	for(Command c : Interpreter::createCommandsFromFile(argv[1])){
		
		std::cout << "==================================" << std::endl;

		std::cout << "Comando: " << c.toString() << std::endl;

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
				}

			break;
		}

		std::cout << "==================================" << std::endl;
			
		std::cout << "Árvore" << std::endl;
			
		std::cout << t.toStringPreOrder() << std::endl;

		std::cout << "==================================" << std::endl;

	}
	
	/*
	RBElement no("pedra",Color::BLACK);
	RBElement no2("sapato",Color::BLACK);
	RBElement no3("algodao",Color::BLACK);
	RBElement no4("garoto",Color::BLACK);
	RBElement no5("sigaa",Color::BLACK);
	
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

	t.insert(&no5);

	std::cout << "inseriu no5" << std::endl;

	std::cout << "Impressão da árvore" << std::endl;

	//std::cout << no3.toString() << std::endl;

	std::cout << t.toStringPreOrder() << std::endl;

	std::cout << "===========================" << std::endl;

	std::cout << "Chaves ordenadas" << std::endl;

	std::cout << t.printSortKeys() << std::endl;
	
	std::cout << "===========================" << std::endl;

	//RBElement* element = t.search("remove");

	t.remove(&no);

	std::cout << "remove no1" <<std::endl;

	//std::cout << no2.toString() << std::endl;

	std::cout << t.toStringPreOrder() << std::endl;
	*/
	return 0;
}