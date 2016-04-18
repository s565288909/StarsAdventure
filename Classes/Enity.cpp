#include "Enity.h"

USING_NS_CC;

Enity::Enity(){}

Enity::~Enity(){}

void Enity::setNode(Node* node){
	this->m_Node = node;
}

Node* Enity::getNode(){
	return m_Node;
}