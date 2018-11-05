#ifndef _RB_ELEMENT_
#define _RB_ELEMENT_

#include <string>

typedef enum Color{
         BLACK,
         RED
}Color;

//Class of RBElement
class RBElement{
public:

	std::string value;
	Color color;
	RBElement* parent;
	RBElement* left;
	RBElement* right;

	RBElement() {
		this->parent= nullptr;
		this->left 	= nullptr;
		this->right = nullptr;
		this->value = "NIL";
		this->color = Color::BLACK;
	}

	RBElement(std::string nValue, Color nColor){
		this->parent= nullptr;
		this->left 	= nullptr;
		this->right = nullptr;
		this->value = nValue;
		this->color = nColor;
	}

	std::string toString(){
		std::string print;

		print+="(";

		if(this->parent==nullptr){
			print+="NIL";
		}else{
			print+=this->parent->value;
		}

		print+=", ";		

		print+=this->value;

		print+=", ";		

		if(this->color==Color::BLACK){
			print+="preto";
		}else{
			print+="vermelho";
		}

		print+=", ";

		print +=std::to_string(this->blackHeight());

		print+=", ";		

		if(this->left->isNil()){
			print+= "NIL";
		}else{
			print+=this->left->value;
		}

		print+=", ";

		if(this->right->isNil()){
			print+="NIL";
		}else{
			print+=this->right->value;
		}

		print +=")" ;
		return print;
	}

	bool isNil(){
		return this->value=="NIL" && this->color==Color::BLACK && this->left==nullptr && this->right==nullptr;
	}

	int blackHeight(){

		//std::cout << "Altura negra : " << this->value << std::endl;

		if(this->isNil()){
			return 0;
		}else{
			
			int l = auxBlackHeight(this->left);
			int r = auxBlackHeight(this->right);
			
			/*
			std::cout << this->value << std::endl;
			std::cout << "LEFT: "<< l << std::endl;
			std::cout << "RIGHT: " << r << std::endl;
			*/

			if(l>=r){
				return l;
			}else{
				return r;
			}
		}
	}

private:
	
	int auxBlackHeight(RBElement* root){

		if(root->isNil()){
			return 1;
		}else{
			
			int leftHeight = 0;
			int rightHeight = 0;

			if(root->color==Color::BLACK){
				leftHeight = 1;
				rightHeight = 1;
			}

			if(root->left != nullptr){
				leftHeight += auxBlackHeight(root->left); 
			}

			if(root->right != nullptr){
				rightHeight += auxBlackHeight(root->right); 
			}

			if(leftHeight>rightHeight){
				return leftHeight;
			}else{
				return rightHeight;
			}

		}

	}

};

#endif