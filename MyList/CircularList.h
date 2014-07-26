// Реализация алгоритма циклического односвязного списка

template <class T>
class clist
{
	struct ELEMENT		// Структура элемент списка
	{
		T data;			// Данные элемента списка
		ELEMENT *next;	// Указатель на следующий элемент списка
	};

private:
	ELEMENT *current;	// Указатель на текущий элемент списка
	int size;			// Размер списка

public:
	clist();	// Конструктор
	clist(T *data, int dataSize); // Конструктор с инициализацией по массиву
	~clist();	// Деструктор

	int Size();		// Размер списка
	T Current();	// Текущий элемент списка
	void Insert(const T data);	// Добавить элемент после текущего
	void operator +(const T data);	// Добавить элемент с помощью оператора +
	void Merge(clist<T> &src_list);		// Слияние списков. После слияния src_list не содержит элементов.
	T Remove();		// Удаление элемента списка
	void Clear();	// Очистка списка
	void Next();	// Смещение указателя списка на следующий элемент
	void Prev();	// Смещение указателя списка на предыдущий элемент
	bool Empty();	// Список пуст?
	void Print();	// Вывод списка в поток
};

template <class T>
clist<T>::clist()
{
	current = NULL;
	size = 0;
}

template <class T>
clist<T>::clist(T *data, int dataSize)
	: clist<T>::clist()
{
	for (int i = 0; i < dataSize; i++)
		Insert(data[i]);
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

	if (Empty()) // пустой список
	{
		newElement->next = newElement; // 1 элемент в списке: указатель следующего элемента указывает сам на себя
	}
	else // список не пуст
	{
		ELEMENT *next = current->next;
		current->next = newElement;
		newElement->next = next;
	}

	current = newElement; // указатель на текущий элемент списка указывает на новый элемент
	size++;
}

template <class T>
void clist<T>::operator +(const T data)
{
	Insert(data);
}

template <class T>
void clist<T>::Merge(clist<T> &src_list)
{
	if (src_list.Empty())
		return;

	ELEMENT *next = src_list.current->next;
	src_list.current->next = current->next;
	current->next = next;

	size += src_list.size;

	// clean src_list
	src_list.current = NULL;
	src_list.size = 0;
}

template <class T>
T clist<T>::Remove()
{
	if (Empty())
		return NULL;

	T data = current->data;			// сохраняем для возврата данные удаляемого элемента

	if (size == 1)
	{
		delete current;
	}
	else // размер списка больше 1 элемента
	{
		ELEMENT *next = current->next;

		current->data = current->next->data;
		current->next = current->next->next;
		delete next;
	}

	size--;

	if (size == 0)
		current = NULL;

	return data;
}

template <class T>
void clist<T>::Clear()
{
	while (!Empty())
		Remove();				// циклически удаляем все элементы списка
}

template <class T>
void clist<T>::Next()
{
	if (!Empty())
		current = current->next;	// Смещаем указатель текущей позиции списка на следующий элемент
}

template <class T>
void clist<T>::Prev()
{
	if (Empty())
		return;

	ELEMENT *prev = current;
	while (prev->next != current) // Предыдущий элемент списка ищем в прямой последовательности перебором всех элементов
		prev = prev->next;
	current = prev;	// перенаправляем текущий элемент на следующий
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
		cout << "List is empty." << endl;
		return;
	}

	ELEMENT *next = current;
	cout << next->data << " ";
	while (next->next != current)
	{
		cout << next->next->data << " ";
		next = next->next;
	}
}

