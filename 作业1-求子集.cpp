
#include <iostream>
#include<fstream>
#include <vector>

using namespace std;

// �ݹ麯�����������Ӽ�
void generateSubsets(vector<char>& set, vector<char>& current, int index) {
    if (index == set.size()) {
        // �����ǰ�Ӽ�
        for (int i = 0; i < current.size(); ++i) {
            if (i > 0) cout << " ";
            cout << current[i];
        }
        cout << endl;
        return;
    }

    // ѡ�������ǰԪ��
    current.push_back(set[index]);
    generateSubsets(set, current, index + 1);

    // ѡ�񲻰�����ǰԪ��
    current.pop_back();
    generateSubsets(set, current, index + 1);
}

int main() {
    ifstream in("input.txt");
    int n;
    in>> n;

    if (n < 1 || n > 26) {
        cout << "WRONG" << endl;
        return 0;
    }

    vector<char> set;
    for (int i = 0; i < n; ++i) {
        set.push_back('a' + i);
    }

    vector<char> current;
    generateSubsets(set, current, 0);

    return 0;
}
