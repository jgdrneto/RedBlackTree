#ifndef _RB_TREE_
#define _RB_TREE_

#include <string>
#include <algorithm>
#include "RBElement.cpp"

class RBTree{
public:

	RBElement* root;
	RBElement* NIL;

	RBTree(){
		this->NIL = new RBElement("NIL", Color::BLACK);
		this->root = this->NIL;
	}

	std::string toStringPreOrder(){
		std::string value = this->auxToStringPreOrder(root);
	
		if(!value.empty()){
			value.pop_back();
		}

		return value;
	} 

	std::string toStringSortKeys(){
		std::string sortKeysPrint;

		std::vector<std::string> keys = this->getKeys(this->root);

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

		if(y->right != this->NIL){
			y->right->parent = x; 
		}

		y->parent = x->parent; 
		
		if(x->parent == this->NIL){
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

		if(y->left != this->NIL){
			y->left->parent = x; 
		}

		y->parent = x->parent; 
		
		if(x->parent == this->NIL){
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

		RBElement* y = this->NIL;
		RBElement* x = this->root;

		while( x != this->NIL){
			y = x;
			if (z->value.compare(x->value)<0){
				x = x->left;
			}else{
				x = x->right;
			}
		}

		z->parent = y;

		if(y == this->NIL){
			this->root = z;
		}else if (z->value.compare(y->value)<0){
			y->left = z;
		}else{
			y->right = z;
		}
		
		z->right = this->NIL;
		z->left = this->NIL;
		z->color = Color::RED;

		this->insertFixUp(z);
	}

	void transplant(RBElement* u, RBElement* v){
		
		if(u->parent == this->NIL){
			this->root = v;
		}else if(u == u->parent->left){
			u->parent->left = v;
		}else{
			u->parent->right = v;
		}
		
		v->parent = u->parent;
	}

	RBElement* minimun(RBElement* x){

		while(x->left != this->NIL){
			x = x->left;
		}
		
		return x;	
	}

	void removeFixUp(RBElement* x){
		while( x != this->root && x->color == Color::BLACK){
			if(x == x->parent->left){
				RBElement* w = x->parent->right;

				if(w->color == Color::RED){
					w->color = Color::BLACK;
					x->parent->color = Color::RED;
					this->leftRotate(x->parent);
					w = x->parent->right;
				}

				if(w->left->color == Color::BLACK && w->right->color == Color::BLACK){
					w->color = Color::RED;
					x = x->parent;
				}else{
					if(w->right->color == Color::BLACK){
						w->left->color = Color::BLACK;
						w->color = Color::RED;
						this->rightRotate(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = Color::BLACK;
					w->right->color = Color::BLACK;
					this->leftRotate(x->parent);
					x = this->root;
				}
			}else{

				RBElement* w = x->parent->left;

				if(w->color == Color::RED){
					w->color = Color::BLACK;
					x->parent->color = Color::RED;
					this->rightRotate(x->parent);
					w = x->parent->left;
				}

				if(w->left->color == Color::BLACK && w->right->color == Color::BLACK){
					w->color = Color::RED;
					x = x->parent;
				}else{ 
					if(w->left->color == Color::BLACK){
						w->right->color = Color::BLACK;
						w->color = Color::RED;
						this->leftRotate(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = Color::BLACK;
						
					w->left->color = Color::BLACK;
		
					this->rightRotate(x->parent);
					x = this->root;
				}
			}
		}
		x->color = Color::BLACK;
	}

	void remove(RBElement* z){
		RBElement* y = z;
		Color yOriginalColor = y->color;
		
		RBElement* x = nullptr;
		
		if(z->left == this->NIL){
			x = z->right;
			this->transplant(z,z->right);
		}else if(z->right == this->NIL){
			x = z->left;
			this->transplant(z,z->left);
		}else{
			y = this->minimun(z->right);
			
			yOriginalColor = y->color;
			x = y->right;

			if(y->parent == z){
				x->parent = y;				
			}else{
				this->transplant(y,y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			this->transplant(z,y);

			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}

		if(yOriginalColor == Color::BLACK){
			this->removeFixUp(x);
		}

		delete(z);
	}

	RBElement* search(std::string name){
		RBElement* x = this->root;

		while( x != this->NIL && x->value!=name){
			
			if (name.compare(x->value)<0){
				x = x->left;
			}else{
				x = x->right;
			}
		}

		if(x == this->NIL){
			std::cout << "SEARCH : Element with the name " << name << " was not found in tree " << std::endl;
			return nullptr;
		}else{
			std::cout << "SEARCH : Element with the name " << name << " was found in tree " << std::endl;
			std::cout << "SEARCH : Element : " << x->toString() << std::endl;
			return x;	
		}
	}

private:

	std::vector<std::string> getKeys(RBElement* element){
		
		std::vector<std::string> keys;

		if(element != this->NIL){

			keys.push_back(element->value);

			std::vector<std::string> l = this->getKeys(element->left);
			std::vector<std::string> r = this->getKeys(element->right);

			keys.insert(keys.end(), l.begin(), l.end());
			keys.insert(keys.end(), r.begin(), r.end());
		}

		return keys;
	}

	std::string auxToStringPreOrder(RBElement* element){

		if(element == nullptr || element == this->NIL){
			return "";
		}else{

			std::string toString;
			
			toString+=element->toString()+"\n";

			if(element->left != this->NIL){
				toString+=auxToStringPreOrder(element->left);
			}
			
			if(element->right != this->NIL){
				toString+=auxToStringPreOrder(element->right);
			}

			return toString;
		}
	}

};

#endif