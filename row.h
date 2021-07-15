// row.h

#include <cassert>
#include <memory>
#include <iostream>

#ifndef ZER__ROW_MODEL
	#define ZER__ROW_MODEL
	// #define ZER__ROW_DEBUG
		namespace zer
		{
			template <typename T>
			class row
			{
				private:
					int iLen = 0;
					T* arr;

				public:
					row();
					row(int iLen);
					row(int iLen, T fillItem);
					row(row& otherRow) : row() {this -> operator =(otherRow);}
					row(row&& otherRow) : row() {this -> operator =(otherRow);}
					row(std::initializer_list<T> list);
					~row();

					void start(T item);
					void end(T item);
					void insert(int iIndex, T item);
					void del(int iIndex);
					void cut(int iIndex, int iRange);
					void swap(int iIndex1, int iIndex2);
					void reverse();
					void forward(int iOffset = 1);
					void backward(int iOffset = 1);
					void clear();
					void operator +=(row&& otherRow) {this -> operator +=(otherRow);}
					void operator +=(row& otherRow);
					void operator =(row&& otherRow) {this -> operator =(otherRow);}
					void operator =(row& otherRow);

					int index(T item);
					int count(T item);
					int len() {return this -> iLen;}

					bool operator ==(row&& otherRow) {return this -> operator ==(otherRow);}
					bool operator ==(row& otherRow);
					bool operator !=(row&& otherRow) {return this -> operator !=(otherRow);}
					bool operator !=(row& otherRow);
					bool operator >(row&& otherRow) {return this -> operator >(otherRow);}
					bool operator >(row& otherRow) {return this -> iLen > otherRow.len();}
					bool operator <(row&& otherRow) {return this -> operator <(otherRow);}
					bool operator <(row& otherRow) {return this -> iLen < otherRow.len();}
					bool operator >=(row&& otherRow) {return this -> operator >=(otherRow);}
					bool operator >=(row& otherRow) {return this -> iLen >= otherRow.len();}
					bool operator <=(row&& otherRow) {return this -> operator <=(otherRow);}
					bool operator <=(row& otherRow) {return this -> iLen <= otherRow.len();}
					bool range(int iIndex) {return iIndex >= 0 && iIndex < this -> iLen;}
					bool have(T item) {return this -> count(item);}
					bool all(T item);
					bool any(T item);

					T sum();
					T& operator [](int iIndex);
					T* start() {return &this -> arr[0];}
					T* end() {return &this -> arr[0] + this -> iLen;}

					row slice(int iIndex, int iRange);
					row diff(row&& otherRow) {return this -> diff(otherRow);}
					row diff(row& otherRow);
					row similar(row&& otherRow) {return this -> similar(otherRow);}
					row similar(row& otherRow);
					row unique();
					row repeat();
					row operator +(row&& otherRow) {return this -> operator +(otherRow);}
					row operator +(row& otherRow);
			};
			#include "row.inl"
		}
#endif