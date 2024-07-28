#include <iostream>
#include <queue>
#include <string>
#include <ctime>
#include <cstdlib>
#include "header.h"
using namespace std;

int main() {
	srand((unsigned)time(NULL));
	while (current_time < MAX_TIME) {
		cout << "\n----- ���� �ð�: " << current_time / 60 + 6 << "�� " << current_time % 60 << "�� -----\n" << endl;

		// �մ��� ���Դ��� Ȯ��
		if (is_customer_entered()) ordering();

		// �����ⱸ�� ��������� Ȯ�� �� ���� ���� ����
		if (!is_fryer1_used()) {
			if (!is_grilling && !fryer_queue.empty()) {
				process_next_job_fryer();
			}
		}
		if (!is_fryer2_used()) {
			if (!is_grilling && !fryer_queue.empty()) {
				process_next_job_fryer();
			}
		}
		if (is_fryer1_used() && remaining_time_fryer1 > 0) {
			cout << "< Ƣ��� 1 : " << fryer1_cooking << " ���� �� >" << endl;
			--remaining_time_fryer1;
			if (remaining_time_fryer1 == 0)
				cout << fryer1_cooking << " ���� �Ϸ�" << endl;
		}
		if (is_fryer2_used() && remaining_time_fryer2 > 0) {
			cout << "< Ƣ��� 2 : " << fryer2_cooking << " ���� �� >" << endl;
			--remaining_time_fryer2;
			if (remaining_time_fryer2 == 0)
				cout << fryer2_cooking << " ���� �Ϸ�" << endl;
		}
		if (!is_grill_used() && !grill_queue.empty()) {
			process_next_job_grill();
		}
		else {
			if (remaining_time_grill > 0) {
				cout << "< ���� : " << grill_cooking << " ���� �� >" << endl;
				--remaining_time_grill;
				if (remaining_time_grill == 0) {
					cout << grill_cooking << " ���� �Ϸ�" << endl;
					if (is_grilling)
						is_grilling = false;
				}
			}
		}
		++current_time;
	}
	cout << "----- 12�� : ���� ���� -----" << endl;
	cout << "�Ѽ��� : " << s.sales << "��" << endl;
	cout << "\n�޴��� �Ǹŷ�" << endl;
	cout << "- �ַ� -" << endl << "���� : " << s.beer << "�� / ���� : " << s.soju << "�� / ���̺� : " << s.highball << "��" << endl;
	cout << "- Ƣ�� -" << endl << "Ƣ������ : " << s.jupo << "�� / ����Ƣ�� : " << s.french_fry << "�� / ��¡��Ƣ�� : " << s.fryed_squid <<
		"�� / ����Ƣ�� : " << s.shrimp << "�� / ġŲ : " << s.chicken << "��" << endl;
	cout << "- ���� -" << endl << "������ : " << s.tteok << "�� / ������ : " << s.oden << "�� / «���� : " << s.jjam << "��" << endl;
	cout << "- ���� -" << endl << "������¡�� : " << s.squid << "�� / ���� : " << s.pollack << "�� / ���� : " << s.jerky << "��\n" << endl;
}

// method
bool is_customer_entered() {
	if (random() < CUSTOMER_PROB) return true;
	else return false;
}
void ordering() {
	int price = 0;
	int person = rand() % 6 + 1;
	cout << "********************" << endl;
	cout << "�մ� " << person << "�� ����" << endl;
	cout << "----- �ֹ� ���� -----" << endl;
	price += beer_order(person);
	price += snack_order(person);
	s.sales += price;
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
		case 0: { cout << "���� 1��" << endl; ++s.beer; return 3500; }
		case 1: { cout << "���� 1��" << endl; ++s.soju; return 4000; }
		case 2: { cout << "���̺� 1��" << endl; ++s.highball; return 5000; }
		}
	}
	order_beer = rand() % a; a -= order_beer;
	charge += order_beer * 3500;
	if (order_beer != 0) cout << "���� " << order_beer << "��" << endl;
	s.beer += order_beer;
	if (a == 0) return charge;

	order_soju = rand() % a; a -= order_soju;
	charge += order_soju * 4000;
	if (order_soju != 0) cout << "���� " << order_soju << "��" << endl;
	s.soju += order_soju;
	if (a == 0) return charge;

	cout << "���̺� " << a << "��" << endl;
	charge += a * 5000;
	s.highball += a;
	return charge;
}
int snack_order(int snack_amount) { // ���� �ֹ�
	int charge = 0; int i = 0;
	int a = rand() % (snack_amount + 1); // ���ִ� �ִ� �������ŭ
	int menu_id;
	Job temp;
	while (i < a) {
		menu_id = rand() % 11;

		switch (menu_id) {
		case 0: { temp.set_name("Ƣ������"); temp.set_charge(3500); temp.set_type(1); temp.set_duration(1); ++s.jupo; break; }
		case 1: { temp.set_name("����Ƣ��"); temp.set_charge(5500); temp.set_type(1); temp.set_duration(4); ++s.french_fry; break; }
		case 2: { temp.set_name("��¡��Ƣ��"); temp.set_charge(6000); temp.set_type(1); temp.set_duration(3); ++s.fryed_squid; break; }
		case 3: { temp.set_name("����Ƣ��"); temp.set_charge(6000); temp.set_type(1); temp.set_duration(5); ++s.shrimp; break; }
		case 4: { temp.set_name("ġŲ"); temp.set_charge(8000); temp.set_type(1); temp.set_duration(8); ++s.chicken; break; }
		case 5: { temp.set_name("������"); temp.set_charge(6000); temp.set_type(2); temp.set_duration(4); ++s.tteok; break; }
		case 6: { temp.set_name("������"); temp.set_charge(9000); temp.set_type(2); temp.set_duration(8); ++s.oden; break; }
		case 7: { temp.set_name("«����"); temp.set_charge(12000); temp.set_type(2); temp.set_duration(8); ++s.jjam; break; }
		case 8: { temp.set_name("������¡��"); temp.set_charge(7000); temp.set_type(3); temp.set_duration(3); ++s.squid; break; }
		case 9: { temp.set_name("����"); temp.set_charge(8000); temp.set_type(3); temp.set_duration(5); ++s.pollack; break; }
		case 10: { temp.set_name("����"); temp.set_charge(8000); temp.set_type(3); temp.set_duration(1); ++s.jerky; break; }
		}
		if (menu_id < 5) fryer_queue.push(temp); // Ƣ��⿡ temp�� Ǫ��
		else grill_queue.push(temp); // ���ʿ� temp�� Ǫ��
		charge += temp.get_charge();
		cout << temp.get_name() << " �ֹ�" << endl;
		++i;
	}
	return charge;
}
void process_next_job_fryer() {
	Job p;
	p = fryer_queue.front();
	fryer_queue.pop();

	if (!is_fryer1_used()) {
		fryer1_cooking = p.get_name();
		remaining_time_fryer1 = p.get_duration();
		cout << "Ƣ��� 1���� " << fryer1_cooking << " ���� ����" << endl;
	}
	else {
		fryer2_cooking = p.get_name();
		remaining_time_fryer2 = p.get_duration();
		cout << "Ƣ��� 2���� " << fryer2_cooking << " ���� ����" << endl;
	}
}
void process_next_job_grill() {
	Job p;
	p = grill_queue.front();
	grill_queue.pop();
	grill_cooking = p.get_name();
	remaining_time_grill = p.get_duration();

	cout << "���ʿ� " << grill_cooking << " ���� ����" << endl;
	if (p.get_type() == 3) is_grilling = true;
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
double random() {
	return rand() / (double)RAND_MAX;
}