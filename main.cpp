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
	cout << "Input: COMMAND <name> [argument]" << endl;
	cout << "ARRAY: MPUSH <name> <value> | MINSERT <name> <value> <index> | MGET <name> <index>" << endl;
	cout << "       MDEL <name> <index> | MSET <name> <value> <index> | MLEN <name>" << endl;
	cout << "FORWARD LIST SLIST: FPUSHHEAD|FPUSHTAIL <name> <value>" << endl;
	cout << "       FPUSHAFTER|FPUSHBEFORE <name> <value> <target>" << endl;
	cout << "       FDELHEAD|FDELTAIL <name> | FDELAFTER|FDELBEFORE <name> <target> | FDELVAL <name> <value>" << endl;
	cout << "       FGET <name> <value>" << endl;
	cout << "LINKED LIST DLIST: LPUSHHEAD|LPUSHTAIL <name> <value> | LPUSHAFTER|LPUSHBEFORE <name> <value> <target>" << endl;
	cout << "       LDELHEAD|LDELTAIL <name> | LDELAFTER|LDELBEFORE <name> <target> | LDELVAL|LGET <name> <value>" << endl;
	cout << "STACK: SPUSH <name> <value> | SPOP <name>" << endl;
	cout << "QUEUE: QPUSH <name> <value> | QPOP <name>" << endl;
	cout << "TREE: TINSERT <name> <number> | TDEL <name> <number> | TGET <name> <number>" << endl;
	cout << "ELSE: PRINT array|slist|dlist|stack|queue|tree <name> | HELP | EXIT" << endl;
}

static const string FILE_NAME = "data.txt";

// регистры для хранения струткур

struct ArrOfArrays { Array* arr; string name; };
struct ArrOfSlists { Slist* arr; string name; };
struct ArrOfDlists { Dlist* arr; string name; };
struct ArrOfStacks { Stack* arr; string name; };
struct ArrOfQueues { Queue* arr; string name; };
struct ArrOfTrees { TreeNode** arr; string name; };

template <typename T>
struct Registry {
	T* items;
	size_t size;
	size_t capacity;
};

Registry<ArrOfArrays> arrays = {nullptr, 0, 0};
Registry<ArrOfSlists> slists = {nullptr, 0, 0};
Registry<ArrOfDlists> dlists = {nullptr, 0, 0};
Registry<ArrOfStacks> stacks = {nullptr, 0, 0};
Registry<ArrOfQueues> queues = {nullptr, 0, 0};
Registry<ArrOfTrees> trees = {nullptr, 0, 0};

template <typename T>
void regGrow(Registry<T>& r) {
	size_t newCap = r.capacity == 0 ? 4 : r.capacity * 2;
	T* n = new T[newCap];
	for (size_t i = 0; i < r.size; ++i) n[i] = r.items[i];
	delete[] r.items;
	r.items = n;
	r.capacity = newCap;
}

// получение и создание структур

Array* getArray(const string& name) {
	for (size_t i = 0; i < arrays.size; ++i)
		if (arrays.items[i].name == name) return arrays.items[i].arr;
	if (arrays.size == arrays.capacity) regGrow(arrays);
	Array* a = new Array;
	MInitArray(*a, 4);
	arrays.items[arrays.size++] = {a, name};
	return a;
}

Slist* getSlist(const string& name) {
	for (size_t i = 0; i < slists.size; ++i)
		if (slists.items[i].name == name) return slists.items[i].arr;
	if (slists.size == slists.capacity) regGrow(slists);
	Slist* s = new Slist;
	FInitializeSlist(*s);
	slists.items[slists.size++] = {s, name};
	return s;
}

Dlist* getDlist(const string& name) {
	for (size_t i = 0; i < dlists.size; ++i)
		if (dlists.items[i].name == name) return dlists.items[i].arr;
	if (dlists.size == dlists.capacity) regGrow(dlists);
	Dlist* d = new Dlist;
	dlists.items[dlists.size++] = {d, name};
	return d;
}

Stack* getStack(const string& name) {
	for (size_t i = 0; i < stacks.size; ++i)
		if (stacks.items[i].name == name) return stacks.items[i].arr;
	if (stacks.size == stacks.capacity) regGrow(stacks);
	Stack* s = new Stack;
	SInitializeStack(s);
	stacks.items[stacks.size++] = {s, name};
	return s;
}

Queue* getQueue(const string& name) {
	for (size_t i = 0; i < queues.size; ++i)
		if (queues.items[i].name == name) return queues.items[i].arr;
	if (queues.size == queues.capacity) regGrow(queues);
	Queue* q = new Queue;
	QInitializeQueue(q);
	queues.items[queues.size++] = {q, name};
	return q;
}

TreeNode** getTree(const string& name) {
	for (size_t i = 0; i < trees.size; ++i)
		if (trees.items[i].name == name) return trees.items[i].arr;
	if (trees.size == trees.capacity) regGrow(trees);
	TreeNode** t = new TreeNode*(nullptr);
	trees.items[trees.size++] = {t, name};
	return t;
}

// сохранение и загрузка

static void SaveAll() {
	ofstream f(FILE_NAME);
	if (!f) return;

	for (size_t i = 0; i < arrays.size; ++i) {
		Array* a = arrays.items[i].arr;
		f << "ARRAY " << arrays.items[i].name << " " << MLength(*a) << "\n";
		for (size_t j = 0; j < MLength(*a); ++j) f << MGet(*a, j) << "\n";
	}

	for (size_t i = 0; i < slists.size; ++i) {
		Slist* s = slists.items[i].arr;
		int count = 0;
		for (SlistNode* n = s->head; n; n = n->next) count++;
		f << "FLIST " << slists.items[i].name << " " << count << "\n";
		for (SlistNode* n = s->head; n; n = n->next) f << n->text << "\n";
	}

	for (size_t i = 0; i < dlists.size; ++i) {
		Dlist* d = dlists.items[i].arr;
		int count = 0;
		for (DlistNode* n = d->head; n; n = n->next) count++;
		f << "DLIST " << dlists.items[i].name << " " << count << "\n";
		for (DlistNode* n = d->head; n; n = n->next) f << n->text << "\n";
	}

	for (size_t i = 0; i < stacks.size; ++i) {
		Stack* st = stacks.items[i].arr;
		int count = 0;
		for (StackNode* n = st->head; n; n = n->next) count++;
		f << "STACK " << stacks.items[i].name << " " << count << "\n";
		for (StackNode* n = st->head; n; n = n->next) f << n->text << "\n";
	}

	for (size_t i = 0; i < queues.size; ++i) {
		Queue* q = queues.items[i].arr;
		int count = 0;
		for (QueueNode* n = q->head; n; n = n->next) count++;
		f << "QUEUE " << queues.items[i].name << " " << count << "\n";
		for (QueueNode* n = q->head; n; n = n->next) f << n->text << "\n";
	}

	for (size_t i = 0; i < trees.size; ++i) {
		TreeNode* r = *trees.items[i].arr;
		f << "TREE " << trees.items[i].name << " ";
		struct Helper {
			static void go(TreeNode* r, ostream& os) {
				if (!r) return;
				os << r->data << " ";
				go(r->left, os);
				go(r->right, os);
			}
		};
		ostringstream oss;
		Helper::go(r, oss);
		f << oss.str() << "\n";
	}
}

static void LoadAll() {
	ifstream f(FILE_NAME);
	if (!f) return;
	string tag, name;
	int count;

	while (f >> tag >> name) {
		if (tag == "TREE") {
			string line; getline(f, line);
			istringstream iss(line);
			int v;
			TreeNode** tree = getTree(name);
			while (tree && iss >> v) {
				if (!*tree) *tree = new TreeNode(v, false);
				else { insertRecursive(*tree, v); (*tree)->isRed = false; }
			}
			continue;
		}

		if (f >> count) {
			f.ignore();
			if (tag == "ARRAY") {
				Array* arr = getArray(name);
				for (int i = 0; i < count; ++i) {
					string s; getline(f, s);
					if (arr) MAddEnd(*arr, s);
				}
			} else if (tag == "FLIST") {
				Slist* slist = getSlist(name);
				for (int i = 0; i < count; ++i) {
					string s; getline(f, s);
					if (slist) {
						SlistNode* newNode = new SlistNode{s, nullptr};
						if (!slist->head) slist->head = newNode;
						else {
							SlistNode* n = slist->head;
							while (n->next) n = n->next;
							n->next = newNode;
						}
					}
				}
			} else if (tag == "DLIST") {
				Dlist* dlist = getDlist(name);
				for (int i = 0; i < count; ++i) {
					string s; getline(f, s);
					if (dlist) DPushTail(*dlist, s);
				}
			} else if (tag == "STACK") {
				Stack* stack = getStack(name);
				string* buf = new string[count > 0 ? count : 1];
				for (int i = 0; i < count; ++i) getline(f, buf[i]);
				if (stack) for (int i = count - 1; i >= 0; --i) SPush(stack, buf[i]);
				delete[] buf;
			} else if (tag == "QUEUE") {
				Queue* queue = getQueue(name);
				for (int i = 0; i < count; ++i) {
					string s; getline(f, s);
					if (queue) QPush(queue, s);
				}
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "");

	LoadAll();
	cout << "Abstract Data Structures. HELP — list of commands." << endl;

	string line;
	while (true) {
		cout << "> ";
		if (!getline(cin, line)) break;
		istringstream in(line);
		string cmdName, dsName, value, target, out;
		if (!(in >> cmdName)) continue;

		Command cmd = GetCommand(cmdName);
		if (cmd == Command::HELP) { printHelp(); continue; }
		if (cmd == Command::EXIT) break;

		if (!(in >> dsName)) { cout << "No name provided" << endl; continue; }

		int index = -1;
		bool changed = false;

		switch (cmd) {
			// --- МАССИВ ---
			case Command::MPUSH: {
				Array* arr = getArray(dsName);
				if (arr && in >> value) { MAddEnd(*arr, value); cout << "-> " << value << endl; changed = true; }
				else cout << "No" << endl;
				break;
			}
			case Command::MINSERT: {
				Array* arr = getArray(dsName);
				if (arr && in >> value >> index && index >= 0 && (size_t)index <= MLength(*arr)) {
					MAddIndex(*arr, value, (size_t)index); cout << "-> " << value << endl; changed = true;
				} else cout << "No" << endl;
				break;
			}
			case Command::MGET: {
				Array* arr = getArray(dsName);
				if (arr && in >> index && index >= 0 && (size_t)index < MLength(*arr)) cout << "-> " << MGet(*arr, (size_t)index) << endl;
				else cout << "No" << endl;
				break;
			}
			case Command::MDEL: {
				Array* arr = getArray(dsName);
				if (arr && in >> index && index >= 0 && (size_t)index < MLength(*arr)) {
					value = MGet(*arr, (size_t)index); MDeleteIndex(*arr, (size_t)index); cout << "-> " << value << endl; changed = true;
				} else cout << "No" << endl;
				break;
			}
			case Command::MSET: {
				Array* arr = getArray(dsName);
				if (arr && in >> value >> index && index >= 0 && (size_t)index < MLength(*arr)) {
					MReplace(*arr, value, (size_t)index); cout << "-> " << value << endl; changed = true;
				} else cout << "No" << endl;
				break;
			}
			case Command::MLEN: {
				Array* arr = getArray(dsName);
				if (arr) cout << "-> " << MLength(*arr) << endl; else cout << "No" << endl;
				break;
			}

			// --- ОДНОСВЯЗНЫЙ СПИСОК ---
			case Command::FPUSHHEAD: {
				Slist* slist = getSlist(dsName);
				if (slist && in >> value) {
					FPushHead(*slist, value);
					cout << "-> " << value << endl; changed = true; }
				else cout << "No" << endl;
				break;
			}
			case Command::FPUSHTAIL: {
				Slist* slist = getSlist(dsName);
				if (slist && in >> value) {
					FPushTail(*slist, value);
					cout << "-> " << value << endl; changed = true;
				} else cout << "No" << endl;
				break;
			}
			case Command::FPUSHAFTER: {
				Slist* slist = getSlist(dsName);
				if (slist && in >> value >> target) {
					FPushAfter(*slist, target, value); cout << "-> " << value << endl; changed = true; 
				} else cout << "No" << endl;
				break;
			}
			case Command::FPUSHBEFORE: {
    			Slist* slist = getSlist(dsName);
    			if (slist && in >> value >> target) {
        			FPushBefore(*slist, target, value); cout << "-> " << value << endl; changed = true;					
    			} else cout << "No" << endl;
    			break;
			}
			case Command::FDELHEAD: {
				Slist* slist = getSlist(dsName);
				if (slist && slist->head) { out = slist->head->text; FDeleteHead(*slist); cout << "-> " << out << endl; changed = true; }
				else cout << "No" << endl;
				break;
			}
			case Command::FDELTAIL: {
				Slist* slist = getSlist(dsName);
				if (slist && slist->head) {
					FDeleteTail(*slist);
					cout << "-> Deleted" << endl; changed = true;
				} else cout << "No" << endl;
				break;
			}
			case Command::FDELAFTER: {
				Slist* slist = getSlist(dsName);
				if (slist && in >> target && FGet(*slist, target)) {
					FDeleteAfter(*slist, target);
					cout << "-> Deleted" << endl; changed = true;
				} else cout << "No" << endl;
				break;
			}
			case Command::FDELBEFORE: {
    			Slist* slist = getSlist(dsName);
    			if (slist && in >> target && FGet(*slist, target)) {
        			FDeleteBefore(*slist, target);
					cout << "-> Deleted" << endl; changed = true;
    			} else cout << "No" << endl;
    			break;
			}
			case Command::FDELVAL: {
				Slist* slist = getSlist(dsName);
				if (slist && in >> value && FGet(*slist, value)) {
					FDeleteValue(*slist, value);
					cout << "-> " << value << endl; changed = true;
				} else cout << "No" << endl;
				break;
			}
			case Command::FGET: {
				Slist* slist = getSlist(dsName);
				if (slist && in >> value) {
					cout << ">> " << ((FGet(*slist, value)) ? "True" : "False") << endl;
				} else cout << "No" << endl;
				break;
			}

			// --- ДВУСВЯЗНЫЙ СПИСОК ---
			case Command::LPUSHHEAD: {
				Dlist* dlist = getDlist(dsName);
				if (dlist && in >> value) { DPushHead(*dlist, value); cout << "-> " << value << endl; changed = true; }
				else cout << "No" << endl;
				break;
			}
			case Command::LPUSHTAIL: {
				Dlist* dlist = getDlist(dsName);
				if (dlist && in >> value) { DPushTail(*dlist, value); cout << "-> " << value << endl; changed = true; }
				else cout << "No" << endl;
				break;
			}
			case Command::LPUSHAFTER: {
				Dlist* dlist = getDlist(dsName);
				if (dlist && in >> value >> target && DFind(*dlist, target)) {
					DPushAfter(*dlist, value, target);
					cout << "-> " << value << endl; changed = true;
				} else cout << "No" << endl;
				break;
			}
			case Command::LPUSHBEFORE: {
				Dlist* dlist = getDlist(dsName);
				if (dlist && in >> value >> target && DFind(*dlist, target)) {
					DPushBefore(*dlist, value, target);
					cout << "-> " << value << endl; changed = true;
				} else cout << "No" << endl;
				break;
			}
			case Command::LDELHEAD: {
				Dlist* dlist = getDlist(dsName);
				if (dlist){
					DDeleteHead(*dlist);
					cout << "-> " << dlist->head->text << endl; changed = true;}
				else cout << "No" << endl;
				break;
			}
			case Command::LDELTAIL: {
				Dlist* dlist = getDlist(dsName);
				if (dlist) {
					DDeleteTail(*dlist); cout << "-> " << dlist->tail->text << endl; changed = true;
				} else cout << "No" << endl;
				break;
			}
			case Command::LDELAFTER: {
				Dlist* dlist = getDlist(dsName);
				if (dlist && in >> target && DFind(*dlist, target)) {
					DDeleteAfter(*dlist, target);
					cout << "-> Deleted" << endl; changed = true; 
				} else cout << "No" << endl;
				break;
			}
			case Command::LDELBEFORE: {
				Dlist* dlist = getDlist(dsName);
				if (dlist && in >> target && DFind(*dlist, target)) {
					DDeleteBefore(*dlist, target); cout << "-> Deleted" << endl; changed = true;
				} else cout << "No" << endl;
				break;
			}
			case Command::LDELVAL: {
				Dlist* dlist = getDlist(dsName);
				if (dlist && in >> value && DFind(*dlist, value)) {
					DDeleteValue(*dlist, value); cout << "-> " << value << endl; changed = true; 
				} else cout << "No" << endl;
				break;
			}
			case Command::LGET: {
				Dlist* dlist = getDlist(dsName);
				if (dlist && in >> value) { if (DFind(*dlist, value)) cout << "-> " << value << endl; else cout << "No" << endl; }
				else cout << "No" << endl;
				break;
			}

			// --- СТЕК ---
			case Command::SPUSH: {
				Stack* stack = getStack(dsName);
				if (stack && in >> value) { SPush(stack, value); cout << "-> " << value << endl; changed = true; }
				else cout << "No" << endl;
				break;
			}
			case Command::SPOP: {
				Stack* stack = getStack(dsName);
				if (stack && stack->head) {
					out = stack->head->text; StackNode* del = stack->head; stack->head = del->next;
					delete del; cout << "-> " << out << endl; changed = true;
				} else cout << "No" << endl;
				break;
			}

			// --- ОЧЕРЕДЬ ---
			case Command::QPUSH: {
				Queue* queue = getQueue(dsName);
				if (queue && in >> value) { QPush(queue, value); cout << "-> " << value << endl; changed = true; }
				else cout << "No" << endl;
				break;
			}
			case Command::QPOP: {
				Queue* queue = getQueue(dsName);
				if (queue && queue->head) {
					out = queue->head->text; QueueNode* del = queue->head; queue->head = del->next;
					if (!queue->head) queue->tail = nullptr;
					delete del; cout << "-> " << out << endl; changed = true;
				} else cout << "No" << endl;
				break;
			}

			// --- ЧЕРНО-КРАСНОЕ ДЕРЕВО ---
			case Command::TINSERT: {
				TreeNode** tree = getTree(dsName);
				if (tree && in >> value) {
					try {
						int v = stoi(value);
						if (!*tree) *tree = new TreeNode(v, false);
						else { insertRecursive(*tree, v); (*tree)->isRed = false; }
						cout << "-> " << v << endl; changed = true;
					} catch (...) { cout << "No" << endl; }
				} else cout << "No" << endl;
				break;
			}
			case Command::TDEL: {
				TreeNode** tree = getTree(dsName);
				if (tree && in >> value) {
					try {
						int v = stoi(value);
						if (search(*tree, v)) { *tree = remove(*tree, v); if (*tree) (*tree)->isRed = false; cout << "-> " << v << endl; changed = true; }
						else cout << "No" << endl;
					} catch (...) { cout << "No" << endl; }
				} else cout << "No" << endl;
				break;
			}
			case Command::TGET: {
				TreeNode** tree = getTree(dsName);
				if (tree && in >> value) {
					try { if (search(*tree, stoi(value))) cout << "-> " << stoi(value) << endl; else cout << "No" << endl; }
					catch (...) { cout << "No" << endl; }
				} else cout << "No" << endl;
				break;
			}

			// --- ВЫВОД ---
			case Command::PRINT: {
				string targetName;
				if (!(in >> targetName)) { cout << "No" << endl; break; }

				if (cmdName == "PRINT") {
					if (dsName == "array") { Array* arr = getArray(targetName); if(arr) MPrint(*arr); }
					else if (dsName == "slist") { Slist* slist = getSlist(targetName); if(slist) { for (SlistNode* n = slist->head; n; n = n->next) cout << n->text << " "; cout << endl; } }
					else if (dsName == "dlist") { Dlist* dlist = getDlist(targetName); if(dlist) DPrintForward(*dlist); }
					else if (dsName == "stack") { Stack* stack = getStack(targetName); if(stack) SPrint(*stack); }
					else if (dsName == "queue") { Queue* queue = getQueue(targetName); if(queue) QPrint(*queue); }
					else if (dsName == "tree") {
						TreeNode** tree = getTree(targetName);
						if(tree) {
							cout << "preorder: "; printPreOrder(*tree); cout << endl;
							cout << "inorder: "; printInOrder(*tree); cout << endl;
							cout << "postorder: "; printPostOrder(*tree); cout << endl;
							cout << "bfs: "; printBFS(*tree);
						}
					}
					else cout << "No" << endl;
				}
				break;
			}

			default: cout << "Unknown command. HELP — list of commands" << endl;
		}

		if (changed) SaveAll();
	}

	SaveAll();

	// Очистка памяти
	for (size_t i = 0; i < arrays.size; ++i) { MFree(*arrays.items[i].arr); delete arrays.items[i].arr; }
	delete[] arrays.items;

	for (size_t i = 0; i < slists.size; ++i) { FFree(*slists.items[i].arr); delete slists.items[i].arr; }
	delete[] slists.items;

	for (size_t i = 0; i < dlists.size; ++i) { DFree(*dlists.items[i].arr); delete dlists.items[i].arr; }
	delete[] dlists.items;

	for (size_t i = 0; i < stacks.size; ++i) { SFree(*stacks.items[i].arr); delete stacks.items[i].arr; }
	delete[] stacks.items;

	for (size_t i = 0; i < queues.size; ++i) { QFree(*queues.items[i].arr); delete queues.items[i].arr; }
	delete[] queues.items;

	for (size_t i = 0; i < trees.size; ++i) { clearTree(*trees.items[i].arr); delete trees.items[i].arr; }
	delete[] trees.items;

	cout << "Done." << endl;
	return 0;
}