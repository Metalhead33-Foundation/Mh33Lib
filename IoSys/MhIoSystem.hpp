#ifndef MHIOSYSTEM_HPP
#define MHIOSYSTEM_HPP
#include <Io/MhIoDevice.hpp>
#include <functional>

namespace MH33 {
namespace Io {

class System {
public:
	typedef std::function<void(const char*)> FilenameCallback;
	virtual ~System() = default;
	// The actual functions to be implemented
	virtual Device* open(const char* path, Mode mode) = 0;
	virtual bool exists(const char* path) = 0;
	virtual char separator() const = 0;
	virtual void enumerate(const char* path, std::vector<std::string>& output) = 0;
	virtual void enumerate(const char* path, FilenameCallback functor) = 0;

	// Convenience wrappers
	inline Device* open(const std::string& path, Mode mode) {
		return open(path.c_str(),mode);
	}
	inline bool exists(const std::string& path) {
		return exists(path.c_str());
	}
	inline void enumerate(const std::string& path, std::vector<std::string>& output) {
		enumerate(path.c_str(),output);
	}
	inline std::vector<std::string> enumerate(const char* path) {
		std::vector<std::string> tmp;
		enumerate(path,tmp);
		return tmp;
	}
	inline std::vector<std::string> enumerate(const std::string& path) {
		std::vector<std::string> tmp;
		enumerate(path,tmp);
		return tmp;
	}
	inline void enumerate(const std::string& path, FilenameCallback functor) {
		enumerate(path.c_str(),functor);
	}
};

}
}
#endif // MHIOSYSTEM_HPP
