#pragma once
#include "Defs.h"
#include "General.h"

template <class T>
class List1 {
protected:
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
    int getSize() {
        return size;
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
    /*
    Get data;
    Complexity is O(n);
    */
    T operator[](int index) {
        typename List1<T>::Node* current;
        l_sts sts = List1<T>::find(&current, index);
        if (sts == SUCCESS)
            return current->data;
        else {
            throw;
        }
    }
    l_sts pop_back() {
        return List1<T>::pop_back();
    }
    l_sts pop_start() {
        return List1<T>::pop_start();
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
	l_sts replace(int index, T value) {
		if (index < 0 || index >= List1<T>::size) {
			return BOUNDS;
		}
		typename List1<T>::Node* node;
		l_sts sts;
		sts = List1<T>::find(&node, index);
		if (sts > SUCCESS) {
			return sts;
		}
		node->data = value;
		return SUCCESS;
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
};

template <class T>
class List2 {
public:
   struct Node {
       T data;
       Node* next;
       Node* prev;
   };
   Node* head;
   Node* tail;
   int size;
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
   virtual l_sts find(Node** res, int index) = 0;
   int getSize() {
       return size;
   }
};

template <class T>
class List2_s : public List2<T>, Container_s<T> {
protected:
    l_sts _insert(T data, int index) {
        if (index == 0) {
            _push_start(data);
            return SUCCESS;
        }
        typename List2<T>::Node* prev_node;
        l_sts sts;
        sts = find(&prev_node, index - 1);
        if (sts > SUCCESS) {
            return sts;
        }
        if (prev_node->next == nullptr) {
            _push_back(data);
            return SUCCESS;
        }
        typename List2<T>::Node* post_node = prev_node->next;
        typename List2<T>::Node* current = new typename List2<T>::Node();
        current->data = data;
        current->next = post_node;
        current->prev = prev_node;
        prev_node->next = current;
        post_node->prev = current;
        this->size++;
        return SUCCESS;
    }
    /*
    Insert data to start of list;
    Complexity is O(1);
    */
    l_sts _push_start(T data) {
        typename List2<T>::Node* m_node = new typename List2<T>::Node();
        m_node->next = this->head;
        m_node->prev = nullptr;
        m_node->data = data;
        this->head = m_node;
        if (this->tail == nullptr)
            this->tail = m_node;
        if (m_node->next)
            m_node->next->prev = m_node;
        this->size++;
        return SUCCESS;
    }
    /*
    Insert data to back of list;
    Complexity is O(1);
    */
    l_sts _push_back(T data) {
        typename List2<T>::Node* m_node = new typename List2<T>::Node();
        m_node->data = data;
        m_node->next = nullptr;
        m_node->prev = this->tail;
        if (this->head == nullptr) {
            this->head = m_node;
        }
        else {
            this->tail->next = m_node;
        }
        this->tail = m_node;
        this->size++;
        return SUCCESS;
    }
public:
    void print() {
        std::cout << "Printing .." << std::endl;
        typename List2<T>::Node* cur = this->head;
        while (cur != nullptr) {
            std::cout << "Pointer: " << cur << " Value: " << cur->data << std::endl;
            cur = cur->next;
        }
        std::cout << "Size: " << this->size << std::endl;
    }

    l_sts replace(int index, T value) {
        if (index < 0 || index >= this->size) {
            return BOUNDS;
        }
        l_sts sts = remove(index);
        if (sts > SUCCESS)
            return sts;
        sts = insert(value);
        if (sts > SUCCESS)
            return sts;
        return SUCCESS;
    }

    T minimum() {
        return this->head->data;
    }

    T maximum() {
        return this->tail->data;
    }

    /*
    Delete node from back of list;
    Complexity is O(n);
    */
    T pop_back() {
        if (this->tail == nullptr) {
            return EMPTY;
        }

        typename List2<T>::Node* prev_node = this->tail->prev;
        int data = this->tail->data;
        delete this->tail;
        if (prev_node != nullptr) {
            this->tail = prev_node;
            this->tail->next = nullptr;
        }
        else {
            this->tail = nullptr;
            this->head = nullptr;
        }
        this->size--;
        return data;
    }
    /*
    Delete node from start of list;
    Complexity is O(1);
    */
    T pop_start() {
        if (this->head == nullptr) {
            return EMPTY;
        }

        int data = this->head->data;
        if (this->head->next == nullptr) {
            delete this->head;
            this->head = nullptr;
            this->tail = nullptr;
        }
        else {
            typename List2<T>::Node* next = this->head->next;
            next->prev = nullptr;
            delete this->head;
            this->head = next;
        }
        this->size--;
        return data;
    }

    /*
    Get pointer of lists's element;
    Complexity is O(n);
    */
    l_sts find(typename List2<T>::Node** res, int index) {
        if (this->head == nullptr)
            return EMPTY;
        typename List2<T>::Node* cur = this->head;
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
    Insert data to list using index;
    Complexity is O(n);
    */
    l_sts insert(T data, int index = 0) {
        typename List2<T>::Node* cur = this->head;
        while (cur != nullptr) {
            if (data <= cur->data)
                break;
            index++;
            cur = cur->next;
        }
        return _insert(data, index);
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
        typename List2<T>::Node* prev_node;
        l_sts sts;
        sts = find(&prev_node, index - 1);
        if (sts > SUCCESS) {
            return sts;
        }
        if (prev_node->next == nullptr) {
            return NOT_FOUND;
        }
        if (prev_node->next->next != nullptr) {
            typename List2<T>::Node* current = prev_node->next;
            prev_node->next = prev_node->next->next;

            delete current;
        }
        else {
            pop_back();
            return SUCCESS;
        }
        this->size--;
        return SUCCESS;
    }
    /*
    Get data;
    Complexity is O(n);
    */
    T operator[](int index) {
        typename List2<T>::Node* current;
        l_sts sts = find(&current, index);
        if (sts == SUCCESS)
            return current->data;
        else {
            throw;
        }
    }
};

template <class T>
class List2_ns : public List2<T>, Container_ns<T> {
public:
	l_sts replace(int index, T value) {
		if (index < 0 || index >= this->size) {
			return BOUNDS;
		}
		typename List2<T>::Node* node;
		l_sts sts;
		sts = this->find(&node, index);
		if (sts > SUCCESS) {
			return sts;
		}
		node->data = value;
		return SUCCESS;
	}
	/*
	Insert data to list using index;
	Complexity is O(n);
	*/
	l_sts insert(T data, int index) {
		return this->_insert(data, index);
	}
	l_sts push_start(T data) {
		return this->_push_start(data);
	}
	l_sts push_back(T data) {
		return this->_push_back(data);
	}
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
};