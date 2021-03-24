#include <bits/stdc++.h>

using namespace std;

// clase que representa un unique_ptr<T>
template<typename T>
class my_unique_ptr {

private:
    // unique_ptr
    T *u_ptr;

public:
    // constructor explicito
    explicit my_unique_ptr(T *p) : u_ptr(p) { }

    // constructor por defecto
    my_unique_ptr() : u_ptr(NULL) { }

    // destructor
    ~my_unique_ptr() {
        delete u_ptr;
    }

    // hacemos al puntero como no copiable
    // constructor por copia
    my_unique_ptr(const my_unique_ptr &my_u_ptr) = delete;

    // hacemos al puntero como no copiable
    // redefiniendo el operador copia (=)
    my_unique_ptr &operator=(const my_unique_ptr &my_u_ptr) = delete;

    // hacemos al puntero como movible
    // constructor de movimiento
    my_unique_ptr(my_unique_ptr &&my_u_ptr) {
        u_ptr = my_u_ptr.u_ptr;
        my_u_ptr.u_ptr = NULL;
    }

    // redefiniendo el operador de movimiento
    my_unique_ptr &operator=(my_unique_ptr &&my_u_ptr) {
        delete u_ptr;
        u_ptr = my_u_ptr.u_ptr;
        my_u_ptr.u_ptr = NULL;
    }

    // devuelve el puntero
    T *get() const {
        return u_ptr;
    }

    // resetea el puntero
    void reset(T *ptr) {
        T *aux = u_ptr;
        u_ptr = ptr;
        delete aux;
    }

    // libera el puntero
    T *release() {
        T *aux = u_ptr;
        u_ptr = NULL;
        return aux;
    }

    // sobrecarga al operador ->
    T *operator->() const {
        return u_ptr;
    }

    // sobrecarga al operador *
    T &operator*() const {
        return *u_ptr;
    }
};

int main() {

    // creamos un punteroa entero ptr
    int *ptr = new int(50);

    // creamos uptr1 llamando al constructor explicito
    my_unique_ptr<int> uptr1(ptr);
    // imprimimos el valor de uptr1
    cout << "valor de uptr1 : " << *uptr1 << endl;

    // modificamos el valor de uptr1
    *uptr1 = 34;
    // imprimimos el valor de uptr1
    cout << "valor de uptr1 : " << *uptr1 << endl;
    // imprimimos el valor de ptr
    cout << "valor de ptr : " << *ptr << endl;

    // error en tiempo de compilacion porque no tiene definido 
    // ningun constructor
    // my_unique_ptr<int> uptr2 = ptr;

    // error en tiempo de ejecucion porque se inicializa un unique_ptr 
    // con un objeto que ya es usado por otro unique_ptr
    // my_unique_ptr<int> uptr3(ptr);

    // error en tiempo de compilacion porque los unique_ptr no pueden 
    // ser copiados
    // my_unique_ptr<int> uptr4 = uptr1;

    // copiamos uptr1 hacia uptr5
    my_unique_ptr<int> uptr5 = move(uptr1);

    // modificamos el valor de uptr5
    *uptr5 = 11;
    // imprimimos el valor de uptr5
    cout << "valor de uptr5 : " << *uptr5 << endl;
    // imprimimos el valor de ptr
    cout << "valor de ptr : " << *ptr << endl;

    // error en tiempo de ejecucion porque uptr1 se perdio al ser copiado
    // cout << "valor de uptr1 : " << *uptr1 << endl;

    // creamos un puntero a string ptr1
    string *ptr1 = new string("LP");
    // unique_ptr uptr6
    my_unique_ptr<string> uptr6;

    // creamos un unique_ptr a traves del metodo reset()
    uptr6.reset(ptr1);

    // imprimimos el valor de uptr6
    cout << "valor de uptr6 : " << *uptr6 << endl;
    // imprimimos el valor de ptr1
    cout << "valor de ptr1 : " << *ptr1 << endl;
}