#ifndef __List__
#define __List__

template<typename Value_type>
class Node
{
public:
	Value_type* value;
	Node<Value_type>* next;

	Node()
	{
		next = nullptr;
		value = nullptr;
	}
};


template<typename Value_type>
class List
{
private:
	Node<Value_type>* find_by_index(int index)
	{
		Node<Value_type>* current_node = head;
		for (int i=0; i<index; ++i)
		{
			if (current_node == nullptr)
				return nullptr;
			current_node = current_node->next;
		}	
		return current_node;
	}
public:
	Node<Value_type>* head;

	List()
	{
		head = nullptr;
	}

	int length()
	{
		Node<Value_type>* current_node = head;
		int length = 0;

		while (current_node != nullptr)
		{
			current_node = current_node->next;
			length += 1;
		}
		return length;
	}

	void push_front(Value_type& value)
	{
		Node<Value_type>* first = new Node<Value_type>;

		first->value = &value;
		first->next = head;

		head = first;
	}

	void pop_front()
	{
		Node<Value_type>* new_head = head->next;
		delete head;
		head = new_head;
	}

	void insert(Value_type& value, int index)
	{
		if (index == 0)
		{
			push_front(value);
		} else {
			Node<Value_type>* previous_node = find_by_index(index-1);

			Node<Value_type>* new_node = new Node<Value_type>;

			new_node->value = &value;
			new_node->next = previous_node->next;

			previous_node->next = new_node;
		}
	}

	void pop(int index)
	{
		if (index == 0)
		{
			return;
		} else {
			Node<Value_type>* previous_node = find_by_index(index-1);

			Node<Value_type>* replacing_node = previous_node->next->next;
			delete previous_node->next;
			previous_node->next = replacing_node;
		}
	}

	void push_back(Value_type& value)
	{
		Node<Value_type>** current_node = &head;
		while (*current_node != nullptr)
		{
			current_node = &(*current_node)->next;
		}

		Node<Value_type>* last = new Node<Value_type>;

		last->value = &value;
		last->next = nullptr;

		*current_node = last;
	}

	void pop_back()
	{
		Node<Value_type>* previous_node;
		if (head->next == nullptr)
		{
			previous_node = head;
			delete head;
			head = nullptr;
		} else {
			Node<Value_type>* current_node = head;
			while (current_node->next->next != nullptr)
			{
				current_node = current_node->next;
			}
			previous_node = current_node;

			delete previous_node->next;
			previous_node->next = nullptr;
		}
	}

	void remove(Value_type& value)
	{
		Value_type* value_ptr = &value;
		if (head == nullptr)
			return;
		if (head->value == value_ptr)
		{
			pop_front();
			return;
		}
		if (head->next == nullptr)
		{
			return;
		}

		Node<Value_type>* current_Node = head;
		bool found_value = false;

		while (current_Node->next != nullptr)
		{
			if (current_Node->next->value == value_ptr)
			{
				found_value = true;
				break;
			}
			current_Node = current_Node->next;
		}

		if (found_value)
		{
			Node<Value_type>* replacing_Node = current_Node->next->next;
			delete current_Node->next;
			current_Node->next = replacing_Node;
		}
	}

	Value_type& operator[](int index)
	{
		return *find_by_index(index)->value;
	}

	void clear()
	{
		while (head != nullptr)
		{
			pop_front();
		}
	}

	void operator=(List<Value_type>& another)
	{
		clear();

		Node<Value_type>* current_node = another.head;
		Node<Value_type>** added_before = &head;
		Node<Value_type>* new_node;
		while (current_node != nullptr)
		{
			new_node = new Node<Value_type>;
			new_node->value = current_node->value;
			*added_before = new_node;

			added_before = &new_node->next;
			current_node = current_node->next;
		}
	}

	~List()
	{
		clear();
	}
};

#endif
