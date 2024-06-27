#include "Bitset.h"

Bitset::Bitset(unsigned N)
{
	bucketsCount = N / elementsInBucket + 1;
	buckets = new uint8_t[bucketsCount]{ 0 };
	this->N = N;
}

//Bitset::Bitset(unsigned n, uint8_t*&& buckets, unsigned bucketsCount)
//{
//	N = n;
//	this->buckets = buckets;
//	buckets = nullptr;
//	this->bucketsCount = bucketsCount;
//}

void Bitset::free()
{
	delete[] buckets;//!!!
	bucketsCount = 0;
	buckets = nullptr;
}
void Bitset::moveFrom(Bitset&& other)
{
	buckets = other.buckets;
	other.buckets = nullptr;

	bucketsCount = other.bucketsCount;
	other.bucketsCount = 0;

	N = other.N;
	other.N = 0;
}
void Bitset::copyFrom(const Bitset& other)
{
	buckets = new uint8_t[other.bucketsCount];
	for (size_t i = 0; i < other.bucketsCount; i++)
		buckets[i] = other.buckets[i];
	bucketsCount = other.bucketsCount;
	N = other.N;
}

Bitset::Bitset(const Bitset& other)
{
	copyFrom(other);
}
Bitset& Bitset::operator=(const Bitset& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Bitset::Bitset(Bitset&& other)
{
	moveFrom(std::move(other));
}
Bitset& Bitset::operator=(Bitset&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
Bitset::~Bitset()
{
	free();
}

unsigned Bitset::getN() const
{
	return N;
}

unsigned Bitset::getBucketIndex(unsigned num) const
{
	return num / elementsInBucket;
}

void Bitset::add(unsigned num)
{
	if (num > N)
		return;

	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = num % elementsInBucket;

	uint8_t mask = 1 << bitIndex;
	buckets[bucketIndex] |= mask;

}

void Bitset::remove(unsigned num)
{

	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = num % elementsInBucket;

	uint8_t mask = ~(1 << bitIndex);
	buckets[bucketIndex] &= mask;
}

bool Bitset::contains(unsigned num) const
{
	unsigned bucketIndex = getBucketIndex(num);
	unsigned bitIndex = num % elementsInBucket;

	uint8_t mask = 1 << bitIndex;

	return buckets[bucketIndex] & mask;
}
