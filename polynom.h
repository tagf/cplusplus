#include <vector>
#include <iostream>

using std::cout;
using std::endl;

namespace NPolynom {
    template <typename T>
    class TPolynom {
        // 6 Перегрузите оператор << для печати многочлена в поток вывода
        // друзья не являются членами класса!
        friend std::ostream& operator<<(std::ostream& os, const TPolynom &ex) {
            for (size_t ix = 0; ix < ex.data.size(); ++ix)
                std::cout << ex.data[ix] << " ";
            return os;
        }

        public:
            // 0 конструктор по умолчанию
            explicit TPolynom(T coeff = T());
            // конструктор инициализации
            TPolynom (T *array, size_t array_size);
            // конструктор копирования
            TPolynom (const TPolynom& rhs);

            // 1 операции сравнения: #2b
            bool operator== (const TPolynom& rhs) const;
            bool operator!= (const TPolynom& rhs) const;

            // операция присваивания:
            TPolynom& operator= (const TPolynom&);

            // 2 Перегрузка операторов +, -, *
            TPolynom operator+(const TPolynom& rhs) {
                *this += rhs;
                return *this;
            }
            TPolynom& operator+=(const TPolynom& rhs) {
                const int _rhs_degr = rhs.Degree();
                const int _degr = std::max(this->Degree(), _rhs_degr);
                if (_degr == -1)
                    return *this;
                this->data.resize(_degr + 1);
                for (int ix = 0; ix <= _rhs_degr; ++ix) {
                    this->data[ix] += rhs.data[ix];
                }
                this->_validate_degree(_degr);
                return *this;
            }
            
            TPolynom operator+(const T& rhs) {
                *this += rhs;
                return *this;
            }
            TPolynom& operator+=(const T& rhs) {
                this->data[0] += rhs;
                this->_validate_degree(std::max(0, this->Degree()));
                return *this;
            }
            
            TPolynom operator-(const T& rhs) {
                *this -= rhs;
                return *this;
            }
            TPolynom& operator-=(const T& rhs) {
                this->data[0] -= rhs;
                this->_validate_degree(std::max(0, this->Degree()));
                return *this;
            }


            TPolynom operator-(const TPolynom& rhs) {
                *this -= rhs;
                return *this;
            }
            TPolynom& operator-=(const TPolynom& rhs) {
                const int _rhs_degr = rhs.Degree();
                const int _degr = std::max(this->Degree(), _rhs_degr);
                if (_degr == -1)
                    return *this;
                this->data.resize(_degr + 1);
                for (int ix = 0; ix <= _rhs_degr; ++ix) {
                    this->data[ix] -= rhs.data[ix];
                }
                this->_validate_degree(_degr);
                return *this;
            }

            TPolynom operator*(const TPolynom& rhs);
            TPolynom& operator*=(const TPolynom& rhs);

            // 3 функция Degree()
            int Degree() const {
                if (_accessed_index < _degree) {
                    return _degree;
                } else if (_accessed_index > _degree) {
                    return (data[_accessed_index] == T()) ? _degree : _accessed_index;
                } else {
                    if (data[_accessed_index] == T()) {
                        int _degr = _degree - 1;
                        for (int ix = _accessed_index - 1; ix >= 0; --ix) {
                            if (data[ix] == T()) {
                                --_degr;
                            }
                        }
                        return _degr;
                    } else {
                        return _degree;
                    }
                }
            }

            // 4 перегрузка операции [ ]
            T& operator[] (int index);
            
            //
            
            // 8 Перегрузка операторов / и %
            TPolynom operator/(const TPolynom& rhs);
            TPolynom& operator/=(const TPolynom& rhs);
            TPolynom operator%(const TPolynom& rhs);
            TPolynom& operator%=(const TPolynom& rhs);

            // 9 перегрузить оператор , (запятая)
            TPolynom operator, (const TPolynom& lhs);


            // для печати в поток вывода можно определеить еще одну функцию
            // void print (std::ostream &os);
        private:
            std::vector<T> data;
            int _degree = 0;
            int _accessed_index = -2;

            void _validate_degree(int degr_max) {
                const T _nul = T();
                if (data[degr_max] == _nul) {
                    int _degr = degr_max - 1;
                    for (int ix = degr_max - 1; ix >= 0; --ix) {
                        if (data[ix] == _nul) {
                            --_degr;
                        }
                    }
                    _degree = _degr;
                } else {
                    _degree = degr_max;
                }
                // _accessed_index = -2;
            }
    };
}

/*-----------------------------INPLEMENTATION---------------------------------*/

// 0 конструктор по умолчанию
template <typename T>
NPolynom::TPolynom<T>::TPolynom(T coeff) {
    data.push_back(coeff);
    if ( coeff == T() ) {
        _degree = -1;
    }
}
// конструктор инициализации
template <typename T>
NPolynom::TPolynom<T>::TPolynom (T *array, size_t array_size) {
    const T _nul = T();
    for (size_t ix = 0; ix < array_size; ++ix) {
        data.push_back(array[ix]);
        if (array[ix] != _nul) {
            _degree = ix + 1;
        }
    }
    --_degree;
}
// конструктор копирования
template <typename T>
NPolynom::TPolynom<T>::TPolynom (const TPolynom &rhs) {
    size_t _size = rhs.data.size();
    // инициализация элементов массива
    for (size_t ix = 0; ix < _size; ++ix) {
        data.push_back(rhs.data[ix]);
    }
}

// 1 операции сравнения: #2b
template <typename T>
bool NPolynom::TPolynom<T>::operator==(const TPolynom& rhs) const {
    int degr;
    if (Degree() == (degr = rhs.Degree())) {
        for (int ix = 0; ix <= degr; ++ix) {
            if (! (data[ix] == rhs.data[ix])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

template <typename T>
bool NPolynom::TPolynom<T>::operator!=(const TPolynom& rhs) const {
    return !(this == rhs);
}

// 4 перегрузка операции [ ]
template <typename T>
T& NPolynom::TPolynom<T>::operator[] (int index) {
    _degree = Degree(); // validates degree before access;
    _accessed_index = index;
    if (data.size() < static_cast<size_t>(index + 1)) {
        data.resize(index + 1);
    }
    return data[index];
}

