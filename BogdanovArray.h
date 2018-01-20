#pragma once

template<class T>
class BogdanovArray{
public:
	using sizeType = size_t;
	using valueType = T;

	explicit BogdanovArray(const sizeType &capacity, const valueType &value) :
		myCapacity(capacity), mySize(0)
	{
		myData = new valueType[myCapacity];
		while (mySize < myCapacity)
			myData[mySize++] = value;
	}

	BogdanovArray(const std::initializer_list<valueType> &iniList){
		myData = new valueType[std::distance(iniList.begin(), iniList.end())];
		myCapacity = 0;
		for (auto i = iniList.begin(); i != iniList.end(); ++i)
			myData[myCapacity++] = *i;
		mySize = myCapacity;
	}

	BogdanovArray(const BogdanovArray &original){
		mySize = original.mySize;
		myCapacity = original.myCapacity;
		myData = new valueType[myCapacity];
		std::copy(original.myData, original.myData + original.mySize, myData);
	}

	BogdanovArray(BogdanovArray &&original) {
		mySize = original.mySize;
		myCapacity = original.myCapacity;
		myData = original.myData;
		original.mySize = 0;
		original.myCapacity = 0;
		original.myData = nullptr;
	}

	~BogdanovArray(){
		delete[] myData;
	}

	BogdanovArray &operator = (const BogdanovArray &original){
		if (this != &original){
			delete[] myData;
			mySize = original.mySize;
			myCapacity = original.myCapacity;
			myData = new valueType[myCapacity];
			std::copy(original.myData, original.myData + original.mySize, myData);
		}
		return *this;
	}

	BogdanovArray &operator = (BogdanovArray &&original){
		if (this != &original){
			delete[] myData;
			mySize = original.mySize;
			myCapacity = original.myCapacity;
			myData = original.myData;
			original.mySize = 0;
			original.myCapacity = 0;
			original.myData = nullptr;
		}
		return *this;
	}

	sizeType getSize() const{
		return mySize;
	}

	sizeType getCapacity() const{
		return myCapacity;
	}

	void pushBack(const valueType &val){
		if (mySize == myCapacity)
			changeCapacity();
		myData[mySize++] = val;
	}

	void resize(const sizeType size_, const valueType &val = 0){
		if (myCapacity <= size_){
			if (myCapacity < size_)
				changeCapacity();
			int dif = size_ - mySize;
			for (int i = 0; i < dif; ++i)
				pushBack(val);
		}
	}

	void reserve(const sizeType capacity_){
		if (myCapacity < capacity_){
			myCapacity = capacity_;
			valueType *newData = new valueType[myCapacity];
			std::copy(myData, myData + mySize, newData);
			delete[] myData;
			myData = newData;
		}
	}

	valueType const & at_(const sizeType val) const {
		checkExc(val);
		return myData[val];
	}

	valueType & at_(const sizeType val){
		checkExc(val);
		return myData[val];
	}

	valueType & operator[](const sizeType x)  {
		return myData[x];
	}

	valueType const & operator[](const sizeType x) const{
		return myData[x];
	}

private:
	void changeCapacity(){
		myCapacity *= 2;
		valueType *newData = new valueType[myCapacity];
		std::copy(myData, myData+mySize, newData);
		delete[] myData;
		myData = newData;
	}

	void checkExc(const sizeType val) const{
		if (val >= mySize)
			throw std::out_of_range("Index is out of range!");
	}

	sizeType mySize;
	sizeType myCapacity;
	valueType * myData;
};
