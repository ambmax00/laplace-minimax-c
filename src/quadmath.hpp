#ifndef QUADMATH_HPP
#define QUADMATH_HPP

#include <iostream>
#include <cstdlib>
#include <string>
#include <cfloat>
#include <cstring>
#include <cctype>
#include <cmath>
#include <limits>
#include <Eigen/Core>
#include <Eigen/Dense>

#define GNU_CXX
//#define INTEL_CXX

#if not defined(GNU_CXX) && not defined(INTEL_CXX)
#error "Header float128.hpp could not be configured for this compiler."
#endif

#if defined(GNU_CXX) && defined(INTEL_CXX)
#error "Both GNU and INTEL is enabled in float128.hpp"
#endif

#ifdef INTEL_CXX
typedef _Quad quad_type;
#else 
#include <quadmath.h>
typedef __float128 quad_type;
#endif

class float128 {
public:

	quad_type _val;

	constexpr float128() : _val(0.0) {}
	
	constexpr float128(const quad_type f) : _val(f) {}

	float128(const float128& f) = default;
	
	float128(float128&& f) = default;

	float128& operator=(const float128& f) = default;
	
	float128& operator=(float128&& f) = default;

	constexpr float128& operator+=(const float128& f) {
		this->_val += f._val;
		return *this;
	}

	constexpr float128& operator-=(const float128& f) {
		this->_val -= f._val;
		return *this;
	}
	
	constexpr float128& operator*=(const float128& f) {
		this->_val *= f._val;
		return *this;
	}
	
	constexpr float128& operator/=(const float128& f) {
		this->_val /= f._val;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const float128& f);
		
	explicit operator int() const { 
		return (int)_val;
	} 
	
	operator float() const { 
		return (float)_val;
	}
	
	operator double() const { 
		return (double)_val;
	}

};

inline std::ostream& operator<<(std::ostream& os, const float128& f) {
#ifdef GNU_CXX
	char buf[128];
	quadmath_snprintf(buf, sizeof(buf), "%+-#*.20Qe", 46, f._val);
	os << buf;
#endif
#ifdef INTEL_CXX
	os << double(f);
#endif
	return os;
}

constexpr inline float128 operator+(const float128& a, const float128& b) {
	float128 out = a;
	out += b;
	return out;
}

constexpr inline float128 operator-(const float128& a, const float128& b) {
	float128 out = a;
	out -= b;
	return out;
}

constexpr inline float128 operator-(const float128& a) {
	float128 out;
	out._val = -a._val; 
	return out;
}

constexpr inline float128 operator/(const float128& a, const float128& b) {
	float128 out = a;
	out /= b;
	return out;
}

constexpr inline float128 operator*(const float128& a, const float128& b) {
	float128 out = a;
	out *= b;
	return out;
}

constexpr inline bool operator<(const float128& a, const float128& b) {
	return a._val < b._val;
}

constexpr inline bool operator<=(const float128& a, const float128& b) {
	return a._val <= b._val;
}

constexpr inline bool operator>=(const float128& a, const float128& b) {
	return a._val >= b._val;
}

constexpr inline bool operator>(const float128& a, const float128& b) {
	return a._val > b._val;
}

constexpr inline bool operator==(const float128& a, const float128& b) {
	return a._val == b._val;
}

constexpr inline bool operator!=(const float128& a, const float128& b) {
	return a._val != b._val;
}

#ifdef GNU_CXX
#define MATHFUNC(name)\
inline float128 name(const float128& f) {\
	return name##q(f._val);\
}
#endif

#ifdef INTEL_CXX
#define MATHFUNC(name)\
extern "C" {\
	quad_type __##name##q(quad_type q);\
}\
inline float128 name(const float128& f) {\
	return __##name##q(f._val);\
}
#endif

MATHFUNC(acos)
MATHFUNC(acosh)
MATHFUNC(asin)
MATHFUNC(asinh)
MATHFUNC(atan)
MATHFUNC(atanh)
MATHFUNC(cosh)
MATHFUNC(cos)
MATHFUNC(sinh)
MATHFUNC(sin)
MATHFUNC(tan)
MATHFUNC(tanh)
MATHFUNC(exp)
MATHFUNC(erf)
MATHFUNC(erfc)
MATHFUNC(fabs)
MATHFUNC(log)
MATHFUNC(log10)
MATHFUNC(sqrt)

#ifdef INTEL_CXX
extern "C" {
	quad_type __powq(quad_type b, quad_type e);
}
#endif

inline float128 pow(const float128& b, const float128& e) {
#ifdef INTEL_CXX
	return __powq(b._val, e._val);
#else
	return powq(b._val, e._val);
#endif
}

inline float128 pow(const float128& b, const int& e) {
#ifdef INTEL_CXX
	return __powq(b._val, e);
#else
	return powq(b._val, e);
#endif
}

inline float128 pow(const float128& b, const double& e) {
#ifdef INTEL_CXX
	return __powq(b._val, e);
#else
	return powq(b._val, e);
#endif
}

inline float128 abs(const float128& f) {
	return fabs(f._val);
}

inline float128 max(const float128& a, const float128& b) {
	return a._val > b._val ? a._val : b._val;
}

// adapted from boost/multiprecision/float128.hpp
constexpr float128 quad_min = float128(1) * 
	float128(DBL_MIN) * 
	float128(DBL_MIN) * 
	float128(DBL_MIN) * 
	float128(DBL_MIN) * 
	float128(DBL_MIN) *
	float128(DBL_MIN) * 
	float128(DBL_MIN) *
	float128(DBL_MIN) *
	float128(DBL_MIN) *
	float128(DBL_MIN) * 
	float128(DBL_MIN) *
	float128(DBL_MIN) * 
	float128(DBL_MIN) * 
	float128(DBL_MIN) *
	float128(DBL_MIN) *
	float128(DBL_MIN) / float128(1073741824);

constexpr double dbl_mult = 8.9884656743115795386e+307;

constexpr float128 quad_max = (float128(1) - float128(9.62964972193617926527988971292463659e-35)) * 
	float128(dbl_mult) * 
	float128(dbl_mult) * 
	float128(dbl_mult) * 
	float128(dbl_mult) * 
	float128(dbl_mult) *
	float128(dbl_mult) * 
	float128(dbl_mult) * 
	float128(dbl_mult) * 
	float128(dbl_mult) * 
	float128(dbl_mult) * 
	float128(dbl_mult) * 
	float128(dbl_mult) * 
	float128(dbl_mult) * 
	float128(dbl_mult) * 
	float128(dbl_mult) * 
	float128(dbl_mult) * float128(65536);

namespace std {

template <>
class numeric_limits<float128> {
public:

	constexpr static bool is_specialized = true;
	constexpr static float128 min() { return quad_min; }
	constexpr static float128 max() { return quad_max; }
	constexpr static float128 lowest() { return - max(); }
	constexpr static int digits = 113;
	constexpr static int digits10 = 33;
	constexpr static int max_digits10 = 36;
	constexpr static bool is_signed = true;
	constexpr static bool is_integer = false;
	constexpr static bool is_exact = false;
	constexpr static int radix = 2;
	constexpr static float128 epsilon() { return 1.92592994438723585305597794258492732e-34; }
	constexpr static float128 round_error() { return 0.5; }
	constexpr static int min_exponent = -16381;
	constexpr static int min_exponent10 = min_exponent * 301L / 1000L;
	constexpr static int max_exponent = 16384;
	constexpr static int max_exponent10 = max_exponent * 301L / 1000L;
	constexpr static bool has_infinity = true;
	constexpr static bool has_quiet_NaN = true;
	constexpr static bool has_signaling_NaN = false;
	constexpr static float_denorm_style has_denorm = denorm_present;
	constexpr static bool has_denorm_loss = true;
	constexpr static float128 infinity() { return float128(1)/float128(0); }
	constexpr static float128 quiet_NaN() { return float128(nan("")); }
	constexpr static float128 signaling_NaN() { return 0; }
	constexpr static bool is_iec559 = true;
	constexpr static bool is_bounded = true;
	constexpr static bool is_modulo = false;
	constexpr static bool traps = false;
	constexpr static bool tinyness_before = false;
	constexpr static float_round_style round_style = round_to_nearest;

};

} // namespace std

template <class T>
void convert_from_string(T& b, const char* p) {

	// check if empty
	if (!p || (*p == 0)) return;

	bool is_neg = false;
	bool is_neg_expo = false;

	// check sign
	if (*p == '+') {
		++p;
	} else if (*p == '-') {
		is_neg = true;
		++p;
	}
	
	// check if nan
	if((std::strcmp(p, "nan") == 0) || (std::strcmp(p, "NaN") == 0) || 
		(std::strcmp(p, "NAN") == 0))
	{
		b = nan("");
		if (is_neg) b *= -1;
		return;
	}
	
	// check if inf
	if((std::strcmp(p, "inf") == 0) || (std::strcmp(p, "Inf") == 0) || 
		(std::strcmp(p, "INF") == 0))
	{
		b = T(1)/T(0);
		if (is_neg) b *= -1;
		return;
	}
		
	b = T();
	int digits_seen = 0;
	int expon = 0;

	// grab leading digits
	while (std::isdigit(*p)) {
		b *= T(10);
		b += T(*p - '0');
		++p;
		++digits_seen;
	}
	
	// grab decimals if present
	if (*p == '.') {
		++p;
		while (std::isdigit(*p)) {
			b *= T(10);
			b += T(*p - '0');
			++p;
			--expon;
			if (digits_seen > std::numeric_limits<T>::max_digits10) break;
		}
		while (std::isdigit(*p)) {
			++p;
		}
	}
	
	// parse exponent
	if ((*p == 'e') || (*p == 'E') || (*p == 'D')) {
		++p;
		if (*p == '+') {
			++p;
		} else if (*p == '-') {
			is_neg_expo = true;
			++p;
		}
		int e2 = 0;
		while (std::isdigit(*p)) {
			e2 *= 10;
			e2 += (*p - '0');
			++p;
		}
		if (is_neg_expo) {
			e2 *= -1;
			expon += e2;
		}
	}
	
	if (expon) {
		T val = T(10);
		if (expon > std::numeric_limits<T>::min_exponent10 + 2) {
			val = pow(val, expon);
			b *= val;
		} else {
			val = pow(val, expon + digits_seen + 1);
			b *= val;
			val = T(10);
			val = pow(val, -digits_seen - 1);
			b *= val;
		}
	}
	
	if (is_neg) {
		b *= T(-1);
	}
	
	if (*p) {
		throw std::runtime_error("Unexpected character in string");
	}	
	
	return;

}

namespace Eigen {

// adapted from boost/multiprecision/eigen.hpp

template<>
struct NumTraits<float128> : GenericNumTraits<float128> {
	
	typedef float128 Real;
	typedef float128 NonInteger;
	typedef float128 Nested;

	enum
	{
	  IsComplex = 0,
	  IsInteger = 0,
	  ReadCost = 1,
	  AddCost = 4,
	  MulCost = 8,
	  IsSigned = 1,
	  RequireInitialization = 1,
	};
	
	static Real epsilon()
	{
	  return std::numeric_limits<Real>::epsilon();
	}
	
	static Real dummy_precision()
	{
	  return float128(1000) * epsilon();
	}
	
	static Real highest()
	{
	  return (std::numeric_limits<Real>::max)();
	}
	
	static Real lowest()
	{
	  return (std::numeric_limits<Real>::min)();
	}
	
	static int digits10()
	{
	  return std::numeric_limits<Real>::digits10;
	}
	
};

using MatrixXq = Matrix<float128,Dynamic,Dynamic>;

using VectorXq = Matrix<float128,Dynamic,1>;

} // namespace Eigen

#endif
