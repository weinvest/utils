#include <boost/lexical_cast.hpp>
#include "Double.h"

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

double Double::Parse(const std::string& v)
{
    try
    {
        return std::stold(v);
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
    return std::to_string(v);
}
