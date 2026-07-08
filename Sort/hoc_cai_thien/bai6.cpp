#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Node
{
private:
    T data;
    Node<T> *next;

public:
    Node(T data)
    {
        this->data = data;
        this->next = nullptr;
    }
    Node()
    {
        this->next = nullptr;
    }
    void insert(Node<T> *p)
    {
        p->next = this->next;
        this->next = p;
    }
    T getData() { return this->data; }
    void setData(T data) { this->data = data; }
    Node<T> *getNext() { return next; }
    void setNext(Node<T> *next) { this->next = next; }
};

template <typename T>
class List
{
private:
    Node<T> *head;
    Node<T> *trail;

public:
    List()
    {
        head = nullptr;
        trail = nullptr;
    }
    void push_back(Node<T> *p)
    {
        if (trail == nullptr)
        {
            head = p;
            trail = p;
        }
        else
        {
            trail->setNext(p);
            trail = p;
        }
    }
    void push_front(Node<T> *p)
    {
        if (!head)
        {
            push_back(p);
            return;
        }
        p->setNext(head);
        head = p;
    }
    void push(int i, Node<T> *p)
    {
        if (i == 0)
        {
            push_front(p);
            return;
        }
        Node<T> *temp = head;
        int cnt = 0;
        while (cnt < i - 1 && temp->getNext())
        {
            temp = temp->getNext();
            cnt++;
        }
        temp->insert(p);
    }

    void BubbleSort(bool (*comp)(T, T))
    {
        if (!head)
            return;
        Node<T> *i = head;
        while (i != nullptr)
        {
            Node<T> *j = head;
            while (j->getNext() != nullptr)
            {
                if (comp(j->getData(), j->getNext()->getData()))
                {
                    T tmp = j->getData();
                    j->setData(j->getNext()->getData());
                    j->getNext()->setData(tmp);
                }
                j = j->getNext();
            }
            i = i->getNext();
        }
    }

    void SelectSort()
    {
        if (!head)
            return;
        Node<T> *i = head;
        while (i->getNext() != nullptr)
        {
            Node<T> *minNode = i;
            Node<T> *j = i->getNext();
            while (j != nullptr)
            {
                if (j->getData() < minNode->getData())
                {
                    minNode = j;
                }
                j = j->getNext(); // luôn tăng j, bất kể điều kiện đúng/sai
            }
            if (minNode != i)
            {
                T tmp = i->getData();
                i->setData(minNode->getData());
                minNode->setData(tmp);
            }
            i = i->getNext(); // tăng i để xử lý vị trí kế tiếp
        }
    }

    void InsertSort()
    {
        if (!head || !head->getNext())
            return;

        Node<T> *sorted = nullptr; // đầu của phần đã sắp xếp (xây mới)
        Node<T> *current = head;

        while (current != nullptr)
        {
            Node<T> *next = current->getNext(); // lưu lại trước khi nối lại next

            if (sorted == nullptr || current->getData() < sorted->getData())
            {
                // current nhỏ nhất trong phần đã sắp -> chèn lên đầu
                current->setNext(sorted);
                sorted = current;
            }
            else
            {
                // dò từ đầu phần đã sắp (chỉ đi tới) để tìm vị trí chèn
                Node<T> *search = sorted;
                while (search->getNext() != nullptr &&
                       search->getNext()->getData() < current->getData())
                {
                    search = search->getNext();
                }
                current->setNext(search->getNext());
                search->setNext(current);
            }
            current = next; // tiếp tục với node kế tiếp của list gốc
        }

        head = sorted;

        // cập nhật lại trail (vì head đã thay đổi cấu trúc liên kết hoàn toàn)
        trail = head;
        while (trail->getNext() != nullptr)
            trail = trail->getNext();
    }

    void print()
    {
        for (Node<T> *p = head; p != nullptr; p = p->getNext())
            cout << p->getData() << ' ';
        cout << '\n';
    }
};

template <typename T>
bool tang(T a, T b) { return a > b; }

template <typename T>
bool giam(T a, T b) { return a < b; }

int main()
{
    List<int> l;
    int vals[] = {5, 1, 4, 2, 8, 9};
    for (int v : vals)
        l.push_back(new Node<int>(v));

    cout << "Truoc khi sort: ";
    l.print();

    l.BubbleSort(tang);
    cout << "Sau sort tang: ";
    l.print();

    l.BubbleSort(giam);
    cout << "Sau sort giam: ";
    l.print();

    return 0;
}