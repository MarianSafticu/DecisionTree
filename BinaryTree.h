#ifndef ARBOREBINAR_H_
#define ARBOREBINAR_H_
#include <memory>
#include <queue>
#include <stack>
#include <iostream>
template <class TElem>
class Iterator{
public:
	virtual void next();
	virtual TElem element();
	virtual bool valid();
	virtual void prim();
	virtual ~Iterator();
};
template <class TElem>
class IteratorInordine;
template <class TElem>
class IteratorPostordine;
template <class TElem>
class IteratorLatime;
template <class TElem>
class IteratorPreordine;
template <class TElem>

//Node class
class Node{
private:
	TElem elem;
	std::shared_ptr<Node<TElem>> st, dr,parinte;
public:
	Node():elem{},st{nullptr},dr{nullptr},parinte{nullptr}{}
	Node(TElem e):elem{e},st{nullptr},dr{nullptr},parinte{nullptr}{}
	Node(const Node<TElem>& ot){
		elem=ot.elem;
		if(ot.st!=nullptr){
			st=std::make_shared<Node<TElem>>();
			*st=*ot.st;
		}
		else
			st=nullptr;
		if(ot.dr!=nullptr){
				dr=std::make_shared<Node<TElem>>();
				*dr=*ot.dr;
		}
		else
			dr=nullptr;
		if(ot.parinte!=nullptr){
				parinte=std::make_shared<Node<TElem>>();
				*parinte=*ot.parinte;
		}
		else
			parinte=nullptr;
	}
Node(const Node<TElem>&& ot){
			elem=ot.elem;
			if(ot.st!=nullptr){
				st=std::make_shared<Node<TElem>>();
				*st=*ot.st;
			}
			else
				st=nullptr;
			if(ot.dr!=nullptr){
					dr=std::make_shared<Node<TElem>>();
					*dr=*ot.dr;
			}
			else
				dr=nullptr;
			if(ot.parinte!=nullptr){
					parinte=std::make_shared<Node<TElem>>();
					*parinte=*ot.parinte;
			}
			else
				parinte=nullptr;
		}
	//Node(const Node<TElem>&& ot):st{ot->st},dr{ot->dr},parinte{ot->parinte},elem{ot->elem}{}
	Node<TElem>& operator=(const Node<TElem>& ot){
		elem=ot.elem;
		if(ot.st!=nullptr){
			st=std::make_shared<Node<TElem>>();
			*st=*ot.st;
		}
		else
			st=nullptr;
		if(ot.dr!=nullptr){
				dr=std::make_shared<Node<TElem>>();
				*dr=*ot.dr;
		}
		else
			dr=nullptr;
		if(ot.parinte!=nullptr){
				parinte=std::make_shared<Node<TElem>>();
				*parinte=*ot.parinte;
		}
		else
			parinte=nullptr;
		return *this;
	}
	void setElem(TElem e){
		elem=e;
	}
	TElem& element(){
		return elem;
	}
	void setStang(std::shared_ptr<Node<TElem>> st){
		this->st=st;
	}
	void setDrept(std::shared_ptr<Node<TElem>> dr){
		this->dr=dr;
	}
	void setParinte(std::shared_ptr<Node<TElem>> par){
		parinte=par;
	}
	std::shared_ptr<Node<TElem>>& getStang(){
		return st;
	}
	std::shared_ptr<Node<TElem>>& getDrept(){
		return dr;
	}
	std::shared_ptr<Node<TElem>>& getParinte(){
		return parinte;
	}
	virtual ~Node(){}
};

//the binary tree class 
template<class TElem>
class BinaryTree {
private:
	std::shared_ptr<Node<TElem>> rad;
public:
	BinaryTree():rad{nullptr}{}
	BinaryTree(TElem e){
		rad=std::make_shared<Node<TElem>>();
		rad->setElem(e);
	}
	BinaryTree (BinaryTree<TElem> st, TElem e, BinaryTree<TElem> dr){
		rad=std::make_shared<Node<TElem>>(e);
		rad->setStang(st.rad);
		rad->setDrept(dr.rad);
		st.rad->setParinte(rad);
		dr.rad->setParinte(rad);
	}
	BinaryTree(const BinaryTree<TElem> & ot){
		if(ot.rad==nullptr)
			this->rad=nullptr;
		else{
			std::queue<std::shared_ptr<Node<TElem>>> Q;
			std::queue<std::shared_ptr<Node<TElem>>> Q2;
			rad=std::make_shared<Node<TElem>>();
			Q.push(ot.rad);
			Q2.push(rad);
			while(!Q.empty()){
				auto x=Q.front();
				auto y=Q2.front();
				Q2.pop();
				Q.pop();
				if (x!=nullptr){
					*y=*x;

					if(x->getStang()!=nullptr){
						Q.push(x->getStang());
						auto st=std::make_shared<Node<TElem>>();
						y->setStang(st);
						Q2.push(y->getStang());
					}

					if(x->getDrept()!=nullptr){
						Q.push(x->getDrept());
						auto dr=std::make_shared<Node<TElem>>();
						y->setDrept(dr);
						Q2.push(y->getDrept());
					}
				}
				else{
					y=nullptr;
				}


			}
		}
	}
	BinaryTree<TElem>& operator=(const BinaryTree<TElem>& ot){
		if(ot.rad==nullptr)
			this->rad=nullptr;
		else{
			std::queue<std::shared_ptr<Node<TElem>>> Q;
			std::queue<std::shared_ptr<Node<TElem>>> Q2;
			rad=std::make_shared<Node<TElem>>();
			Q.push(ot.rad);
			Q2.push(rad);
			while(!Q.empty()){
				auto x=Q.front();
				auto y=Q2.front();
				Q2.pop();
				Q.pop();
				if (x!=nullptr){
					*y=*x;
					if(x->getStang()!=nullptr){
						Q.push(x->getStang());
						auto st=std::make_shared<Node<TElem>>();
						y->setStang(st);
						Q2.push(y->getStang());
					}

					if(x->getDrept()!=nullptr){
						Q.push(x->getDrept());
						auto dr=std::make_shared<Node<TElem>>();
						y->setDrept(dr);
						Q2.push(y->getDrept());
					}
				}
				else{
				y=nullptr;
				}

			}
		}
	return *this;
	}
	TElem& Element(){
		return rad->element();
	}
	BinaryTree<TElem> stang(){
		BinaryTree<TElem> a;
		a.rad=rad->getStang();
		return a;
	}
	BinaryTree<TElem> drept(){
			BinaryTree<TElem> a;
			a.rad=rad->getDrept();
			return a;
	}
	void adaugaSubStang(BinaryTree<TElem> st){
		rad->setStang(st.rad);
		//st.rad->setParinte(rad);
	}
	void adaugaSubDrept(BinaryTree<TElem> dr){
		rad->setDrept(dr.rad);
		//dr.rad->setParinte(rad);
	}
	void adaugaElement(TElem e){
		if(rad==nullptr)
			rad=std::make_shared<Node<TElem>>();
		rad->setElem(e);
	}
	std::shared_ptr<Node<TElem>> getRad(){
		return rad;
	}
	void setRad(std::shared_ptr<Node<TElem>> a){
		rad=a;
	}
	bool vid(){
		return (rad==nullptr);
	}
	friend class IteratorInordine<TElem>;
	IteratorInordine<TElem> iteratorInordine ()const{
		return IteratorInordine<TElem>(*this);
	}
	friend class IteratorLatime<TElem>;
	IteratorLatime<TElem> iteratorLatime ()const{
		return IteratorLatime<TElem>(*this);
	}
	friend class IteratorPostordine<TElem>;
	IteratorPostordine<TElem> iteratorPostordine ()const{
		return IteratorPostordine<TElem>(*this);
	}
	friend class IteratorPreordine<TElem>;
	IteratorPreordine<TElem> iteratorPreordine ()const{
		return IteratorPreordine<TElem>(*this);
	}
	virtual ~BinaryTree(){}
};



//iterators 
template <class TElem>
class IteratorInordine{
private:
	const BinaryTree<TElem>& ab;
	std::shared_ptr<Node<TElem>> curent;
	std::stack<std::shared_ptr<Node<TElem>>> s;
	IteratorInordine(const BinaryTree<TElem>& a):ab{a}{
		curent=ab.rad;
	}
public:
	friend class BinaryTree<TElem>;
	bool valid(){
		return (curent!=nullptr || !s.empty());
	}
	void next(){
		curent=curent->getDrept();
	}
	TElem element(){
		while(curent!=nullptr){
			s.push(curent);
			curent=curent->getStang();
		}
		curent=s.top();
		s.pop();
		return curent->element();
	}
	void prim();
};

template <class TElem>
class IteratorPreordine{
private:
	const BinaryTree<TElem>& ab;
	std::shared_ptr<Node<TElem>> curent;
	std::stack<std::pair<std::shared_ptr<Node<TElem>>,int>> s;
	IteratorPreordine(const BinaryTree<TElem>& a):ab{a}{
		curent=ab.rad;
	}
public:
	friend class BinaryTree<TElem>;
	bool valid(){
		return (curent!=nullptr || !s.empty());
	}
	void next(){
	}
	TElem element(){
		while(curent!=nullptr){
			s.push(std::make_pair(curent,0));
			curent=curent->getStang();
		}
		auto c=s.top();
		s.pop();
		curent=c.first;
		if(c.second==0)
		{
			s.push(std::make_pair(curent,1));
			curent=curent->getDrept();
			return element();
		}
		else{
			auto e=curent->element();
			curent=nullptr;
			return e;
		}
	}
	void prim();
};

template <class TElem>
class IteratorPostordine{
private:
	friend class BinaryTree<TElem>;
	const BinaryTree<TElem>& ab;
	std::shared_ptr<Node<TElem>> curent;
	std::stack<std::shared_ptr<Node<TElem>>> s;
	IteratorPostordine(const BinaryTree<TElem>& a):ab{a}{
		curent=ab.rad;
		s.push(ab.rad);
	}
public:
	bool valid(){
		return (!s.empty());
	}
	void next(){
	}
	TElem element(){
		if(!s.empty()){
			curent=s.top();
			s.pop();
			if(curent->getDrept()!=nullptr)
				s.push(curent->getDrept());
			if(curent->getStang()!=nullptr)
				s.push(curent->getStang());
		}
		return curent->element();
	}
	void prim();
};
template <class TElem>
class IteratorLatime{
private:
	const BinaryTree<TElem>& ab;
	std::shared_ptr<Node<TElem>> curent;
	std::queue<std::shared_ptr<Node<TElem>>> q;
	IteratorLatime(const BinaryTree<TElem>& a):ab{a}{
		curent=ab.rad;
		//q.push(curent);
	}
public:
	friend class BinaryTree<TElem>;
	bool valid(){
		return (curent!=nullptr);
	}
	void next(){
		if(q.empty()){
			curent=nullptr;
			return;
		}
		curent=q.front();
		q.pop();
	}
	TElem element(){
		if(curent->getStang()!=nullptr){
			q.push(curent->getStang());
		}
		if(curent->getDrept()!=nullptr){
			q.push(curent->getDrept());
		}
		return curent->element();
	}
	void prim();
};
#endif /* ARBOREBINAR_H_ */
