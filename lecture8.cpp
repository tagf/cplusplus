#include <iostream>
#include <string>
#include <memory>

class TAnimal {
    public:
        virtual ~TAnimal() {
            std::cout << "animal destroyed" << std::endl;
        }
        virtual void Cry() const {}; // = 0;
        void Walk() const {
            std::cout << "TAnimal::walk" << std::endl;
        }
};

typedef void (TAnimal::*TWalkMethod) () const;

class TCat : public TAnimal {
    public:
        ~TCat() { // âîîáùå íàäî áû ïèñàòü âåçäå virtual
            std::cout << "cat destroyed" << std::endl;
        }
        virtual void Cry() {
            std::cout << "Hi I'm cat" << std::endl;
        }
        void Walk() const {
            std::cout << "TCat::walk" << std::endl;
        }
};

class TDog : public TAnimal {
    public:
        ~TDog() {
            std::cout << "dog destroyed" << std::endl;
        }
        virtual void Cry() {
            std::cout << "Hi I'm dog" << std::endl;
        }
        void Walk() const {
            std::cout << "TDog::walk" << std::endl;
        }
};


class TBadDog : public TDog {
    public:
        ~TBadDog() {
            std::cout << "bad dog destroyed" << std::endl;
        }
        virtual void Cry() {
        std::cout << "Hi I'm bad dog" << std::endl;
        throw 1;
    }
};

// "Virtual function table"
// äëÿ ïîíèìàíèÿ ìåõàíèêè ðàáîòû âèðò. ôóíêöèé âòîðîé àðãóìåíò
TAnimal *CreateAnimal (const std::string& type, TWalkMethod &walkMethod) {
    if (type == "cat") {
        walkMethod = static_cast<TWalkMethod> (&TCat::Walk);
        return new TCat;
    } else if (type == "dog") {
        walkMethod = static_cast<TWalkMethod> (&TDog::Walk);
        return new TDog;
    } else if (type == "baddog") {
        walkMethod = static_cast<TWalkMethod> (&TCat::Walk);
        return new TBadDog;
    }
    else
        walkMethod = NULL;
        return NULL;
}

int main0() {
    std::string type;
    std::cin >> type;
    TWalkMethod meth;
    //TAnimal *animal = animal(CreateAnimal(type));
    std::auto_ptr<TAnimal> animal(CreateAnimal(type, meth));
    if (animal.get() != NULL) {
        animal->Cry(); // possible exception
        ((*animal).*meth)(); // ->* operator âûçîâà ìåòîäà ïî óêàçàòåëþ íå ïðîêàòèò
        (animal.get()->*meth)();
        //xxx
    }
    // äîïóñòèìà óòå÷êà ïàìÿòè!
    // we shuld write virtual at least in TAnimal.
    // delete animal; // undefined behavior if destructor is NOT virtual.
    return 0;
}


int main1() {
    main0();
    try {
        // Work();
    } catch (...) {
        std::cout << "exception caught" << std::cout;
    }
    return 0;
}


typedef bool(*TCmpFunc)(int, int);
typedef bool(*TConditionFunc)(int);

size_t CountIf0(int *a, size_t n, bool (*condition) (int)) {
    size_t res = 0;
    for (size_t i = 0; i < n; ++i) {
        if (condition(a[i])) {
            ++res;
        }
    }
    return res;
}


size_t CountIf(int *a, size_t n, TConditionFunc condition) {
    size_t res = 0;
    for (size_t i = 0; i < n; ++i) {
        if (condition(a[i])) {
            ++res;
        }
    }
    return res;
}

bool Less5(int a) {
    return a < 5;
}


int main() {
    main1();
    int A[] = {1,2,4,3,5,6,7,8,9,10};
    std::cout << CountIf(A, sizeof(A) / sizeof(A[0]), &Less5);
    return 0;
}
