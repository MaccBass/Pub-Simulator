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
		cout << "\n----- ÇöÀç ½Ã°£: " << current_time / 60 + 6 << "½Ã " << current_time % 60 << "ºÐ -----\n" << endl;

		// ¼Õ´ÔÀÌ µé¾î¿Ô´ÂÁö È®ÀÎ
		if (is_customer_entered()) ordering();

		// Á¶¸®±â±¸°¡ »ç¿ëÁßÀÎÁö È®ÀÎ ÈÄ À½½Ä Á¶¸® ½ÃÀÛ
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
			cout << "< Æ¢±è±â 1 : " << fryer1_cooking << " Á¶¸® Áß >" << endl;
			--remaining_time_fryer1;
			if (remaining_time_fryer1 == 0)
				cout << fryer1_cooking << " Á¶¸® ¿Ï·á" << endl;
		}
		if (is_fryer2_used() && remaining_time_fryer2 > 0) {
			cout << "< Æ¢±è±â 2 : " << fryer2_cooking << " Á¶¸® Áß >" << endl;
			--remaining_time_fryer2;
			if (remaining_time_fryer2 == 0)
				cout << fryer2_cooking << " Á¶¸® ¿Ï·á" << endl;
		}
		if (!is_grill_used() && !grill_queue.empty()) {
			process_next_job_grill();
		}
		else {
			if (remaining_time_grill > 0) {
				cout << "< ¹ö³Ê : " << grill_cooking << " Á¶¸® Áß >" << endl;
				--remaining_time_grill;
				if (remaining_time_grill == 0) {
					cout << grill_cooking << " Á¶¸® ¿Ï·á" << endl;
					if (is_grilling)
						is_grilling = false;
				}
			}
		}
		++current_time;
	}
	cout << "----- 12½Ã : ¿µ¾÷ Á¾·á -----" << endl;
	cout << "ÃÑ¼öÀÍ : " << s.sales << "¿ø" << endl;
	cout << "\n¸Þ´ºº° ÆÇ¸Å·®" << endl;
	cout << "- ÁÖ·ù -" << endl << "¸ÆÁÖ : " << s.beer << "ÀÜ / ¼ÒÁÖ : " << s.soju << "ÀÜ / ÇÏÀÌº¼ : " << s.highball << "ÀÜ" << endl;
	cout << "- Æ¢±è -" << endl << "Æ¢±èÁãÆ÷ : " << s.jupo << "°³ / °¨ÀÚÆ¢±è : " << s.french_fry << "°³ / ¿ÀÂ¡¾îÆ¢±è : " << s.fryed_squid <<
		"°³ / »õ¿ìÆ¢±è : " << s.shrimp << "°³ / Ä¡Å² : " << s.chicken << "°³" << endl;
	cout << "- ÅÁ·ù -" << endl << "¶±ººÀÌ : " << s.tteok << "°³ / ¿Àµ­ÅÁ : " << s.oden << "°³ / Â«»ÍÅÁ : " << s.jjam << "°³" << endl;
	cout << "- ±¸ÀÌ -" << endl << "¸¶¸¥¿ÀÂ¡¾î : " << s.squid << "°³ / ¸ÔÅÂ : " << s.pollack << "°³ / À°Æ÷ : " << s.jerky << "°³\n" << endl;
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
	cout << "¼Õ´Ô " << person << "¸í ÀÔÀå" << endl;
	cout << "----- ÁÖ¹® ³»¿ª -----" << endl;
	price += beer_order(person);
	price += snack_order(person);
	s.sales += price;
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
		case 0: { cout << "¸ÆÁÖ 1ÀÜ" << endl; ++s.beer; return 3500; }
		case 1: { cout << "¼ÒÁÖ 1º´" << endl; ++s.soju; return 4000; }
		case 2: { cout << "ÇÏÀÌº¼ 1ÀÜ" << endl; ++s.highball; return 5000; }
		}
	}
	order_beer = rand() % a; a -= order_beer;
	charge += order_beer * 3500;
	if (order_beer != 0) cout << "¸ÆÁÖ " << order_beer << "ÀÜ" << endl;
	s.beer += order_beer;
	if (a == 0) return charge;

	order_soju = rand() % a; a -= order_soju;
	charge += order_soju * 4000;
	if (order_soju != 0) cout << "¼ÒÁÖ " << order_soju << "º´" << endl;
	s.soju += order_soju;
	if (a == 0) return charge;

	cout << "ÇÏÀÌº¼ " << a << "ÀÜ" << endl;
	charge += a * 5000;
	s.highball += a;
	return charge;
}
int snack_order(int snack_amount) { // ¾ÈÁÖ ÁÖ¹®
	int charge = 0; int i = 0;
	int a = rand() % (snack_amount + 1); // ¾ÈÁÖ´Â ÃÖ´ë »ç¶÷¼ö¸¸Å­
	int menu_id;
	Job temp;
	while (i < a) {
		menu_id = rand() % 11;

		switch (menu_id) {
		case 0: { temp.set_name("Æ¢±èÁãÆ÷"); temp.set_charge(3500); temp.set_type(1); temp.set_duration(1); ++s.jupo; break; }
		case 1: { temp.set_name("°¨ÀÚÆ¢±è"); temp.set_charge(5500); temp.set_type(1); temp.set_duration(4); ++s.french_fry; break; }
		case 2: { temp.set_name("¿ÀÂ¡¾îÆ¢±è"); temp.set_charge(6000); temp.set_type(1); temp.set_duration(3); ++s.fryed_squid; break; }
		case 3: { temp.set_name("»õ¿ìÆ¢±è"); temp.set_charge(6000); temp.set_type(1); temp.set_duration(5); ++s.shrimp; break; }
		case 4: { temp.set_name("Ä¡Å²"); temp.set_charge(8000); temp.set_type(1); temp.set_duration(8); ++s.chicken; break; }
		case 5: { temp.set_name("¶±ººÀÌ"); temp.set_charge(6000); temp.set_type(2); temp.set_duration(4); ++s.tteok; break; }
		case 6: { temp.set_name("¿Àµ­ÅÁ"); temp.set_charge(9000); temp.set_type(2); temp.set_duration(8); ++s.oden; break; }
		case 7: { temp.set_name("Â«»ÍÅÁ"); temp.set_charge(12000); temp.set_type(2); temp.set_duration(8); ++s.jjam; break; }
		case 8: { temp.set_name("¸¶¸¥¿ÀÂ¡¾î"); temp.set_charge(7000); temp.set_type(3); temp.set_duration(3); ++s.squid; break; }
		case 9: { temp.set_name("¸ÔÅÂ"); temp.set_charge(8000); temp.set_type(3); temp.set_duration(5); ++s.pollack; break; }
		case 10: { temp.set_name("À°Æ÷"); temp.set_charge(8000); temp.set_type(3); temp.set_duration(1); ++s.jerky; break; }
		}
		if (menu_id < 5) fryer_queue.push(temp); // Æ¢±è±â¿¡ temp¸¦ Çª½¬
		else grill_queue.push(temp); // ¹ö³Ê¿¡ temp¸¦ Çª½¬
		charge += temp.get_charge();
		cout << temp.get_name() << " ÁÖ¹®" << endl;
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
		cout << "Æ¢±è±â 1¹ø¿¡ " << fryer1_cooking << " Á¶¸® ½ÃÀÛ" << endl;
	}
	else {
		fryer2_cooking = p.get_name();
		remaining_time_fryer2 = p.get_duration();
		cout << "Æ¢±è±â 2¹ø¿¡ " << fryer2_cooking << " Á¶¸® ½ÃÀÛ" << endl;
	}
}
void process_next_job_grill() {
	Job p;
	p = grill_queue.front();
	grill_queue.pop();
	grill_cooking = p.get_name();
	remaining_time_grill = p.get_duration();

	cout << "¹ö³Ê¿¡ " << grill_cooking << " Á¶¸® ½ÃÀÛ" << endl;
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