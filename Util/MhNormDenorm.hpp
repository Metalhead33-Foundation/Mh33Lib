#include <limits>
#include <cmath>
#include "half.hpp"
namespace MH33 {

template <typename T> struct _norm_denorm {
    constexpr static const float minF = -1.0f * float(std::numeric_limits<T>::min());
    constexpr static const float maxF = float(std::numeric_limits<T>::max());
    constexpr static const float recMinF = ((std::numeric_limits<T>::min())) ? 1.0f / minF : 0.0f;
    constexpr static const float recMaxF = 1.0f / maxF;
    inline static constexpr float normalize(const T& val) {
        return (val < 0) ? (float(val) * recMinF) : (float(val) * recMaxF);
    }
    inline static T denormalize(const float& val) {
        return (std::signbit(val)) ? T(val*minF) : T(val*maxF);
    }
};
template <> struct _norm_denorm<half_float::half> {
    inline static float normalize(const half_float::half& val) {
        return float(val);
    }
    inline static half_float::half denormalize(const float& val) {
        return half_float::half(val);
    }
};
template <> struct _norm_denorm<float> {
    inline constexpr static float normalize(const float& val) {
        return val;
    }
    inline constexpr static float denormalize(const float& val) {
        return val;
    }
};
template <> struct _norm_denorm<double> {
    inline constexpr static float normalize(const double& val) {
        return float(val);
    }
    inline constexpr static double denormalize(const float& val) {
        return double(val);
    }
};

template <typename T> inline float normalize(const T& val) { return _norm_denorm<T>::normalize(val); }
template <typename T> inline T denormalize(const float& val) { return _norm_denorm<T>::denormalize(val); }

}
