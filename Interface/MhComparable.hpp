#ifndef MHCOMPARABLE_HPP
#define MHCOMPARABLE_HPP

namespace MH33 {
namespace Interface {

enum ComparisonResult {
	EQUAL,
	GREATER,
	LESSER
};
template <typename T> class Comparable {
public:
	virtual ~Comparable() = default;
	virtual ComparisonResult compare(const T& b) const = 0;
	bool operator==(const T& b) const { return compare(b) == EQUAL; }
	bool operator!=(const T& b) const { return compare(b) != EQUAL; }
	bool operator<(const T& b) const { return compare(b) == LESSER; }
	bool operator<=(const T& b) const { return compare(b) != GREATER; }
	bool operator>(const T& b) const { return compare(b) == GREATER; }
	bool operator>=(const T& b) const { return compare(b) != LESSER; }

};

}
}

#endif // MHCOMPARABLE_HPP
