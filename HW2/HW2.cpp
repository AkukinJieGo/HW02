#include <iostream>
#include <stack>
#include <string>
using namespace std;

// 定義運算符的優先級
int op_first(char op) {
    if (op == '+' || op == '-') {
        return 1;  // 加法和減法的優先級較低
    }
    else if (op == '*' || op == '/') {
        return 2;  // 乘法和除法的優先級較高
    }
    else {
        return 0;  // 非運算符返回0
    }
}

// 判斷是否是運算符
bool op_true(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// 中序轉後續表示法的函式
string input_fix(string input) {
    stack<char> st;
    string output;

	int n = input.length();  // 輸入表達式的長度

    for (int i = 0; i < n; i++) {
        // 如果輸入為數字，存入輸出
        if (input[i] != '(' && input[i]!= ')' && !op_true(input[i])) {
            output += input[i];
        }
        // 如果輸入為左括號，推入堆疊
        else if (input[i] == '(') {
            st.push(input[i]);
        }
        // 如果輸入為右括號，彈出堆疊直到遇到左括號
        else if (input[i] == ')') {
            // 如果堆疊不為空且堆疊頂部不為左括號
            while (!st.empty() && st.top() != '(') {
				output += st.top();  // 將運算符存入輸出
				st.pop();  // 彈出堆疊
            }
            st.pop();  // 移除左括號
        }
        // 如果輸入為運算符，處理優先級
        else if (op_true(input[i])) {
			// 如果堆疊不為空且堆疊頂部的運算符優先級大於等於輸入的運算符
            while (!st.empty() && op_first(st.top()) >= op_first(input[i])) {
				output += st.top();  // 將優先的運算符存入輸出
				st.pop();  // 彈出堆疊
            }
			st.push(input[i]);  // 將輸入的運算符推入堆疊
        }
    }

    // 將堆疊中剩餘的運算符彈出
    while (!st.empty()) {
        output += st.top();
        st.pop();
    }

	return output;  // 返回後序表達式
}

int main() {
    string input;
    cout << "輸入中序表達式: ";
	cin >> input;  // 輸入中序表達式

    string output = input_fix(input);  // 進入轉後序的函式

	cout << "後序表達式為: " << output << endl;  // 輸出後序表達式

    return 0;
}