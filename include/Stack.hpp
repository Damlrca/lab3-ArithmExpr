class Stack {
	int p[10];
	int top;
public:
	Stack() : top(-1) {}
	bool is_empty() { return top == -1; }
	bool is_full() { return top >= 9; }
	int pop() { return p[top--]; }
	void push(int x) { p[++top] = x; }
};