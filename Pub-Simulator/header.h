#pragma once
#include <string>
#include <queue>
#define MAX_TIME 360 // 영업시간 6시간
#define MAX_JOB_SIZE 100
#define CUSTOMER_PROB 0.05 // 손님이 들어올 확률 5%
using namespace std;

int current_time = 0; // 현재 시간
int remaining_time_fryer1 = 0; // 튀김기1 남은시간
int remaining_time_fryer2 = 0; // 튀김기2 남은시간
int remaining_time_grill = 0; // 탕, 구이 남은시간
string fryer1_cooking; // 튀김기1 메뉴
string fryer2_cooking; // 튀김기2 메뉴
string grill_cooking; // 버너 메뉴
bool is_grilling = false; // 구이 하는 중

bool is_customer_entered();

void ordering();
class Job {
	string name; // 요리 이름
	int charge; // 요리 가격
	int type; // 요리 종류 1튀김 2탕 3구이
	int duration; // Job의 조리 시간
public:
	// job의 변수에 접근하기 위한 메소드
	void set_name(string n);
	string get_name();
	void set_charge(int c);
	int get_charge();
	void set_type(int t);
	int get_type();
	void set_duration(int d);
	int get_duration();
};
class Sales { // 판매량 및 수익을 출력하기 위한 전역 변수 클래스
public:
	int sales = 0; // 총수익
	// 각 메뉴별 판매 갯수
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

bool is_fryer1_used(); // 튀김기 사용 여부
bool is_fryer2_used();
bool is_grill_used(); // 버너 사용 여부

double random();

