#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <algorithm>

#define STEP_CAPACITY 15

enum State { empty, busy, deleted };

template <class T> class TDMassive;
template <class T> std::ostream& operator<<(std::ostream& out, const TDMassive<T>& dmass);

template <class T>
class TDMassive {
    T* _data;
    State* _states;
    size_t _capacity;
    size_t _size;
    size_t _deleted;
public:
    TDMassive() {
        _size = 0;
        _capacity = STEP_CAPACITY;
        _data = new T[_capacity];
        _states = new State[_capacity];
        for (size_t i = 0; i < _capacity; i++) {
            _states[i] = State::empty;
        }
    }

    TDMassive(const TDMassive& other) {
        _size = other._size;
        _capacity = other._capacity;
        _data = new T[_capacity];
        _states = new State[_capacity];
        for (size_t i = 0; i < _capacity; i++) {
            _data[i] = other._data[i];
            _states[i] = other._states[i];
        }
    }

    TDMassive(const T* arr, size_t n) {
        _capacity = n;
        _data = new T[n];
        _states = new State[n];
        for (size_t i = 0; i < n; i++) {
            _states[i] = State::busy;
            _data[i] = arr[i];
        }
        _size = n;
        _deleted = 0;
    }

    TDMassive(size_t n) {
        _capacity = n;
        _data = new T[n];
        _states = new State[n];
        for (size_t i = 0; i < n; i++) {
            _states[i] = State::busy;
            _data[i] = T();
        }
        _size = n;
        _deleted = 0;
    }

    ~TDMassive() { delete[] _data; delete[] _states; }

    size_t size() const { return _size; }

    void swap(TDMassive& archive) {
        std::swap(_data, archive._data);
        std::swap(_states, archive._states);
        std::swap(_capacity, archive._capacity);
        std::swap(_size, archive._size);
        std::swap(_deleted, archive._deleted);
    }

    State getState(size_t index) const {
        return _states[index];
    }

    size_t count_value(T value) const noexcept {
        size_t count = 0;
        for (size_t i = 0; i < _size; i++) {
            if (_data[i] == value && _states[i] != State::deleted) {
                count++;
            }
        }
        return count;
    }

    size_t getDeletedCount() const {
        size_t count = 0;
        for (size_t i = 0; i < _size; ++i) {
            if (_states[i] == State::deleted) {
                ++count;
            }
        }
        return count;
    }

    T& operator[](size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Индекс выходит за пределы массива");
        }
        for (size_t i = index; i < _size; i++){
            if(_states[i] == State::busy ){
                return _data[i];
            }
        }
        throw std::out_of_range("Элемент не найден");
    }

    const T& operator[](size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Индекс выходит за пределы массива");
        }
        for (size_t i = index; i < _size; i++){
            if(_states[i] == State::busy ){
                return _data[i];
            }
        }
        throw std::out_of_range("Элемент не найден");
    }

    TDMassive<T>& operator=(const TDMassive<T>& other) {
        if (this != &other) {
            delete[] _data;
            delete[] _states;
            _size = other._size;
            _capacity = other._capacity;
            _deleted = other._deleted;
            _data = new T[_capacity];
            _states = new State[_capacity];
            for (size_t i = 0; i < _size; i++) {
                _data[i] = other._data[i];
                _states[i] = other._states[i];
            }
        }
        return *this;
    }
};

template <class T>
std::ostream& operator<<(std::ostream& out, const TDMassive<T>& dmass) {
    for (size_t i = 0; i < dmass.size(); i++) {
        out << dmass[i] << " ";
    }
    return out;
}

template <class T> class TVector;
template <class T> std::ostream& operator<<(std::ostream& out, const TVector<T>& vec);

template <class T>
class TVector {
protected:
    TDMassive<T> _values;
    size_t _start_index;
public:
    TVector(size_t size = STEP_CAPACITY, size_t start_index = 0) : _values(size), _start_index(start_index) {}
    TVector(const T* arr, size_t size, size_t start_index = 0) : _values(arr, size), _start_index(start_index) {}
    TVector(const TVector &vec) : _values(vec._values), _start_index(vec._start_index) {}
    ~TVector() {}

    T& operator[](size_t pos) {
        if (pos - _start_index < 0 || pos - _start_index >= _values.size()) { throw std::logic_error("Uncorrect position in vector"); }
        return _values[pos - _start_index];
    }

    const T& operator[](size_t pos) const {
        if (pos - _start_index < 0 || pos - _start_index >= _values.size()) { throw std::logic_error("Uncorrect position in vector"); }
        return _values[pos - _start_index];
    }

    TVector& operator=(const TVector& other) {
        if (this != &other) {
            _values = other._values;
            _start_index = other._start_index;
        }
        return *this;
    }

    TVector& operator+=(const TVector& other) {
        if (_values.size() != other._values.size()) { throw std::logic_error("Vector must be with equal sizes"); }
        for (size_t i = 0; i < _values.size(); i++) {
            _values[i] += other._values[i];
        }
        return *this;
    }

    TVector operator+(const TVector& other) const {
        TVector res(*this);
        res += other;
        return res;
    }

    void swap(TVector& vec) {
        _values.swap(vec._values);
        std::swap(_start_index, vec._start_index);
    }

    size_t size() const { return _values.size(); }
    size_t start_index() const { return _start_index; }

    friend std::ostream& operator<<(std::ostream& out, const TVector<T>& vec) {
        for (size_t i = 0; i < vec.size(); i++) {
            out << vec[i] << " ";
        }
        return out;
    }

    TVector<T>& operator*=(const T& scalar) {
        for (size_t i = 0; i < this->size(); ++i) {
            (*this)[i] *= scalar;
        }
        return *this;
    }

    TVector<T>& operator*=(const TVector<T>& other) {
        if (this->size() != other.size()) {
            throw std::logic_error("Vectors must have the same size for addition.");
        }
        TVector<T> result(this->size() * 2, this->_start_index);
        for (size_t i = 0; i < this->size(); ++i) {
            result.push_back((*this)[i]);
        }
        for (size_t i = 0; i < other.size(); ++i) {
            result.push_back(other[i]);
        }
        *this = result;
        return *this;
    }
};

template <class T> class TUpperTriangularMatrix;
template <class T> std::ostream& operator<<(std::ostream& out, const TUpperTriangularMatrix<T>& m);

template <class T>
class TUpperTriangularMatrix : public TVector<TVector<T>> {
private:
    using TVector<TVector<T>>::_values;
    using TVector<TVector<T>>::_start_index;
public:
    TUpperTriangularMatrix(size_t size = STEP_CAPACITY) : TVector<TVector<T>>(size) {
        for (size_t i = 0; i < size; i++) {
            _values[i] = TVector<T>(size - i, i);
        }
    }

    TUpperTriangularMatrix(T const* const * arr, size_t size) : TVector<TVector<T>>(size) {
        for (size_t i = 0; i < size; i++) {
            _values[i] = TVector<T>(size - i, i);
            for (size_t j = 0; j < size - i; j++) {
                _values[i][j + i] = arr[i][j + i];
            }
        }
    }

    TUpperTriangularMatrix(const T* arr, size_t size) : TVector<TVector<T>>(size) {
        for (size_t i = 0; i < size; i++) {
            _values[i] = TVector<T>(size - i, i);
            for (size_t j = 0; j < size - i; j++) {
                _values[i][j + i] = arr[i * size + j + i];
            }
        }
    }

    TUpperTriangularMatrix(const TUpperTriangularMatrix &m) : TVector<TVector<T>>(m) {}
    TUpperTriangularMatrix(const TVector<TVector<T>> &m) : TVector<TVector<T>>(m) {}
    ~TUpperTriangularMatrix() {}

    size_t size() const { return _values.size(); }

    using TVector<TVector<T>>::operator[];
    using TVector<TVector<T>>::operator=;

    TUpperTriangularMatrix& operator+=(const TUpperTriangularMatrix& other) {
        if (this->size() != other.size()) {
            throw std::logic_error("Matrices must be of the same size");
        }
        for (size_t i = 0; i < this->size(); ++i) {
            for (size_t j = i; j < this->size(); ++j) {
                (*this)[i][j] += other[i][j];
            }
        }
        return *this;
    }

    TUpperTriangularMatrix operator+(const TUpperTriangularMatrix& other) const {
        TUpperTriangularMatrix result(*this);
        result += other;
        return result;
    }

    TUpperTriangularMatrix operator*(const TUpperTriangularMatrix& other) {
        if (size() != other.size()) {
            throw std::invalid_argument("Matrices must be of the same size");
        }
        TUpperTriangularMatrix result(size());
        for (size_t i = 0; i < size(); ++i) {
            for (size_t j = i; j < size(); ++j) {
                result[i][j] = 0;
                for (size_t k = i; k <= j; ++k) {
                    result[i][j] += (*this)[i][k] * other[k][j];
                }
            }
        }
        return result;
    }

    TUpperTriangularMatrix operator*(const T& scalar) {
        TUpperTriangularMatrix result(size());
        for (size_t i = 0; i < size(); ++i) {
            for (size_t j = i; j < size(); ++j) {
                result[i][j] = (*this)[i][j] * scalar;
            }
        }
        return result;
    }

    TUpperTriangularMatrix operator/(const T& scalar) {
        if (scalar == 0) {
            throw std::invalid_argument("Division by zero is not allowed.");
        }
        TUpperTriangularMatrix result(size());
        for (size_t i = 0; i < size(); ++i) {
            for (size_t j = i; j < size(); ++j) {
                result[i][j] = (*this)[i][j] / scalar;
            }
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& out, const TUpperTriangularMatrix<T>& m) {
        for (size_t i = 0; i < m.size(); i++) {
            for (size_t j = 0; j < m.size(); j++) {
                if (j < i) { out << 0 << " "; }
                else { out << m[i][j] << " "; }
            }
            out << "\n";
        }
        return out;
    }
    TDMassive<T> to_upper_triangular(const TDMassive<T>& matrix, size_t size);
};

template <typename T>
TDMassive<T> to_upper_triangular(const TDMassive<T>& matrix, size_t size) {
    TDMassive<T> result(matrix);

    for (size_t k = 0; k < size; ++k) {
        if (result[k * size + k] == 0) {
            bool swapped = false;
            for (size_t i = k + 1; i < size; ++i) {
                if (result[i * size + k] != 0) {

                    for (size_t j = 0; j < size; ++j) {
                        std::swap(result[k * size + j], result[i * size + j]);
                    }
                    swapped = true;
                    break;
                }
            }
            if (!swapped) {
                throw std::runtime_error("Matrix cannot be converted to upper triangular due to zero pivot element");
            }
        }

        for (size_t i = k + 1; i < size; ++i) {
            T factor = result[i * size + k] / result[k * size + k];
            for (size_t j = k; j < size; ++j) {
                result[i * size + j] -= factor * result[k * size + j];
            }
        }
    }

    return result;
}
