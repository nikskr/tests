#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <ranges>

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

//---------------8----------------------------------------------------------------------------------------------

bool hasSymbol(string str, unsigned char ch) {
    if (str.find(ch) != string::npos) {
        return true;
    }
    return false;
}

int countMaxUniqueSymbols(string str) {
    string substr = "";
    int counter = 0;
    for (int i = 0; i < str.length(); i++) {
        if (hasSymbol(substr, str[i])) {
            substr.erase(0, substr.find(str[i]) + 1);
            substr += str[i];
        }
        else {
            substr += str[i];
            if (substr.length() > counter) {
                counter++;
            }
        }
    }
    return counter;
}

//---------------9----------------------------------------------------------------------------------------------

int coins(vector<int> coinArr, int amount) {

    int* dp = new int[amount + 1];
    dp[0] = 0;
    int inf = 9999999;

    for (int i = 1; i < amount + 1; i++) {
        dp[i] = inf;
    }

    for (int i = 1; i < amount + 1; i++) {
        for (int coin = 0; coin < coinArr.size(); coin++) {
            if (coinArr[coin] <= i) {
                dp[i] = min(dp[i], dp[i - coinArr[coin]] + 1);
            }
        }
    }

    int result = dp[amount];

    delete dp;

    if (result == inf) return -1;

    return result;
}

//---------------10----------------------------------------------------------------------------------------------

vector<vector<char>> createBinaryMatrix(int n) {
    vector<vector<char>> matrix(n);
    srand(time(NULL));


    for (int i = 0; i < n; i++) {
        matrix[i].reserve(n);
        for (int j = 0; j < n; j++) {
            (rand() % 2 == 1) ? matrix[i].push_back('1') : matrix[i].push_back('0');
        }
    }
    return matrix;
}

void printMatrix(vector<vector<char>> matrix) {
    cout << '[' << endl;

    for (int i = 0; i < matrix.size(); i++) {
        cout << " [ ";
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << ' ';
        }
        cout << ']' << endl;
    }

    cout << ']' << endl;
}

void clearIslandFields(vector<vector<char>>& matrix, int i, int j) {
    if (i > matrix.size() - 1 || i < 0 || j > matrix[i].size() - 1 || j < 0 || matrix[i][j] != '1') {
        return;
    }

    matrix[i][j] = '0';

    clearIslandFields(matrix, i + 1, j);
    clearIslandFields(matrix, i - 1, j);
    clearIslandFields(matrix, i, j + 1);
    clearIslandFields(matrix, i, j - 1);
}

int countIslands(vector<vector<char>> matrix) {
    int counter = 0;

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == '1') {
                counter++;
                clearIslandFields(matrix, i, j);
            }
        }
    }

    return counter;
}

//---------------11----------------------------------------------------------------------------------------------

void printArray(vector<int> arr) {
    cout << "[ ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << "]" << endl;
}

float medianOfSortedArrays(vector<int> nums1, vector<int> nums2) {
    if (nums2.size() < nums1.size()) {
        vector<int> h = nums1;
        nums1 = nums2;
        nums2 = h;
    }

    int negInf = -9999999;
    int posInf = 9999999;

    int len1 = nums1.size();
    int len2 = nums2.size();
    int totalLen = len1 + len2;
    int halfTotalLen = ceil(totalLen / 2);

    int nums1LeftPtr = 0;
    int nums1RightPtr = len1 - 1;

    while (true) {
        int nums1MidPtr = ceil((nums1LeftPtr + nums1RightPtr) / 2);
        int nums2MidPtr = halfTotalLen - nums1MidPtr - 2;
        int nums1MidLeftVal, nums1MidRightVal, nums2MidLeftVal, nums2MidRightVal;
        if (nums1MidPtr >= 0) {
            nums1MidLeftVal = nums1[nums1MidPtr];
        }
        else {
            nums1MidLeftVal = negInf;
        }

        if (nums1MidPtr + 1 < len1) {
            nums1MidRightVal = nums1[nums1MidPtr + 1];
        }
        else {
            nums1MidRightVal = posInf;
        }

        if (nums2MidPtr >= 0) {
            nums2MidLeftVal = nums2[nums2MidPtr];
        }
        else {
            nums2MidLeftVal = negInf;
        }

        if (nums2MidPtr + 1 < len2) {
            nums2MidRightVal = nums2[nums2MidPtr + 1];
        }
        else {
            nums2MidRightVal = posInf;
        }
        
        if (nums1MidLeftVal <= nums2MidRightVal && nums2MidLeftVal <= nums1MidRightVal) {
            if (totalLen % 2 == 0) {
                return (max(nums1MidLeftVal, nums2MidLeftVal) + min(nums1MidRightVal, nums2MidRightVal)) / 2.;
            }
            else {
                return min(nums1MidRightVal, nums2MidRightVal);
            }
        }
        else {
            if (nums1MidLeftVal > nums2MidLeftVal) {
                nums1RightPtr = nums1MidPtr - 1;
            }
            else {
                nums1LeftPtr = nums1MidPtr + 1;
            }
        }

    }
}

//---------------12----------------------------------------------------------------------------------------------

struct Trie {
    char value;
    bool key;
    map <char, Trie*> childs;

    Trie(char val) : value(val), key(false), childs({}) {};

    bool hasChild(char ch) {
        if (this->childs.find(ch) != this->childs.end()) {
            return true;
        }
        return false;
    }

    void addChild(char ch) {
        this->childs[ch] = new Trie(ch);
    }

    Trie* getChild(char ch) {
        return this->childs.at(ch);
    }

    void setKey(bool isValid) {
        this->key = isValid;
    }

    void insert(string str) {
        Trie* node = this;
        for (int i = 0; i < str.length(); i++) {
            char ch = str[i];
            if (!node->hasChild(ch)) {
                node->addChild(ch);
            }
            node = node->getChild(ch);
        }
        node->setKey(true);
    }

    bool search(string str) {
        Trie* node = this;
        for (int i = 0; i < str.length(); i++) {
            char ch = str[i];
            if (!node->hasChild(ch)) {
                return false;
            }
            node = node->getChild(ch);
        }
        return node->key;
    }

    bool startsWith(string str) {
        if (str.length() == 0) {
            return true;
        }

        Trie* node = this;
        for (int i = 0; i < str.length(); i++) {
            char ch = str[i];
            if (!node->hasChild(ch)) {
                return false;
            }
            node = node->getChild(ch);
        }
        return true;
    }
};

//---------------13----------------------------------------------------------------------------------------------

bool isOneLetterDiffer(string word1, string word2) {
    if (word1.length() != word2.length()) {
        return false;
    }

    int difCounter = 0;

    for (int i = 0; i < word1.length(); i++) {
        if (word1[i] != word2[i]) {
            difCounter++;
        }
        if (difCounter > 1) {
            return false;
        }
    }
    if (difCounter == 1) {
        return true;
    }
    else {
        return false;
    }
}

struct WordGraph {
    string word;
    map<string, WordGraph*> closeWords;

    WordGraph(string w) : word(w), closeWords({}) {};
};

map<string, WordGraph*> createGraph(vector<string> wordList) {
    map<string, WordGraph*> wordNodeMap;

    for (int i = 0; i < wordList.size(); i++) {
        WordGraph* node = new WordGraph(wordList[i]);
        wordNodeMap[wordList[i]] = node;
    }

    for (const auto& it : wordNodeMap) {
        WordGraph* node = it.second;
        for (int i = 0; i < wordList.size(); i++) {
            if (it.first == wordList[i]) {
                continue;
            }
            if (isOneLetterDiffer(it.first, wordList[i])) {
                node->closeWords[wordList[i]] = wordNodeMap.at(wordList[i]);
            }
        }
    }
    return wordNodeMap;
}

void addBeginWord(vector<string>& wordList, string beginWord) {
    if (count(wordList.begin(), wordList.end(), beginWord) == 0) {
        wordList.push_back(beginWord);
    }
}

int countSteps(string beginWord, string endWord, vector<string> wordList) {
    addBeginWord(wordList, beginWord);
    map<string, WordGraph*> wordMap = createGraph(wordList);
    queue<WordGraph*> q;
    unordered_set<string> visited;

    q.push(wordMap.at(beginWord));
    visited.insert(beginWord);
    int len = 1;

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            WordGraph* current = q.front();
            q.pop();
            if (current->word == endWord) {
                for (auto& pair : wordMap) {
                    delete pair.second;
                }
                return len;
            }
            for (const auto& pair : current->closeWords) {
                if (visited.find(pair.first) == visited.end()) {
                    visited.insert(pair.first);
                    q.push(pair.second);
                }
            }
        }
        len++;
    }

    for (auto& pair : wordMap) {
        delete pair.second;
    }

    return 0;
}


//vector<vector<int>> breadthFirstSearch(TreeNode* root) {
//    if (root == nullptr) return { {} };
//
//    queue<TreeNode*> q;
//    q.push(root);
//    int lvl = 0;
//    vector<vector<int>> arr;
//
//    while (!q.empty()) {
//        arr.resize(lvl + 1);
//        int lvlSize = q.size();
//        for (int i = 0; i < lvlSize; i++) {
//            TreeNode* current = q.front();
//
//            q.pop();
//
//            arr[lvl].push_back(current->value);
//
//            if (current->left != nullptr) q.push(current->left);
//            if (current->right != nullptr) q.push(current->right);
//        }
//        lvl++;
//    }
//
//    return arr;
//}


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

    //--------------------8------------------------------

    /*cout << countMaxUniqueSymbols("abcde") << endl;
    cout << countMaxUniqueSymbols("aaaaa") << endl;
    cout << countMaxUniqueSymbols("AaBbC") << endl;
    cout << countMaxUniqueSymbols("a b !") << endl;
    cout << countMaxUniqueSymbols("") << endl;*/

    //--------------------9------------------------------
    
    /*cout << coins({ 1, 3, 4 }, 10) << endl;
    cout << coins({ 1, 3, 4 }, 6) << endl;
    cout << coins({ 1, 3, 4 }, 7) << endl;*/

    //--------------------10------------------------------

    //vector<vector<char>> matrix = createBinaryMatrix(7);
    //printMatrix(matrix);
    //int islandsAmount = countIslands(matrix);
    //cout << islandsAmount << endl;

    //matrix = createBinaryMatrix(7);
    //printMatrix(matrix);
    //islandsAmount = countIslands(matrix);
    //cout << islandsAmount << endl;

    //matrix = createBinaryMatrix(7);
    //printMatrix(matrix);
    //islandsAmount = countIslands(matrix);
    //cout << islandsAmount << endl;

    //--------------------11------------------------------

    /*vector<int> arr1 = { 1, 2 };
    vector<int> arr2 = { 5, 10};
    printArray(arr1);
    printArray(arr2);
    cout << "Median: " << medianOfSortedArrays(arr1, arr2) << endl;*/

    //--------------------12------------------------------

    /*Trie* trie = new Trie(' ');
    trie->insert("apple");
    cout << "Search \"apple\": " << trie->search("apple") << endl;
    cout << "Search \"app\": " << trie->search("app") << endl;
    cout << "Search prefix \"app\": " << trie->startsWith("app") << endl;
    trie->insert("app");
    cout << "Search \"app\": " << trie->search("app") << endl;*/

    //--------------------13------------------------------

    //string beginWord = "hit";
    //string endWord = "cog";
    //vector<string> wordList = { "hot", "dot", "dog", "lot", "log", "cog" };
    //cout << countSteps(beginWord, endWord, wordList) << endl;

}

