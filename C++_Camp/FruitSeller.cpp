#include <iostream>
#include <string>
using namespace std;

class FruitSeller {
private:
	int FRUIT_PRICE;
	int numOfFruits;
	int myMoney;

public:
  string name;
  string fruit;
	void InitMembers(int price, int num, int money, string inputName, string fruitName)	{
		FRUIT_PRICE = price;
		numOfFruits = num;
		myMoney = money;
    name = inputName;
    fruit = fruitName;
	}

	int SaleFruits(string fruitName, int money, int& change) {
    if(numOfFruits <= 0) {
      cout << "죄송하지만 남은 " << fruit << "이 없습니다." << endl << endl;
      return -1;
    }
    if(fruitName.compare(fruit) != 0) {
      cout << fruitName << "를 팔지 않는 가게입니다." << endl << endl;
      return -1;
    }
		int num = money / FRUIT_PRICE;
    if(numOfFruits < num) {
      num = numOfFruits;
    }
		numOfFruits -= num;
    int price = num * FRUIT_PRICE;
    change = money - price;
    if(num >= 10) {
      num += (num / 10);
      numOfFruits -= (num / 10);
      cout << name << ": "  << fruit << " " << (num / 10) << "개는 덤입니다." << endl;
    }
    cout << name << ": "  << fruit << " " << num << "개에 " << price << "원입니다." << endl;
  	cout << name << ": "  << "거스름돈은 " << change << "원입니다." << endl << endl;
		myMoney += (money - change);
		return num;
	}

  int SaleFruits(string fruitName, int money, int& change, int num) {
    if(numOfFruits <= 0) {
      cout << "죄송하지만 남은 " << fruit << "(이)가 없습니다." << endl << endl;
      return -1;
    }
    if(fruitName.compare(fruit) != 0) {
      cout << fruitName << "를 팔지 않는 가게입니다." << endl << endl;
      return -1;
    }
    if(numOfFruits < num) {
      cout << "죄송하지만 " << fruit << "(이)가 " << numOfFruits << "개밖에 없습니다." << endl;
      num = numOfFruits;
      cout << name << ": "  << fruit << " " << (num / 10) << "개는 덤입니다." << endl;
    }
		numOfFruits -= num;
    int price = num * FRUIT_PRICE;
    change = money - price;
    if(num >= 10) {
      num += (num / 10);
      numOfFruits -= (num / 10);
    }
  	cout << name << ": "  << fruit << " " << num << "개에 " << price << "원입니다." << endl;
  	cout << name << ": "  << "거스름돈은 " << change << "원입니다." << endl << endl;
		myMoney += (money - change);
		return num;
	}

	void ShowSalesResult() {
    cout << "판매자: " << name << endl;
		cout << "남은 " << fruit << ": " << numOfFruits << endl;
		cout << "판매 수익: " << myMoney << endl << endl;
	}
};

class FruitBuyer {
	int myMoney;
	int numOfApples;
  int numOfOranges;
  string name;
  string fruit;

public:
	void InitMembers(int money, string inputName)	{
		myMoney = money;
		numOfApples = 0;
    numOfOranges = 0;
    name = inputName;
    fruit = "미정";
	}

	void BuyFruits(FruitSeller &seller, string fruit, int money) {
    if(money > myMoney) {
      cout << name << ": 돈이 없다...ㅜㅜ" << endl << endl;
      return;
    }
		cout << name << ": " << money << "어치의 " << fruit << "를 주세요." << endl << endl;
    int change = 0;
		int num = seller.SaleFruits(fruit, money, change);
    if(num == -1) return;
    if(fruit == "사과") numOfApples += num;
    else if(fruit == "오렌지") numOfOranges += num;
		myMoney -= (money - change);
	}

  void BuyFruits(FruitSeller &seller, string fruit, int money, int count) {
    if(money > myMoney) {
      cout << name << ": 돈이 없다...ㅜㅜ" << endl << endl;
      return;
    }
		cout << name << ": " << count << "개의 " << fruit << "를 주세요." << endl << endl;
    int change = 0;
		int num = seller.SaleFruits(fruit, money, change, count);
    if(num == -1) return ;
    if(fruit == "사과") numOfApples += num;
    else if(fruit == "오렌지") numOfOranges += num;
		myMoney -= (money - change);
	}

	void ShowBuyResult() {
    cout << "구매자: " << name << endl;
		cout << "현재 잔액: " << myMoney << endl;
		cout << "사과 개수: " << numOfApples << endl;
    cout << "오렌지 개수: " << numOfOranges << endl << endl;
	}
};

int main(void) {
	FruitSeller AppleSeller;
	AppleSeller.InitMembers(1000, 20, 0, "사과 파는 집", "사과");
  FruitSeller OrangeSeller;
  OrangeSeller.InitMembers(1500, 20, 0, "오렌지 파는 집", "오렌지");
	FruitBuyer buyer;
	buyer.InitMembers(20000, "철수");

	AppleSeller.ShowSalesResult();
	OrangeSeller.ShowSalesResult();
	buyer.ShowBuyResult();

	buyer.BuyFruits(AppleSeller, "사과", 10000);
  buyer.BuyFruits(OrangeSeller, "오렌지", 5000, 3);
  buyer.BuyFruits(OrangeSeller, "사과", 5000, 3);

	AppleSeller.ShowSalesResult();
	OrangeSeller.ShowSalesResult();
	buyer.ShowBuyResult();
	return 0;
}
