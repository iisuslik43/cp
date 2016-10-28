#include "my_vector.h"
#include <iostream>
#include <stdexcept>
#include <utility>
#include <cstdio>

    MyVector::MyVector(){
	_cp=4;
	_sz=0;	
	_data=new int(_cp);
    }
    MyVector::MyVector(std::size_t init_capacity){
    	_cp=init_capacity;
	_sz=0;	
	_data=new int(_cp);
    }
    MyVector::~MyVector(){
	delete [] _data;
	_sz=0;
	_cp=0;
    }

    void MyVector::set(std::size_t index, int value){
	_data[index]=value;
    }
    int MyVector::get(std::size_t index){
	return _data[index];
    }
    std::size_t MyVector::size(){
        return _sz;
    }

    std::size_t MyVector::capacity(){
        return _cp;
    }

    void MyVector::reserve(std::size_t new_capacity){
	int *new_data=_data;
	new_data = new int(new_capacity);
	for(size_t i=0;i<_sz&&i<new_capacity;i++)
		new_data[i]=_data[i];
	delete [] _data;
	_cp=new_capacity;
	_sz=std::min(_sz,_cp);
	_data=new_data;
    }
    void MyVector::resize(std::size_t new_size){
	if(new_size>_cp)
	    reserve(new_size);
	if(new_size<=_sz)_sz=new_size;
	else{
	    for(size_t i=_sz;i<new_size;i++)
		_data[i]=0;	
	}
	_sz=new_size;
    }
  
    void MyVector::push_back(int value){
    	if(_sz==_cp)reserve(2*_cp);
	_data[_sz]=value;
	_sz++;
    }
    void MyVector::insert(std::size_t index, int value){
	if(_sz==_cp)reserve(_cp+1);
	for(size_t i=_sz-1;i>index;i--)_data[i]=_data[i-1];
	_data[index]=value;
    }
    void MyVector::erase(std::size_t index){
	for(size_t i=index;i<_sz-1;i++)_data[i]=_data[i+1];
	_sz--;
    }

