#ifndef MHEQUATABLE_HPP
#define MHEQUATABLE_HPP

namespace MH33 {
namespace Interface {

template <typename T> class Equatable {
	virtual ~Equatable() = default;
	virtual bool equals(const T& b) const = 0;
	bool operator==(const T& b) const { return equals(b); }
	bool operator!=(const T& b) const { return !equals(b); }
};

}
}
#endif // MHEQUATABLE_HPP
