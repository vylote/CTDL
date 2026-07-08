#include <iostream>
#include <string>
using namespace std;

class Contact
{   
    string fax;
    string name;
    string address;
public:
    friend istream& operator>>(istream &is, Contact &contact)
    {
        cout << "Enter your number phone\n";
        getline(is, contact.fax);
        cout << "Enter your name\n";
        getline(is, contact.name);
        cout << "Enter your address\n";
        getline(is, contact.address);
        return is;
    }
    friend ostream& operator<<(ostream &os, const Contact contact)
    {
        os << contact.fax << ' ' << contact.name << ' ' << contact.address << '\n' << '\n';
        return os;
    }
    Contact() {}
    Contact(string sdt, string ten, string diaChi) : fax(sdt), name(ten), address(diaChi) {}
    string getName() {
        return name;
    }
};

template <class T>

class Node{
    private:
        T data;
        Node<T> *next, *prev;
    public:
        Node(T Data, Node<T>* L=0, Node<T> *R=0) {
            data = Data;next = R;prev = L;
        }
        T& getData() {return data;}
        Node<T> *&getNext() {return next;}
        Node<T> *&getPrev() {return prev;}
        void setData(T Data) {data = Data;}
        void setNext(Node<T> *temp=nullptr) {next = temp;}
        void setPrev(Node<T> *temp=nullptr) {prev = temp;}
};
template <class T>
class Iterator;
template <class T>
class Dlist {
    Node<T> *head, *tail;
    unsigned int num;
    public:
        Dlist() : head(nullptr), tail(nullptr), num(0) {}
        Dlist(int n, T d) {
            num = 0; head = tail = nullptr;
            while(n--) push_back(d); 
        }
        void push_back(T d) {
            if (num==0) head = tail = new Node<T>(d);
            else {
                tail->setNext(new Node<T> (d, tail, 0));
            }
            num++;
        }
        void push_front(T d) {
            if (num ==0 ) head = tail = new Node<T>(d);
            else {
                head->setPrev(new Node<T> (d, nullptr, head));
                head = head->getPrev();
            }
            num++;
        }
        void erase(T d) {
            if (num==0) {
                cout << "chua co du lieu de xoa!" << endl;
                return;
            }
            
        }
        typedef Iterator<T> iterator;
        Iterator<T> begin() {return head;}
        Iterator<T> end() {return NULL;}
};

template <class T>
class Iterator {
    Node<T> *cur;
    public:
        Iterator(Node<T> *p=nullptr) {cur = p;}
        Node<T> *getCur() {return cur;}
        T& operator*() {
            return cur->getData();
        }
        Iterator<T>& operator++() {
            cur = cur->getNext();
            return *this;
        }
        bool operator!=(const Iterator<T>& other) const{
            return cur != other.cur;
        }
        bool operator==(const Iterator<T>& other) const{
            return cur == other.cur;
        }
};

int main()
{
    Dlist<Contact> quanLy;
    int choice;
    do {
        cout << "\033[1m====================================\033[0m\n";
        cout << "\033[1m          CONTACT MANAGER           \033[0m\n";
        cout << "\033[1m====================================\033[0m\n";
        cout << "\033[1m1. ADD A CONTACT\033[0m\n";
        cout << "\033[1m2. PRINT CONTACT LIST\033[0m\n";
        cout << "\033[1m6. EXIT\033[0m\n";
        cout << "\033[1m====================================\033[0m\n";
        cout << "\033[1mEnter your choice: \033[0m";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            cout << "nhap thong tin danh ba: "<<endl;
            Contact ct; cin >> ct; // neu k sử dụng dấu {} thì qua các case khác ct vẫn hiển thị trong các case khác, nhưng chúng sẽ k dc khởi tạo 
            cout << "Them vao sau (1), Them vao truoc(2): ";
            int n; cin >> n;
            if (n==1) {
                quanLy.push_back(ct);
            }
            if (n==2) {
                quanLy.push_front(ct);

            }
            break;
        }
        case 2:
            cout << "in thong tin danh ba: " << endl;
            for (Dlist<Contact>::iterator it = quanLy.begin(); it != quanLy.end(); ++it) {
                cout << *it << endl;
            }
            break;
        default:
            cout << "option khong co: " << endl;
            break;
        }
    }while(true);

}