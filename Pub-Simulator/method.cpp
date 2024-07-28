#include <iostream>
#include "header.h"
using namespace std;

Customer::Customer() { // �մ� �� ����: �ִ� 6��
	person = rand() / 6 + 1;
	ordering();
}
void Customer::ordering() {
	int price = 0;
	cout << "********************" << endl;
	price += beer_order(this->person);
	price += snack_order(this->person);
	sales += price;
	cout << "�� " << price << "��" << endl;
	cout << "********************" << endl;
}
void Job::set_name(string n) { name = n; }
string Job::get_name() { return name; }
void Job::set_charge(int c) { charge = c; }
int Job::get_charge() { return charge; }
void Job::set_type(int t) { type = t; }
int Job::get_type() { return type; }
void Job::set_duration(int d) { duration = d; }
int Job::get_duration() { return duration; }
int beer_order(int beer_amount) { // ���� �ֹ�
	int charge = 0;
	int order_beer, order_soju; int a = beer_amount; // ���� �������ŭ
	if (a == 1) {
		int random = rand() % 3;
		switch (random) {
		case 0: { cout << "���� 1��" << endl; return 3500; }
		case 1: { cout << "���� 1��" << endl; return 4000; }
		case 2: { cout << "���̺� 1��" << endl; return 5000; }
		}
	}
	order_beer = rand() % a; a -= order_beer;
	charge += order_beer * 3500;
	cout << "���� " << order_beer << "��" << endl;
	if (a == 0) return charge;

	order_soju = rand() % a; a -= order_soju;
	charge += order_soju * 4000;
	cout << "���� " << order_soju << "��" << endl;
	if (a == 0) return charge;

	cout << "���̺� " << a << "��" << endl;
	charge += a * 5000;
	return charge;
}
int snack_order(int snack_amount) { // ���� �ֹ�
	int charge = 0; int i = 0;
	int a = rand() % (snack_amount + 1); // ���ִ� �ִ� �������ŭ
	int menu_id;
	Job temp;
	while(i < a) {
		menu_id = rand() % 11;
		switch (menu_id) {
		case 0: { temp.set_name("����"); temp.set_charge(3500); temp.set_type(1); temp.set_duration(1); }
		case 1: { temp.set_name("����Ƣ��"); temp.set_charge(5500); temp.set_type(1); temp.set_duration(4); }
		case 2: { temp.set_name("��¡��Ƣ��"); temp.set_charge(6000); temp.set_type(1); temp.set_duration(3); }
		case 3: { temp.set_name("����Ƣ��"); temp.set_charge(6000); temp.set_type(1); temp.set_duration(5); }
		case 4: { temp.set_name("ġŲ"); temp.set_charge(8000); temp.set_type(1); temp.set_duration(8); }
		case 5: { temp.set_name("������"); temp.set_charge(6000); temp.set_type(2); temp.set_duration(4); }
		case 6: { temp.set_name("������"); temp.set_charge(9000); temp.set_type(2); temp.set_duration(8); }
		case 7: { temp.set_name("«��"); temp.set_charge(12000); temp.set_type(2); temp.set_duration(8); }
		case 8: { temp.set_name("������¡��"); temp.set_charge(7000); temp.set_type(3); temp.set_duration(3); }
		case 9: { temp.set_name("����"); temp.set_charge(8000); temp.set_type(3); temp.set_duration(5); }
		case 10: { temp.set_name("����"); temp.set_charge(8000); temp.set_type(3); temp.set_duration(1); }
		}
		if (menu_id < 5) fryer_queue.push(temp); // Ƣ��⿡ temp�� Ǫ��
		else grill_queue.push(temp); // ���ʿ� temp�� Ǫ��
		charge += temp.get_charge();
		cout << temp.get_name() << "�ֹ�";
		++i;
	}
	return charge;
}
void process_next_job_fryer() {
	Job p;
	p = fryer_queue.front();
	fryer_queue.pop();

	if (!is_fryer1_used()) {
		remaining_time_fryer1 = p.get_duration() - 1;
		cout << "Ƣ��� 1���� " << p.get_name() << " ���� ����" << endl;
	}
	else {
		remaining_time_fryer2 = p.get_duration() - 1;
		cout << "Ƣ��� 2���� " << p.get_name() << " ���� ����" << endl;
	}
}
void process_next_job_grill() {
	Job p;
	p = grill_queue.front();
	grill_queue.pop();
	if (!is_grill_used()) {
		remaining_time_grill = p.get_duration() - 1;
		cout << "���ʿ� " << p.get_name() << " ���� ����" << endl;
		if (p.get_type() == 3) is_grilling = true;
	}
}
bool is_fryer1_used() {
	if (remaining_time_fryer1 > 0)
		return true;
	else
		return false;
}
bool is_fryer2_used() {
	if (remaining_time_fryer2 > 0)
		return true;
	else
		return false;
}
bool is_grill_used() {
	if (remaining_time_grill > 0)
		return true;
	else
		return false;
}