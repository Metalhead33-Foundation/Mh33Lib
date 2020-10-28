#ifndef FLOAT32X8_PRIVATE_HPP
#define FLOAT32X8_PRIVATE_HPP
#ifdef __AVX__
#include <cstdint>
#include <array>
extern "C" {
#include <immintrin.h>
}
namespace MH33 {
namespace SIMD {

class Float32x8_private {
public:
	typedef float* iterator;
	typedef const float* const_iterator;
	typedef std::array<float,8> ArrayType;
private:
	__m256 _data;
public:
	Float32x8_private();
	Float32x8_private(const ArrayType& a);
	Float32x8_private(const __m256& a);
	Float32x8_private(float a);
	Float32x8_private(const float* arr);
	Float32x8_private(float e0, float e1, float e2, float e3, float e4, float e5, float e6, float e7);
	Float32x8_private(const Float32x8_private& cpy); // Copy constructor;
	void operator=(const Float32x8_private& cpy); // Copy assignment
	void operator=(float a);
	void operator=(const float* arr);
	void operator=(const ArrayType& arr);
	void store(float* arr) const;
	Float32x8_private reciprocal() const;
	void set_to_reciprocal();

	// Compatibility with STL containers
	ArrayType& asArray();
	const ArrayType& asArray() const;
	float* data();
	const float* data() const;
	size_t size() const;
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	float& at(size_t i);
	const float& at(size_t i) const;
	float& operator[](size_t i);
	const float& operator[](size_t i) const;
	// Arithemetics and comparisons with other vectors
	void operator+=(const Float32x8_private& b);
	void operator-=(const Float32x8_private& b);
	void operator*=(const Float32x8_private& b);
	void operator/=(const Float32x8_private& b);
	void operator<<=(const Float32x8_private& b); // Minimum
	void operator>>=(const Float32x8_private& b); // Maximum
	Float32x8_private operator+(const Float32x8_private& b) const;
	Float32x8_private operator-(const Float32x8_private& b) const;
	Float32x8_private operator*(const Float32x8_private& b) const;
	Float32x8_private operator/(const Float32x8_private& b) const;
	bool operator==(const Float32x8_private& b) const;
	bool operator!=(const Float32x8_private& b) const;
	bool operator>(const Float32x8_private& b) const;
	bool operator>=(const Float32x8_private& b) const;
	bool operator<(const Float32x8_private& b) const;
	bool operator<=(const Float32x8_private& b) const;
	Float32x8_private operator<<(const Float32x8_private& b); // Minimum
	Float32x8_private operator>>(const Float32x8_private& b); // Maximum
	static Float32x8_private min(const Float32x8_private& a, const Float32x8_private& b); // Minimum
	static Float32x8_private max(const Float32x8_private& a, const Float32x8_private& b); // Maximum
	static Float32x8_private clamp(const Float32x8_private& a, const Float32x8_private& _min, const Float32x8_private& _max); // Clamp
	float vectorialMul(const Float32x8_private& b) const;
	// Arithemetics with scalars
	void operator+=(float b);
	void operator-=(float b);
	void operator*=(float b);
	void operator/=(float b);
	void operator<<=(float b); // Minimum
	void operator>>=(float b); // Maximum
	Float32x8_private operator+(float b) const;
	Float32x8_private operator-(float b) const;
	Float32x8_private operator*(float b) const;
	Float32x8_private operator/(float b) const;
	Float32x8_private operator<<(float b); // Minimum
	Float32x8_private operator>>(float b); // Maximum
	bool operator==(float b) const;
	bool operator!=(float b) const;
	bool operator>(float b) const;
	bool operator>=(float b) const;
	bool operator<(float b) const;
	bool operator<=(float b) const;
	float vectorialMul(float b) const;
	// Other mathematical goodies
	Float32x8_private sqrt() const;
	void set_to_sqrt();
	Float32x8_private rsqrt() const;
	void set_to_rsqrt();
	Float32x8_private normalize() const;
	void set_to_norm();
	float sum() const;
};

}
}
#endif
#else
#warning "AVX not supported."
#endif // FLOAT32X8_PRIVATE_HPP
