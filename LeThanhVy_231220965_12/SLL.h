#pragma once
#include <iostream>
using namespace std;

// ============================================================================
// NODE
// ============================================================================
#pragma region Node

template <typename T>
class Node
{
private:
    T data;
    Node *next;

public:
    Node(T data) : data(data), next(nullptr) {}
    Node() : data(), next(nullptr) {}

    void insert(Node<T> *p)
    {
        // this ở đây là con trỏ Node<T>* (địa chỉ của node đang gọi insert()).
        // this->next  <=> (*this).next : "->" đã bao gồm sẵn 1 phép dereference ẩn.
        // this->next KHÔNG so sánh địa chỉ, nó ĐỌC RA giá trị của member "next"
        // (mà bản thân "next" tình cờ cũng là 1 con trỏ).
        p->next = this->next;
        this->next = p;
    }

    // this->data : cũng là this->member -> có dereference ẩn qua "->"
    T &getData() { return this->data; }
    void setData(T data) { this->data = data; }

    Node<T> *getNext() { return this->next; }
    void setNext(Node<T> *p) { this->next = p; }
};

#pragma endregion Node

// ============================================================================
// SLL - Singly Linked List
// ============================================================================
template <typename T>
class SLL
{
private:
    Node<T> *head;
    Node<T> *trail;

public:
#pragma region Rule of Five (constructor / destructor / copy / move)

    // Constructor mặc định: list rỗng
    SLL() : head(nullptr), trail(nullptr) { 
        // cout << "default ctor\n"; 
    }

    // Destructor: giải phóng toàn bộ node
    ~SLL()
    {
        Node<T> *cur = head;
        while (cur != nullptr)
        {
            Node<T> *tmp = cur->getNext();
            delete cur;
            cur = tmp;
        }
        head = trail = nullptr;
    }

    // --- COPY CONSTRUCTOR (deep copy) ---
    // NHẮC LẠI: nếu KHÔNG tự viết hàm này, compiler tự sinh bản SHALLOW COPY:
    //     SLL(const SLL &other) : head(other.head), trail(other.trail) {}
    // -> chỉ copy GIÁ TRỊ CON TRỎ (con số địa chỉ), tức là "a" và "b" sẽ CÙNG
    //    TRỎ VÀO 1 chuỗi Node vật lý duy nhất trên heap, KHÔNG có Node nào
    //    được tạo thêm. Hệ quả: 1 trong 2 destruct trước -> delete hết Node
    //    -> con trỏ còn lại thành dangling pointer -> đọc/ghi vào là UB.
    //    Nếu cả 2 cùng destruct -> DOUBLE FREE (delete cùng 1 vùng nhớ 2 lần).
    // => Vì vậy phải tự viết deep copy: duyệt qua "other" và new Node MỚI
    //    cho từng phần tử, không dùng chung Node với other.
    //
    // Hàm này (và operator= copy) KHÔNG được gọi tường minh ở đâu trong file
    // này -- chúng chỉ tồn tại sẵn để code BÊN NGOÀI dùng, ví dụ:
    //     SLL<int> b = a;   // gọi copy constructor này
    SLL(const SLL &other) : head(nullptr), trail(nullptr)
    {
        // cout << "COPY ctor called\n";
        for (Iterator it = other.begin(); it != other.end(); ++it)
            pushBack(new Node<T>(*it));
    }

    // --- COPY ASSIGNMENT ---
    // Trường hợp: SLL a; a = b;  (khác với "SLL a = b;" là copy constructor)
    // Phải: (1) tự dọn dữ liệu cũ của chính mình trước khi nhận dữ liệu mới,
    // (2) deep copy từ other, (3) tự gán không được tự phá hủy chính mình.
    SLL &operator=(const SLL &other)
    {
        // this == &other : so sánh 2 ĐỊA CHỈ (2 con trỏ), KHÔNG dereference.
        // this   : con trỏ SLL*, giá trị là địa chỉ của object đang gọi hàm.
        // &other : lấy địa chỉ của "other" (other vốn là tham chiếu SLL&),
        //          cũng ra 1 con trỏ. So sánh 2 con số địa chỉ này với nhau
        //          để phát hiện trường hợp tự gán "a = a;".
        if (this == &other)
            return *this; // tự gán cho chính mình -> không làm gì cả

        Node<T> *cur = head;
        while (cur != nullptr)
        {
            Node<T> *tmp = cur->getNext();
            delete cur;
            cur = tmp;
        }
        head = trail = nullptr;

        for (Iterator it = other.begin(); it != other.end(); ++it)
            pushBack(new Node<T>(*it));

        // Kiểu trả về khai báo là SLL& (tham chiếu), không phải SLL (object
        // mới) và cũng không phải SLL* (con trỏ). Vì vậy PHẢI trả *this
        // (dereference this) chứ không phải this trần trụi:
        //   this   -> kiểu SLL*  (không khớp kiểu trả về SLL&, không compile)
        //   *this  -> kiểu SLL&  (dereference this: "đi tới địa chỉ this
        //             đang lưu, lấy CHÍNH object nằm ở đó ra" -> khớp đúng)
        // Trả về T& (chứ không phải T) để hỗ trợ chuỗi gán a = b = c;
        // và để KHÔNG phải deep-copy thêm 1 bản dư thừa chỉ để trả về rồi vứt.
        return *this;
    }

    // --- MOVE CONSTRUCTOR ---
    // Dùng khi "other" là một giá trị tạm sắp bị hủy (rvalue), ví dụ:
    //   return newSLL;                (khi KHÔNG áp dụng được NRVO)
    //   return {even, odd};           (dùng std::move bên dưới trong split())
    //
    // rvalue KHÔNG phải "removed value" -- đó là 1 giá trị TẠM THỜI, không
    // có tên cố định, sắp biến mất (ngược với lvalue: có tên, có địa chỉ,
    // sống lâu dài). "newSLL" tự nó VẪN LÀ lvalue (có tên), nhưng vì nó sắp
    // chết ngay sau return, compiler NGẦM coi nó như rvalue để ưu tiên chọn
    // move constructor này thay vì copy constructor.
    //
    // std::move(x) (dùng ở split()) không di chuyển/xoá gì cả -- nó CHỈ ép
    // kiểu x (vốn là lvalue) thành rvalue reference, để compiler chọn đúng
    // overload (move) thay vì copy. Sau std::move, biến gốc (even/odd) vẫn
    // tồn tại và VẪN bị destructor gọi bình thường khi hết scope -- chỉ là
    // lúc đó head/trail của nó đã bị set nullptr (xem 2 dòng dưới) nên
    // destructor không xoá gì cả.
    //
    // Thay vì tạo Node mới (tốn thời gian) như copy constructor, ta chỉ đơn
    // giản "cướp" luôn con trỏ head/trail của other, rồi set other về rỗng.
    // "Cướp" nghĩa là: copy 2 con số địa chỉ (head, trail) sang *this (O(1),
    // không đụng tới Node nào cả), rồi xoá dấu vết ở other (set nullptr) để
    // khi destructor của other chạy, nó không delete nhầm Node vừa "cho đi".
    // Bước set other = nullptr là BẮT BUỘC: nếu không, destructor của other
    // (sắp chạy ngay sau đó) sẽ delete các node mà ta vừa "lấy", khiến head/trail
    // của *this trở thành dangling pointer.
    SLL(SLL &&other) noexcept : head(other.head), trail(other.trail)
    {
        // cout << "MOVE ctor called\n";
        other.head = nullptr;
        other.trail = nullptr;
    }

    // --- MOVE ASSIGNMENT ---
    // Tương tự move constructor, nhưng *this đã có dữ liệu cũ -> phải dọn
    // dữ liệu cũ của *this trước khi "cướp" dữ liệu mới từ other.
    SLL &operator=(SLL &&other) noexcept
    {
        if (this == &other)
            return *this;

        Node<T> *cur = head;
        while (cur != nullptr)
        {
            Node<T> *tmp = cur->getNext();
            delete cur;
            cur = tmp;
        }

        head = other.head;
        trail = other.trail;
        other.head = nullptr;
        other.trail = nullptr;

        return *this; // xem giải thích *this ở copy assignment phía trên
    }

#pragma endregion Rule of Five

#pragma region Insert operations

    void pushBack(Node<T> *a)
    {
        if (trail == nullptr)
        {
            head = trail = a;
            return;
        }
        trail->setNext(a);
        trail = a;
    }

    void pushFront(Node<T> *a)
    {
        if (head == nullptr)
        {
            head = trail = a;
            return;
        }
        a->setNext(head);
        head = a;
    }

    void push(int i, Node<T> *a)
    {
        if (i == 0)
        {
            pushFront(a);
            return;
        }
        Node<T> *tmp = head;
        int pos = 0;
        while (pos < i - 1 && tmp->getNext())
        {
            tmp = tmp->getNext();
            pos++;
        }
        tmp->insert(a);
    }

    // Bài 1: chèn giữ thứ tự tăng dần, không cho phép trùng giá trị.
    // Duyệt tìm vị trí đầu tiên có data > val (hoặc hết list) để chèn vào trước đó.
    // Nếu gặp giá trị bằng val -> hủy node mới tạo, không chèn (tránh trùng).
    void insertOrder(T val)
    {
        Node<T> *newNode = new Node<T>(val);
        if (head == nullptr)
        {
            head = trail = newNode;
            return;
        }

        Node<T> *cur = head;
        Node<T> *prev = nullptr;

        while (cur != nullptr)
        {
            if (cur->getData() == val)
            {
                delete newNode; // đã tồn tại -> không chèn, tránh leak con trỏ vừa new
                return;
            }
            if (cur->getData() <= val)
                break;
            prev = cur;
            cur = cur->getNext();
        }

        if (prev == nullptr)
        {
            pushFront(newNode);
            return;
        }
        if (cur == nullptr)
        {
            pushBack(newNode);
            return;
        }
        prev->setNext(newNode);
        newNode->setNext(cur);
    }

#pragma endregion Insert operations

#pragma region Iterator

    class Iterator
    {
    private:
        Node<T> *ptr;

    public:
        Iterator(Node<T> *p) : ptr(p) {}
        // T& để tránh copy, nhưng đồng nghĩa với việc cho phép sửa data
        // Nếu cần read-only thì dùng const T& (ConstIterator)
        T &operator*() { return ptr->getData(); }   // trả về T& -> đọc/sửa được giá trị thật
        T *operator->() { return &ptr->getData(); } // trả về T* -> để C++ tự dereference tiếp
        Node<T> *node() { return ptr; }             // trả thẳng con trỏ Node, dùng khi cần thao tác nội bộ list
        Iterator &operator++()
        {
            ptr = ptr->getNext();
            // *this ở đây: this là Iterator* (con trỏ tới Iterator hiện tại),
            // *this dereference ra chính object Iterator đó (kiểu Iterator&).
            // Trả về Iterator& (không phải Iterator) để KHÔNG copy, cho phép
            // for(...; ...; ++it) và chuỗi ++(++it) hoạt động, giống hệt lý do
            // operator= của SLL trả về SLL& ở trên.
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator tmp = *this; // ở đây *this bị COPY vào tmp (kiểu trả về
                                   // của constructor ngầm là Iterator, giá trị
                                   // -> tạo object MỚI, độc lập với *this)
            ptr = ptr->getNext();
            return tmp; // trả về BẢN COPY cũ (trước khi tăng) -> đúng ngữ nghĩa postfix it++
        }
        bool operator!=(const Iterator &other) { return ptr != other.ptr; }
    };

    // CHÚ Ý: begin()/end() const chỉ cam kết không sửa head/trail của SLL,
    // KHÔNG ngăn sửa data bên trong node qua Iterator (vì operator* trả về T&)
    // Để chặt hoàn toàn cần implement thêm ConstIterator riêng
    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }

#pragma endregion Iterator

#pragma region Sort

    // Bổ sung tham số ascending: true = tăng dần (mặc định), false = giảm dần.
    void mergeSort(bool ascending = true)
    {
        head = mergeSortRec(head, ascending);
        // Vì liên kết giữa các node đã bị thay đổi hoàn toàn trong lúc sort,
        // trail cũ không còn đúng nữa -> phải duyệt lại để tìm node cuối cùng.
        trail = head;
        while (trail && trail->getNext())
            trail = trail->getNext();
    }

#pragma endregion Sort

#pragma region IO

    void input()
    {
        cout << "n: ";
        int n;
        cin >> n;
        cout << n << " phan tu: ";
        while (n--)
        {
            T val;
            cin >> val;
            pushBack(new Node<T>(val));
        }
    }

    void print() const
    {
        for (Iterator it = begin(); it != end(); ++it)
            cout << *it << " ";
        cout << endl;
    }

#pragma endregion IO

#pragma region Merge and Split

    // Bài 2: trộn 2 danh sách đã tăng dần thành 1 danh sách tăng dần mới.
    // An toàn nhờ Rule of Five đã bổ sung ở trên: dù NRVO có được áp dụng
    // hay không, "return newSLL;" luôn đúng (NRVO không copy gì cả; nếu vì
    // lý do nào đó NRVO không chạy thì move constructor sẽ được gọi thay vì
    // copy constructor, vẫn an toàn, không có node nào bị chia sẻ 2 nơi).
    SLL merge(const SLL &a)
    {
        SLL newSLL; // newSLL: biến cục bộ, "sở hữu" các Node MỚI (tạo bằng
                     // new Node<T>(...) ở dưới) thông qua 2 con trỏ head/trail.
        Iterator it1 = begin();
        Iterator it2 = a.begin();
        while (it1 != this->end() && it2 != a.end())
        {
            if (*it1 < *it2)
            {
                newSLL.pushBack(new Node<T>(*it1));
                it1++;
            }
            else
            {
                newSLL.pushBack(new Node<T>(*it2));
                it2++;
            }
        }
        while (it1 != this->end())
        {
            newSLL.pushBack(new Node<T>(*it1));
            it1++;
        }
        while (it2 != a.end())
        {
            newSLL.pushBack(new Node<T>(*it2));
            it2++;
        }
        // return newSLL:
        //  - Có NRVO: newSLL được xây THẲNG vào chỗ nhớ của biến nhận kết quả
        //    bên ngoài, KHÔNG gọi constructor nào cả (không copy, không move).
        //  - Không có NRVO: compiler coi newSLL (lvalue, sắp chết vì hàm sắp
        //    kết thúc) như rvalue -> ưu tiên gọi MOVE CONSTRUCTOR (không phải
        //    copy) -> chỉ copy 2 con trỏ head/trail sang object bên ngoài rồi
        //    set newSLL.head/trail = nullptr -> khi ~SLL() của newSLL chạy,
        //    head đã null nên không delete Node nào cả -> an toàn, không leak,
        //    không double-free.
        return newSLL;
    }

    // Bài 3: tách 1 danh sách thành 2 danh sách chẵn/lẻ.
    // QUAN TRỌNG: dùng std::move(even), std::move(odd) khi trả về.
    // Lý do: "return {even, odd};" phải copy 2 biến cục bộ vào 2 slot
    // (.first, .second) của pair -> đây KHÔNG phải trường hợp NRVO (NRVO chỉ
    // áp dụng khi trả thẳng 1 biến cục bộ duy nhất về đúng kiểu trả về).
    // Ở đây ta đang CONSTRUCT 1 pair<SLL,SLL> MỚI từ even/odd, nên bắt buộc
    // phải chọn: copy constructor (deep copy, O(n)) hay move constructor
    // (chỉ cướp con trỏ, O(1)) cho .first/.second bên trong pair.
    // Nếu không có std::move, code vẫn compile được (nhờ copy constructor ta
    // vừa viết) nhưng sẽ deep-copy node 1 lần dư thừa rồi xóa bản gốc ngay
    // sau đó -> lãng phí. std::move ép dùng move constructor (chỉ "cướp" con
    // trỏ, không cấp phát node mới) -> vừa đúng vừa nhanh.
    // Sau std::move, "even" và "odd" VẪN bị destructor gọi khi hàm split()
    // kết thúc -- chỉ là lúc đó head/trail của chúng đã null nên không xoá gì.
    pair<SLL<T>, SLL<T>> split() const
    {
        SLL<T> even, odd;
        for (Iterator it = begin(); it != end(); ++it)
        {
            if (*it & 1)
                odd.pushBack(new Node<T>(*it));
            else
                even.pushBack(new Node<T>(*it));
        }
        return {std::move(even), std::move(odd)};
    }

#pragma endregion Merge and Split

private:
#pragma region Merge sort helpers

    // Tách 1 danh sách thành 2 nửa bằng kỹ thuật con trỏ chậm/nhanh (slow/fast).
    // h: head của danh sách cần tách (nửa trái sẽ giữ nguyên biến h sau khi hàm chạy xong,
    //    vì Node<T>* là con trỏ, "cắt" next của node cuối nửa trái là đủ, không cần trả về).
    // Trả về head của nửa phải.
    Node<T> *getMid(Node<T> *h)
    {
        if (!h || !h->getNext())
            return nullptr; // 0 hoặc 1 phần tử thì không tách được nữa

        Node<T> *slow = h;
        Node<T> *fast = h->getNext();

        // fast đi nhanh gấp đôi slow: mỗi vòng lặp slow đi 1 bước, fast đi 2 bước.
        // Khi fast chạy hết danh sách (đến cuối) thì slow đang đứng đúng giữa danh sách.
        while (fast && fast->getNext())
        {
            slow = slow->getNext();
            fast = fast->getNext()->getNext();
        }

        Node<T> *secondHead = slow->getNext(); // node đầu tiên của nửa phải
        slow->setNext(nullptr);                // cắt đứt liên kết -> nửa trái kết thúc tại slow
        return secondHead;
    }

    // Merge 2 danh sách đã sort sẵn (a và b) thành 1 danh sách sort, bằng cách nối lại
    // con trỏ next của các node có sẵn (không cấp phát node mới, không dùng mảng phụ).
    // ascending = true -> lấy phần tử nhỏ hơn trước; false -> lấy phần tử lớn hơn trước.
    Node<T> *mergeTwo(Node<T> *a, Node<T> *b, bool ascending)
    {
        Node<T> dummy; // node giả làm điểm neo, giúp code không phải xử lý case đầu riêng
        Node<T> *tail = &dummy;

        while (a && b)
        {
            bool takeA = ascending ? (a->getData() <= b->getData())
                                    : (a->getData() >= b->getData());
            if (takeA)
            {
                tail->setNext(a);
                tail = a;
                a = a->getNext();
            }
            else
            {
                tail->setNext(b);
                tail = b;
                b = b->getNext();
            }
        }
        // 1 trong 2 danh sách đã hết, nối phần còn lại (đã sort sẵn) vào đuôi
        tail->setNext(a ? a : b);

        return dummy.getNext(); // bỏ qua node dummy, lấy node thật đầu tiên
    }

    // Đệ quy: chia đôi bằng getMid, sort từng nửa, rồi merge lại.
    Node<T> *mergeSortRec(Node<T> *h, bool ascending)
    {
        if (!h || !h->getNext())
            return h; // danh sách rỗng hoặc 1 phần tử: đã sort

        Node<T> *h2 = getMid(h); // h: head nửa trái (đã bị cắt), h2: head nửa phải
        Node<T> *left = mergeSortRec(h, ascending);
        Node<T> *right = mergeSortRec(h2, ascending);
        return mergeTwo(left, right, ascending);
    }

#pragma endregion Merge sort helpers
};