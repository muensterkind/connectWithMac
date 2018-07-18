// MONEYBOX.CPP

#include <iostream>
#include <string>
using namespace std;

class MoneyBox{																							//통장 클래스

private:
	string name;							  															//예금주 이름
	int sum;																									//예금 잔고
  int grade;                      													//신용 등급
  int interest;                   													//이자

public:
	void init(string newname, int money = 0, int member = 3);	//통장초기화
	void save(int money);										                  //예금하기
	void use(int money);										                  //출금하기
	void print();  												                    //통장내용인쇄
  void calcInt();                                           //이자계산
	int getSum();												                      //현재잔고가져오기
  int getGrade();                                           //신용등급가져오기
	int transfer(MoneyBox &t, int money);
};

void MoneyBox::init(string newname, int money, int member) {
	name = newname;         																	//예금주 이름을 세팅
	sum = money;																							//통장잔고 세팅
  grade = member;         																	//신용등급 세팅
}

void MoneyBox::save(int money) {
	sum += money;																							//통장잔고에 입금처리
}

void MoneyBox::use(int money) {
	if (money > sum && grade > 1)															//신용등급이 1이 아니면서 잔고가 출금액보다 적은 경우
		cout << "잔고가 부족합니다!\n";
	else
		sum -= money;																						//통장잔고에서 출금처리
}

void MoneyBox::print() {
	cout << name << "님[등급 " << grade << "]의 예금잔고는 " << sum << "원입니다.\n";
}

void MoneyBox::calcInt() {
  int grade = getGrade();
  float rate;
  if(grade == 1) rate = 0.03;
  else if(grade == 2) rate = 0.02;
  else if(grade == 3) rate = 0.01;
  interest = sum * rate;
  float tax = interest * 0.22;
  cout << name << "님에게 이자가 지급되었습니다." << endl;
  cout << "이자 : " << interest << ", 세금 : " << tax << endl;
  sum += (interest - tax);
}

int MoneyBox::getSum() {
	return sum;
}

int MoneyBox::getGrade() {
  return grade;
}

int MoneyBox::transfer(MoneyBox &t, int money) {
	if (sum < money && grade > 1)
		return 0;
	else
	{
		use(money);
		t.save(money);
		return 1;
	}
}


int main() {
	MoneyBox a, b;																						//통장 a와 b를 생성한다.
	int key;																									//메뉴선택을 위한 키 변수
	int howmuch;																							//입출금액을 위한 변수

	a.init("Kim", 10000, 1);																	//통장 a의 소유주는 Kim으로 세팅한다. 잔고는 10000원. 1등급.
	b.init("Lee", 10000, 3);																	//통장 b의 소유주는 Lee로 세팅한다. 잔고는 10000원. 3등급.

	while(1) {
		cout << "\n11: Kim 입금 12: Kim 출금 13: Kim 잔고확인 14: Kim 이자계산 15: Lee에게 송금";
		cout << "\n21: Lee 입금 22: Lee 출금 23: Lee 잔고확인 24: Lee 이자계산 25: Kim에게 송금\n";
		cout << "위 메뉴 중에서 하나를 선택하시오.(0:종료) ------> ";
		cin >> key;

		switch(key) {
			case 0:
				cout << "종료합니다.\n";
				return 0;
			case 11:
				cout << "입금할 금액은? ";
				cin >> howmuch;
				a.save(howmuch);
				break;
			case 12:
				cout << "출금할 금액은? ";
				cin >> howmuch;
				a.use(howmuch);
				break;
			case 13:
				a.print();
				break;
      case 14:
        a.calcInt();
        break;
			case 15:
				cout << "송금할 금액은? ";
				cin >> howmuch;
				if (a.transfer(b,howmuch) == 0) cout << "송금 실패\n";
        else cout << "송금 성공\n";
				break;
			case 21:
				cout << "입금할 금액은? ";
				cin >> howmuch;
				b.save(howmuch);
				break;
			case 22:
				cout << "출금할 금액은? ";
				cin >> howmuch;
				b.use(howmuch);
				break;
			case 23:
				b.print();
				break;
      case 24:
        b.calcInt();
        break;
      case 25:
  			cout << "송금할 금액은? ";
  			cin >> howmuch;
  			if (b.transfer(a,howmuch) == 0) cout << "송금 실패\n";
        else cout << "송금 성공\n";
				break;
			default:
				cout << "잘못 입력했습니다. 다시 입력하시오\n";
				break;
		}
	}
	return 0;
}
