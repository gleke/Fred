/*
Copyright 2020 Dennis Rohde

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include <vector>
#include <iostream>

#include "types.hpp"

class Interval {
    coordinate_t beg, en;
    
public:
    Interval() : beg{1}, en{0} {}

    Interval(const coordinate_t begin, const coordinate_t end) : beg{begin}, en{end} {}

    inline bool operator<(const Interval &other) const {
        return (beg < other.begin()) or ((beg == other.begin()) and (en < other.end()));
    }

    inline bool is_empty() const { 
        return beg > en; 
    }
    
    inline bool intersects(const Interval &other) const {
        if (is_empty() or other.is_empty()) return false;

        return ((other.beg >= beg) and (other.beg <= en)) or
            ((other.en >= beg) and (other.en <= en)) or
            ((other.beg <= beg) and (other.en >= en));
    }
    
    inline const coordinate_t begin() const {
         return beg; 
    }
    
    inline const coordinate_t end() const { 
        return en; 
    }
};

std::ostream& operator<<(std::ostream&, const Interval&);
