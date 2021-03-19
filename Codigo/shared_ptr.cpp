#include <bits/stdc++.h>

using namespace std;
 
// clase que representa el conteo por referencias
class counter {

private:
    unsigned int count { };

public:
    // constructor por defecto
    counter() : count(0) { };

	// constructor por copia
    counter(const counter&) = delete;

	// redefiniendo el operador copia (=)
    counter &operator=(const counter&) = delete;

    // destructor
    ~counter() { }

	// resetea el contador
    void reset() {
    	count = 0;
    }

	// devuelve el contador
    unsigned int get() {
    	return count;
    }

    // sobrecarga al operador ++ (i++ y ++i)
    void operator++() {
    	count++;
    }
    void operator++(int) {
    	count++;
    }

    // sobrecarga al operador -- (i-- y --i)
    void operator--() {
    	count--;
    }
    void operator--(int) {
    	count--;
    }

    // sobrecarga al operador <<
    friend ostream &operator<<(ostream &ostream, const counter &counter) {
        ostream << "contador : " << counter.count;
        return ostream;
    }
};

// clase que representa un shared_ptr<T>
template <typename T>
class my_shared_ptr {

private:
    // contador por referencia
    counter *count;
    // shared_ptr
    T *sh_ptr;

public:
    // constructor explicito
    explicit my_shared_ptr(T *ptr = nullptr) {
        sh_ptr = ptr;
        count = new counter();
        if (ptr)
            (*count)++;
    }

    // constructor por copia
    my_shared_ptr(my_shared_ptr<T> &my_sh_ptr) {
        sh_ptr = my_sh_ptr.sh_ptr;
        count = my_sh_ptr.count;
        (*count)++;
    }

    // devuelve la cantidad de referencias
    unsigned int use_count() {
    	return count->get();
    }

	// devuelve el shared_pointer
    T *get() {
    	return sh_ptr;
    }

	// sobrecarga al operador *
    T &operator*() {
    	return *sh_ptr;
    }

	// sobrecarga al operador ->
    T *operator->() {
    	return sh_ptr;
    }

    // destructor
    ~my_shared_ptr() {
        (*count)--;
        if (count->get() == 0) {
            delete count;
            delete sh_ptr;
        }
    }

	// sobrecarga al operador <<
    friend ostream &operator<<(ostream &ostream, my_shared_ptr<T> &my_sh_ptr) {
        ostream << "direccion : " << my_sh_ptr.get() << endl;
        ostream << *(my_sh_ptr.count) << endl;
		ostream << "valor : " << *my_sh_ptr << endl;
        return ostream;
    }
};

int main()
{
	cout << "SCOPE (sh_ptr1)" << endl << endl;

	// creamos sh_ptr1 llamando al constructor explicito
    my_shared_ptr<int> sh_ptr1(new int(50));

	// cambiamos el valor del puntero sh_ptr1
    *sh_ptr1 = 101;

	// imprimimos los datos de sh_ptr1
    cout << "datos de sh_ptr1" << endl;
    cout << sh_ptr1 << endl;
	
	{
		// nuevo scope
		cout << "NUEVO SCOPE (sh_ptr1 , sh_ptr2)" << endl << endl;

		// creamos sh_ptr2 llamando al constructor copia
		my_shared_ptr<int> sh_ptr2 = sh_ptr1;

		// cambiamos el valor del puntero sh_ptr2
    	*sh_ptr2 = 102;

		// imprimimos los datos de sh_ptr1
		cout << "datos de sh_ptr1" << endl;
		cout << sh_ptr1 << endl;

		// imprimimos los datos de sh_ptr2
		cout << "datos de sh_ptr2" << endl;
		cout << sh_ptr2 << endl;
	
		{
			// nuevo scope
			cout << "NUEVO SCOPE (sh_ptr1 , sh_ptr2 , sh_ptr3)" << endl << endl;

			// creamos sh_ptr3 llamando al constructor copia
			my_shared_ptr<int> sh_ptr3(sh_ptr2);

			// cambiamos el valor del puntero sh_ptr3
    		*sh_ptr3 = 103;

			// imprimimos los datos de sh_ptr1
			cout << "datos de sh_ptr1" << endl;
			cout << sh_ptr1 << endl;

			// imprimimos los datos de sh_ptr2
			cout << "datos de sh_ptr2" << endl;
			cout << sh_ptr2 << endl;

			// imprimimos los datos de sh_ptr3
			cout << "datos de sh_ptr3" << endl;
			cout << sh_ptr3 << endl;
		}

		// sh_ptr3 fue destruido por el destructor porque esta fuera del scope
		cout << "SALIMOS DEL SCOPE (sh_ptr1 , sh_ptr2)" << endl << endl;

		// imprimimos los datos de sh_ptr1
        cout << "datos de sh_ptr1" << endl;
		cout << sh_ptr1 << endl;

		// imprimimos los datos de sh_ptr2
		cout << "datos de sh_ptr2" << endl;
		cout << sh_ptr2 << endl;
	}

	// sh_ptr2 fue destruido por el destructor porque esta fuera del scope
	cout << "SALIMOS DEL SCOPE (sh_ptr1)" << endl << endl;

	// imprimimos los datos de sh_ptr1
    cout << "datos de sh_ptr1" << endl;
	cout << sh_ptr1 << endl;
}