#include <boost/lexical_cast.hpp>
#include "Double.h"


bool Double::IsValid(double v)
{
    return !IsInfinity(v) && !IsNaN(v) && !IsMaxValue(v) && !IsMinValue(v);
}

double Double::Divide(double v1, double v2)
{
    if(Double::Equal(v2, 0.0))
    {
	return Double::NaN();
    }
    return v1 / v2;
}

int Double::Sign(double v)
{
    if (GreatThan(v, 0.0))
    {
        return 1;
    }
    else if (LessThan(v, 0.0))
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

double Double::Floor(double v)
{
    if (Double::Equal(v, std::round(v)))
    {
        return std::round(v);
    }
    return std::floor(v);
}

double Double::Ceil(double v)
{
    if (Double::Equal(v, std::round(v)))
    {
        return std::round(v);
    }
    return std::ceil(v);
}

int Double::Round(double v)
{
    double f = std::floor(v);
    if (Double::Equal(v - f, 0.5))
    {
        return f + 1;
    }
    return std::round(v);
}

int32_t Double::Round(double v, int nanValue)
{
    if(Double::IsNaN(v))
    {
	return nanValue;
    }

    return Round(v);
}

double Double::Parse(const std::string& v)
{
    try
    {
	return boost::lexical_cast<double>(v);
    }
    catch(...)
    {
	if(v.size() > 0)
	{
	    if(v[0] == '-')
	    {
		return Double::MinValue();
	    }
	    return Double::MaxValue();
	}
	return Double::NaN();
    }
}

std::string Double::ToString(double v)
{
    return boost::lexical_cast<std::string>(v);
}
