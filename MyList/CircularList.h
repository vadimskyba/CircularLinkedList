// Реализация алгоритма циклического односвязного списка

template <class T>
class clist
{
	struct ELEMENT		// Структура элемент списка
	{
		T data;			// Данные элемента списка
		ELEMENT *next;	// Указатель на следующий єлемент списка
	};

private:
	ELEMENT *current;	// Указатель на текущий элемент списка
	int size;			// Размер списка

public:
	clist();	// Конструктор
	clist(clist<T> &src_list); // Конструктор с инициализацие: добавление элементов из источника src_list
	~clist();	// Деструктор

	int Size();		// Размер списка
	T Current();	// Текущий элемент списка
	void Insert(const T data);	// Добавить элемент 
	void operator +(const T data);	// Добавить элемент с помощью оператора +
	void Insert(clist<T> &src_list);	// Слияние списков
	T Remove();		// Удаление элемента списка
	void Clear();	// Очистка списка
	void Next();	// Смещение указателя списка на следующий єлемент
	void Prev();	// Смещение указателя списка на предыдущий элемент
	bool Empty();	// Список пуст?
	void Print();	// Вывод списка в поток
	void Sort(bool bAscending = false);	// Сортировка списка
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

	if (Empty()) // пустой список
	{
		newElement->next = newElement; // 1 элемент в списке: указатель следующего элемента указывает сам на себя
	}
	else // список не пуст
	{
		newElement->next = current;

		// Циклически ищем предыдущий элемент 
		ELEMENT *prev = current;
		while (prev->next != current)
			prev = prev->next;

		prev->next = newElement; // и устанавливаем указатель сдедующего элемента ->next на новый элемент newElement
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
void clist<T>::Insert(clist<T> &src_list)
{
	if (src_list.Empty())
		return;

	Insert(src_list.current->data);				// Вставляем текущий элемент списка src_list

	// Циклически вставляем последующие элементы, пока не упремся в текущий элемент списка src_list
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

	T data = current->data;		// сохраняем для возврата данные удаляемого элемента
	ELEMENT *tmp = current;		// копируем текущий удаляемый элемент на временную переменную

	if (size == 1)				// В списке будет удален последний элемент
	{
		current = NULL;			// значит указатель текущего элемента обнуляем
	}
	else
	{
		// Циклически ищем предыдущий элемент и устанавливаем указатель сдедующего элемента ->next на следующий за current элемент
		ELEMENT *prev = current;
		while (prev->next != current)
			prev = prev->next;
		prev->next = current->next;

		current = current->next;	// перенаправляем текущий элемент на следующий
	}

	delete tmp;					// удаляем временной элемент
	size--;						// уменшаем размер списка

	return data;				// возвращаем данные удаленного элемента
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
		cout << "Список пуст" << endl;
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

	clist<T> sortedList; // Временный список, содержащий отсортированные элементы

	while (!Empty())	// Рекурсивно делаем проходы списка, пока он не обнулится
	{
		ELEMENT *sortedElement = current; // элемент списка, который содержит макс. (bAscending == false) или мин. (bAscending == true) значение данных (в зависимости от bAscending)
		ELEMENT *next = current;

		while (next->next != current)	// Далаем проход списка и ищем макс. или мин. значение 
		{
			if (bAscending) // Восходящая сортировка
			{
				if (next->next->data < sortedElement->data)
					sortedElement = next->next;
			}
			else // Убывающая сортировка
			{
				if (next->next->data > sortedElement->data)
					sortedElement = next->next;
			}

			next = next->next;
		}
		current = sortedElement;
		sortedList.Insert(Remove()); // Перемещаем текущий элемент во временный список
	}

	Insert(sortedList);	// Копируем элементы временного отсортированного в текущий список
}