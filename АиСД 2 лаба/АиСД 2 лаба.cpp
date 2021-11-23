#include<iostream>
#include<complex>
#include <iomanip>

using namespace std;

template <class T>class Polynomial
{
	struct Node
	{
		int degree;
		T coefficient;
		Node* next;

		Node(int degree, T coefficient, Node* next = nullptr) :degree(degree), coefficient(coefficient), next(next) { }
	};
	Node* head;

public:
	Polynomial() : head(nullptr) {}

	Polynomial(const Polynomial& other) : head(nullptr)
	{
		Node* _head = other.head;
		while (_head)
		{
			set(_head->degree, _head->coefficient);
			_head = _head->next;

		}
	}

	~Polynomial()
	{
		clear();
	}

	T specified(const double x) const
	{
		T value = 0;
		Node* polyn = head;
		while (polyn)
		{
			value = value + (polyn->coefficient) * pow(x, polyn->degree);
			polyn = polyn->next;
		}
		return value;
	}

	T operator[](int degree) const
	{
		Node* polyn = head;
		while (polyn)
		{
			if (polyn->degree == degree)
			{
				return polyn->coefficient;
			}
			polyn = polyn->next;
		}
		return 0;
	}

	Polynomial& operator=(const Polynomial& other)
	{
		this->clear();
		Node* _head = other.head;
		while (_head)
		{
			set(_head->degree, _head->coefficient);
			_head = _head->next;
		}
		return *this;
	}

	Polynomial  operator +(const Polynomial<T>& other)
	{
		Node* variable = head;
		Polynomial<T> res = other;
		while (variable)
		{
			int value = 0;
			Node* polyn = res.head;
			while (polyn)
			{
				if (polyn->degree == variable->degree)
				{
					res.set(variable->degree, polyn->coefficient + variable->coefficient);
					value = 1;
					break;
				}
				polyn = polyn->next;
			}
			if (value == 0)
			{
				res.set(variable->degree, variable->coefficient);
			}
			variable = variable->next;
		}
		return res;
	}

	Polynomial  operator -(const Polynomial<T>& other)
	{
		Node* variable = head;
		Polynomial<T> res = other;
		while (variable)
		{
			int value = 0;
			Node* polyn = res.head;
			while (polyn)
			{
				if (polyn->degree == variable->degree)
				{
					res.set(variable->degree, polyn->coefficient - variable->coefficient);
					value = 1;
					break;
				}
				polyn = polyn->next;
			}
			if (value == 0)
			{
				res.set(variable->degree, -(variable->coefficient));
			}
			variable = variable->next;
		}
		return res;
	}

	void set(int degree, T coefficient)
	{
		if (degree < 0)
			throw "The degree must be positive!";
		bool exists = 0;
		Node* polyn = head;
		while (polyn)
		{
			if (polyn->degree == degree)
			{
				if (coefficient == (T)0)
				{
					Node* tmp = head;
					if (tmp->next != NULL)
					{
						while (tmp->next->degree != degree)
						{
							tmp = tmp->next;
						}
						tmp->next = polyn->next;
						delete polyn;
					}
					else;
					delete tmp;
				}
				else
				polyn->coefficient = coefficient;
				exists = 1;
				break;
			}
			polyn = polyn->next;
		}
		if (!exists)
		{
			if (coefficient != (T)0)
			{
				head = new Node(degree, coefficient, head);
			}
		}
	}

	void clear()
	{
		while (head)
		{
			Node* tmp = head;
			head = head->next;
			delete tmp;
		}
	}

	Polynomial  operator *(const T scalar)
	{

		Node* variable = head;
		Polynomial res;
		while (variable)
		{
			res.set(variable->degree, scalar * (variable->coefficient));
			variable = variable->next;
		}
		return res;
	}

	ostream& operator <<(ostream& out)
	{
		Node* polyn = head;
		cout << "f(x)=";
		while (polyn)
		{
			if (polyn->next != NULL)
			{
				out << polyn->coefficient << "x^" << polyn->degree << "+";
			}
			out << polyn->coefficient << "x^" << polyn->degree << endl;
			polyn = polyn->next;
		}
		return out;
	}

	friend Polynomial<T> operator *(const T scalar, const Polynomial<T>& other)
	{
		Node* variable = other.head;
		Polynomial res;
		while (variable)
		{
			res.set(variable->degree, scalar * (variable->coefficient));
			variable = variable->next;
		}
		return res;
	}


};

int main()
{
	Polynomial<int> a;
	Polynomial<int> b;
	Polynomial<float> c;
	Polynomial<float> d;
	Polynomial<complex<double>> e;
	Polynomial<complex<double>> f;
	std::complex<double> x;
	std::complex<double> y;
	try
	{
		cout << "class int" << endl;
		a.set(2, 2);
		a << cout;
		b.set(2, 4);
		b << cout;
		cout << "f1(2)= " << a.specified(2) << endl;
		cout << "f2(2)= " << b.specified(2) << endl;
		cout << "sum ";
		a + b << cout;
		cout << "dif ";
		a - b << cout;
		cout << "mul f1 by 2 ";
		2 * a << cout;

		cout << "class float" << endl;
		c.set(2, 2.345);
		c << cout;
		d.set(2, 4.987);
		d << cout;
		cout << "f1(2)= " << c.specified(2) << endl;
		cout << "f2(2)= " << d.specified(2) << endl;
		cout << "sum ";
		c + d << cout;
		cout << "dif ";
		c - d << cout;
		cout << "mul f1 by 2 ";
		2 * c << cout;

		cout << "class complex<double>" << endl;
		e.set(2, x);
		e << cout;
		f.set(2, y);
		f << cout;
		cout << "f1(2)= " << e.specified(2) << endl;
		cout << "f2(2)= " << f.specified(2) << endl;
		cout << "sum ";
		e + f << cout;
		cout << "dif ";
		e - f << cout;
		cout << "mul f1 by 2 ";
		2 * e << cout;

	}
	catch (const char* err)
	{
		cout << err;
	}

}
