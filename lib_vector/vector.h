// Copyright 2024 Anvar

#include "../lib_dmassive/archive.h"
#include <stdexcept>
#include <vector>

template <typename T>
class TVector {
    TDMassive _data;
    size_t _start_index;

public:
    // Конструктор по умолчанию
    TVector(size_t size = 0, size_t start_index = 0)
        : _data(size), _start_index(start_index) {}

    // Конструктор из массива
    TVector(const std::vector<double>& values, size_t start_index = 0)
        : _data(values.size()), _start_index(start_index) {
        for (size_t i = 0; i < values.size(); ++i) {
            _data[i] = values[i];
        }
    }

    // Перегрузка оператора []
    double& operator[](size_t index) {
        return _data[index];
    }

    const double& operator[](size_t index) const {
        return _data[index];
    }
     // Перегрузка оператора () для доступа к элементам
    TVector operator()(size_t index) {
        return (*this)[index];
    }
    
    const TVector operator()(size_t index) const {
        return (*this)[index];
    }

    // Перегрузка оператора +
    TVector operator+(const TVector& other) const {
        if (_data.size() != other._data.size()) {
            throw std::logic_error("Vectors must be of the same size.");
        }
        TVector result(_data.size());
        for (size_t i = 0; i < _data.size(); ++i) {
            result[i] = _data[i] + other[i];
        }
        return result;
    }

    // Перегрузка оператора -
    TVector operator-(const TVector& other) const {
        if (_data.size() != other._data.size()) {
            throw std::logic_error("Vectors must be of the same size.");
        }
        TVector result(_data.size());
        for (size_t i = 0; i < _data.size(); ++i) {
            result[i] = _data[i] - other[i];
        }
        return result;
    }

    // Перегрузка оператора *
    double operator*(const TVector& other) const {
        if (_data.size() != other._data.size()) {
            throw std::logic_error("Vectors must be of the same size.");
        }
        double result = 0.0;
        for (size_t i = 0; i < _data.size(); ++i) {
            result += _data[i] * other[i];
        }
        return result;
    }

    // Перегрузка оператора +=
    TVector& operator+=(const TVector& other) {
        if (_data.size() != other._data.size()) {
            throw std::logic_error("Vectors must be of the same size.");
        }
        for (size_t i = 0; i < _data.size(); ++i) {
            _data[i] += other[i];
        }
        return *this;
    }

    // Перегрузка оператора -=
    TVector& operator-=(const TVector& other) {
        if (_data.size() != other._data.size()) {
            throw std::logic_error("Vectors must be of the same size.");
        }
        for (size_t i = 0; i < _data.size(); ++i) {
            _data[i] -= other[i];
        }
        return *this;
    }

    // Перегрузка оператора == для сравнения векторов
    bool operator==(const TVector& other) const {
        if (_data.size() != other._data.size()) {
            return false;
        }
        for (size_t i = 0; i < _data.size(); ++i) {
            if (_data[i] != other[i]) {
                return false;
            }
        }
        return true;
    }

    // Перегрузка оператора != для сравнения векторов
    bool operator!=(const TVector& other) const {
        return !(*this == other);
    }

    // Перегрузка оператора * для умножения на число
    TVector operator*(double scalar) const {
        TVector result(_data.size());
        for (size_t i = 0; i < _data.size(); ++i) {
            result[i] = _data[i] * scalar;
        }
        return result;
    }

    // Перегрузка оператора *= для умножения на число с присваиванием
    TVector& operator*=(double scalar) {
        for (size_t i = 0; i < _data.size(); ++i) {
            _data[i] *= scalar;
        }
        return *this;
    }

    // Перегрузка оператора / для деления на число
    TVector operator/(double scalar) const {
        if (scalar == 0) {
            throw std::logic_error("Cannot divide by zero.");
        }
        TVector result(_data.size());
        for (size_t i = 0; i < _data.size(); ++i) {
            result[i] = _data[i] / scalar;
        }
        return result;
    }

    friend std::istream& operator>>(std::istream& is, TVector& vec) {
        for (size_t i = 0; i < vec._data.size(); ++i) {
            is >> vec[i];
        }
        return is;
    }

    // Перегрузка операторов сравнения
    bool operator==(const TVector& other) const {
        if (_data.size() != other._data.size()) return false;
        for (size_t i = 0; i < _data.size(); ++i) {
            if ((*this)[i] != other[i]) return false;
        }
        return true;
    }

    bool operator!=(const TVector& other) const {
        return !(*this == other);
    }

    TVector operator|(const TVector& other) const {
        // Реализация побитового OR
        TVector result(_data.size());
        for (size_t i = 0; i < _data.size(); ++i) {
            result[i] = static_cast<int>((*this)[i]) | static_cast<int>(other[i]);
        }
        return result;
    }

    // Перегрузка оператора /= для деления на число с присваиванием
    TVector& operator/=(double scalar) {
        if (scalar == 0) {
            throw std::logic_error("Cannot divide by zero.");
        }
        for (size_t i = 0; i < _data.size(); ++i) {
            _data[i] /= scalar;
        }
        return *this;
    }

    size_t size() const {
        return _data.size();
    }
};
