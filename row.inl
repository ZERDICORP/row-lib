// row.inl

template <typename T>
row<T>::row()
{
	#ifdef ZER__ROW_DEBUG
		std::cout << "con: " << this << std::endl;
	#endif
	this -> arr = new T[this -> iLen];
}

template <typename T>
row<T>::row(int iLen)
{
	this -> arr = new T[iLen];
	this -> iLen = iLen;
}

template <typename T>
row<T>::row(int iLen, T fillItem)
{
	this -> arr = new T[iLen];
	for (int i = 0; i < iLen; ++i)
		arr[i] = fillItem;
	this -> iLen = iLen;
}

template <typename T>
row<T>::row(std::initializer_list<T> list) : row()
{
	int iNewLen = list.size();
	T* newRow = new T[iNewLen];
	int i = 0;
	for (auto item : list)
	{
		newRow[i] = item;
		i++;
	}
	delete[] this -> arr;
	this -> arr = newRow;
	this -> iLen = iNewLen;
}

template <typename T>
row<T>::~row()
{
	#ifdef ZER__ROW_DEBUG
		std::cout << "des: " << this << std::endl;
	#endif
	delete[] this -> arr;
}

// *

template <typename T>
void row<T>::start(T item)
{
	T* newRow = new T[this -> iLen + 1];
	for (int i = 1; i <= this -> iLen; ++i)
		newRow[i] = this -> arr[i - 1];
	newRow[0] = item;
	delete[] this -> arr;
	this -> arr = newRow;
	this -> iLen++;
}

template <typename T>
void row<T>::end(T item)
{
	T* newRow = new T[this -> iLen + 1];
	for (int i = 0; i < this -> iLen; ++i)
		newRow[i] = this -> arr[i];
	newRow[this -> iLen] = item;
	delete[] this -> arr;
	this -> arr = newRow;
	this -> iLen++;
}

template <typename T>
void row<T>::insert(int iIndex, T item)
{
	assert(iIndex >= 0 && iIndex < this -> iLen);
	T* newRow = new T[this -> iLen + 1];
	int j = 0;
	for (int i = 0; i <= this -> iLen; ++i)
		if (i - 1 == iIndex)
			newRow[i] = item;
		else
		{
			newRow[i] = this -> arr[j];
			++j;
		}
	delete[] this -> arr;
	this -> arr = newRow;
	this -> iLen++;
}

template <typename T>
void row<T>::del(int iIndex)
{
	assert(iIndex >= 0 && iIndex < this -> iLen);
	assert(this -> iLen - 1 >= 0);
	T* newRow = new T[this -> iLen - 1];
	int j = 0;
	for (int i = 0; i < this -> iLen; ++i)
		if (i != iIndex)
		{
			newRow[j] = this -> arr[i];
			j++;
		}
	delete[] this -> arr;
	this -> arr = newRow;
	this -> iLen--;
}

template <typename T>
void row<T>::cut(int iIndex, int iRange)
{
	assert(iIndex >= 0 && iIndex + iRange <= this -> iLen);
	int iNewLen = this -> iLen - iRange;
	T* newRow = new T[iNewLen];
	int j = 0;
	for (int i = 0; i < this -> iLen; ++i)
	{
		if (i < iIndex || i >= iIndex + iRange)
		{
			newRow[j] = this -> arr[i];
			j++;
		}
	}
	delete[] this -> arr;
	this -> arr = newRow;
	this -> iLen = iNewLen;
}

template <typename T>
void row<T>::swap(int iIndex1, int iIndex2)
{
	assert(iIndex1 >= 0 && iIndex1 < this -> iLen);
	assert(iIndex2 >= 0 && iIndex2 < this -> iLen);
	T temp = this -> arr[iIndex1];
	this -> arr[iIndex1] = this -> arr[iIndex2];
	this -> arr[iIndex2] = temp;
}

template <typename T>
void row<T>::reverse()
{
	for (int i = 0; i < this -> iLen / 2; ++i)
	{
		T temp = this -> arr[i];
		this -> arr[i] = this -> arr[this -> iLen - (i + 1)];
		this -> arr[this -> iLen - (i + 1)] = temp;
	}
}

template <typename T>
void row<T>::forward(int iOffset)
{
	for (int i = 0; i < iOffset; ++i)
	{
		T temp = this -> arr[this -> iLen - 1];
		for (int j = this -> iLen - 2; j >= 0 ; --j)
			this -> arr[j + 1] = this -> arr[j];
		this -> arr[0] = temp;
	}
}

template <typename T>
void row<T>::backward(int iOffset)
{
	for (int i = 0; i < iOffset; ++i)
	{
		T temp = this -> arr[0];
		for (int j = 1; j < this -> iLen; ++j)
			this -> arr[j - 1] = this -> arr[j];
		this -> arr[this -> iLen - 1] = temp;
	}
}

template <typename T>
void row<T>::clear()
{
	for (int i = this -> iLen - 1; i >= 0; --i)
		this -> del(i);
}

template <typename T>
void row<T>::operator +=(row& otherRow)
{
	int iNewLen = this -> iLen + otherRow.len();
	T* newRow = new T[iNewLen];
	int i = 0;
	for (; i < this -> iLen; ++i)
		newRow[i] = this -> arr[i];
	for (int j = 0; j < otherRow.len(); ++j, ++i)
		newRow[i] = otherRow[j];
	delete[] this -> arr;
	this -> arr = newRow;
	this -> iLen = iNewLen;
}

template <typename T>
void row<T>::operator =(row& otherRow)
{
	int iNewLen = otherRow.len();
	T* newRow = new T[iNewLen];
	for (int i = 0; i < iNewLen; ++i)
		newRow[i] = otherRow[i];
	delete[] this -> arr;
	this -> arr = newRow;
	this -> iLen = iNewLen;
}

// *

template <typename T>
int row<T>::index(T item)
{
	for (int i = 0; i < this -> iLen; ++i)
		if (this -> arr[i] == item)
			return i;
	return -1;
}

template <typename T>
int row<T>::count(T item)
{
	int iCount = 0;
	for (int i = 0; i < this -> iLen; ++i)
		if (this -> arr[i] == item)
			iCount++;
	return iCount;
}

// *

template <typename T>
bool row<T>::operator ==(row& otherRow)
{
	if (this -> iLen != otherRow.len())
		return false;
	for (int i = 0; i < this -> iLen; ++i)
		if (this -> arr[i] != otherRow[i])
			return false;
	return true;
}

template <typename T>
bool row<T>::operator !=(row& otherRow)
{
	if (this -> iLen != otherRow.len())
		return true;
	for (int i = 0; i < this -> iLen; ++i)
		if (this -> arr[i] != otherRow[i])
			return true;
	return false;
}

template <typename T>
bool row<T>::all(T item)
{
	for (int i = 0; i < this -> iLen; ++i)
		if (this -> arr[i] != item)
			return false;
	return true;
}

template <typename T>
bool row<T>::any(T item)
{
	for (int i = 0; i < this -> iLen; ++i)
		if (this -> arr[i] == item)
			return true;
	return false;
}

// *

template <typename T>
T row<T>::sum()
{
	int iSum = 0;
	for (int i = 0; i < this -> iLen; ++i)
		iSum += this -> arr[i];
	return iSum;
}

template <typename T>
T& row<T>::operator [](int iIndex)
{
	assert(iIndex >= 0 && iIndex < this -> iLen);
	return this -> arr[iIndex];
}

// *

template <typename T>
row<T> row<T>::slice(int iIndex, int iRange)
{
	assert(iIndex >= 0 && iIndex + iRange <= this -> iLen);
	row<T> newRow;
	for (int i = 0; i < this -> iLen; ++i)
		if (i >= iIndex && i < iIndex + iRange)
			newRow.end(this -> arr[i]);
	return newRow;
}

template <typename T>
row<T> row<T>::diff(row& otherRow)
{
	row<T> newRow;
	for (int i = 0; i < this -> iLen; ++i)
		if (!otherRow.count(this -> arr[i]) && !newRow -> count(this -> arr[i]))
			newRow -> end(this -> arr[i]);
	return newRow;
}

template <typename T>
row<T> row<T>::similar(row& otherRow)
{
	row<T> newRow;
	for (int i = 0; i < this -> iLen; ++i)
		if (otherRow.count(this -> arr[i]) && !newRow -> count(this -> arr[i]))
			newRow.end(this -> arr[i]);
	return newRow;
}

template <typename T>
row<T> row<T>::unique()
{
	row<T> newRow;
	for (int i = 0; i < this -> iLen; ++i)
	{
		int iCount = 0;
		for (int j = 0; j < this -> iLen; ++j)
			if (this -> arr[i] == this -> arr[j])
				iCount++;
		if (iCount == 1)
			newRow.end(this -> arr[i]);
	}
	return newRow;
}

template <typename T>
row<T> row<T>::repeat()
{
	row<T> newRow;
	for (int i = 0; i < this -> iLen; ++i)
	{
		int iCount = 0;
		for (int j = 0; j < this -> iLen; ++j)
			if (this -> arr[i] == this -> arr[j])
				iCount++;
		if (iCount > 1 && !newRow.count(this -> arr[i]))
			newRow.end(this -> arr[i]);
	}
	return newRow;
}

template <typename T>
row<T> row<T>::operator +(row& otherRow)
{
	int iNewLen = this -> iLen + otherRow.len();
	row<T> newRow;
	int i = 0;
	for (; i < this -> iLen; ++i)
		newRow.end(this -> arr[i]);
	for (int j = 0; j < otherRow.len(); ++j, ++i)
		newRow.end(otherRow[j]);
	return newRow;
}