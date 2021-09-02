#pragma once
#ifndef __OBJECT_POOL_H__
#include <list>
#include <algorithm>


//It is template class to create different type of this class
template<class T> class ObjectPool {

private:
	//Creating list of any type called object pool
	std::list<T*> _objectPool;
public:
	ObjectPool() {}

public:
	
	//If pool is empty, create new of that type, else take from list
	T* GetObjectFromPool() {
		if (_objectPool.empty()) {
			return new T;
		}

		else {
			T* selectedObject = _objectPool.front();
			_objectPool.pop_front();
			return selectedObject;
		}
	}
	;
	
	//This function takes parameter of any type, push it back to pool
	void ReturnObjectToPool(T* returnedObject) {
		if(!(std::find(_objectPool.begin(), _objectPool.end(), returnedObject) != _objectPool.end())){
			_objectPool.push_back(returnedObject);
		}
		
		
	};
};


#endif //  __OBJECT_POOL_H__