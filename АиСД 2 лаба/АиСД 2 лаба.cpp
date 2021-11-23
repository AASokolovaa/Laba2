#include<iostream>

using namespace std;

class Polynomial
{
	struct Node
	{
		int degree;
		double coefficient;
		Node* next;

		Node(int degree, double coefficient, Node* next = nullptr) :degree(degree), coefficient(coefficient), next(next) { }
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

	double specified(const double x) const
	{
		int value = 0;
		Node* polyn = head;
		while (polyn)
		{
			value = value + (polyn->coefficient) * pow(x, polyn->degree);
			polyn = polyn->next;
		}

	}

	double operator[](int degree) const
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

	Polynomial  operator +(const Polynomial& other)
	{
		Node* variable = head;
		Polynomial res = other;
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

	Polynomial  operator -(const Polynomial& other)
	{
		Node* variable = head;
		Polynomial res = other;
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

	void set(int degree, double coefficient)
	{
		if (degree < 0)
			throw "The degree must be positive!";
		bool exists = 0;
		Node* polyn = head;
		while (polyn)
		{
			if (polyn->degree == degree)
			{
				if (coefficient == 0)
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
					delete tmp;
				}
				polyn->coefficient = coefficient;
				exists = 1;
				break;
			}
			polyn = polyn->next;
		}
		if (!exists)
		{
			if (coefficient != 0)
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

	Polynomial  operator *(const double scalar)
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

	friend Polynomial operator *(const double scalar, const Polynomial& other)
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

int main() {}
