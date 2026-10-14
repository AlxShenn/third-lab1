#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "commands.h"
#include "structures/array.h"
#include "structures/slist.h"
#include "structures/dlist.h"
#include "structures/stack.h"
#include "structures/queue.h"
#include "structures/blackredtree.h"

using namespace std;

static void printHelp() {
    cout << "ARRAY:               MPUSH <value> | MINSERT <value> <index> | MGET <index>" << endl;
    cout << "                     MDEL <index> | MSET <value> <index> | MLEN" << endl;
    cout << "FORWARD LIST SLIST:  FPUSHHEAD|FPUSHTAIL <value>" << endl;
    cout << "                     FPUSHAFTER|FPUSHBEFORE <value> <target>" << endl;
    cout << "                     FDELHEAD|FDELTAIL | FDELAFTER|FDELBEFORE <target> | FDELVAL <value>" << endl;
    cout << "                     FGET <value>" << endl;
    cout << "LINKED LIST DLIST:   LPUSHHEAD|LPUSHTAIL|LPUSHAFTER|LPUSHBEFORE|LDELHEAD|LDELTAIL" << endl;
    cout << "                     LDELAFTER|LDELBEFORE|LDELVAL|LGET <value>" << endl;
    cout << "STACK:               SPUSH <value> | SPOP" << endl;
    cout << "QUEUE:               QPUSH <value> | QPOP" << endl;
    cout << "TREE:                TINSERT <number> | TDEL <number> | TGET <number>" << endl;
    cout << "ELSE:                PRINT array|slist|dlist|stack|queue|queue1|tree | HELP | EXIT" << endl;
}

static const string FILE_NAME = "data.txt";

static void SaveAll(Array& arr, Slist& slist, DlistNode* dlist,
                    Stack& stack, Queue& queue, TreeNode* tree) {
    ofstream f(FILE_NAME);
    if (!f) return;

    f << "ARRAY " << MLength(arr) << "\n";
    for (size_t i = 0; i < MLength(arr); ++i)
        f << MGet(arr, i) << "\n";

    int fcount = 0;
    for (SlistNode* n = slist.head; n; n = n->next) ++fcount;
    f << "FLIST " << fcount << "\n";
    for (SlistNode* n = slist.head; n; n = n->next)
        f << n->text << "\n";

    int lcount = 0;
    for (DlistNode* n = dlist; n; n = n->next) ++lcount;
    f << "DLIST " << lcount << "\n";
    for (DlistNode* n = dlist; n; n = n->next)
        f << n->text << "\n";

    int scount = 0;
    for (StackNode* n = stack.head; n; n = n->next) ++scount;
    f << "STACK " << scount << "\n";
    for (StackNode* n = stack.head; n; n = n->next)
        f << n->text << "\n";

    int qcount = 0;
    for (QueueNode* n = queue.head; n; n = n->next) ++qcount;
    f << "QUEUE " << qcount << "\n";
    for (QueueNode* n = queue.head; n; n = n->next)
        f << n->text << "\n";

    f << "TREE ";
    {
        struct Helper {
            static void go(TreeNode* r, ostream& os) {
                if (!r) return;
                os << r->data << " ";
                go(r->left, os);
                go(r->right, os);
            }
        };
        ostringstream oss;
        Helper::go(tree, oss);
        f << oss.str() << "\n";
    }
}

static void LoadAll(Array& arr, Slist& slist, DlistNode*& dlist,
                    Stack& stack, Queue& queue, TreeNode*& tree) {
    ifstream f(FILE_NAME);
    if (!f) return;

    string tag;
    int count;

    if (f >> tag >> count && tag == "ARRAY") {
        f.ignore();
        for (int i = 0; i < count; ++i) {
            string s; getline(f, s);
            MAddEnd(arr, s);
        }
    }

    if (f >> tag >> count && tag == "FLIST") {
        f.ignore();
        for (int i = 0; i < count; ++i) {
            string s; getline(f, s);
            SlistNode* newNode = new SlistNode{s, nullptr};
            if (!slist.head) slist.head = newNode;
            else {
                SlistNode* n = slist.head;
                while (n->next) n = n->next;
                n->next = newNode;
            }
        }
    }

    if (f >> tag >> count && tag == "DLIST") {
        f.ignore();
        for (int i = 0; i < count; ++i) {
            string s; getline(f, s);
            DPushTail(dlist, s);
        }
    }

    if (f >> tag >> count && tag == "STACK") {
        f.ignore();
        string* buf = new string[count > 0 ? count : 1];
        for (int i = 0; i < count; ++i) getline(f, buf[i]);
        for (int i = count - 1; i >= 0; --i) SPush(&stack, buf[i]);
        delete[] buf;
    }

    if (f >> tag >> count && tag == "QUEUE") {
        f.ignore();
        for (int i = 0; i < count; ++i) {
            string s; getline(f, s);
            QPush(&queue, s);
        }
    }

    if (f >> tag) {
        if (tag == "TREE") {
            string line; getline(f, line);
            istringstream iss(line);
            int v;
            while (iss >> v) {
                if (!tree) tree = new TreeNode(v, false);
                else { insertRecursive(tree, v); tree->isRed = false; }
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "");

    Array      arr;
    Slist      slist;
    DlistNode* dlist = nullptr;
    Stack      stack;
    Queue      queue;
    TreeNode*  tree  = nullptr;

    MInitArray(arr, (size_t)4);
    FInitializeSlist(&slist);
    SInitializeStack(&stack);
    QInitializeQueue(&queue);

    LoadAll(arr, slist, dlist, stack, queue, tree);

    cout << "Abstract Data Structures. HELP — list of commands." << endl;

    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        istringstream in(line);
        string name;
        if (!(in >> name)) continue;

        Command cmd = GetCommand(name);
        string value, target, out;
        int index = -1;
        bool ok = true;
        bool changed = false;

        switch (cmd) {
        // массив
        case Command::MPUSH:
            if (in >> value) {
                MAddEnd(arr, value);
                cout << "-> " << value << endl;
                changed = true;
            } else cout << "No" << endl;
            break;
        case Command::MINSERT:
            if (in >> value >> index && index >= 0 && (size_t)index <= MLength(arr)) {
                MAddIndex(arr, value, (size_t)index);
                cout << "-> " << value << endl;
                changed = true;
            } else cout << "No" << endl;
            break;
        case Command::MGET:
            if (in >> index && index >= 0 && (size_t)index < MLength(arr)) {
                cout << "-> " << MGet(arr, (size_t)index) << endl;
            } else cout << "No" << endl;
            break;
        case Command::MDEL:
            if (in >> index && index >= 0 && (size_t)index < MLength(arr)) {
                value = MGet(arr, (size_t)index);
                MDeleteIndex(arr, (size_t)index);
                cout << "-> " << value << endl;
                changed = true;
            } else cout << "No" << endl;
            break;
        case Command::MSET:
            if (in >> value >> index && index >= 0 && (size_t)index < MLength(arr)) {
                MReplace(arr, value, (size_t)index);
                cout << "-> " << value << endl;
                changed = true;
            } else cout << "No" << endl;
            break;
        case Command::MLEN:
            cout << "-> " << MLength(arr) << endl;
            break;

        // односвязный список
        case Command::FPUSHHEAD:
            if (in >> value) {
                slist.head = new SlistNode{value, slist.head};
                cout << "-> " << value << endl;
                changed = true;
            } else cout << "No" << endl;
            break;
        case Command::FPUSHTAIL:
            if (in >> value) {
                SlistNode* newNode = new SlistNode{value, nullptr};
                if (!slist.head) {
                    slist.head = newNode;
                } else {
                    SlistNode* n = slist.head;
                    while (n->next) n = n->next;
                    n->next = newNode;
                }
                cout << "-> " << value << endl;
                changed = true;
            } else cout << "No" << endl;
            break;
        case Command::FPUSHAFTER:
            if (in >> value >> target) {
                SlistNode* n = slist.head;
                while (n && n->text != target) n = n->next;
                if (n) {
                    FPushAfter(n, value);
                    cout << "-> " << value << endl;
                    changed = true;
                } else cout << "No" << endl;
            } else cout << "No" << endl;
            break;
        case Command::FPUSHBEFORE:
            if (in >> value >> target) {
                if (!slist.head) { cout << "No" << endl; break; }
                if (slist.head->text == target) {
                    slist.head = new SlistNode{value, slist.head};
                    cout << "-> " << value << endl;
                    changed = true;
                    break;
                }
                SlistNode* n = slist.head;
                while (n->next && n->next->text != target) n = n->next;
                if (n->next) {
                    FPushAfter(n, value);
                    cout << "-> " << value << endl;
                    changed = true;
                } else cout << "No" << endl;
            } else cout << "No" << endl;
            break;
        case Command::FDELHEAD:
            if (slist.head) {
                out = slist.head->text;
                FDeleteHead(&slist);
                cout << "-> " << out << endl;
                changed = true;
            } else cout << "No" << endl;
            break;
        case Command::FDELTAIL:
            if (slist.head) {
                SlistNode* n = slist.head;
                while (n->next) n = n->next;
                out = n->text;
                FDeleteTail(&slist);
                cout << "-> " << out << endl;
                changed = true;
            } else cout << "No" << endl;
            break;
        case Command::FDELAFTER:
            if (in >> target) {
                SlistNode* n = slist.head;
                while (n && n->text != target) n = n->next;
                if (n && n->next) {
                    out = n->next->text;
                    FDeleteAfter(n);
                    cout << "-> " << out << endl;
                    changed = true;
                } else cout << "No" << endl;
            } else cout << "No" << endl;
            break;
        case Command::FDELBEFORE:
            if (in >> target) {
                if (!slist.head || slist.head->text == target) { cout << "No" << endl; break; }
                if (slist.head->next && slist.head->next->text == target) {
                    out = slist.head->text;
                    FDeleteHead(&slist);
                    cout << "-> " << out << endl;
                    changed = true;
                    break;
                }
                SlistNode* n = slist.head;
                while (n->next && n->next->next && n->next->next->text != target) n = n->next;
                if (n->next && n->next->next) {
                    out = n->next->text;
                    FDeleteAfter(n);
                    cout << "-> " << out << endl;
                    changed = true;
                } else cout << "No" << endl;
            } else cout << "No" << endl;
            break;
        case Command::FDELVAL:
            if (in >> value) {
                SlistNode* n = slist.head;
                while (n && n->text != value) n = n->next;
                if (n) {
                    FDeleteValue(&slist, value);
                    cout << "-> " << value << endl;
                    changed = true;
                } else cout << "No" << endl;
            } else cout << "No" << endl;
            break;
        case Command::FGET:
            if (in >> value) {
                SlistNode* n = slist.head;
                while (n && n->text != value) n = n->next;
                if (n) cout << "-> " << value << endl;
                else   cout << "No" << endl;
            } else cout << "No" << endl;
            break;

        // двусвязный список
        case Command::LPUSHHEAD:
            if (in >> value) {
                DPushHead(dlist, value);
                cout << "-> " << value << endl;
                changed = true;
            } else cout << "No" << endl;
            break;
        case Command::LPUSHTAIL:
            if (in >> value) {
                DPushTail(dlist, value);
                cout << "-> " << value << endl;
                changed = true;
            } else cout << "No" << endl;
            break;
        case Command::LPUSHAFTER:
            if (in >> value >> target) {
                DlistNode* n = DFind(dlist, target);
                if (n) {
                    DPushAfter(n, value);
                    cout << "-> " << value << endl;
                    changed = true;
                } else cout << "No" << endl;
            } else cout << "No" << endl;
            break;
        case Command::LPUSHBEFORE:
            if (in >> value >> target) {
                DlistNode* n = DFind(dlist, target);
                if (n) {
                    if (n == dlist) DPushHead(dlist, value);
                    else DPushBefore(n, value);
                    cout << "-> " << value << endl;
                    changed = true;
                } else cout << "No" << endl;
            } else cout << "No" << endl;
            break;
        case Command::LDELHEAD:
            if (dlist) {
                out = dlist->text;
                DDeleteHead(dlist);
                cout << "-> " << out << endl;
                changed = true;
            } else cout << "No" << endl;
            break;
        case Command::LDELTAIL:
            if (dlist) {
                DlistNode* n = dlist;
                while (n->next) n = n->next;
                out = n->text;
                DDeleteTail(dlist);
                cout << "-> " << out << endl;
                changed = true;
            } else cout << "No" << endl;
            break;
        case Command::LDELAFTER:
            if (in >> target) {
                DlistNode* n = DFind(dlist, target);
                if (n && n->next) {
                    out = n->next->text;
                    DDeleteAfter(n);
                    cout << "-> " << out << endl;
                    changed = true;
                } else cout << "No" << endl;
            } else cout << "No" << endl;
            break;
        case Command::LDELBEFORE:
            if (in >> target) {
                DlistNode* n = DFind(dlist, target);
                if (n && n->prev) {
                    out = n->prev->text;
                    if (n->prev == dlist) DDeleteHead(dlist);
                    else DDeleteBefore(n);
                    cout << "-> " << out << endl;
                    changed = true;
                } else cout << "No" << endl;
            } else cout << "No" << endl;
            break;
        case Command::LDELVAL:
            if (in >> value) {
                DlistNode* n = DFind(dlist, value);
                if (n) {
                    DDeleteValue(dlist, value);
                    cout << "-> " << value << endl;
                    changed = true;
                } else cout << "No" << endl;
            } else cout << "No" << endl;
            break;
        case Command::LGET:
            if (in >> value) {
                DlistNode* n = DFind( dlist, value);
                if (n) cout << "-> " << value << endl;
                else cout << "No" << endl;
            } else cout << "No" << endl;
            break;

        // стек
        case Command::SPUSH:
            if (in >> value) {
                SPush(&stack, value);
                cout << "-> " << value << endl;
                changed = true;
            } else cout << "No" << endl;
            break;
        case Command::SPOP:
            if (stack.head) {
                out = stack.head->text;
                StackNode* nodeToDelete = stack.head;
                stack.head = nodeToDelete->next;
                delete nodeToDelete;
                cout << "-> " << out << endl;
                changed = true;
            } else cout << "No" << endl;
            break;


        // очередь
        case Command::QPUSH:
            if (in >> value) {
                QPush(&queue, value);
                cout << "-> " << value << endl;
                changed = true;
            } else cout << "No" << endl;
            break;
        case Command::QPOP:
            if (queue.head) {
                out = queue.head->text;
                QueueNode* nodeToDelete = queue.head;
                queue.head = nodeToDelete->next;
                if (!queue.head) queue.tail = nullptr;
                delete nodeToDelete;
                cout << "-> " << out << endl;
                changed = true;
            } else cout << "No" << endl;
            break;

        // чб дерево
        case Command::TINSERT:
            if (in >> value) {
                try {
                    int v = stoi(value);
                    if (!tree) tree = new TreeNode(v, false);
                    else { insertRecursive(tree, v); tree->isRed = false; }
                    cout << "-> " << v << endl;
                    changed = true;
                } catch (...) {
                    cout << "No" << endl;
                }
            } else cout << "No" << endl;
            break;
        case Command::TDEL:
            if (in >> value) {
                try {
                    int v = stoi(value);
                    if (search(tree, v)) {
                        tree = remove(tree, v);
                        if (tree) tree->isRed = false;
                        cout << "-> " << v << endl;
                        changed = true;
                    } else cout << "No" << endl;
                } catch (...) {
                    cout << "No" << endl;
                }
            } else cout << "No" << endl;
            break;
        case Command::TGET:
            if (in >> value) {
                try {
                    int v = stoi(value);
                    if (search(tree, v)) cout << "-> " << v << endl;
                    else cout << "No" << endl;
                } catch (...) {
                    cout << "No" << endl;
                }
            } else cout << "No" << endl;
            break;


        // вывод
        case Command::PRINT: {
            string type;
            if (!(in >> type)) { cout << "No" << endl; break; }
            if (type == "array") {
                MPrint(arr);
            } else if (type == "slist") {
                for (SlistNode* n = slist.head; n; n = n->next) cout << n->text << " ";
                cout << endl;
            } else if (type == "dlist") {
                DPrintForward(dlist);
            } else if (type == "stack") {
                SPrint(stack);
            } else if (type == "queue") {
                QPrint(queue);
            } else if (type == "queue1") {
                QPrint(queue);
            } else if (type == "tree") {
                cout << "preorder:  "; printPreOrder(tree); cout << endl;
                cout << "inorder:   "; printInOrder(tree); cout << endl;
                cout << "postorder: "; printPostOrder(tree); cout << endl;
                cout << "bfs:       "; printBFS(tree);
            } else {
                cout << "No" << endl;
            }
            break;
        }

        case Command::HELP:
            printHelp();
            break;
        case Command::EXIT:
            ok = false;
            break;
        default:
            cout << "Unknown command. HELP — list of commands" << endl;
        }

        if (changed) SaveAll(arr, slist, dlist, stack, queue, tree);
        if (!ok) break;
    }

    SaveAll(arr, slist, dlist, stack, queue, tree);

    MFree(arr);
    FFree(&slist);
    DFree(dlist);
    SFree(stack);
    QFree(queue);
    clearTree(tree);

    cout << "Done." << endl;
    return 0;
}
