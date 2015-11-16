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
            TPolynom& operator= (const TPolynom& rhs) {
                if (rhs == *this) {
                    return *this;
                }
                data = rhs.data;
                _degree = rhs._degree;
                _accessed_index = rhs._accessed_index;
                return *this;
            }
            
            TPolynom& operator= (const T& rhs) {
                return *this = TPolynom(rhs);
            }

            // 2 Перегрузка операторов +, -, *
            TPolynom operator+(const TPolynom& rhs) const {
                TPolynom poly(*this);
                poly += rhs;
                return poly;
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
                this->_validate_degree_after_operation(_degr);
                return *this;
            }
            
            TPolynom operator+(const T& rhs) const {
                TPolynom poly(*this);
                poly += rhs;
                return poly;
            }
            TPolynom& operator+=(const T& rhs) {
                this->data[0] += rhs;
                this->_validate_degree_after_operation(std::max(0, this->Degree()));
                return *this;
            }
            
            TPolynom operator-(const T& rhs) const {
                TPolynom poly(*this);
                poly -= rhs;
                return poly;
            }
            TPolynom& operator-=(const T& rhs) {
                this->data[0] -= rhs;
                this->_validate_degree_after_operation(std::max(0, this->Degree()));
                return *this;
            }


            TPolynom operator-(const TPolynom& rhs) const {
                TPolynom poly(*this);
                poly -= rhs;
                return poly;
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
                this->_validate_degree_after_operation(_degr);
                return *this;
            }

            TPolynom operator*(const TPolynom& rhs) {
                TPolynom poly;
                int _degr = std::max(-1, this->Degree() + rhs.Degree());
                for (int curr = 0; curr <= _degr; ++curr) {
                    for (int ix = 0; ix <= curr; ++ix) {
                        poly[curr] += (*this)[ix] * rhs[curr - ix];
                    }
                    if (poly[curr] != _nul) {
                        poly._degree = curr;
                    }
                }
                return poly;
            }
            
            TPolynom& operator*=(const TPolynom& rhs) {
                TPolynom prod(*this * rhs);
                *this = prod;
                return *this;
            }

            TPolynom operator*(const T& _rhs) {
                TPolynom poly;
                TPolynom rhs(_rhs);
                int _degr = std::max(-1, this->Degree() + rhs.Degree());
                for (int curr = 0; curr <= _degr; ++curr) {
                    for (int ix = 0; ix <= curr; ++ix) {
                        poly[curr] += (*this)[ix] * rhs[curr - ix];
                    }
                    if (poly[curr] != _nul) {
                        poly._degree = curr;
                    }
                }
                return poly;
            }

            TPolynom& operator*=(const T& rhs) {
                TPolynom prod(*this * rhs);
                *this = prod;
                return *this;
            }

            // 3 функция Degree()
            int Degree() const {
                if (_accessed_index < _degree) {
                    return _degree;
                } else if (_accessed_index > _degree) {
                    return (data[_accessed_index] == _nul) ? _degree : _accessed_index;
                } else {
                    if (data[_accessed_index] == _nul) {
                        int _degr = _degree - 1;
                        for (int ix = _accessed_index - 1; ix >= 0; --ix) {
                            if (data[ix] == _nul) {
                                --_degr;
                            }
                        }
                        return _degr;
                    } else {
                        return _degree;
                    }
                }
            }

            // 4 перегрузка операций [ ]
            T& operator[] (const int index);
            const T& operator[] (const int index) const;
            
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
            const T _nul = T(); // for comparison

            void _validate_degree_after_operation(int degr_max) {
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
    if ( coeff == _nul ) {
        _degree = -1;
    }
}

// конструктор инициализации
template <typename T>
NPolynom::TPolynom<T>::TPolynom (T *array, size_t array_size) {
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
NPolynom::TPolynom<T>::TPolynom (const TPolynom &rhs)
    : data(rhs.data)
    , _degree(rhs._degree)
    , _accessed_index(rhs._accessed_index) {
    cout << data[2] << endl;
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
const T& NPolynom::TPolynom<T>::operator[] (const int index) const {
    if (data.size() <= static_cast<size_t>(index)) {
        return _nul;
    }
    return data[index];
}

template <typename T>
T& NPolynom::TPolynom<T>::operator[] (const int index) {
    _degree = Degree();
    _accessed_index = index;
    if (data.size() <= static_cast<size_t>(index)) {
        data.resize(index + 1);
    }
    return data[index];
}

