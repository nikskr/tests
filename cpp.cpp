#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <queue>

using namespace std;


//---------------1----------------------------------------------------------------------------------------------

vector<int> getIndexForSum(const vector<int>& nums, int target) {
    vector<int> indexForSum(2);
    for (auto i = 0; i < nums.size() - 1; i++) {
        for (auto j = i + 1; j < nums.size(); j++) {
            if (nums[i] + nums[j] == target) {
                indexForSum[0] = i;
                indexForSum[1] = j;
                return indexForSum;
            }
        }
    }
    return { 0, 0 };
}



//---------------2----------------------------------------------------------------------------------------------

string strToLowerCase(string str) {
    string newStr = str;
    transform(newStr.begin(), newStr.end(), newStr.begin(), [](unsigned char c) {
        return tolower(c);
        });
    return newStr;
}

string strToOneWord(string str) {
    string newStr;
    for (unsigned char ch : str) {
        if (isalnum(ch)) {
            newStr += ch;
        }
    }
    return newStr;
}

bool isPalindrome(string str) {
    string processedStr = strToOneWord(str);
    processedStr = strToLowerCase(processedStr);
    for (int i = 0; i < floor((processedStr.length() - 1)/ 2); i++) {
        if (processedStr[i] != processedStr[processedStr.length() - 1 - i]) {
            cout << "false" << endl;
            return false;
        }
    }
    cout << "true" << endl;
    return true;
}



//---------------3-----------------------------------------------------------------------------------------

bool isValidBracketSequence(string str) {
    map <char, char> bracketMap = {
        {'(', ')'},
        {'{', '}'},
        {'[', ']'},
    };

    stack <char> bracketStack;

    for (unsigned char ch : str) {
        if (ch == '(' || ch == '[' || ch == '{') {
            bracketStack.push(ch);
        }
        else {
            if (ch != bracketMap[bracketStack.top()]) {
                return false;
            }
            else {
                bracketStack.pop();
            }
        }
    }

    if (!bracketStack.empty()) return false;

    return true;
}



//---------------4----------------------------------------------------------------------------------------------

vector <int> sortArray(vector <int> arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[i]) {
                int p = arr[i];
                arr[i] = arr[j];
                arr[j] = p;
            }
        }
    }
    return arr;
}

int binarySearch(vector <int> arr, int target) {
    arr = sortArray(arr);
    int left = 0;
    int right = arr.size() - 1;
    int mid = floor((right + left) / 2);
    int loopCounter = 0;

    while (left < right && arr[mid] != target) {
        loopCounter++;
        if (arr[mid] > target) {
            right = mid;
            mid = floor((right + left) / 2);
            
        } else if (arr[mid] < target) {
            left = mid;
            mid = floor((right + left) / 2);
        } else {
            return mid;
        }
        cout << "left: " << left << ", mid: " << mid << ", right: " << right << endl;
    }
    cout << loopCounter << endl;
    return -1;
}


//---------------5----------------------------------------------------------------------------------------------

struct Node {
    int value;
    Node* next;
    Node(int val) : value(val), next(nullptr) {};
};

struct forwardList {
    Node* first;
    Node* last;

    forwardList() : first(nullptr), last(nullptr) {};

    bool isEmpty() {
        return first == nullptr;
    }

    void addNodeBack(int val) {
        Node* p = new Node(val);
        if (isEmpty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }

    void addNodeBackByPointer(Node* p) {
        if (isEmpty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }

    void print() {
        if (isEmpty()) return;
        Node* p = first;
        while (p) {
            cout << p->value << " ";
            p = p->next;
        }
        cout << endl;
    }

    int length() {
        int counter = 0;
        Node* p = first;
        while (p != nullptr) {
            counter++;
            p = p->next;
        }
        return counter;
    }
};

vector <Node*> getOrderedPointers(forwardList l) {
    vector <Node*> pointers;
    Node* p = l.first;
    while (p) {
        pointers.push_back(p);
        p = p->next;
    }
    return pointers;
}

forwardList reverseList(forwardList l) {
    int len = l.length();
    forwardList newList;
    vector <Node*> pointers = getOrderedPointers(l);
    for (int i = 0; i < len; i++) {
        newList.addNodeBackByPointer(pointers[(len - 1 - i)]);
    }
    newList.last->next = nullptr;
    return newList;
}

forwardList createNodeList(vector <int> arr) {
    forwardList l;
    for (int i = 0; i < arr.size(); i++) {
        l.addNodeBack(arr[i]);
    }
    return l;
}




//---------------6----------------------------------------------------------------------------------------------



struct biDirNode {
    int key;
    int value;
    biDirNode* next;
    biDirNode* prev;
    biDirNode(int key, int val) : key(key), value(val), next(nullptr), prev(nullptr) {};
};

struct biDirList {
    biDirNode* head;
    biDirNode* tail;

    biDirList() : head(nullptr), tail(nullptr) {};

    biDirNode* addNodeHead(int key, int val) {
        biDirNode* p = new biDirNode(key, val);
        if (head == nullptr) {
            head = p;
            tail = p;
            return p;
        }
        else {
            p->next = head;
            head->prev = p;
            head = p;
        }
        return p;
    }

    void removeTail() {
        biDirNode* nodeToDelete = tail;
        if (tail -> prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else {
            head = nullptr;
            tail = nullptr;
        }
        
        delete nodeToDelete;
    }

    biDirNode* extractNode(biDirNode* p) {
        if (p == nullptr) return nullptr;
        biDirNode* prev = p->prev;
        biDirNode* next = p->next;
        if (p->prev) {
            prev->next = next;
        }
        else {
            head = next;
        }

        if (p->next) {
            next->prev = prev;
        }
        else {
            tail = prev;
        }

        if (p == head) head = next;
        if (p == tail) tail = prev;

        p->next = nullptr;
        p->prev = nullptr;
        return p;
    }


};

struct LRUCache {
    int csize;
    unordered_map <int, biDirNode*> hashTable;
    biDirList* list;

    LRUCache(int size) : csize(size), hashTable(), list(new biDirList()) {};

    int get(int key) {
        if (hasCacheKey(key)) {
            auto it = hashTable.find(key);
            if (it->second) {
                biDirNode* p = list->extractNode(it->second);
                int result = list->addNodeHead(key, it->second->value)->value;
                delete p;
                return result;
            }
        }
        else return -1;
    }

    void put(int key, int val) {
        if (hasCacheKey(key)) {
            biDirNode* p = list->extractNode(hashTable.find(key)->second);
            if (p->value != val) {
                p->value = val;
            }
            hashTable.erase(key);
            list->addNodeHead(key, val);
            hashTable.insert({ key, list->head });
            delete p;
            return;
        } if (isCacheFull()) {
            int removeKey = list->tail->key;
            list->removeTail();
            hashTable.erase(removeKey);
        }
        list->addNodeHead(key, val);
        hashTable.insert({ key, list->head });
    }

    bool hasCacheKey(int key) {
        auto it = hashTable.find(key);
        if (it != hashTable.end()) {
            return true;
        }
        else {
            return false;
        }
    }

    bool isCacheFull() {
        if (hashTable.size() >= csize) {
            return true;
        }
        else {
            return false;
        }
    }
};

//---------------7----------------------------------------------------------------------------------------------


struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {};
};

vector<vector<int>> breadthFirstSearch(TreeNode* root) {
    if (root == nullptr) return { {} };

    queue<TreeNode*> q;
    q.push(root);
    int lvl = 0;
    vector<vector<int>> arr;

    while (!q.empty()) {
        arr.resize(lvl + 1);
        int lvlSize = q.size();
        for (int i = 0; i < lvlSize; i++) {
            TreeNode* current = q.front();

            q.pop();

            arr[lvl].push_back(current->value);

            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
        lvl++;
    }

    return arr;
}

void printResult(vector<vector<int>> arr) {
    cout << "[";
    for (int i = 0; i < arr.size(); i++) {
        cout << " [ ";

        for (int j = 0; j < arr[i].size(); j++)
            cout << arr[i][j] << ' ';

        cout << "] ";
    }
    cout << "]";
}


int main()
{
    //---------------1-----------------------------------
    /*vector<int> arr1 = {1, 2, 3, 4, 5, 6, 7};
    vector<int> arr2 = {7, 6, 5, 4, 3, 2, 1};
    vector<int> arr3 = {1, 7, 2, 6, 3, 5, 4};
    vector<int> arr4 = {3, 7, 2, 5, 1, 6, 4};
    int target1 = 8;
    vector<int> answer1 = getIndexForSum(arr4, target1);
    if (answer1[0]== 0 && answer1[1] == 0) {
        cout << "Numbers are not founded" << endl;
    } else {
        cout << "Indexes: ";
    for (int index : answer1) cout << index << " ";
    }*/

    //-----------------2---------------------------------
    /*isPalindrome("A man, a plan, a canal: Panama");
    isPalindrome("vevge");
    isPalindrome("vevev");
    isPalindrome("abba");*/
    
    //--------------------3-----------------------------
    /*cout << isValidBracketSequence("([{}])") << endl;
    cout << isValidBracketSequence("([{}]") << endl;
    cout << isValidBracketSequence("([(){}])") << endl;
    cout << isValidBracketSequence("({}])") << endl;*/

    //--------------------4-----------------------------
    /*binarySearch({ 1, 2, 3, 4, 5 ,6, 7, 8 }, 5);
    binarySearch({ 1, 2, 3, 4, 5 ,6, 7, 8 }, 5);
    binarySearch({ 1, 2, 3, 4, 5 ,6, 7, 8 }, 7);
    binarySearch({ 1, 2, 3, 4, 5 ,6, 7, 8 }, 1);*/
    

    //--------------------5------------------------------
    /*forwardList l;
    cout << l.isEmpty() << endl;
    l = createNodeList({ 1, 2, 3, 4, 5, 6, 7 });
    l.print();
    reverseList(l).print();*/


    //--------------------6------------------------------
    /*LRUCache* cache = new LRUCache(4);
    cache->put(2, 5555);
    cache->put(3, 8756);
    cache->put(4, 123);
    cache->put(5, 654);
    biDirList* l = cache->list;
    biDirNode* p = l->head;
    while (p != nullptr) {
        cout << p->value << " - prev: " << p->prev << ", next: " << p->next << endl;
        p = p->next;
    }
    cout << endl;

    cache->put(3, 128);
    cache->put(2, 255);
    cache->put(5, 77777);
    cache->put(4, 987);

    p = l->head;
    while (p != nullptr) {
        cout << p->value << " - prev: " << p->prev << ", next: " << p->next << endl;
       p = p->next;
    }
    cout << endl;*/

    //--------------------7------------------------------

    /*TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->left->right = new TreeNode(7);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(6);
    root->right->left->left = new TreeNode(8);

    vector<vector<int>> result = breadthFirstSearch(root);
    printResult(result);*/


}

