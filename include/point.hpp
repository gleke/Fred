/*
Copyright 2020 Dennis Rohde

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without result.riction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPresult. OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include <vector>
#include <iostream>
#include <cmath>

#include "types.hpp"
#include "interval.hpp"

class Point {
    std::vector<coordinate_t> coordinates;
    
public:    
    inline Point() {}
    
    inline Point(const std::vector<coordinate_t> &in) : coordinates{in} {}
    
    inline std::vector<coordinate_t>& getCoordinates() {
        return this->coordinates;
    }
    
    inline const std::vector<coordinate_t>& getCoordinates() const {
        return this->coordinates;
    }
    
    inline coordinate_t operator[](dimensions_t i) const { 
        return coordinates[i]; 
    }
    
    inline Point& operator+=(const Point &point) {
        for (dimensions_t i = 0; i < coordinates.size(); ++i){
            coordinates[i] += point.getCoordinates()[i];
        }
        return *this;
    }
    
    inline Point& operator-=(const Point &point) {
        for (dimensions_t i = 0; i < coordinates.size(); ++i){
            coordinates[i] -= point.getCoordinates()[i];
        }
        return *this;
    }
    
    inline Point& operator/=(distance_t distance) {
        for (dimensions_t i = 0; i < coordinates.size(); ++i){
            coordinates[i] /= distance;
        }
        return *this;
    }
    
    inline Point operator+(const Point &point) const {
        auto result = *this;
        for (dimensions_t i = 0; i < coordinates.size(); ++i){
            result.coordinates[i] += point.getCoordinates()[i];
        }
    
        return result;
    }
    
    inline Point operator-(const Point &point) const {
        auto result = *this;
        for (dimensions_t i = 0; i < coordinates.size(); ++i){
            result.coordinates[i] -= point.getCoordinates()[i];
        }
    
        return result;
    }
    
    inline Point operator*(const distance_t mult) const {
        Point result;
        result.coordinates = std::vector<coordinate_t> (coordinates.size());
        for (dimensions_t i = 0; i < coordinates.size(); ++i){
            result.getCoordinates()[i] = coordinates[i] * mult;
        }
        return result;
    }
    
    inline distance_t operator*(const Point &p) const {
        distance_t result = 0;
        for (dimensions_t i = 0; i < coordinates.size(); ++i) {
            result += coordinates[i] * p.getCoordinates()[i];
        }
        return result;
    }
    
    inline Point operator/(distance_t dist) {
        Point result;
        result.coordinates = std::vector<coordinate_t>(coordinates.size());
        for (dimensions_t i = 0; i < coordinates.size(); ++i){
            result.getCoordinates()[i] = coordinates[i] / dist;
        }
        return result;
    }
    
    inline distance_t dist_sqr(const Point &point) const {
        distance_t result = 0;
        distance_t temp;
        for (dimensions_t i = 0; i < coordinates.size(); ++i){
            temp = coordinates[i] - point.getCoordinates()[i];
            result += temp * temp;
        }
        return result;
    }
    
    inline distance_t dist(const Point &point) const {
        return std::sqrt(dist_sqr(point));
    }
    
    inline distance_t length_sqr() const {
        distance_t result = 0;
        for (dimensions_t i = 0; i < coordinates.size(); ++i){
            result += coordinates[i] * coordinates[i];
        }
        return result;
    }
    
    inline distance_t length() const {
        return std::sqrt(length_sqr());
    }
    
    inline Interval intersection_interval(const distance_t distance_sqr, const Point &line_start, const Point &line_end) const {
        const Vector u = line_end-line_start;
        const distance_t ulen_sqr = u.length_sqr(), tlen_sqr = this->length_sqr();
                
        const distance_t p =  -2. / ulen_sqr * ((u * *this) - (line_start * u)), 
            q = (tlen_sqr + line_start.length_sqr() - distance_sqr - 2. * (line_start * *this)) / ulen_sqr;
        
        const distance_t phalf_sqr = p * p / 4., discriminant = phalf_sqr - q;
        
        if (discriminant < 0) return Interval();
        
        const distance_t discriminant_sqrt = std::sqrt(discriminant);
        
        const distance_t r1 = - p / 2. + discriminant_sqrt, r2 = - p / 2. - discriminant_sqrt;
        const distance_t lambda1 = std::min(r1, r2), lambda2 = std::max(r1, r2);
                
        return Interval(std::max(0., lambda1), std::min(1., lambda2));
    }
    
};


std::ostream& operator<<(std::ostream&, const Point&);