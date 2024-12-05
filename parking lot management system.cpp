#include <iostream>
#include <string>
using namespace std;

#define MAXSIZE 3	//The maximum number of cars that can stay in the parking lot
const float price = 0.05;	//Parking fee per minute
int i;	//The position of the car on the service road

//Time
typedef struct time {
	int h, m;	//Hour Minute
}Time;

//Car
typedef struct car {
	Time t1, t2;	//Arriving time and departure time
	string num;	//car number
	int p1, p2;	//The position of the car in the parking lot
}Car;

//parking lot
typedef struct {
	Car data[MAXSIZE];
	int top;
}SeqList;

//service road
typedef struct qnode {
	Car data;
	struct qnode* next;
}QNode;
typedef struct lqueue {
	QNode* front, * rear;
}LQueue;

//initializing parking lot
SeqList* Init_SeqList()
{
	SeqList* s;
	s = new SeqList;
	s->top = -1;
	return s;
}

//initializing service road
LQueue* Init_LQueue()
{
	LQueue* q;
	QNode* p;
	q = new lqueue;
	p = new qnode;
	p->next = NULL;
	q->front = p;
	q->rear = p;
	return q;
}

void Push_SeqList(SeqList* s, Car x)
{
	s->top++;
	s->data[s->top] = x;
}

Car Pop_SeqList(SeqList* s)
{
	Car x = s->data[s->top];
	s->top--;
	return x;
}

void In_LQueue(LQueue* q, Car x)
{
	QNode* p;
	p = new qnode;
	p->data = x;
	p->next = NULL;
	q->rear->next = p;
	q->rear = p;
}

Car Out_LQueue(LQueue* q)
{
	Car x;
	QNode* p;
	p = q->front->next;
	q->front->next = p->next;
	x = p->data;
	delete p;
	if (q->front->next == NULL)
	{
		q->front->next = NULL;
		q->rear = q->front;
	}
	return x;
}

void Car_In(SeqList* p, LQueue* q)
{
	Car c;
	cout << "Please input car number and arriving time(hour,minute)£º";
	cin >> c.num >> c.t1.h >> c.t1.m;
	if (p->top == MAXSIZE - 1)
	{
		c.p2 = ++i;
		cout << "The parking lot is full. please enter the service road and wait, your position is£º00" << c.p2 << endl;
		In_LQueue(q, c);
	}
	else {
		c.p1 = p->top + 2;
		cout << "Enter parking lot£¬position is£º00" << c.p1 << endl;
		Push_SeqList(p, c);
	}
}

Car* Car_if(SeqList* p, Car c)
{
	int t;
	SeqList* temp = Init_SeqList();
	static Car x;
	while (c.num != p->data[p->top].num && p->top != -1)
	{
		x = Pop_SeqList(p);
		Push_SeqList(temp, x);
	}
	t = p->top;
	while (temp->top != -1)
	{
		x = Pop_SeqList(temp);
		Push_SeqList(p, x);
	}
	if (t == -1) return NULL;
	else return &x;
}

void Car_Out(SeqList* p, LQueue* q)
{
	Car c, x, first;
	int flag = 0;
	if (p->top == -1)
	{
		cout << "There are no cars in the parking lot~" << endl;
		return;
	}
	if (p->top == MAXSIZE - 1)
	{
		if (q->front == q->rear) return;
		else {
			first = Out_LQueue(q);
			flag = 1;
		}
	}
	SeqList* temp = Init_SeqList();
	cout << "Please input car number and departure time(hour,minute): º";
	cin >> c.num >> c.t2.h >> c.t2.m;
	if (!Car_if(p, c))
	{
		cout << "There is no such vehicle in the parking lot~" << endl;
		return;
	}
	while (c.num != p->data[p->top].num)
	{
		x = Pop_SeqList(p);
		cout << "car number is" << x.num << "gives the right of way·" << endl;
		Push_SeqList(temp, x);
	}
	x = Pop_SeqList(p);
	x.t2.h = c.t2.h, x.t2.m = c.t2.m;
	float t = (x.t2.h - x.t1.h) * 60 + x.t2.m - x.t1.m;
	float t1, t2;
	if (x.t2.m >= x.t1.m)
	{
		t2 = x.t2.m - x.t1.m;
		t1 = x.t2.h - x.t1.h;
	}
	else {
		t2 = x.t2.m + 60 - x.t1.m;
		t1 = x.t2.h - x.t1.h - 1;
	}
	cout << "car number is" << x.num << "depart" << endl;
	while (temp->top != -1)
	{
		x = Pop_SeqList(temp);
		x.p1 = p->top + 2;
		cout << "car number is" << x.num << "enter" << endl;
		Push_SeqList(p, x);
	}
	if (flag)
	{
		first.p1 = p->top + 2;
		Push_SeqList(p, first);
		cout << "car number is" << first.num << "enter" << endl;
	}
	cout << "parking time£º" << t1 << "hour" << t2 << "minute" << "    fee£º" << t * price << "dollars\n" << "Welcome to come again~" << endl;
}

void Display(SeqList* p)
{
	Car x;
	SeqList* temp = Init_SeqList();
	if (p->top == -1)
	{
		cout << "There are no cars in the parking lot" << endl;
		return;
	}
	else
	{
		while (p->top != -1)
		{
			x = Pop_SeqList(p);
			Push_SeqList(temp, x);
		}
		cout << "The information of cars in the parking lot:" << endl;
		while (temp->top != -1)
		{
			x = Pop_SeqList(temp);
			cout << "parking position£º00" << x.p1 << "  car number:" << x.num << "  parking time£º" << x.t1.h << "hour" << x.t1.m << "minute" << endl;
			Push_SeqList(p, x);
		}
	}
}

int main()
{
	int flag = 1;
	SeqList* p = Init_SeqList();
	LQueue* q = Init_LQueue();
	while (flag)
	{
		cout << "=========================Welcome to our parking lot===========================" << endl;
		puts("");
		cout << "                   The maximum parking number is" << MAXSIZE << "cars" << endl;
		puts("");
		cout << "==================================================================" << endl;
		int i;
		cout << "**********1.car arriving  2.car departure  3.View parking lot  4.exit system**********" << endl;
		scanf("%d", &i);
		while(getchar() != '\n');
		switch (i)
		{
		case 1:Car_In(p, q); break;
		case 2:Car_Out(p, q); break;
		case 3:Display(p); break;
		case 4:cout << "Have a good day" << endl; flag = 0; break;
		default:cout << "oops,input error,please input integral number range from 1 to 4, try again" << endl;break;
		}
	}
	system("pause");
	return 0;
}
