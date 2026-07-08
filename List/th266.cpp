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
    void setPrice(double price) { this->price = price; }

    friend ostream &operator<<(ostream &os, const Product &p)
    {
        os << "ID: " << p.id
           << " | Ten: " << p.name
           << " | Loai: " << p.category
           << " | SL: " << p.quantity
           << " | Gia: " << p.price;
        return os;
    }

    // Cần 2 phép so sánh này để hàm Partition/quickSort (vốn viết cho int)
    // dùng được trực tiếp cho Product, không phải sửa lại thuật toán chia để trị.
    // So sánh theo đơn giá (price).
    friend bool operator<=(const Product &a, const Product &b) { return a.price <= b.price; }
    friend bool operator>(const Product &a, const Product &b) { return a.price > b.price; }
};

// ====== Quick sort tổng quát (chia để trị) - giữ nguyên thuật toán bạn viết,
// chỉ sửa 2 lỗi để nó thực sự generic theo T thay vì luôn coi pivot là int ======
template <class T>
int Partition(T *a, int left, int right)
{
    T x = a[left]; // BUG cũ: "int x = a[left]" -> ép kiểu về int, sai khi T = Product
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
            j--; // BUG cũ: "j--;x" -> dư ký tự x gây lỗi cú pháp
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

    // ===== 1. Thêm mặt hàng vào danh sách =====
    void addProduct(const Product &p)
    {
        pushBack(new Node<Product>(p));
    }

    // ===== 2. In danh sách mặt hàng =====
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

    // ===== 3. Tìm kiếm mặt hàng theo mã =====
    Product *searchById(int id)
    {
        Iterator it = find(id);
        if (it == end()) return nullptr;
        return &(*it);
    }

    // ===== 4. Xóa mặt hàng theo mã =====
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

    // ===== 5. Cập nhật đơn giá mặt hàng =====
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

    // ===== 6. Tìm mặt hàng có đơn giá cao nhất (so sánh tuyến tính, không dùng cây) =====
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

    // ===== 7. Tính tổng giá trị hàng tồn kho =====
    double totalValueStockQuantity()
    {
        double res = 0.0;
        for (Iterator it = begin(); it != end(); ++it)
            res += it->getPrice() * it->getQuantity();
        return res;
    }

    // ===== 8. Sắp xếp danh sách theo đơn giá bằng quick sort =====
    // Không dùng vector: chỉ mượn 1 mảng C thuần (new[]/delete[]) làm vùng nhớ tạm
    // cho thuật toán chia để trị, danh sách liên kết vẫn do ta tự cài đặt.
    void sortByPrice()
    {
        int n = size();
        if (n <= 1) return;

        Product *arr = new Product[n];

        int idx = 0;
        for (Node<Product> *cur = head; cur != nullptr; cur = cur->getNext())
            arr[idx++] = cur->getProduct();

        quickSort<Product>(arr, 0, n - 1);

        idx = 0;
        for (Node<Product> *cur = head; cur != nullptr; cur = cur->getNext())
            cur->setProduct(arr[idx++]);

        delete[] arr;
    }

    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
};

int main()
{
    ProductLinkedList list;

    // 1. Thêm mặt hàng
    list.addProduct(Product(1, "Ban phim", "Phu kien", 10, 250000));
    list.addProduct(Product(2, "Chuot", "Phu kien", 20, 150000));
    list.addProduct(Product(3, "Man hinh", "Man hinh", 5, 2500000));
    list.addProduct(Product(4, "Tai nghe", "Am thanh", 8, 350000));
    list.addProduct(Product(5, "Webcam", "Phu kien", 12, 400000));

    // 2. In danh sách
    cout << "-- Danh sach ban dau --\n";
    list.print();

    // 3. Tìm kiếm theo mã
    cout << "\n-- Tim id = 3 --\n";
    Product *found = list.searchById(3);
    if (found) cout << *found << "\n";
    else cout << "Khong tim thay\n";

    // 5. Cập nhật đơn giá
    cout << "\n-- Cap nhat gia id = 2 thanh 175000 --\n";
    list.updatePriceById(2, 175000);
    list.print();

    // 6. Mặt hàng giá cao nhất
    cout << "\n-- Mat hang gia cao nhat --\n";
    cout << *(list.findMaxPrice()) << "\n";

    // 7. Tổng giá trị hàng tồn kho
    cout << "\n-- Tong gia tri hang ton kho --\n";
    cout << fixed << setprecision(0) << list.totalValueStockQuantity() << "\n";

    // 8. Sắp xếp theo đơn giá (quick sort)
    cout << "\n-- Sau khi sap xep theo don gia tang dan --\n";
    list.sortByPrice();
    list.print();

    // 4. Xóa theo mã
    cout << "\n-- Xoa id = 1 --\n";
    list.removeById(1);
    list.print();

    return 0;
}