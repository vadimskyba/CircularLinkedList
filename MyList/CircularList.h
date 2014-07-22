// ���������� ��������� ������������ ������������ ������

template <class T>
class clist
{
	struct ELEMENT		// ��������� ������� ������
	{
		T data;			// ������ �������� ������
		ELEMENT *next;	// ��������� �� ��������� ������� ������
	};

private:
	ELEMENT *current;	// ��������� �� ������� ������� ������
	int size;			// ������ ������

public:
	clist();	// �����������
	clist(clist<T> &src_list); // ����������� � �������������: ���������� ��������� �� ��������� src_list
	~clist();	// ����������

	int Size();		// ������ ������
	T Current();	// ������� ������� ������
	void Insert(const T data);	// �������� ������� 
	void operator +(const T data);	// �������� ������� � ������� ��������� +
	void Insert(clist<T> &src_list);	// ������� �������
	T Remove();		// �������� �������� ������
	void Clear();	// ������� ������
	void Next();	// �������� ��������� ������ �� ��������� �������
	void Prev();	// �������� ��������� ������ �� ���������� �������
	bool Empty();	// ������ ����?
	void Print();	// ����� ������ � �����
	void Sort(bool bAscending = false);	// ���������� ������
};

template <class T>
clist<T>::clist()
{
	current = NULL;
	size = 0;
}

template <class T>
clist<T>::clist(clist<T> &src_list)
	: clist<T>::clist()
{
	Insert(src_list);
}

template <class T>
clist<T>::~clist()
{
	Clear();
}

template <class T>
int clist<T>::Size()
{
	return size;
}

template <class T>
T clist<T>::Current()
{
	if (!Empty())
		return current->data;

	return NULL;
}

template <class T>
void clist<T>::Insert(const T data)
{
	ELEMENT *newElement = new ELEMENT;
	newElement->data = data;

	if (Empty()) // ������ ������
	{
		newElement->next = newElement; // 1 ������� � ������: ��������� ���������� �������� ��������� ��� �� ����
	}
	else // ������ �� ����
	{
		newElement->next = current;

		// ���������� ���� ���������� ������� 
		ELEMENT *prev = current;
		while (prev->next != current)
			prev = prev->next;

		prev->next = newElement; // � ������������� ��������� ���������� �������� ->next �� ����� ������� newElement
	}

	current = newElement; // ��������� �� ������� ������� ������ ��������� �� ����� �������
	size++;
}

template <class T>
void clist<T>::operator +(const T data)
{
	Insert(data);
}

template <class T>
void clist<T>::Insert(clist<T> &src_list)
{
	if (src_list.Empty())
		return;

	Insert(src_list.current->data);				// ��������� ������� ������� ������ src_list

	// ���������� ��������� ����������� ��������, ���� �� ������� � ������� ������� ������ src_list
	ELEMENT *src_next = src_list.current;		
	while (src_next->next != src_list.current)
	{
		Insert(src_next->next->data);
		src_next = src_next->next;
	}
}

template <class T>
T clist<T>::Remove()
{
	if (Empty())
		return NULL;

	T data = current->data;		// ��������� ��� �������� ������ ���������� ��������
	ELEMENT *tmp = current;		// �������� ������� ��������� ������� �� ��������� ����������

	if (size == 1)				// � ������ ����� ������ ��������� �������
	{
		current = NULL;			// ������ ��������� �������� �������� ��������
	}
	else
	{
		// ���������� ���� ���������� ������� � ������������� ��������� ���������� �������� ->next �� ��������� �� current �������
		ELEMENT *prev = current;
		while (prev->next != current)
			prev = prev->next;
		prev->next = current->next;

		current = current->next;	// �������������� ������� ������� �� ���������
	}

	delete tmp;					// ������� ��������� �������
	size--;						// �������� ������ ������

	return data;				// ���������� ������ ���������� ��������
}

template <class T>
void clist<T>::Clear()
{
	while (!Empty())
		Remove();				// ���������� ������� ��� �������� ������
}

template <class T>
void clist<T>::Next()
{
	if (!Empty())
		current = current->next;	// ������� ��������� ������� ������� ������ �� ��������� �������
}

template <class T>
void clist<T>::Prev()
{
	if (Empty())
		return;

	
	ELEMENT *prev = current;
	while (prev->next != current) // ���������� ������� ������ ���� � ������ ������������������ ��������� ���� ���������
		prev = prev->next;
	current = prev;	// �������������� ������� ������� �� ���������
}

template <class T>
bool clist<T>::Empty()
{
	return (current == NULL) ? true : false;
}

template <class T>
void clist<T>::Print()
{
	if (Empty())
	{
		cout << "������ ����" << endl;
		return;
	}

	ELEMENT *next = current;
	cout << next->data << endl;
	while (next->next != current)
	{
		cout << next->next->data << endl;
		next = next->next;
	}
}

template <class T>
void clist<T>::Sort(bool bAscending = false)
{
	if (Empty())
		return;

	clist<T> sortedList; // ��������� ������, ���������� ��������������� ��������

	while (!Empty())	// ���������� ������ ������� ������, ���� �� �� ���������
	{
		ELEMENT *sortedElement = current; // ������� ������, ������� �������� ����. (bAscending == false) ��� ���. (bAscending == true) �������� ������ (� ����������� �� bAscending)
		ELEMENT *next = current;

		while (next->next != current)	// ������ ������ ������ � ���� ����. ��� ���. �������� 
		{
			if (bAscending) // ���������� ����������
			{
				if (next->next->data < sortedElement->data)
					sortedElement = next->next;
			}
			else // ��������� ����������
			{
				if (next->next->data > sortedElement->data)
					sortedElement = next->next;
			}

			next = next->next;
		}
		current = sortedElement;
		sortedList.Insert(Remove()); // ���������� ������� ������� �� ��������� ������
	}

	Insert(sortedList);	// �������� �������� ���������� ���������������� � ������� ������
}