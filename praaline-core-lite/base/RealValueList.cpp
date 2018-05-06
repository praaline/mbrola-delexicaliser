/*
    Praaline - Core module - Base
    Copyright (c) 2011-2018 George Christodoulides

    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version. It is provided
    for educational purposes and is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
    the GNU General Public License for more details.
*/

#include <math.h>
#include <QList>
#include "RealValueList.h"

RealValueList::RealValueList()
{
    m_mean = 0.0f;
    m_M2 = 0.0f;
    m_sum = 0.0f;
}

void RealValueList::recalculate()
{
    m_mean = 0.0f;
    m_M2 = 0.0f;
    m_sum = 0.0f;
    foreach(double x, *this) {
        double delta = x - m_mean;
        m_mean += delta / (double)count();
        m_M2 += delta * (x - m_mean);
        m_sum += x;
    }
}

void RealValueList::append(const double &x)
{
    QList<double>::append(x);
    double delta = x - m_mean;
    m_mean += delta / (double)count();
    m_M2 += delta * (x - m_mean);
    m_sum += x;
}

double RealValueList::mean() const
{
    return m_mean;
}
double RealValueList::variance() const
{
    return m_M2 / (double)(count() - 1);
}
double RealValueList::stddev() const
{
    return sqrt(variance());
}
double RealValueList::sum() const
{
    return m_sum;
}

double RealValueList::zscore(int i) const
{
    if ((i < 0) || (i >= count()))
        return 0.0;
    return (at(i) - mean()) / stddev();
}

double RealValueList::zscore_calculate(double x) const
{
    return (x - mean()) / stddev();
}
