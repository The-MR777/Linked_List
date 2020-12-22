#include <iostream>
#define END cout << endl;
using namespace std;


// To Convert in into Static Class
// -------------------------------

using T = string;
using T2 = T;



class Linked_List
{
	//template<typename T2>
	struct __Node
	{
		T2 m_Data;
		__Node* m_Next;

		__Node(const T2& data, __Node*& next)	: m_Data(data), m_Next(next) {}
		__Node(const T2& data)					      : m_Data(data), m_Next(nullptr) {}
	};

	using Node = __Node;
	//using Node = __Node<T>;   // To Change all the Nodes at once
	Node* m_Head;				        // For Keeping Track
	Node* m_Tail;				        // For adding new element in the List
	size_t m_size;				      // Size of List
	static Node* m_It;			    // Temporary Iterator

	void move_Iterator(const int& i)
	{
		// Preparing an Iterator
		// ------------

		  begin();


		// Iterating till index
		// ------------

      for (int i_it = 1; i_it != i; ++i_it)
      {
        m_It = m_It->m_Next;
      }
	}

	void insert(const T& n)
	{
		// Exchanging the Addresses of
		// new_Node and previous Node
		// -----------------

		  m_It->m_Next = new Node(n, m_It->m_Next);

		// Incrementing size
		// -----------------

		  ++m_size;
	}

	template<class T3>
	void swap(T3& _Left, T3& _Right) noexcept
	{
      T3 _Tmp = move(_Left);
      _Left = move(_Right);
      _Right = move(_Tmp);
	}


public:

	Linked_List() : m_Head(nullptr), m_Tail(nullptr), m_size(NULL) {}

	Linked_List(initializer_list<T> L) : m_Head(new Node(L.begin()[0])), m_Tail(m_Head), m_size(L.size())
	{
		// Adding all Nodes
		// ------------

		  for (int i = 1; i < L.size(); ++i) m_Tail = m_Tail->m_Next = new Node(L.begin()[i]);
	}

	void add(const T& i)
	{
		// Adding new Node
		// ---------------

		(m_Head == nullptr) ? m_Head = m_Tail = new Node(i) : m_Tail = m_Tail->m_Next = new Node(i); ++m_size;
	}

	void add_front(const T& i)
	{
		// Nodenizing
		// ----------

		m_Head = new Node(i, m_Head); ++m_size;
	}

	void begin()
	{
		m_It = move(m_Head);
	}

	void end()
	{
		m_It = move(m_Tail);
	}

	void remove_at(const int& index)
	{
		// Moving the Iterator to (index - 1)
		// -------------

		move_Iterator(index - 1);

		// Selecting the Item to be deleted
		// -------------

		Node* n_target = move(m_It->m_Next);

		// Linking (index + 1) and (index - 1)
		// -------------

		m_It->m_Next = m_It->m_Next->m_Next;

		// Deleting the Target
		// -------------

		delete n_target;
		--m_size;
	}

	void remove_every(const T& n)
	{
		// m_Head Checks
		// -----------------

		while (m_Head->m_Data == n) remove_Head();


		// Running m_It without checking
		// m_Head and m_Tail
		// -----------------

		begin();
		for (Node* m_Excluder; m_It->m_Next != m_Tail; m_It = m_It->m_Next)
		{
			while (m_It->m_Next->m_Data == n)
			{
				m_Excluder = move(m_It->m_Next);
				m_It->m_Next = m_It->m_Next->m_Next;
				delete m_Excluder; --m_size;
			}
		}


		// m_Tail Check
		// -----------------

		if (m_It->m_Next->m_Data == n)
		{
			delete m_It->m_Next;
			m_Tail = m_It;
			m_Tail->m_Next = nullptr; --m_size;
		}
	}

	void remove_Head()
	{
		// Using iterator as m_Target
		// --------------

		m_It = m_Head;
		m_Head = m_Head->m_Next;

		// Deletion of Orginal Head
		// --------------

		delete m_It; --m_size;
	}

	void remove_Tail()
	{
		// Using m_Tail as Iterator
		// --------------

		m_Tail = m_Head;

		// Iterating just before the m_Tail
		// --------------

		for (int i = 1; i < (m_size - 1); ++i)
		{
			m_Tail = m_Tail->m_Next;
		}

		// Deleting original m_Tail
		// --------------

		delete m_Tail->m_Next; m_Tail->m_Next = nullptr; --m_size;
	}

	void insert_before(const T& i, const int& index)
	{
		// Selecting the (index - 1) Node
		// -----------------

		move_Iterator(index - 1);

		// Inserting Data at iterator
		// -----------------

		insert(i);

		// Flushing Iterator
		// -----------------

		m_It = nullptr;
	}

	void insert_after(const T& i, const int& index)
	{
		// Selecting the index Node
		// -----------------

		move_Iterator(index);

		// Inserting Data at iterator
		// -----------------

		insert(i);

		// Flushing Iterator
		// -----------------

		m_It = nullptr;
	}

	void insert_before_n_after(const T& i, const int& index)
	{
		// Selecting the index Node
		// -----------------

		move_Iterator(index - 1);
		insert(i);
		m_It = m_It->m_Next->m_Next;
		insert(i);

		// Flushing Iterator
		// -----------------

		m_It = nullptr;
	}

	void update_Data_at(const T& data, const int& index)
	{
		// Moving Iterator
		// ---------------

		move_Iterator(index);

		// Inserting Perticular Data
		// ---------------

		m_It->m_Data = move(*(int*)&data);
		m_It = nullptr;
	}

	void swap_Nodes(int&& index1, int&& index2)
	{
		// Arranging in Order to better Optimize it later

		if (index2 < index1)
		{
			swap(index1, index2);
		}

		// Moving 1st Iterator at index1

		move_Iterator(index1);

		// Creating 2nd Iterator and Moving it at index2 from index1

		Node* m_it_2 = m_It;
		for (int i_it = index1; i_it != index2; ++i_it) m_it_2 = m_it_2->m_Next;

		// Swaping Nodes

		swap(m_It->m_Data, m_it_2->m_Data);
	}

	void swap_Nodes(const int& index1, const int& index2)
	{
		// Moving 1st Iterator at index1

		move_Iterator(index1);

		// Creating 2nd Iterator and Moving it at index2 from index1

		Node* m_it_2 = m_Head;
		for (int i_it = 1; i_it != index2; ++i_it) m_it_2 = m_it_2->m_Next;

		// Swaping Nodes

		swap(m_It->m_Data, m_it_2->m_Data);
	}

	bool is_empty() const
	{
		return (m_Head == nullptr);
	}

	void safayi()
	{
		// Iterating the whole List
		// --------------

		while (m_Head != nullptr)
		{
			m_It = m_Head;
			m_Head = m_Head->m_Next;
			delete m_It;
		}
		m_size = 0;
	}

	void clear()
	{
		safayi();
	}

	void reverse()
	{
		// Initialization
		// --------------

		Node* pre_it = nullptr;
		m_It = m_Head;
		Node* dex_it = m_It->m_Next;


		while (dex_it != nullptr)
		{
			// Swapping
			// --------------

			m_It->m_Next = pre_it;

			// Moving Forward
			// --------------

			pre_it = m_It;
			m_It = dex_it;
			dex_it = dex_it->m_Next;
		}

		m_It->m_Next = pre_it;

		// Swapping Head and Tailes
		// ----------------

		m_It = m_Head;
		m_Head = m_Tail;
		m_Tail = m_It;
	}

	void Print_All()
	{
		begin();
		for (int i = 1; m_It != nullptr; ++i)
		{
			cout << "Data at Index#[ " << i << " ] : [ " << m_It->m_Data << " ]" << endl;
			m_It = m_It->m_Next;
		}
		Print_Size();
	}

	void Print_Linear()
	{
		begin();
		cout << "Data : [ ";
		while (m_It != nullptr)
		{
			cout << m_It->m_Data << " ";
			m_It = m_It->m_Next;
		}
		cout << "]" << endl;

		Print_Size();
	}

	void Print_Recursively()
	{
		// Declaring Iterator
		// ------------------

		begin();

		// Lambda which Iterates and Prints Only
		// ------------------

		const auto Print = [&](const auto& Print)
		{
			if (m_It == nullptr) return;

			// Printing the Data at Iterator
			// --------------------

			cout << "Data : [ " << m_It->m_Data << " ]" << endl;

			// Iterating the Iterator
			// --------------------

			m_It = m_It->m_Next;

			// Calling the Lambda
			// --------------------

			Print(Print);
		};

		// Recursive Callings using While Loop
		// ------------------

		Print(Print);

		// Printing Size as well
		// ------------------

		Print_Size();
	}

	void Print_Reverse()
	{
		// Declaring Iterator to Head to be used later
		// --------------------

		begin();

		// Declaring Lambda
		// --------------------

		const auto Print_Rev = [&](const auto& Print_Rev, Node* t_it = m_It) -> void
		{
			// Checking if the t_it is Empty
			// -----------------

			if (t_it != nullptr)
			{
				// Iterating to the Next Block
				// ---------

				Print_Rev(Print_Rev, t_it->m_Next);

				// Printing out at the End
				// ---------

				cout << "Data : [ " << t_it->m_Data << " ]" << endl;
			}

		};

		// Calling Anonymous Function
		// --------------------

		Print_Rev(Print_Rev);

		// Priniting the Size
		// --------------------

		cout << "------------\n";
		Print_Size();
	}

	void Print_Size() const
	{
		cout << "Size : ( " << m_size << " )" << endl;
	}

	bool verify_Size()
	{
		// Initialization
		// --------------

		begin();
		int i_it = 0;

		// Checking for Size
		// --------------

		while (m_It != nullptr)
		{
			m_It = m_It->m_Next;
			++i_it;
		}

		// Returning the Result
		// --------------

		return (m_size == i_it);
	}

	const size_t& get_Size() const
	{
		return m_size;
	}

	T& operator[] (const int& index)
	{
		begin();
		for (int i_it = 1; i_it != index; ++i_it)
		{
			m_It = m_It->m_Next;
		}
		return m_It->m_Data;
	}

	~Linked_List()
	{
		clear();
	}
};

Linked_List::__Node* Linked_List::m_It = nullptr;



int main()
{
		Linked_List L{ "Test","Of","Linked","List" };
		L.Print_All();

	END

		L.insert_before_n_after("TTT", 3);
		L.add_front("Success");
		L.add("Done");
		L.Print_All();

	END

		L.swap_Nodes(8, 1);
		L.Print_All();
}
