#include "Platform.h"

class Node
{
public:
	Platform* value;
	Node* next;

	Node()
	{
		next = nullptr;
		value = nullptr;
	}

	~Node()
	{
		delete value;
	}
};


class List
{
private:
	Node* find_by_index(int index)
	{
		Node* current_node = head;
		for (int i=0; i<index; ++i)
		{
			current_node = current_node->next;
		}	
		return current_node;
	}
public:
	Node* head;

	List()
	{
		head = nullptr;
	}

	int length()
	{
		Node* current_node = head;
		int length = 0;

		while (current_node != nullptr)
		{
			current_node = current_node->next;
			length += 1;
		}
		return length;
	}

	void push_front(Platform value)
	{
		Node* first = new Node;

		Platform* new_value = new Platform(value.x, value.y, value.kind);
		first->value = new_value;
		first->next = head;

		head = first;
	}

	Platform pop_front()
	{
		Platform pop_value = *head->value;
		Node* new_head = head->next;
		delete head;
		head = new_head;
		return pop_value;
	}

	void insert(Platform& value, int index)
	{
		if (index == 0)
		{
			push_front(value);
		} else {
			Node* previous_node = find_by_index(index-1);

			Node* new_node = new Node;

			new_node->value = &value;
			new_node->next = previous_node->next;

			previous_node->next = new_node;
		}
	}

	Platform pop(int index)
	{
		if (index == 0)
		{
			return pop_front();
		} else {
			Node* previous_node = find_by_index(index-1);

			Platform pop_value = *previous_node->next->value;
			Node* replacing_node = previous_node->next->next;
			delete previous_node->next;
			previous_node->next = replacing_node;
			return pop_value;
		}
	}

	void push_back(Platform& value)
	{
		Node** current_node = &head;
		while (*current_node != nullptr)
		{
			current_node = &(*current_node)->next;
		}

		Node* last = new Node;

		last->value = &value;
		last->next = nullptr;

		*current_node = last;
	}

	Platform pop_back()
	{
		Node* previous_node;
		if (head->next == nullptr)
		{
			previous_node = head;
			Platform pop_value = *head->value;
			delete head;
			head = nullptr;
			return pop_value;
		} else {
			Node* current_node = head;
			while (current_node->next->next != nullptr)
			{
				current_node = current_node->next;
			}
			previous_node = current_node;

			Platform pop_value = *previous_node->next->value;
			delete previous_node->next;
			previous_node->next = nullptr;
			return pop_value;
		}
	}

	Platform& operator[](int index)
	{
		Node* current_node = head;
		for (int i=0; i<index; ++i)
		{
			current_node = current_node->next;
		}
		return *current_node->value;
	}

	Platform& find(int index)
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

	void print()
	{
		Node* current_node = head;
		while (current_node != nullptr)
		{
			current_node->value->print();
			current_node = current_node->next;
		}
		printf("\n");
	}

	void operator=(List& another)
	{
		clear();

		Node* current_node = another.head;
		Node** added_before = &head;
		Node* new_node;
		while (current_node != nullptr)
		{
			new_node = new Node;
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
