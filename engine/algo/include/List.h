#pragma once
#include "General.h"

template <class T>
class List1 {
#ifdef GMOCK_DEBUG
public:
#else
protected:
#endif
    struct Node {
        T data;
        Node* next;
    };
    Node* tail;
    Node* head;
    int size;
    //http ://geneura.ugr.es/~jmerelo/c++-faq/nondependent-name-lookup-types.html
    l_sts _insert(T data, int index) {
        if (index == 0) {
            _push_start(data);
            return SUCCESS;
        }
        Node* prev_node;
        l_sts sts;
        sts = find(&prev_node, index - 1);
        if (sts > SUCCESS) {
            return sts;
        }
        if (prev_node->next == nullptr) {
            _push_back(data);
            return SUCCESS;
        }
        Node* post_node = prev_node->next;
        Node* current = new Node();
        current->data = data;
        current->next = post_node;
        prev_node->next = current;
        size++;
        return SUCCESS;
    }
    /*
    Insert data to start of list;
    Complexity is O(1);
    */
    l_sts _push_start(T data) {
        Node* m_node = new Node();
        m_node->next = head;
        m_node->data = data;
        head = m_node;
        if (tail == nullptr)
            tail = m_node;
        size++;
        return SUCCESS;
    }
    /*
    Insert data to back of list;
    Complexity is O(1);
    */
    l_sts _push_back(T data) {
        Node* m_node = new Node();
        m_node->data = data;
        m_node->next = nullptr;
        if (head == nullptr) {
            head = m_node;
        }
        else {
            tail->next = m_node;
        }
        tail = m_node;
        size++;
        return SUCCESS;
    }
    /*
    Get pointer of lists's element;
    Complexity is O(n);
    */
    l_sts find(Node** res, int index) {
        if (head == nullptr)
            return EMPTY;
        Node* cur = head;
        int m_index = 0;
        while (cur != nullptr) {
            if (m_index == index) {
                *res = cur;
                return SUCCESS;
            }
            m_index++;
            cur = cur->next;
        }
        return NOT_FOUND;
    }
    /*
    Remove data from list;
    Complexity is O(n);
    */
    l_sts remove(int index) {
        if (index == 0) {
            pop_start();
            return SUCCESS;
        }
        Node* prev_node;
        l_sts sts;
        sts = find(&prev_node, index - 1);
        if (sts > SUCCESS) {
            return sts;
        }
        if (prev_node->next == nullptr) {
            return NOT_FOUND;
        }
        if (prev_node->next->next != nullptr) {
            Node* current = prev_node->next;
            prev_node->next = prev_node->next->next;

            delete current;
        }
        else {
            pop_back();
            return SUCCESS;
        }
        size--;
        return SUCCESS;
    }
    /*
    Delete node from back of list;
    Complexity is O(n);
    */
    l_sts pop_back() {
        if (tail == nullptr) {
            return EMPTY;
        }

        Node* prev_node;
        l_sts sts = find(&prev_node, size - 2);
        int data = tail->data;
        delete tail;
        if (sts == SUCCESS) {
            tail = prev_node;
            tail->next = nullptr;
        }
        else {
            tail = nullptr;
            head = nullptr;
        }
        size--;
        return SUCCESS;
    }
    /*
    Delete node from start of list;
    Complexity is O(1);
    */
    l_sts pop_start() {
        if (head == nullptr) {
            return EMPTY;
        }

        int data = head->data;
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else {
            Node* next = head->next;
            delete head;
            head = next;
        }
        size--;
        return SUCCESS;
    }
public:
    List1() : size(0), head(nullptr), tail(nullptr) {
    }
    ~List1() {
        Node* cur = head;
        while (cur != nullptr) {
            Node* tmp = cur;
            cur = cur->next;
            delete tmp;
        }
        head = nullptr;
        tail = nullptr;
    }
    void print() {
        std::cout << "Printing .." << std::endl;
        Node* cur = head;
        while (cur != nullptr) {
            std::cout << "Pointer: " << cur << " Value: " << cur->data << std::endl;
            cur = cur->next;
        }
        std::cout << "Size: " << size << std::endl;
    }
};
    
template <class T>
class List1_s : public Container_s<T>, public List1<T> {
public:
    T minimum() {
        return List1<T>::head->data;
    }
    T maximum() {
        return List1<T>::tail->data;
    }
    l_sts remove(int index) {
        return List1<T>::remove(index);
    }

    l_sts insert(T data) {
        int index = 0;
        typename List1<T>::Node* cur = List1<T>::head;
        while (cur != nullptr) {
            if (data <= cur->data)
                break;
            index++;
            cur = cur->next;
        }
        return  List1<T>::_insert(data, index);
    }
	l_sts pop_back() {
		return List1<T>::pop_back();
	}
	l_sts pop_start() {
		return List1<T>::pop_start();
	}
    T operator[](int index) {
        typename List1<T>::Node* current;
        l_sts sts = List1<T>::find(&current, index);
        if (sts == SUCCESS)
            return current->data;
        else {
            throw;
        }
    }
	int getSize() {
		return this->size;
	}
};

template <class T> class List1_ns : public Container_ns<T>, public List1<T> {
public:
	T minimum() {
		typename List1<T>::Node* cur = List1<T>::head;
		T min = cur->data;
		while (cur != NULL) {
			if (cur->data < min)
				min = cur->data;
			cur = cur->next;
		}
		return min;
	}
	T maximum() {
		typename List1<T>::Node* cur = List1<T>::head;
		T max = cur->data;
		while (cur != NULL) {
			if (cur->data > max)
				max = cur->data;
			cur = cur->next;
		}
		return max;
	}
	l_sts remove(int index) {
		return List1<T>::remove(index);
	}
	l_sts insert(T data, int index) {
		return List1<T>::_insert(data, index);
	}
	l_sts push_back(T data) {
		return List1<T>::_push_back(data);
	}
	l_sts push_start(T data) {
		return List1<T>::_push_start(data);
	}
	l_sts pop_back() {
		return List1<T>::pop_back();
	}
	l_sts pop_start() {
		return List1<T>::pop_start();
	}
	/*
	Get data;
	Complexity is O(n);
	*/
	T& operator[](int index) {
		typename List1<T>::Node* current;
		l_sts sts = List1<T>::find(&current, index);
		if (sts == SUCCESS)
			return current->data;
		else {
			throw;
		}
	}
	int getSize() {
		return this->size;
	}

};

template <class T>
class List2 {
#ifdef GMOCK_DEBUG
public:
#else
protected:
#endif
	struct Node {
		T data;
		Node* next;
		Node* prev;
	};
	Node* head;
	Node* tail;
	int size;
	l_sts _insert(T data, int index) {
		if (index == 0) {
			_push_start(data);
			return SUCCESS;
		}
		Node* prev_node;
		l_sts sts;
		sts = find(&prev_node, index - 1);
		if (sts > SUCCESS) {
			return sts;
		}
		if (prev_node->next == nullptr) {
			_push_back(data);
			return SUCCESS;
		}
		Node* post_node = prev_node->next;
		Node* current = new Node();
		current->data = data;
		current->next = post_node;
		current->prev = prev_node;
		prev_node->next = current;
		post_node->prev = current;
		size++;
		return SUCCESS;
	}
	/*
	Insert data to start of list;
	Complexity is O(1);
	*/
	l_sts _push_start(T data) {
		Node* m_node = new Node();
		m_node->next = head;
		m_node->prev = nullptr;
		m_node->data = data;
		head = m_node;
		if (tail == nullptr)
			tail = m_node;
		if (m_node->next)
			m_node->next->prev = m_node;
		size++;
		return SUCCESS;
	}
	/*
	Insert data to back of list;
	Complexity is O(1);
	*/
	l_sts _push_back(T data) {
		Node* m_node = new Node();
		m_node->data = data;
		m_node->next = nullptr;
		m_node->prev = tail;
		if (head == nullptr) {
			head = m_node;
		}
		else {
			tail->next = m_node;
		}
		tail = m_node;
		size++;
		return SUCCESS;
	}
	/*
	Get pointer of lists's element;
	Complexity is O(n);
	*/
	l_sts find(Node** res, int index) {
		if (head == nullptr)
			return EMPTY;
		Node* cur = head;
		int m_index = 0;
		while (cur != nullptr) {
			if (m_index == index) {
				*res = cur;
				return SUCCESS;
			}
			m_index++;
			cur = cur->next;
		}
		return NOT_FOUND;
	}
	/*
	Remove data from list;
	Complexity is O(n);
	*/
	l_sts remove(int index) {
		if (index == 0) {
			pop_start();
			return SUCCESS;
		}
		Node* prev_node;
		l_sts sts;
		sts = find(&prev_node, index - 1);
		if (sts > SUCCESS) {
			return sts;
		}
		if (prev_node->next == nullptr) {
			return NOT_FOUND;
		}
		if (prev_node->next->next != nullptr) {
			Node* current = prev_node->next;
			prev_node->next = prev_node->next->next;
			delete current;
		}
		else {
			pop_back();
			return SUCCESS;
		}
		size--;
		return SUCCESS;
	}
	/*
	Delete node from back of list;
	Complexity is O(n);
	*/
	l_sts pop_back() {
		if (tail == nullptr) {
			return EMPTY;
		}

		Node* prev_node = tail->prev;
		int data = tail->data;
		delete tail;
		if (prev_node != nullptr) {
			tail = prev_node;
			tail->next = nullptr;
		}
		else {
			tail = nullptr;
			head = nullptr;
		}
		size--;
		return SUCCESS;
	}
	/*
	Delete node from start of list;
	Complexity is O(1);
	*/
	l_sts pop_start() {
		if (head == nullptr) {
			return EMPTY;
		}

		int data = head->data;
		if (head->next == nullptr) {
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else {
			Node* next = head->next;
			next->prev = nullptr;
			delete head;
			head = next;
		}
		size--;
		return SUCCESS;
	}
public:
   List2() : head(nullptr), tail(nullptr), size(0) {
   }
   ~List2() {
       Node* cur = head;
       while (cur != nullptr) {
           Node* tmp = cur;
           cur = cur->next;
           delete tmp;
       }
       head = nullptr;
       tail = nullptr;
   }
   void print() {
	   std::cout << "Printing .." << std::endl;
	   Node* cur = head;
	   while (cur != nullptr) {
		   std::cout << "Pointer: " << cur << " Value: " << cur->data << std::endl;
		   cur = cur->next;
	   }
	   std::cout << "Size: " << size << std::endl;
   }

};

template <class T>
class List2_s : public List2<T>, Container_s<T> {
public:
    T minimum() {
        return List2<T>::head->data;
    }

    T maximum() {
        return List2<T>::tail->data;
    }
	l_sts remove(int index) {
		return List2<T>::remove(index);
	}
    /*
    Insert data to list using index;
    Complexity is O(n);
    */
    l_sts insert(T data) {
		int index = 0;
        typename List2<T>::Node* cur = this->head;
        while (cur != nullptr) {
            if (data <= cur->data)
                break;
            index++;
            cur = cur->next;
        }
        return List2<T>::_insert(data, index);
    }
	l_sts pop_back() {
		return List2<T>::pop_back();
	}

	l_sts pop_start() {
		return List2<T>::pop_start();
	}
    T operator[](int index) {
        typename List2<T>::Node* current;
        l_sts sts = List2<T>::find(&current, index);
        if (sts == SUCCESS)
            return current->data;
        else {
            throw;
        }
    }
	int getSize() {
		return this->size;
	}
};

template <class T>
class List2_ns : public List2<T>, Container_ns<T> {
public:
	T minimum() {
		typename List2<T>::Node* cur = this->head;
		T min = cur->data;
		while (cur != NULL) {
			if (cur->data < min)
				min = cur->data;
			cur = cur->next;
		}
		return min;
	}
	T maximum() {
		typename List2<T>::Node* cur = this->head;
		T max = cur->data;
		while (cur != NULL) {
			if (cur->data > max)
				max = cur->data;
			cur = cur->next;
		}
		return max;
	}
	l_sts remove(int index) {
		return List2<T>::remove(index);
	}

	l_sts insert(T data, int index) {
		return this->_insert(data, index);
	}

	l_sts replace(int index, T value) {
		if (index < 0 || index >= this->size) {
			return BOUNDS;
		}
		typename List2<T>::Node* node;
		l_sts sts;
		sts = List2<T>::find(&node, index);
		if (sts > SUCCESS) {
			return sts;
		}
		node->data = value;
		return SUCCESS;
	}
	
	l_sts push_back(T data) {
		return this->_push_back(data);
	}

	l_sts push_start(T data) {
		return this->_push_start(data);
	}

	l_sts pop_back() {
		return List2<T>::pop_back();
	}

	l_sts pop_start() {
		return List2<T>::pop_start();
	}

	T& operator[](int index) {
		typename List2<T>::Node* current;
		l_sts sts = List2<T>::find(&current, index);
		if (sts == SUCCESS)
			return current->data;
		else {
			throw;
		}
	}
	int getSize() {
		return this->size;
	}
};