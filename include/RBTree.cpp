#ifndef _RB_TREE_
#define _RB_TREE_

#include <string>
#include <algorithm>
#include "RBElement.cpp"

class RBTree{
public:

	RBElement* root;
	
	RBTree(){
		this->root = new RBElement();
	}

	RBTree(RBElement& nRoot){
		this->root = &nRoot;
	}

	std::string toStringPreOrder(){
		std::string value = this->auxToStringPreOrder(root);
	
		if(!value.empty()){
			value.pop_back();
		}

		return value;
	} 

	std::string printSortKeys(){
		std::string sortKeysPrint;

		std::vector<std::string> keys = this->takeKeys(this->root);

		std::sort(keys.begin(), keys.end());

		for(std::string key : keys){
			
			sortKeysPrint+=key;
			
			if(key!=keys.back()){
				sortKeysPrint+=" ";
			}

		}

		return sortKeysPrint;
	} 

	void rightRotate(RBElement* x){
		
		RBElement* y = x->left;
		x->left = y->right;

		if(!y->right->isNil()){
			y->right->parent = x; 
		}

		y->parent = x->parent; 
		
		if(x->parent->isNil()){
			this->root = y;
		}else if(x == x->parent->left){
			x->parent->left = y;
		}else{
			x->parent->right = y;
		}
		
		y->right = x;
		x->parent = y;

	}

	void leftRotate(RBElement* x){
		
		RBElement* y = x->right;
		x->right = y->left;

		if(!y->left->isNil()){
			y->left->parent = x; 
		}

		y->parent = x->parent; 
		
		if(x->parent->isNil()){
			this->root = y;
		}else if(x == x->parent->left){
			x->parent->left = y;
		}else{
			x->parent->right = y;
		}
		
		y->left = x;
		x->parent = y;
	}

	void insertFixUp(RBElement* z){
		while(z->parent->color == Color::RED){

			if(z->parent == z->parent->parent->left){

				RBElement* y = z->parent->parent->right;

				if(y->color == Color::RED){

					z->parent->color = Color::BLACK;
					y->color = Color::BLACK;
					z->parent->parent->color = Color::RED;
					z = z->parent->parent;
				}else{
					if(z == z->parent->right){
						z = z->parent;
						leftRotate(z);
					}
					z->parent->color = Color::BLACK;
					z->parent->parent->color = Color::RED;
					rightRotate(z->parent->parent);
				}
			}else{

				RBElement* y = z->parent->parent->left;

				if(y->color == Color::RED){

					z->parent->color = Color::BLACK;
					y->color = Color::BLACK;
					z->parent->parent->color = Color::RED;
					z = z->parent->parent;
				}else{
					if(z == z->parent->left){
						z = z->parent;
						rightRotate(z);
					}
					z->parent->color = Color::BLACK;
					z->parent->parent->color = Color::RED;
					leftRotate(z->parent->parent);
				}
			}
		}
			
		this->root->color = Color::BLACK;
	}

	void insert(RBElement* z){

		RBElement* y = new RBElement();
		RBElement* x = this->root;

		while( !x->isNil()){
			y = x;
			if (z->value.compare(x->value)<0){
				x = x->left;
			}else{
				x = x->right;
			}
		}

		z->parent = y;

		if(y->isNil()){
			this->root = z;
		}else if (z->value.compare(y->value)<0){
			y->left = z;
		}else{
			y->right = z;
		}
		
		z->right = new RBElement();
		//z->right->parent = z;
		z->left = new RBElement();
		//z->right->parent = z;
		z->color = Color::RED;

		this->insertFixUp(z);
	}

	void transplant(RBElement* u, RBElement* v){
		
		std::cout << "z: " << u->toString() << std::endl;
		std::cout << "y: " << v->toString() << std::endl;

		if(u->parent->isNil()){
			this->root = v;

			//std::cout << "root: " << this->root->toString() << std::endl;

		}else if(u == u->parent->left){
			u->parent->left = v;
		}else{
			u->parent->right = v;
		}
		
		v->parent = u->parent;
		
		std::cout << "za: " << u->toString() << std::endl;
		std::cout << "ya: " << v->toString() << std::endl;
	}

	RBElement* minimun(RBElement* x){

		while(!x->left->isNil()){
			x = x->left;
		}
		
		return x;	
	}

	void removeFixUp(RBElement* x){
		while( x != this->root && x->color == Color::BLACK){
			if(x == x->parent->left){
				RBElement* w = x->parent->right;
				
				std::cout << "lw: "<< w->toString() << std::endl;

				if(w->color == Color::RED){
					w->color = Color::BLACK;
					x->parent->color = Color::RED;
					this->leftRotate(x->parent);
					w = x->parent->right;
				}

				std::cout << "lw: "<< w->toString() << std::endl;

				if(w->left->color == Color::BLACK && w->right->color == Color::BLACK){
					w->color = Color::RED;
					x = x->parent;
				}else if(w->right->color == Color::BLACK){
					w->left->color = Color::BLACK;
					w->color = Color::RED;
					this->rightRotate(w);
					w = x->parent->right;
				}else{
					w->color = x->parent->color;
					x->parent->color = Color::BLACK;
					w->right->color = Color::BLACK;
					this->leftRotate(x->parent);
					x = this->root;
				}
			}else{

				RBElement* w = x->parent->left;

				std::cout << "rw: "<< w->toString() << std::endl;

				if(w->color == Color::RED){
					w->color = Color::BLACK;
					x->parent->color = Color::RED;
					this->rightRotate(x->parent);
					w = x->parent->left;
				}

				std::cout << "rw2: "<< w->toString() << std::endl;

				if(w->left->color == Color::BLACK && w->right->color == Color::BLACK){
					w->color = Color::RED;
					x = x->parent;
					std::cout << "rw3: "<< w->toString() << std::endl;
				}else if(w->left->color == Color::BLACK){
					w->left->color = Color::BLACK;
					w->color = Color::RED;
					this->leftRotate(w);
					w = x->parent->left;

					std::cout << "rw4: "<< w->toString() << std::endl;

				}else{
					w->color = x->parent->color;
					x->parent->color = Color::BLACK;
					w->left->color = Color::BLACK;
					this->leftRotate(x->parent);
					x = this->root;

					std::cout << "rw5: "<< w->toString() << std::endl;
				}
			}
		}

		x->color = Color::BLACK;

	}

	void remove(RBElement* z){
		std::cout << "z: " << z->toString() << std::endl;
		RBElement* y = z;
		Color yOriginalColor = y->color;
		
		RBElement* x = nullptr;
		
		if(z->left->isNil()){
			x = z->right;
			this->transplant(z,z->right);
		}else if(z->right->isNil()){
			x = z->left;
			this->transplant(z,z->left);
		}else{
			y = this->minimun(z->right);
			
			std::cout <<"y: " << y->toString() << std::endl;
			
			yOriginalColor = y->color;
			x = y->right;

			std::cout <<"x: " << x->toString() << std::endl;

			if(y->parent == z){
				x->parent = y;
				std::cout <<"x2: " << x->toString() << std::endl;				
			}else{
				this->transplant(y,y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			/*
			std::cout << "z: " << z->toString() << std::endl;
			std::cout << "y: " << y->toString() << std::endl;
			*/
			this->transplant(z,y);
			/*
			std::cout << "z2: " << z->toString() << std::endl;
			std::cout << "y2: " << y->toString() << std::endl;
			*/
			y->left = z->left;
			y->left->parent = y;
			y->color =  z->color;
			
			std::cout <<"y: " << y->toString() << std::endl;
			std::cout <<"x: " << x->toString() << std::endl;
			std::cout <<"ARVORE: " << this->toStringPreOrder() << std::endl;
		}

		if(yOriginalColor == Color::BLACK){

			std::cout << "Remove concertar: " << x->toString() << std::endl;
			
			std::cout << "corecao" << std::endl;

			this->removeFixUp(x);
		}

	}

	RBElement* search(std::string name){
		RBElement* x = this->root;

		while( !x->isNil() && x->value!=name){
			if (x->value.compare(name)<0){
				x = x->left;
			}else{
				x = x->right;
			}
		}

		if(x->isNil()){
			std::cout << "SEARCH : Element with the name : " << name << " was not found in the tree " << std::endl;
			return nullptr;
		}else{
			std::cout << "SEARCH : Element with the name : " << name << " was found in the tree " << std::endl;
			std::cout << "SEARCH : Element : " << x->toString() << std::endl;
			return x;	
		}
	}

private:

	std::vector<std::string> takeKeys(RBElement* element){
		
		std::vector<std::string> keys;

		if(!element->isNil()){

			keys.push_back(element->value);

			std::vector<std::string> l = takeKeys(element->left);
			std::vector<std::string> r = takeKeys(element->right);

			keys.insert(keys.end(), l.begin(), l.end());
			keys.insert(keys.end(), r.begin(), r.end());
		}

		return keys;
	}

	std::string auxToStringPreOrder(RBElement* element){

		if(element->isNil()){
			return "";
		}else{

			std::string toString;
			
			toString+=element->toString()+"\n";

			if(!element->left->isNil()){
				toString+=auxToStringPreOrder(element->left);
			}
			
			if(!element->right->isNil()){
				toString+=auxToStringPreOrder(element->right);
			}

			return toString;
		}
	}

};

#endif