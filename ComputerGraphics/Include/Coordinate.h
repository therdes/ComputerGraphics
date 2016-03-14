#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate
{
public:
	Coordinate() = default;

	Coordinate(double x, double y, double z) :
		_x(x), _y(y), _z(z)
	{}

	Coordinate(const Coordinate& other) :
		_x(other.x()), _y(other.y()), _z(other.z())
	{}
	Coordinate(const Coordinate&& other) :
		_x(other.x()), _y(other.y()), _z(other.z())
	{}

	const Coordinate& operator=(const Coordinate& other)
	{
		_x = other.x();
		_y = other.y();
		_z = other.z();

		return *this;
	}
	const Coordinate& operator=(const Coordinate&& other)
	{
		_x = other.x();
		_y = other.y();
		_z = other.z();

		return *this;
	}

	friend Coordinate operator*(const Coordinate& v, double factor);
	friend Coordinate operator*(double factor, const Coordinate& v);
	friend Coordinate operator+(const Coordinate& x, const Coordinate& y);

	double x() const
	{
		return _x;
	}
	double y() const
	{
		return _y;
	}
	double z() const
	{
		return _z;
	}

private:
	double _x;
	double _y;
	double _z;
};

inline Coordinate operator*(const Coordinate& v, double factor)
{
	return Coordinate(v.x() * factor, v.y() * factor, v.z() * factor);
}
inline Coordinate operator*(double factor, const Coordinate& v)
{
	return operator*(v, factor);
}

inline Coordinate operator+(const Coordinate& x, const Coordinate& y)
{
	return Coordinate(x.x() + y.x(), x.y() + y.y(), x.z() + y.z());
}

#endif // COORDINATE_H