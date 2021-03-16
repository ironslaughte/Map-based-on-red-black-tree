#pragma once
template <class Value>
class List {
public:
    List();
    ~List();
    void Pop_Front();
    void Clear();
    void Push_back(Value number);
    void Push_front(Value number);
    void Pop_back();
    void Insert(Value s, size_t index);
    void Print_to_console();
    size_t GetSize();
    bool IsEmpty();
    void Set(size_t index, Value number);
    Value& operator[] (size_t index);
    void Reverse();
    void Remove(size_t index);
private:
    template <class Value>
    class Node {
    public:
        Node* pnext;
        Value obj;
        Node(Value obj, Node<Value>* pNext = nullptr) {
            this->obj = obj;
            this->pnext = pNext;
  
        }
    };
    size_t Size;
    Node<Value>* head;
};

template <class Value>
List<Value>::~List() {
    Clear();
}

template <class Value>
List<Value>::List() {
    Size = 0;
    head = nullptr;
}

template <class Value>
void List<Value>::Pop_back() {
    Node<Value>* cur = head;
    while (cur->pnext != nullptr) {
        cur = cur->pnext;
    }
    delete cur;
    Size--;
}

template <class Value>
void List<Value>::Pop_Front()
{
    Node<Value>* cur = head;
    head = head->pnext;
    delete cur;
    Size--;
}

template <class Value>
void List<Value>::Push_front(Value number) {
    head = new Node<Value>(number, head);
    Size++;
}

template <class Value>
void List<Value>::Clear()
{
    while (Size > 0) {
        Pop_Front();
    }
}



template <class Value>
void List<Value>::Push_back(Value number)
{
    if (head == nullptr) {
        head = new Node<Value>(number);
    }
    else {
        Node<Value>* cur = head;
        while (cur->pnext != nullptr) {
            cur = cur->pnext;
        }
        cur->pnext = new Node<Value>(number);
    }
    Size++;
}

template <class Value>
size_t List<Value>::GetSize()
{
    return Size;
}

template <class Value>
void List<Value>::Insert(Value s, size_t index)
{
    if (index > Size + 1) {
        throw std::out_of_range("Wrong index\n");
    }
    if (index == Size) {
        Push_back(s);
    }

    if (index == 0) {
        Push_front(s);
    }
    else {
        Node<Value>* prev = head;
        for (int i = 0; i < (index - 1); i++) {
            prev = prev->pnext;
        }
        Node<Value>* newNode = new Node<Value>(s, prev->pnext);
        prev->pnext = newNode;
        Size++;
    }

}

template <class Value>
Value& List<Value>::operator[](size_t index)
{
    int count = 0;
    Node<Value>* cur = head;
    while (cur != nullptr) {
        if (count == index) {
            return cur->obj;
        } cur = cur->pnext;
        count++;
    }
}

template <class Value>
void List<Value>::Print_to_console() {
    Node<Value>* cur = head;
    for (size_t i = 0; i < Size; i++) {
        std::cout << cur->Num << " ";
        cur = cur->pnext;
    }
    std::cout << "\n";
}

template <class Value>
bool List<Value>::IsEmpty() {

    return Size == 0;
}

template <class Value>
void List<Value>::Set(size_t index, Value number) {
    if (index > Size - 1)
        throw std::out_of_range("Wrong index\n");
    size_t i = 0;
    Node<Value>* cur = head;
    while (cur != nullptr) {
        if (i == index) {
            cur->Num = number;
            break;
        }
        i++;
        cur = cur->pnext;
    }
}

template <class Value>
void List<Value>::Reverse() {
    List tmp_list = *this;
    for (size_t i = 0; i < Size / 2; i++) {
        int tmp_number = tmp_list[i];
        tmp_list[i] = tmp_list[Size - i - 1];
        tmp_list[Size - i - 1] = tmp_number;
    }
    *this = tmp_list;
}

template <class Value>
void List<Value>::Remove(size_t index) {
    if (index > Size - 1) {
        throw std::out_of_range("Wrong index\n");
    }
    if (index == 0) {
        Pop_Front();
    }
    else if (index == Size - 1) {
        Pop_back();
    }
    else {
        Node<Value>* cur = head;
        size_t i = 0;
        while (cur != nullptr) {
            if (index == i - 1) {
                Node<Value>* tmp = cur->pnext;
                cur->pnext = tmp->pnext;
                delete tmp;
                break;
            }
            i++;
            cur = cur->pnext;
        }
    }
}


