
#include"../common/Vector2.h"

template <class T>
Vector2Template<T>::Vector2Template()
{
	x_ = 0;
	y_ = 0;
}

template <class T>
Vector2Template<T>::Vector2Template(T x, T y)
{
	x_ = x;
	y_ = y;
}

template<class T>
Vector2Template<T>::~Vector2Template()
{
}

// ‘ã“ü‰‰Zq
template <class T>
Vector2Template<T>& Vector2Template<T>::operator=(const Vector2Template<T>& vec)
{
	x_ = vec.x_;
	y_ = vec.y_;
	return *this;
}

// “Y‚¦š‰‰Zq
template <class T>
int& Vector2Template<T>::operator[](int i)
{
	switch (i)
	{
	case 0:
		return x_;
		// break;
	case 1:
		return y_;
		// break;
	default:
		break;
	}
}

// ’P€‰‰Zq
template <class T>
Vector2Template<T>& Vector2Template<T>::operator+=(const Vector2Template<T>& vec)
{
	x_ += vec.x_;
	y_ += vec.y_;
	return *this;
}

template <class T>
Vector2Template<T>& Vector2Template<T>::operator-=(const Vector2Template<T>& vec)
{
	x_ -= vec.x_;
	y_ -= vec.y_;
	return *this;
}

template <class T>
Vector2Template<T>& Vector2Template<T>::operator*=(const Vector2Template<T>& vec)
{
	x_ *= vec.x_;
	y_ *= vec.y_;
	return *this;
}

template <class T>
Vector2Template<T>& Vector2Template<T>::operator/=(const Vector2Template<T>& vec)
{
	if (vec.x_)
	{
		x_ /= vec.x_;
	}
	else
	{
		x_ = 0;
	}

	if (vec.y_)
	{
		y_ /= vec.y_;
	}
	else
	{
		y_ = 0;
	}
	return *this;
}

template <class T>
Vector2Template<T>& Vector2Template<T>::operator%=(const Vector2Template<T>& vec)
{
	if (vec.x_)
	{
		x_ %= vec.x_;
	}
	else
	{
		x_ = 0;
	}

	if (vec.y_)
	{
		y_ %= vec.y_;
	}
	else
	{
		y_ = 0;
	}
	return *this;
}

template <class T>
Vector2Template<T> Vector2Template<T>::operator+() const
{
	return *this;
}

template <class T>
Vector2Template<T> Vector2Template<T>::operator-() const
{

	return {-x_,-y_};
}

// “ñ€‰‰Zq

template <class T>
Vector2Template<T> Vector2Template<T>::operator+(Vector2Template<T> vec)
{
	return {x_ + vec.x_,y_ + vec.y_};
}

template <class T>
Vector2Template<T> Vector2Template<T>::operator-(Vector2Template<T> vec)
{
	return { x_ - vec.x_,y_ - vec.y_ };
}

template <class T>
Vector2Template<T> Vector2Template<T>::operator*(Vector2Template<T> vec)
{
	return { x_ * vec.x_,y_ * vec.y_ };
}

template <class T>
Vector2Template<T> Vector2Template<T>::operator/(Vector2Template<T> vec)
{
	return { x_ / vec.x_,y_ / vec.y_ };
}

template <class T>
Vector2Template<T> Vector2Template<T>::operator%(Vector2Template<T> vec)
{
	return { x_ % vec.x_,y_ % vec.y_ };
}

// ”äŠr‰‰Zq
template <class T>
bool Vector2Template<T>::operator==(const Vector2Template<T>& vec) const
{
	return (x_ == vec.x_ && y_ == vec.y_);
}

template <class T>
bool Vector2Template<T>::operator!=(const Vector2Template<T>& vec) const
{
	return !(x_ == vec.x_ && y_ == vec.y_);
}

template <class T>
bool Vector2Template<T>::operator<(const Vector2Template<T>& vec) const
{
	return (x_ < vec.x_ && y_ < vec.y_);
}

template <class T>
bool Vector2Template<T>::operator<=(const Vector2Template<T>& vec) const
{
	return (x_ <= vec.x_ && y_ <= vec.y_);
}

template <class T>
bool Vector2Template<T>::operator>(const Vector2Template<T>& vec) const
{
	return (x_ > vec.x_&& y_ > vec.y_);
}

template <class T>
bool Vector2Template<T>::operator>=(const Vector2Template<T>& vec) const
{
	return (x_ >= vec.x_ && y_ >= vec.y_);
}

// Vector2‚Æint‚ÌŠ|‚¯Z
template <class T>
Vector2Template<T> operator*(const Vector2Template<T>& u, T k)
{
	return { u.x_ * k, u.y_ * k };
}

template <class T>
Vector2Template<T> operator*(T k, const Vector2Template<T>& u)
{
	return { k * u.x_ , k * u.y_ };
}
