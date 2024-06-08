#pragma once
#include <iostream>

const unsigned elementsInBucket = sizeof(uint8_t) * 8;

class Bitset
{
	uint8_t* buckets = nullptr;
	unsigned bucketsCount = 0;
	unsigned N = 0;

	void free();
	void moveFrom(Bitset&& other);
	void copyFrom(const Bitset& other);

	unsigned getBucketIndex(unsigned num) const;
public:
	Bitset(unsigned n);
	Bitset(unsigned n, uint8_t*&& buckets, unsigned bucketsCount);

	Bitset(const Bitset& other);
	Bitset& operator=(const Bitset& other);
	
	Bitset(Bitset&& other);
	Bitset& operator=(Bitset&& other);

	~Bitset();

	unsigned getN() const;

	void add(unsigned num);
	void remove(unsigned num);
	bool contains(unsigned num) const;

};

