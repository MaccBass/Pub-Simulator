#pragma once
#include <string>
#include <queue>
#define MAX_TIME 360 // �����ð� 6�ð�
#define MAX_JOB_SIZE 100
#define CUSTOMER_PROB 0.05 // �մ��� ���� Ȯ�� 5%
using namespace std;

int current_time = 0; // ���� �ð�
int remaining_time_fryer1 = 0; // Ƣ���1 �����ð�
int remaining_time_fryer2 = 0; // Ƣ���2 �����ð�
int remaining_time_grill = 0; // ��, ���� �����ð�
string fryer1_cooking; // Ƣ���1 �޴�
string fryer2_cooking; // Ƣ���2 �޴�
string grill_cooking; // ���� �޴�
bool is_grilling = false; // ���� �ϴ� ��

bool is_customer_entered();

void ordering();
class Job {
	string name; // �丮 �̸�
	int charge; // �丮 ����
	int type; // �丮 ���� 1Ƣ�� 2�� 3����
	int duration; // Job�� ���� �ð�
public:
	// job�� ������ �����ϱ� ���� �޼ҵ�
	void set_name(string n);
	string get_name();
	void set_charge(int c);
	int get_charge();
	void set_type(int t);
	int get_type();
	void set_duration(int d);
	int get_duration();
};
class Sales { // �Ǹŷ� �� ������ ����ϱ� ���� ���� ���� Ŭ����
public:
	int sales = 0; // �Ѽ���
	// �� �޴��� �Ǹ� ����
	int
		beer = 0, soju = 0, highball = 0,
		jupo = 0, french_fry = 0, fryed_squid = 0, shrimp = 0, chicken = 0,
		tteok = 0, oden = 0, jjam = 0,
		squid = 0, pollack = 0, jerky = 0;
};
Sales s;
Job job[MAX_JOB_SIZE];
queue<Job> fryer_queue;
queue<Job> grill_queue;

int beer_order(int beer_amount);
int snack_order(int beer_amount);

void process_next_job_fryer();
void process_next_job_grill();

bool is_fryer1_used(); // Ƣ��� ��� ����
bool is_fryer2_used();
bool is_grill_used(); // ���� ��� ����

double random();

