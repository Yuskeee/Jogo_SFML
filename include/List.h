#ifndef _LIST_H
#define _LIST_H

#include <string>

//Classe Element em formato Template------------------------------------------------
template<class T1>
class Element{
private:
	T1 info; //guarda elemento do tipo T1

//lista duplamente encadeada
	Element<T1> *next;
	Element<T1> *prev;

public:
	Element(T1& info = NULL);
	~Element();

//funções set
	void setInfo(const T1& info);
	void setNext(Element<T1> *element = NULL);
	void setPrev(Element<T1> *element = NULL);

//funções get
	T1 getInfo();
	Element<T1> *getNext() const;
	Element<T1> *getPrev() const;

};

template<class T1>
Element<T1>::Element(T1& info){
	setInfo(info);
	next = NULL;
	prev = NULL;
}

template<class T1>
Element<T1>::~Element(){
	next = NULL;
	prev = NULL;
}

template<class T1>
void Element<T1>::setInfo(const T1& info){//referencia escondida
	this->info = info;
}

template<class T1>
void Element<T1>::setNext(Element<T1> *element){
	next = element;
}

template<class T1>
void Element<T1>::setPrev(Element<T1> *element){
	prev = element;
}

template<class T1>
T1 Element<T1>::getInfo(){
	return info;
}

template<class T1>
Element<T1>* Element<T1>::getNext() const{
	return next;
}

template<class T1>
Element<T1>* Element<T1>::getPrev() const{
	return prev;
}

//Classe List em formato Template-----------------------------------------------------
template<class T2>
class List{
public:
//tipo iterator para classe List percorrer elementos. Referencia: https://internalpointers.com/post/writing-custom-iterators-modern-cpp (Acesso em: 05/04/2021 (DD/MM/YYYY))
	class Iterator{
	private:
		Element<T2> *element;
	public:
		Iterator(Element<T2> *element = NULL);
		~Iterator();

		Element<T2>* getElement();
		Element<T2>* getNext();
		Element<T2>* getPrev();

//sobrecarga de operadores para iterator
		T2 operator*();
		T2 operator->();
		Iterator& operator++();
		Iterator operator++(int);
		Iterator& operator--();
		Iterator operator--(int);
		bool operator==(const Iterator& iterator) const;
		bool operator!=(const Iterator& iterator) const;
	};
private:
	Element<T2> *firstElement;
	Element<T2> *lastElement;
	long int n_elements;

public:
	List();
	~List();

//metodos push
	void push_back(T2 type);
	void push_front(T2 type);

//metodos pop //nao retornam nada
	void pop_back();
	void pop_front();

//metodos com iterator
	Iterator begin();
	Iterator end();
	Iterator erase(Iterator iterator);

//retorna tamanho
	long int size() const;

//retorna se esta vazia ou nao
	bool empty() const;

//limpa a lista
	void clear();

//operador sobrecarregado para []
	T2 operator[](int n);


void listAll(){
	printf("\n\nLIST FROM %d to %d:\n", firstElement, lastElement);

	    
    Element<T2> *aux = firstElement;
    for(int n = n_elements; n != 0; n--){
		printf("prev: %d, this:%d, next:%d\n", aux->getPrev(), aux, aux->getNext());
        if(aux)
			aux = aux->getNext();
    }
    printf("LISTING DONE\n\n");
	
			
}


};

/*~~~~~~~~~~~~~~~~class Iterator*/
template<class T2>
List<T2>::Iterator::Iterator(Element<T2> *element){
	this->element = element;
}

template<class T2>
List<T2>::Iterator::~Iterator(){
//nao faz nada
}

template<class T2>
Element<T2>* List<T2>::Iterator::getElement(){
	return element;
}

template<class T2>
Element<T2>* List<T2>::Iterator::getNext(){
	return element->getNext();
}

template<class T2>
Element<T2>* List<T2>::Iterator::getPrev(){
	return element->getPrev();
}

template<class T2>
T2 List<T2>::Iterator::operator*(){
	return element->getInfo();
}

template<class T2>
T2 List<T2>::Iterator::operator->(){
	return *(*this);//usa o operator* de Iterator
}

template<class T2>
typename List<T2>::Iterator& List<T2>::Iterator::operator++(){
	if(element)
		element = element->getNext();
	return *this;
}

template<class T2>
typename List<T2>::Iterator List<T2>::Iterator::operator++(int){
	Iterator iterator = *this;
	++(*this);
	return iterator;
}

template<class T2>
typename List<T2>::Iterator& List<T2>::Iterator::operator--(){
	if(element)
		element = element->getPrev();
	return *this;
}

template<class T2>
typename List<T2>::Iterator List<T2>::Iterator::operator--(int){
	Iterator iterator = *this;
	--(*this);
	return iterator;
}

template<class T2>
bool List<T2>::Iterator::operator==(const Iterator& iterator) const{
		return element == iterator.element;
}

template<class T2>
bool List<T2>::Iterator::operator!=(const Iterator& iterator) const{
		return element != iterator.element;
}

/*~~~~~~~~~~~~~~~~class List*/

template<class T2>
List<T2>::List(){
    n_elements = 0;
	firstElement = NULL;
	lastElement = NULL;
}

template<class T2>
List<T2>::~List(){
	clear();
}

template<class T2>
void List<T2>::push_back(T2 type){
	Element<T2>* element = new Element<T2>(type);
	if(!firstElement)
		firstElement = element;
	else{
		lastElement->setNext(element);
		element->setPrev(lastElement);
	}
	lastElement = element;
	n_elements++;
}

template<class T2>
void List<T2>::push_front(T2 type){
	Element<T2>* element = new Element<T2>(type);
	if(!firstElement)
		lastElement = element;
	else{
		firstElement->setPrev(element);
		element->setNext(firstElement);
	}
	firstElement = element;
	n_elements++;
}

template<class T2>
void List<T2>::pop_back(){
	if(lastElement){
		Element<T2> *aux = lastElement->getPrev();
		delete lastElement;
		if(aux){
			aux->setNext();
			lastElement = aux;
		}
		else{
			firstElement = NULL;
			lastElement = NULL;
		}
		n_elements--;
	}
}

template<class T2>
void List<T2>::pop_front(){
	if(firstElement){
		Element<T2> *aux = firstElement->getNext();
		delete firstElement;
		if(aux){
			aux->setPrev();
			firstElement = aux;
		}
		else{
			firstElement = NULL;
			lastElement = NULL;
		}
		n_elements--;
	}
}

template<class T2>
typename List<T2>::Iterator List<T2>::begin(){
	return Iterator(firstElement);
}

template<class T2>
typename List<T2>::Iterator List<T2>::end(){
	return Iterator(NULL);
}

template<class T2>
typename List<T2>::Iterator List<T2>::erase(Iterator iterator){
//exceções
	if(iterator == end())//caso null
		return iterator;
	
	if(iterator == begin()){//caso first
		pop_front();
		return iterator;
	}
	if(iterator.getNext() == NULL){//caso last
		pop_back();
		return end();
	}

//caso "normal"
	iterator.getNext()->setPrev(iterator.getPrev());
	iterator.getPrev()->setNext(iterator.getNext());
	Element<T2> *aux = iterator.getElement();
	iterator++;
	n_elements--;
	delete aux;
	return iterator;
}

template<class T2>
long int List<T2>::size() const{
	return n_elements;
}

template<class T2>
bool List<T2>::empty() const{
	return n_elements == 0;
}

template<class T2>
void List<T2>::clear(){
	while(!empty()){
        Element<T2> *aux = firstElement->getNext();
        delete firstElement;
        firstElement = aux;
		n_elements--;
	}
}

template<class T2>
T2 List<T2>::operator[](int n){
    if(n < n_elements){
        Element<T2> *aux = firstElement;
    	for(; n != 0; n--){
            aux = aux->getNext();
    	}
    	return aux->getInfo();
    }
    else
        exit(1);
}

#endif
