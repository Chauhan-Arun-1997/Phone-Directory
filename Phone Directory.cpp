#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class contactNode {
public:
    vector<string > name;
    vector<string > mobile;
    vector<string > email;
    contactNode *next, *pre;
    contactNode(vector<string > &name, vector<string > &mobile, vector<string > &email) {
        this->name = name;
        this->mobile = mobile;
        this->email = email;
        next = pre = NULL;
    }
};

class contact {
private:
    contactNode *head = NULL, *tail = NULL;

    void Sort(contactNode *newContact) {
        if (head != NULL) {
            contactNode *temp = head;
            string NewNode_name = newContact->name[0];
            transform(NewNode_name.begin(), NewNode_name.end(), NewNode_name.begin(), ::tolower);
            while (temp != NULL) {
                string OldNode_name = temp->name[0];
                transform(OldNode_name.begin(), OldNode_name.end(), OldNode_name.begin(), ::tolower);
                int res = NewNode_name.compare(OldNode_name);

                if (res >= 0 && temp->next != NULL) {
                    temp = temp->next;
                }
                else if (res <= 0 && temp->pre == NULL) {
                    newContact->next = temp;
                    newContact->pre = temp->pre;
                    temp->pre = newContact;
                    head = newContact;
                    break;
                }
                else if (res <= 0) {
                    newContact->next = temp;
                    newContact->pre = temp->pre;
                    temp->pre->next = newContact;
                    temp->pre = newContact;
                    break;
                }
                else if (temp->next == NULL) {
                    tail->next = newContact;
                    newContact->pre = tail;
                    tail = tail->next;
                    break;
                }
            }
        }
        else if (head == NULL) {
            head = newContact;
            tail = head;
        }
    }


    void Display(vector<contactNode *> temp, string s) {
        cout << "|-----------------------------------|\n";
        cout << "|\t" << s << "\t\t|\n";
        cout << "|-----------------------------------|\n";
        cout << "Contacts -> \t\t" << temp.size() << " found" << endl;

        for (int i = 0; i < temp.size(); ++i) {
            cout << i << " : " << temp[i]->name[0] << ' ' << temp[i]->name[1] << "\t";
            for (auto j = 0; j < (temp[i]->mobile).size(); ++j)
                cout << "+91 " << temp[i]->mobile[j] << "\n";
            cout << "\t";
            for (auto j = 0; j < (temp[i]->email).size(); ++j)
                cout << temp[i]->email[j] << "\n";
            cout << '\n';
        }
    }

protected:

    void New() {
        vector<string > name;
        vector<string > mobile;
        vector<string > email;
        cout << "First Name : ";
        string first_name; cin >> first_name;
        cout << "Last Name : ";
        string last_name; cin >> last_name;
        name.push_back(first_name);
        name.push_back(last_name);
        cout << "Phone : ";
        // int n; cin>>n;
        // while(n--) {
        string phone; cin >> phone;
        while (phone.size() != 10) {
            cout << "\nEnter Correct Phone : ";
            cin >> phone;
        }
        mobile.push_back(phone);
        // }
        cout << "Email : ";
        string e_mail; cin >> e_mail;
        email.push_back(e_mail);
        cout << '\n';
        contactNode *newContact = new contactNode(name, mobile, email);
        Sort(newContact);
        cout << "\n\n------Contact Save Successful------\n\n";
    }

    // TC : O(n)
    void Delete() {
        vector<contactNode*> searchResult = search();
        if (searchResult.size() == 0) return;
        cout << "\n\nEnter Your Index to delete : ";
        int index; cin >> index;
        contactNode *temp = searchResult[index];

        if (temp == head && temp->next == NULL) {
            delete temp;
            head = NULL;
            tail = NULL;
        }
        else if (temp == head) {
            temp->next->pre = NULL;
            head = head->next;
            delete temp;
        }
        else if (temp->next == NULL) {
            temp->pre->next = NULL;
            tail = temp->pre;
            delete temp;
        }
        else {
            temp->pre->next = temp->next;
            temp->next->pre = temp->pre;
            delete temp;
        }

        cout << "-------Deletion successfull-------" << "\n";
    }


    vector<contactNode *> search() {
        contactNode* temp = head;
        string s;
        bool flag = true;
        vector<contactNode *> searchResult;
        cout << "Enter detail for search : ";   cin >> s;
        string searchName = s;
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        while (temp != NULL)
        {
            string first_name = temp->name[0];
            transform(first_name.begin(), first_name.end(), first_name.begin(), ::tolower);
            string last_name = temp->name[1];
            transform(last_name.begin(), last_name.end(), last_name.begin(), ::tolower);
            string Email = temp->email[0];
            transform(Email.begin(), Email.end(), Email.begin(), ::tolower);

            if (first_name == s) flag = false;
            else if (last_name == s) flag = false;
            else if (temp->mobile[0] == s) flag = false;
            else if (Email == s) flag = false;

            if (!flag) {
                searchResult.push_back(temp);
                flag = true;
            }
            temp = temp->next;
        }
        if (searchResult.empty())
            cout << "Contact not found!!!\n";
        else Display(searchResult, searchName);
        return searchResult;
    }


    // TC : O(n)
    // SC : O(1)
    void view() {
        contactNode *temp = head;
        if (!head) {
            cout << "\n\nNo Contact Found!!!\n";
            return;
        }
        cout << '\n';
        int c = 1;
        while (temp != NULL) {
            cout << c << ". " << temp->name[0] << ' ' << temp->name[1] << "\t";
            for (auto i = 0; i < (temp->mobile).size(); ++i)
                cout << "+91 " << temp->mobile[i] << "\t";
            cout << "\t";
            for (auto i = 0; i < (temp->email).size(); ++i)
                cout << temp->email[i] << "\n";
            temp = temp->next;
            c++;
            cout << '\n';
        }
    }


    void Update() {
        vector<contactNode* > searchResult = search();
        if (searchResult.empty()) return;
        cout << "\n\nEnter Your Index : ";
        int index; cin >> index;
        contactNode *temp = searchResult[index];
        if (temp != NULL) {
            string n, m, e;
            vector<string > mobile;
            vector<string > email;
            char c;
            cout << "\nDo you want to update First name press y/n!\n";  cin >> c;
            if (c == 'y' || c == 'Y') {
                vector<string > name;
                cout << "\nEnter the name for updation: ";    cin >> n;
                name.push_back(n);
                temp->name[0] = name[0];
            }

            cout << "\nDo you want to update Last name press y/n!\n";  cin >> c;
            if (c == 'y' || c == 'Y') {
                vector<string > name;
                cout << "\nEnter the name for updation: ";    cin >> n;
                name.push_back(n);
                temp->name[1] = name[0];
            }

            cout << "\nDo you want to update contact number press y/n!\n";    cin >> c;
            if (c == 'y' || c == 'Y') {
                cout << "Enter the contact number: "; cin >> m;
                mobile.push_back(m);
                temp->mobile[0] = mobile[0];
            }

            cout << "\nDo you want to update email press y/n!\n"; cin >> c;
            if (c == 'y' || c == 'Y') {
                cout << "Enter the e-mail id: ";  cin >> e;
                email.push_back(e);
                temp->email[0] = email[0];
            }

            cout << "\n------Updatation Successful------\n";
        }

        if (head == temp && temp->next != NULL) {
            head = head->next;
            temp->next->pre = NULL;
            temp->next = NULL;
        }
        else if (head == temp) {
            tail = head;
            return;
        }
        else if (temp->next != NULL) {
            temp->pre->next = temp->next;
            temp->next->pre = temp->pre;
            temp->pre = NULL;
            temp->next = NULL;
        }
        else {
            temp->pre->next = temp->next;
            tail = temp->pre;
            temp->pre = NULL;
        }
        Sort(temp);
    }


    void DeleteAllContact() {
        while (head != NULL) {
            contactNode* temp = head;
            head = head->next;
            delete temp;
        }
        cout << "\n\n------------Delete All Contact Successful----------\n\n";
    }
};

class choice : protected contact {
private:
    void menu() {
        cout << " ____________________________\n";
        cout << "|1. Create New Contact       |\n";
        cout << "|2. Update Existing Contact  |\n";
        cout << "|3. Delete Contact           |\n";
        cout << "|4. View All Contact         |\n";
        cout << "|5. Search Contact           |\n";
        cout << "|6. Delete All Contact       |\n";
        cout << "|7. Exit                     |\n";
        cout << "|____________________________|\n";
    }

public:
    void chooseChoice() {

        while (true) {
            menu();
            char choice;
            cout << "\nEnter Your Choice : ";
            cin >> choice;
            switch (choice) {
            case '1':
                New();
                break;
            case '2':
                Update();
                break;
            case '3':
                Delete();
                break;
            case '4':
                view();
                break;
            case '5':
                search();
                break;
            case '6':
                DeleteAllContact();
                break;
            case '7':
                cout << "\n\n\tThank You!!!\n\n";
                exit(1);
            }
        }
    }
};

int main() {
    choice ob;
    ob.chooseChoice();
    return 0;
}