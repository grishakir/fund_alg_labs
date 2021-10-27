#include "Data.h"

bool Data::operator>(const Data& right) const
{
    return this->key > right.key;
}

bool Data::operator<(const Data& right) const
{
    return !(*this > right);
}

bool Data::operator==(const Data& right) const
{
    return !(*this > right || *this < right);
}

