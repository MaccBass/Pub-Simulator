#include <iostream>
#include "header.h"
using namespace std;

Customer::Customer() { // ¼Õ´Ô ¼ö ¼³Á¤: ÃÖ´ë 6¸í
	person = rand() / 6 + 1;
	ordering();
}
void Customer::ordering() {
	int price = 0;
	cout << "********************" << endl;
	price += beer_order(this->person);
	price += snack_order(this->person);
	sales += price;
	cout << "ÃÑ " << price << "¿ø" << endl;
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
int beer_order(int beer_amount) { // ¸ÆÁÖ ÁÖ¹®
	int charge = 0;
	int order_beer, order_soju; int a = beer_amount; // ¼úÀº »ç¶÷¼ö¸¸Å­
	if (a == 1) {
		int random = rand() % 3;
		switch (random) {
		case 0: { cout << "¸ÆÁÖ 1ÀÜ" << endl; return 3500; }
		case 1: { cout << "¼ÒÁÖ 1º´" << endl; return 4000; }
		case 2: { cout << "ÇÏÀÌº¼ 1ÀÜ" << endl; return 5000; }
		}
	}
	order_beer = rand() % a; a -= order_beer;
	charge += order_beer * 3500;
	cout << "¸ÆÁÖ " << order_beer << "ÀÜ" << endl;
	if (a == 0) return charge;

	order_soju = rand() % a; a -= order_soju;
	charge += order_soju * 4000;
	cout << "¼ÒÁÖ " << order_soju << "º´" << endl;
	if (a == 0) return charge;

	cout << "ÇÏÀÌº¼ " << a << "ÀÜ" << endl;
	charge += a * 5000;
	return charge;
}
int snack_order(int snack_amount) { // ¾ÈÁÖ ÁÖ¹®
	int charge = 0; int i = 0;
	int a = rand() % (snack_amount + 1); // ¾ÈÁÖ´Â ÃÖ´ë »ç¶÷¼ö¸¸Å­
	int menu_id;
	Job temp;
	while(i < a) {
		menu_id = rand() % 11;
		switch (menu_id) {
		case 0: { temp.set_name("ÁãÆ÷"); temp.set_charge(3500); temp.set_type(1); temp.set_duration(1); }
		case 1: { temp.set_name("°¨ÀÚÆ¢±è"); temp.set_charge(5500); temp.set_type(1); temp.set_duration(4); }
		case 2: { temp.set_name("¿ÀÂ¡¾îÆ¢±è"); temp.set_charge(6000); temp.set_type(1); temp.set_duration(3); }
		case 3: { temp.set_name("»õ¿ìÆ¢±è"); temp.set_charge(6000); temp.set_type(1); temp.set_duration(5); }
		case 4: { temp.set_name("Ä¡Å²"); temp.set_charge(8000); temp.set_type(1); temp.set_duration(8); }
		case 5: { temp.set_name("¶±ººÀÌ"); temp.set_charge(6000); temp.set_type(2); temp.set_duration(4); }
		case 6: { temp.set_name("¿Àµ­ÅÁ"); temp.set_charge(9000); temp.set_type(2); temp.set_duration(8); }
		case 7: { temp.set_name("Â«»Í"); temp.set_charge(12000); temp.set_type(2); temp.set_duration(8); }
		case 8: { temp.set_name("¸¶¸¥¿ÀÂ¡¾î"); temp.set_charge(7000); temp.set_type(3); temp.set_duration(3); }
		case 9: { temp.set_name("¸ÔÅÂ"); temp.set_charge(8000); temp.set_type(3); temp.set_duration(5); }
		case 10: { temp.set_name("À°Æ÷"); temp.set_charge(8000); temp.set_type(3); temp.set_duration(1); }
		}
		if (menu_id < 5) fryer_queue.push(temp); // Æ¢±è±â¿¡ temp¸¦ Çª½¬
		else grill_queue.push(temp); // ¹ö³Ê¿¡ temp¸¦ Çª½¬
		charge += temp.get_charge();
		cout << temp.get_name() << "ÁÖ¹®";
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
		cout << "Æ¢±è±â 1¹ø¿¡ " << p.get_name() << " Á¶¸® ½ÃÀÛ" << endl;
	}
	else {
		remaining_time_fryer2 = p.get_duration() - 1;
		cout << "Æ¢±è±â 2¹ø¿¡ " << p.get_name() << " Á¶¸® ½ÃÀÛ" << endl;
	}
}
void process_next_job_grill() {
	Job p;
	p = grill_queue.front();
	grill_queue.pop();
	if (!is_grill_used()) {
		remaining_time_grill = p.get_duration() - 1;
		cout << "¹ö³Ê¿¡ " << p.get_name() << " Á¶¸® ½ÃÀÛ" << endl;
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