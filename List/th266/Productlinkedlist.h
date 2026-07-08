#pragma once
#include <bits/stdc++.h>
using namespace std;

class Product
{
private:
    int id;
    string name;
    string category;
    int quantity;
    double price;

public:
    Product() : id(0), name(""), category(""), quantity(0), price(0.0) {}

    Product(int id, string name, string category, int quantity, double price) : id(id),
        name(name), category(category), quantity(quantity), price(price) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getCategory() const { return category; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    void setQuantity(int q) { this->quantity = q; }
    void setPrice(double price) { this->price = price; }

    friend ostream &operator<<(ostream &os, const Product &p)
    {
        // FIX "Gia: 2.5e+06": mac dinh cout dung dinh dang "general float" voi
        // precision = 6 chu so co nghia -> so >= 1e6 se tu chuyen sang dang
        // khoa hoc (scientific notation). Phai ep "fixed" + setprecision(0)
        // khi in price thi moi hien day du nhu "2500000".
        // Luu/khoi phuc lai flags & precision cu de khong lam anh huong toi
        // cac lenh cout khac sau do (vi os chinh la cout, thay doi se "dinh"
        // luon cho ca chuong trinh neu khong restore lai).
        ios::fmtflags oldFlags = os.flags();
        streamsize oldPrecision = os.precision();

        os << "ID: " << p.id
           << " | Ten: " << p.name
           << " | Loai: " << p.category
           << " | SL: " << p.quantity
           << " | Gia: " << fixed << setprecision(0) << p.price;

        os.flags(oldFlags);
        os.precision(oldPrecision);
        return os;
    }

    // Can 2 phep so sanh nay de Partition/quickSort (von viet cho int) dung
    // duoc truc tiep cho Product, khong phai sua lai thuat toan chia de tri.
    // So sanh theo don gia (price).
    friend bool operator<=(const Product &a, const Product &b) { return a.price <= b.price; }
    friend bool operator>(const Product &a, const Product &b) { return a.price > b.price; }
};

// ====== Quick sort tong quat (chia de tri) ======
template <class T>
int Partition(T *a, int left, int right)
{
    T x = a[left];
    int i = left + 1;
    int j = right;
    do
    {
        while (i <= j && a[i] <= x) i++;
        while (i <= j && a[j] > x) j--;
        if (i < j)
        {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    } while (i <= j);
    swap(a[left], a[j]);
    return j;
}

template <class T>
void quickSort(T *a, int left, int right)
{
    int k;
    if (left < right)
    {
        k = Partition(a, left, right);
        quickSort(a, left, k - 1);
        quickSort(a, k + 1, right);
    }
}

template <class T>
class Node
{
private:
    Product product;
    Node<Product> *next;

public:
    Node(Product p) : product(p), next(nullptr) {}
    Node() : product(), next(nullptr) {}

    void insert(Node<Product> *p)
    {
        p->next = this->next;
        this->next = p;
    }

    Product &getProduct() { return this->product; }
    void setProduct(Product p) { this->product = p; }

    Node<Product> *getNext() { return this->next; }
    void setNext(Node<Product> *p) { this->next = p; }
};

class Iterator
{
private:
    Node<Product> *ptr;

public:
    Iterator(Node<Product> *p) : ptr(p) {}
    Product &operator*() { return ptr->getProduct(); }
    Product *operator->() { return &ptr->getProduct(); }
    Node<Product> *node() { return ptr; }
    Iterator &operator++()
    {
        ptr = ptr->getNext();
        return *this;
    }
    Iterator operator++(int)
    {
        Iterator tmp = *this;
        ptr = ptr->getNext();
        return tmp;
    }
    bool operator!=(const Iterator &other) { return ptr != other.ptr; }
    bool operator==(const Iterator &other) { return ptr == other.ptr; }
};

class ProductLinkedList
{
private:
    Node<Product> *head;
    Node<Product> *trail;

public:
    ProductLinkedList() : head(nullptr), trail(nullptr) {}

    ~ProductLinkedList()
    {
        Node<Product> *cur = head;
        while (cur != nullptr)
        {
            Node<Product> *tmp = cur->getNext();
            delete cur;
            cur = tmp;
        }
        head = trail = nullptr;
    }

    bool isEmpty() const { return head == nullptr; }

    int size() const
    {
        int count = 0;
        for (Node<Product> *cur = head; cur != nullptr; cur = cur->getNext())
            count++;
        return count;
    }

    void pushBack(Node<Product> *p)
    {
        if (trail == nullptr)
        {
            head = trail = p;
            return;
        }
        trail->setNext(p);
        trail = p;
    }

    void pushFront(Node<Product> *p)
    {
        if (head == nullptr)
        {
            head = trail = p;
            return;
        }
        p->setNext(head);
        head = p;
    }

    void push(int i, Node<Product> *p)
    {
        if (i <= 0 || head == nullptr)
        {
            pushFront(p);
            return;
        }
        Node<Product> *tmp = head;
        int pos = 0;
        while (pos < i - 1 && tmp->getNext() != nullptr)
        {
            tmp = tmp->getNext();
            pos++;
        }
        tmp->insert(p);
        if (tmp == trail)
        {
            trail = p;
        }
    }

    void addProduct(const Product &p)
    {
        pushBack(new Node<Product>(p));
    }

    void print()
    {
        if (head == nullptr)
        {
            cout << "(Danh sach rong)\n";
            return;
        }
        for (Iterator it = begin(); it != end(); ++it)
            cout << *it << "\n";
    }

    Iterator find(int id)
    {
        for (Iterator it = begin(); it != end(); ++it)
            if (it->getId() == id) return it;
        return end();
    }

    Product *searchById(int id)
    {
        Iterator it = find(id);
        if (it == end()) return nullptr;
        return &(*it);
    }

    bool removeById(int id)
    {
        if (head == nullptr) return false;

        if (head->getProduct().getId() == id)
        {
            Node<Product> *tmp = head;
            head = head->getNext();
            if (head == nullptr) trail = nullptr;
            delete tmp;
            return true;
        }

        Node<Product> *prev = head;
        Node<Product> *cur = head->getNext();
        while (cur != nullptr)
        {
            if (cur->getProduct().getId() == id)
            {
                prev->setNext(cur->getNext());
                if (cur == trail) trail = prev;
                delete cur;
                return true;
            }
            prev = cur;
            cur = cur->getNext();
        }
        return false;
    }

    bool updatePriceById(int productId, double price)
    {
        for (Iterator it = begin(); it != end(); ++it)
        {
            if (it->getId() == productId)
            {
                it->setPrice(price);
                return true;
            }
        }
        return false;
    }

    Product *findMaxPrice()
    {
        if (head == nullptr) return nullptr;

        Node<Product> *cur = head;
        Node<Product> *maxNode = head;
        while (cur != nullptr)
        {
            if (cur->getProduct().getPrice() > maxNode->getProduct().getPrice())
                maxNode = cur;
            cur = cur->getNext();
        }
        return &(maxNode->getProduct());
    }

    double totalValueStockQuantity()
    {
        double res = 0.0;
        for (Iterator it = begin(); it != end(); ++it)
            res += it->getPrice() * it->getQuantity();
        return res;
    }

    // ascending = true -> tang dan, false -> giam dan
    void sortByPrice(bool ascending = true)
    {
        int n = size();
        if (n <= 1) return;

        Product *arr = new Product[n];

        int idx = 0;
        for (Node<Product> *cur = head; cur != nullptr; cur = cur->getNext())
            arr[idx++] = cur->getProduct();

        quickSort<Product>(arr, 0, n - 1); // luon tra ve mang tang dan

        idx = 0;
        if (ascending)
        {
            for (Node<Product> *cur = head; cur != nullptr; cur = cur->getNext())
                cur->setProduct(arr[idx++]);
        }
        else
        {
            for (Node<Product> *cur = head; cur != nullptr; cur = cur->getNext())
                cur->setProduct(arr[n - 1 - idx++]);
        }

        delete[] arr;
    }

    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
};