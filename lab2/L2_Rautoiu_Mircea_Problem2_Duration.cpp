//
// Created by Mircea on 3/15/2023.
//

#include "L2_Rautoiu_Mircea_Problem2_Duration.h"
#include <stdexcept>
#include <utility>

Duration::Duration(float value, string unit) {
    this->value = value;
    this->unit = std::move(unit);
}

float Duration::get_value() const {
    return value;
}

string Duration::get_unit() const {
    return unit;
}

Duration Duration::add(const Duration &other) const {
    if (unit != other.unit)
        throw std::invalid_argument("add(): Incompatible unit types " + unit + " != " + other.unit);
    return {value + other.value, unit};
}

Duration Duration::subtract(const Duration &other) const {
    if (unit != other.unit)
        throw std::invalid_argument("add(): Incompatible unit types " + unit + " != " + other.unit);
    return {value - other.value, unit};
}

void Duration::scale(float factor) {
    value *= factor;
}

void Duration::divide(float factor) {
    value /= factor;
}

string Duration::text() {
    return to_string(value) + " " + unit;
}

int Duration::compare(const Duration &other) {
    if (unit != other.unit)
        throw std::invalid_argument("add(): Incompatible unit types " + unit + " != " + other.unit);
    if (value < other.value)
        return -1;
    else if (value == other.value)
        return 0;
    else
        return 1;
}

Duration Duration::operator+(const Duration &other) {
    if (unit != other.unit)
        throw std::invalid_argument("+: Incompatible unit types " + unit + " != " + other.unit);

    float res_val = value + other.value;
    return {res_val, unit};
}

Duration Duration::operator-(const Duration &other) {
    if (unit != other.unit)
        throw std::invalid_argument("-: Incompatible unit types " + unit + " != " + other.unit);

    float res_val = value - other.value;
    return {res_val, unit};
}

Duration Duration::operator*(float factor) {
    float res_val = value * factor;
    return {res_val, unit};
}

Duration Duration::operator/(float factor) {
    float res_val = value / factor;
    return {res_val, unit};
}


