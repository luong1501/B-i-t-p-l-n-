#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <queue>
using namespace std;

// Struct luu tru thong tin cua moi quyensach
struct book {
    int id;
    string tensach;
    string theloai;
    string tacgia;
    string namxb;
    int giatien;
	bool isBorrowed ;
	queue<string> hangdoi;
    book() {

	}
    book(int id, string tensach, string theloai, string tacgia, string namxb, int giatien) {
        this->id = id;
        this->tensach = tensach;
        this->theloai = theloai;
        this->tacgia = tacgia;
        this->namxb = namxb;
        this->giatien = giatien;
        this->isBorrowed = false; // Mac dinh la sach chua duoc muon
      
    }
};

// Struct node
struct node {
    book data;
    node *next;
};

// Class quan ly danh sach cac quyensach
class List {
private:
    node *head;  // Con tro den node dau tien trong danh sach
    node *tail; // Con tro den node cuoi cung trong danh sach
    int slsachhientai; // So luong sach hien tai trong danh sach

public:
    List();
    ~List();
    node* createbook(int id, string tensach, string theloai, string tacgia, string namxb, int giatien);
    void addFirst(int id, string tensach, string theloai, string tacgia, string namxb, int giatien);
    void addLast(int id, string tensach, string theloai, string tacgia, string namxb, int giatien);
    void insert(int id, string tensach, string theloai, string tacgia, string namxb, int giatien, int pos);
    void sosach_hienco();
    void deleteFirst();
    void deleteLast();
    void deleteMid();
    void clear();
    void duyetsach();
    void sapXepTheoID();
    void sapXepTheoTenSach();
    void sapXepTheoGiaTien();
    void timKiemTheoTenSach(string tensach);
    void timKiemSachGiaLonHon(int GT);
    void timKiemTheoTuKhoa(string tuKhoa);
    void borrowBook(string tensach, string nguoimuon);
    void returnBook(string tensach);
    void saveToFile(ofstream& outFile);
    void loadFromFile(ifstream& inFile);
};

// Constructor cua List
List::List() {
    head = tail = NULL;
    slsachhientai = 0;
}

// Destructor de giai phong bo nho
List::~List() {
    clear();
}

// Tao mot node chua thong tin sach
node* List::createbook(int id, string tensach, string theloai, string tacgia, string namxb, int giatien) {
    book b(id, tensach, theloai, tacgia, namxb, giatien);  // Tao bien b kieu book
    node *tmp = new node();
    tmp->data = b;  // Gan b cho tmp->data
    tmp->next = NULL;
    return tmp;
}

// Them sach vao dau danh sach
void List::addFirst(int id, string tensach, string theloai, string tacgia, string namxb, int giatien) {
    node *p = createbook(id, tensach, theloai, tacgia, namxb, giatien);
    if (head == NULL) {
        head = tail = p;
    } else {
        p->next = head;
        head = p;
    }
    slsachhientai++;
}

// Them sach vao cuoi danh sach
void List::addLast(int id, string tensach, string theloai, string tacgia, string namxb, int giatien) {
    node *p = createbook(id, tensach, theloai, tacgia, namxb, giatien);
    if (head == NULL) {
        head = tail = p;
    } else {
        tail->next = p;
        tail = p;
    }
    slsachhientai++;
}

// Them sach vao vi tri bat ky trong danh sach
void List::insert(int id, string tensach, string theloai, string tacgia, string namxb, int giatien, int pos) {
    if (pos > slsachhientai + 1) {
        cout << "Vuot qua danh sach" << endl;
        return;
    } else if (pos == 1) {
        addFirst(id, tensach, theloai, tacgia, namxb, giatien);
        return;
    } else if (pos == slsachhientai + 1) {
        addLast(id, tensach, theloai, tacgia, namxb, giatien);
        return;
    }

    node *p = createbook(id, tensach, theloai, tacgia, namxb, giatien);
    node *a = head;
    for (int i = 1; i < pos - 1; i++) {
        a = a->next;
    }
    p->next = a->next;
    a->next = p;
    slsachhientai++;
}

// Hien so luong sach hien co
void List::sosach_hienco() {
    cout << "So sach hien co la: " << slsachhientai << endl;
}

// Xoa sach dau tien
void List::deleteFirst() {
    if (head == NULL) {
        cout << "Danh sach dang rong" << endl;
        return;
    }

    node *temp = head;
    head = head->next;
    delete temp;
    slsachhientai--;
}

// Xoa sach cuoi cung
void List::deleteLast() {
    if (head == NULL) {
        cout << "Danh sach dang rong" << endl;
        return;
    }

    if (head == tail) {
        delete head;
        head = tail = NULL;
    } else {
        node *a = head;
        while (a->next != tail) {
            a = a->next;
        }
        delete tail;
        tail = a;
        tail->next = NULL;
    }
    slsachhientai--;
}

// Xoa sach o vi tri giua
void List::deleteMid() {
    if (head == NULL) {
        cout << "Danh sach dang rong" << endl;
        return;
    }

    int pos;
    cout << "Nhap vi tri can xoa: ";
    cin >> pos;

    if (pos < 1 || pos > slsachhientai) {
        cout << "Vi tri khong hop le!\n";
        return;
    } else if (pos == 1) {
        deleteFirst();
        return;
    } else if (pos == slsachhientai) {
        deleteLast();
        return;
    }

    node *a = head;
    for (int i = 1; i < pos - 1; i++) {
        a = a->next;
    }

    node *temp = a->next;
    a->next = temp->next;
    delete temp;
    slsachhientai--;
}

// Xoa toan bo danh sach
void List::clear() {
    if (head == NULL) {
        cout<<"Danh sach dang rong ";
    } else {
        while (head != NULL) {
            node* p = head;
            head = p->next;
            delete p;
        }
        tail = NULL;
    }
    return ;
}
// Duyet danh sach sach
void List::duyetsach() {
    if (head == NULL) {
        cout << "Danh sach rong" << endl;
        return;
    }

	cout << "------------------------------------------------------------------------------------------------------------\n";
    cout << "| " << setw(5) << left << "ID"
         << " | " << setw(20) << left << "Ten sach"
         << " | " << setw(15) << left << "The loai"
         << " | " << setw(20) << left << "Tac gia"
         << " | " << setw(8) << left << "Nam XB"
         << " | " << setw(8) << right << "Gia tien"
         << " | " << setw(10) << left << "Trang thai" << " |\n";
    cout << "------------------------------------------------------------------------------------------------------------\n";

    for (node *i = head; i != NULL; i = i->next) {
        cout << "| " << setw(5) << left << i->data.id
             << " | " << setw(20) << left << i->data.tensach
             << " | " << setw(15) << left << i->data.theloai
             << " | " << setw(20) << left << i->data.tacgia
             << " | " << setw(8) << left << i->data.namxb
             << " | " << setw(8) << right << i->data.giatien
             << " | " << setw(10) << left << (i->data.isBorrowed ? "Da muon" : "Chua muon")
             << " |\n";
    }
    cout << "------------------------------------------------------------------------------------------------------------\n";

}

// Sap xep theo id
void List::sapXepTheoID() {
    for (node *i = head; i != NULL; i = i->next) {
        node *minNode = i;
        for (node *j = i->next; j != NULL; j = j->next) {
            if (minNode->data.id > j->data.id) {
                minNode = j;
            }
        }
        if (minNode != i) {
            swap(i->data, minNode->data);
        }
    }
}
//Sap xep theo ten
void List::sapXepTheoTenSach() {
    for (node *i = head; i != NULL; i = i->next) {
        node *minNode = i;
        for (node *j = i->next; j != NULL; j = j->next) {
            if (minNode->data.tensach > j->data.tensach) {
                minNode = j;
            }
        }

        if (minNode != i) {
            swap(i->data, minNode->data);
        }
    }
}
// Sap xep theo gia tien
void List::sapXepTheoGiaTien() {
    for (node *i = head; i != NULL; i = i->next) {
        node *minNode = i;
        for (node *j = i->next; j != NULL; j = j->next) {
            if (minNode->data.giatien > j->data.giatien) {
                minNode = j;
            }
            else if(minNode->data.giatien == j->data.giatien){
            	if(minNode->data.tensach > j->data.tensach){
            		minNode = j;
				}
			}
        }
        if (minNode != i) {
            swap(i->data, minNode->data);
        }
    }
}
// Tim kiem theo ten
void List::timKiemTheoTenSach(string tensach) {
    node* tmp = head;
    bool found = false;
    while (tmp != NULL) {
        if (tmp->data.tensach == tensach) {
            cout << "Thong tin sach:" << endl;
            cout << "ID: " << tmp->data.id << endl;
            cout << "Ten sach: " << tmp->data.tensach << endl;
            cout << "The loai: " << tmp->data.theloai << endl;
            cout << "Tac gia: " << tmp->data.tacgia << endl;
            cout << "Nam xuat ban: " << tmp->data.namxb << endl;
            cout << "Gia tien: " << tmp->data.giatien << " VND" << endl;
            cout << "----------------------" << endl;
            found = true;
        }
        tmp = tmp->next;
    }
    if (!found) {
        cout << "Khong tim thay sach nao co ten: " << tensach << endl;
    }
}
// Tim kiem sach co gia lon hon 1 gt nao do
void List::timKiemSachGiaLonHon(int GT) {
    bool found = false;
    for (node *i = head; i != NULL; i = i->next) {
        if (i->data.giatien > GT) {
            cout << "Sach co gia lon hon " << GT << ": " << endl;
		    cout << "ID: " << i->data.id << endl;
			cout << "Ten sach: " << i->data.tensach << endl;
        	cout << "The loai: " << i->data.theloai << endl;
			cout << "Tac gia: " << i->data.tacgia << endl;
            cout << "Nam xuat ban: " << i->data.namxb << endl;
			cout << "Gia tien: " << i->data.giatien <<" VND"<< endl;
			cout << "----------------------" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Khong tim thay sach nao co gia lon hon " << GT << "!\n";
    }
}
// Tim kiem theo tu khoa
void List::timKiemTheoTuKhoa(string tuKhoa) {
    node* tmp = head;
    bool found = false;
    while (tmp != NULL) {
        if (tmp->data.tensach.find(tuKhoa) != string::npos) {
            cout << "Thong tin sach:" << endl;
            cout << "ID: " << tmp->data.id << endl;
            cout << "Ten sach: " << tmp->data.tensach << endl;
            cout << "The loai: " << tmp->data.theloai << endl;
            cout << "Tac gia: " << tmp->data.tacgia << endl;
            cout << "Nam xuat ban: " << tmp->data.namxb << endl;
            cout << "Gia tien: " << tmp->data.giatien << " VND" << endl;
            cout << "----------------------" << endl;
            found = true;
        }
        tmp = tmp->next;
    }
    if (!found) {
        cout << "Khong tim thay sach nao chua tu khoa: " << tuKhoa << endl;
    }
}


void List::borrowBook(string tensach, string nguoimuon) {
        node* current = head;
        while (current != NULL) {
            if (current->data.tensach == tensach) {
                if (current->data.isBorrowed) {
                    current->data.hangdoi.push(nguoimuon);
                    cout << "Sach hien tai da duoc muon. Ban " << nguoimuon << " da duoc them vao danh sach cho." << endl;
                } else {
                    current->data.isBorrowed = true;
                    cout << "Xin chuc mung, ban " << nguoimuon << " da muon thanh cong sach '" << current->data.tensach << "'." << endl;
                }
                return;
            }
            current = current->next;
        }
        cout << "Khong tim thay sach co ten '" << tensach << "'." << endl;
    }

void List::returnBook(string tensach) {
        node* current = head;
        while (current != NULL) {
            if (current->data.tensach == tensach) {
                if (!current->data.isBorrowed) {
                    cout << "Sach hien khong duoc muon!" << endl;
                } else {
                    current->data.isBorrowed = false;
                    cout << "Ban da tra sach '" << current->data.tensach << "' thanh cong." << endl;

                    if (!current->data.hangdoi.empty()) {
                        string nguoitieptheo = current->data.hangdoi.front();
                        current->data.hangdoi.pop();
                        current->data.isBorrowed = true;
                        cout << "Ban " << nguoitieptheo  << " la nguoi tiep theo va da duoc muon sach '" << current->data.tensach << "'." << endl;
                    }
                }
                return;
            }
            current = current->next;
        }
        cout << "Khong tim thay sach co ten '" << tensach << "'." << endl;
    }

// Ham luu danh sach vao file
void List::saveToFile(ofstream& outFile) {
    for (node* i = head; i != NULL; i = i->next) {
        outFile << i->data.id << "," << i->data.tensach << "," << i->data.theloai << ","
                << i->data.tacgia << "," << i->data.namxb << "," << i->data.giatien << ","
                << i->data.isBorrowed << endl;
    }
    cout << "Da luu danh sach vao file." << endl;
}
//Ham tai danh sach tu file
void List::loadFromFile(ifstream& inFile) {
    int id, giatien;
    string tensach, theloai, tacgia, namxb;
    bool isBorrowed;

    while (inFile >> id) {
        inFile.ignore();
        getline(inFile, tensach, ',');
        getline(inFile, theloai, ',');
        getline(inFile, tacgia, ',');
        getline(inFile, namxb, ',');
        inFile >> giatien;
        inFile.ignore();
        inFile >> isBorrowed;
        addLast(id, tensach, theloai, tacgia, namxb, giatien);

        if (tail != NULL) {
            tail->data.isBorrowed = isBorrowed;
        }
    }
    inFile.close();
    cout << "Da tai danh sach tu file." << endl;
}
void showMenu() {
	system("cls");
    cout << "---------------- MENU --------------" << endl;
    cout << "------------------------------------ "<<endl;
    cout << "|1. Them sach vao dau danh sach     |"    << endl;
    cout << "|2. Them sach vao cuoi danh sach    |" << endl;
    cout << "|3. Chen sach vao vi tri            |" << endl;
    cout << "|4. Hien thi so sach hien co        |" << endl;
    cout << "|5. Xoa sach dau danh sach          |" << endl;
    cout << "|6. Xoa sach cuoi danh sach         |" << endl;
    cout << "|7. Xoa sach o giua                 |" << endl;
    cout << "|8. Xoa tat ca sach                 |" << endl;
    cout << "|9. Duyet sach                      |" << endl;
    cout << "|10. Sap xep sach theo ID           |" << endl;
    cout << "|11. Sap xep sach theo ten sach     |" << endl;
    cout << "|12. Sap xep sach theo gia tien     |" << endl;
    cout << "|13. Tim kiem sach theo ten sach    |" << endl;
    cout << "|14. Tim kiem sach co gia lon hon   |" << endl;
    cout << "|15. Tim kiem sach theo chu cai     |" << endl;
    cout << "|16. Muon sach                      |" << endl;
    cout << "|17. Tra sach                       |" << endl;
    cout << "|18. Luu vao file                   |" << endl;
    cout << "|19. Tai tu file                    |" << endl;
    cout << "|0.  Thoat                          |" << endl;
    cout << "------------------------------------ "<<endl;
    cout << "------------------------------------ "<<endl;
    cout << "Chon tuy chon: ";
}

int main() {
    List manager;
    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, giatien;
                string tensach, theloai, tacgia, namxb;
                cout << "Nhap ID sach: ";
                cin >> id;
                cout << "Nhap ten sach: ";
                cin.ignore();
                getline(cin, tensach);
                cout << "Nhap the loai: ";
                getline(cin, theloai);
                cout << "Nhap tac gia: ";
                getline(cin, tacgia);
                cout << "Nhap nam xuat ban: ";
                getline(cin, namxb);
                cout << "Nhap gia tien: ";
                cin >> giatien;
                manager.addFirst(id, tensach, theloai, tacgia, namxb, giatien);
                break;
            }
            case 2: {
                int id, giatien;
                string tensach, theloai, tacgia, namxb;
                cout << "Nhap ID sach: ";
                cin >> id;
                cout << "Nhap ten sach: ";
                cin.ignore();
                getline(cin, tensach);
                cout << "Nhap the loai: ";
                getline(cin, theloai);
                cout << "Nhap tac gia: ";
                getline(cin, tacgia);
                cout << "Nhap nam xuat ban: ";
                getline(cin, namxb);
                cout << "Nhap gia tien: ";
                cin >> giatien;
                manager.addLast(id, tensach, theloai, tacgia, namxb, giatien);
                break;
            }
            case 3: {
                int id, giatien, pos;
                string tensach, theloai, tacgia, namxb;
                cout << "Nhap ID sach: ";
                cin >> id;
                cout << "Nhap ten sach: ";
                cin.ignore();
                getline(cin, tensach);
                cout << "Nhap the loai: ";
                getline(cin, theloai);
                cout << "Nhap tac gia: ";
                getline(cin, tacgia);
                cout << "Nhap nam xuat ban: ";
                getline(cin, namxb);
                cout << "Nhap gia tien: ";
                cin >> giatien;
                cout << "Nhap vi tri chen: ";
                cin >> pos;
                manager.insert(id, tensach, theloai, tacgia, namxb, giatien, pos);
                break;
            }
            case 4:
                manager.sosach_hienco();
                 cout << "Press any key to continue...";
                cin.ignore();
                cin.get();
                break;
            case 5:
                manager.deleteFirst();
                break;
            case 6:
                manager.deleteLast();
                break;
            case 7:
                manager.deleteMid();
                break;
            case 8:
                manager.clear();
                cout << "Press any key to continue...";
                cin.ignore();
                cin.get();
                break;
            case 9:
                manager.duyetsach();
                cout << "Press any key to continue...";
                cin.ignore();
                cin.get();
                break;
            case 10:
                manager.sapXepTheoID();
                break;
            case 11:
                manager.sapXepTheoTenSach();
                break;
            case 12:
                manager.sapXepTheoGiaTien();
                break;
            case 13: {
            	string tensach;
			    cout << "Nhap ten sach: ";
				cin.ignore();
                getline(cin, tensach);
    		    manager.timKiemTheoTenSach(tensach);
			    cout << "Press any key to continue...";
			    cin.ignore();
			    cin.get();
			    break;
			}

            case 14: {
                int GT;
                cout << "Nhap gia tien lon hon: ";
                cin >> GT;
                manager.timKiemSachGiaLonHon(GT);
                cout << "Press any key to continue...";
                cin.ignore();
                cin.get();
                break;
            }
            case 15: {
               	string tuKhoa;
			    cout << "Nhap tu khoa: ";
			    cin >> tuKhoa;
			    manager.timKiemTheoTuKhoa(tuKhoa);
			    cout << "Press any key to continue...";
			    cin.ignore();
			    cin.get();
			    break;
            }
            case 16: {
                string tensach;
                string borrowerName ;
                cout << "Nhap ten sach de muon: ";
                cin.ignore();
                getline(cin, tensach);
                cout<<"Nhap ten nguoi muon: ";
                getline(cin, borrowerName);
                manager.borrowBook(tensach, borrowerName);
                cout << "Press any key to continue...";
                cin.ignore();
                cin.get();
                break;
            }
            case 17: {
                string tensach;
                cout << "Nhap ten sach de tra: ";
                cin.ignore();
                getline(cin, tensach);
                manager.returnBook(tensach);
                cout << "Press any key to continue...";
                cin.ignore();
                cin.get();
                break;
            }
			case 18: {
			    ofstream outFile;
			    outFile.open("thaydoi.txt", ios::out);
			    if (!outFile) {
			        cout << "Khong the mo file de ghi!" << endl;
			    }
				else {
			        manager.saveToFile(outFile);
			    }
			    outFile.close();
			    cout << "Press any key to continue...";
			    cin.ignore();
			    cin.get();

			    break;
			}
           case 19: {
	     		ifstream inFile;
	    		inFile.open("text.txt", ios::in);
	    		if (!inFile) {
	       			cout << "Khong the mo file de doc!" << endl;

	    		} else {
	       		 manager.loadFromFile(inFile);
			    }
			    inFile.close();
			    cout << "Press any key to continue...";
			    cin.ignore();
				cin.get();
           		break;
			}
            case 0:
                cout << "Thoat chuong trinh." << endl;
                cout << "Press any key to continue...";
                cin.ignore();
                cin.get();
                return 0;
            default:
                cout << "Tuy chon khong hop le. Vui long thu lai." << endl;
                cout << "Press any key to continue...";
                cin.ignore();
                cin.get();
        }
	}
    return 0;
}
