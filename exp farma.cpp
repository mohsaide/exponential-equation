#include <iostream>
#include<cmath>
using namespace std;  

class node
{
private:
	double coef;
	int  pow;
	node* next;
	friend class poly;

public:
	node* get_next()
	{
		return next;
	}
	int  get_pow()
	{
		return pow;
	}

	double get_coef()
	{
		return coef; 
	}

	node()
	{
		coef = pow = 0;  
		next = NULL;  
	}
};

class poly
{

private:

	node* head;  
	node* tail;


public :  


	poly()
	{
		head = tail = NULL; 
     }


	poly(int  p[], double c[], int s)
	{
		head = tail = NULL; 

		for (int i = 0; i < s; i++)
		{
			insert(p[i], c[i]); 
		}
	}



	bool empty()
	{
		if (head==NULL)return true;
		else return false; 
	}



	void insert(int p, double c)
	{
		node* N = new node();   
		N->coef = c;  
		N->pow = p;  
		N->next = NULL;
		

		
			node* ptr1 = head; 
			node* ptr2 = NULL;  

			if (!empty())
				while (ptr1)
				{
					if (ptr1->pow == p)
					{
						ptr1->coef += c;
						return;
						cout << "cas0" << endl; 
					}
					ptr1 = ptr1->next; 
				}; 

			ptr1 = head;  

			while (ptr1 && ptr1->pow < p)
			{
				ptr2 = ptr1;  
				ptr1 = ptr1->next;  
			}

			if (ptr1 && ptr2) // middle case 
			{
				N->next = ptr1;
				ptr2->next = N;
				cout << "cas1" << endl;
			}
			else if (!ptr1 && !ptr2)// empty case 
			{
				head = N;
				tail = N;
				cout << "cas2" << endl;
			}
			else if (!ptr1 && ptr2) // last case 
			{
				tail->next = N;  
				tail = N; 
				cout << "cas3" << endl;
			}
			else // ptr1 && !ptr2 // first case 
			{
				N->next = head;
				head = N;
				cout << "cas4" << endl;
			}
		
			cout << "done " << endl; 
	}



	void remove_based_power(int p)
	{
		
		if (!empty())
		{
			node* ptr1 = head, * ptr2 = NULL;

			while (ptr1 && ptr1->pow != p)
			{
				ptr2 = ptr1;
				ptr1 = ptr1->next;
			}

			if (ptr1 && ptr2) // middle case 
			{
				ptr2->next = ptr1->next;
				delete ptr1;
			}

			else if (!ptr1 && ptr2) // last case 
			{
				cout << "dont found...\n"; 
			}
			else // ptr1 && !ptr2 //  first case 
			{
				head = head->next; 
				delete ptr1; 
			}
		}
		
	}


	void remove_front()
	{
		if (!empty())
		{
			node* ptr = head;  
			head = head->next;  
			delete ptr;  
		}
	}



	double eval(int x)
	{
		double result = 0.0; 
		node* ptr = head;  
		while (ptr)
		{
			result += (ptr->coef * pow(x, ptr->pow)); 
			ptr = ptr->next; 
	    }

		return result; 
	}



	int degree()
	{
		if (!empty())
		{
			return tail->pow; 
		}
		else
		{
			return -9999; //poly is empty 
		}
	}




	friend ostream& operator<<(ostream& , const poly& ); 

	friend istream& operator>>(istream& , poly& );



	void merge( poly & obj )
	{
		if (!obj.empty())
		{
			node* ptr = obj.head;  

			while (ptr)
			{
				node* ptr2 = head; 
				int flag = 0;
				while (ptr2)
				{
					if (ptr2->pow == ptr->pow)
					{
						ptr2->coef += ptr->coef;
						flag = 1;
						break;
					}
					ptr2 = ptr2->next; 
				}
				if (flag == 0)
				{
					insert(ptr->pow , ptr->coef);  
				}

				ptr = ptr->next; 
			}

			while (!obj.empty())
			{
				obj.remove_front();
			}
			obj.head = obj.tail = NULL;
		}
		
	}


	 
	poly& operator+(const poly& obj)
	{
		poly sum;  

		node* ptr = head;  
		while (ptr)
		{
			sum.insert(ptr->pow, ptr->coef); 
			ptr = ptr->next;  
		}

		 ptr = obj.head;

		while (ptr)
		{
			node* ptr2 = sum.head;
			int flag = 0;
			while (ptr2)
			{
				if (ptr2->pow == ptr->pow)
				{
					ptr2->coef += ptr->coef;
					flag = 1;
					break;
				}
				ptr2 = ptr2->next;
			}
			if (flag == 0)
			{
				insert(ptr->pow, ptr->coef);
			}

			ptr = ptr->next;
		}

		return sum; 
	}
	

	~poly()
	{
		while (!empty())
		{
			remove_front(); 
		}
		head = tail = NULL; 

	}
};

ostream& operator<<(ostream& out, const poly& obj)
{
	
		
		node* m = obj.head;


		if (m)
		{
			while ( m )
			{
				if (m->get_coef() > 0)
				{
					cout << "+" << abs(m->get_coef());
			     }
				else if (m->get_coef() < 0)
				{
					cout << "-" << abs(m->get_coef()); 
				}
				else //coef == 0 
				{
					cout << "0 "; 
					continue; 
				}

				///////////////////////////////////////

				if (m->get_pow() > 0)
				{
					cout << "X^" << abs(m->get_pow()) << " ";
			     }
				else if (m->get_pow() < 0)
				{
					cout << "X^-" << abs(m->get_pow()) << " "; 
				}
				else //pow == 0 
				{
					cout << " "; 
					continue; 
				}


				m = m->get_next();
			}
		}
		else
		{
			cout << "Empty";
		}


	return out;  
}


istream& operator>>(istream& in, poly& obj)
{

	int no = 0;  
	cout << "please enter number of terms in the polynomials : ";  
	cin >> no;  


	while (!obj.empty())
	{
		obj.remove_front();
	}
	obj.head = obj.tail = NULL;

	int pp;  
	double cc;  
	for (int i = 0; i < no; i++)
	{
		cout << "Enter #" << i + 1 << " node coef : ";  
		cin >> cc; 
		cout << "Enter #" << i + 1 << " node pow  : ";
		cin >> pp; 
		obj.insert(pp, cc); 
	}

	
	return in;  

}

int main()
{
	
	poly x; 
	cin >> x; 
	cout << x << endl ; 

	system("pause"); 
	return 0;  
}