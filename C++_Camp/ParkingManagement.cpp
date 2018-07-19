#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

// 현재시간을 string type으로 return하는 함수
string timeToString(time_t t){
  struct tm * tstruct;
  char str[80];
  tstruct = localtime(&t);
  strftime(str, sizeof(str), "[%Y-%m-%d] %X", tstruct); // YYYY-MM-DD.HH:mm:ss 형태의 스트링
  return str;
}

class Car {
private:
  int carNumber; // 차량번호
  string carType; // 차종
  time_t enterTime; // 입차시간
public:
  Car(int num, string type, time_t time) { // 정보 초기화
    carNumber = num; // 차량번호 초기화
    carType = type; // 차종 초기화
    enterTime = time; // 입차시간 초기화
  }
  getCar() {
    정보 돌려주기
  }
  time_t getTime() {
    return enterTime; // 입차시간 return
  }
};

class ParkingLot {
private:
  int MAX_COUNT;
  vector<Car> carList;
  int totalFee = 0;
public:
  ParkingLot() {
    MAX_COUNT = 100;
  }
  ParkingLot(int count) {
    MAX_COUNT = count;
  }
  void CarIn() { // 입차
    MAX_COUNT 이상 넘어가면 안내 후 return
    사용자에게 정보 입력받기(차량번호, 차량종류, 입차시간)
    Car c(차량번호, 차량종류, 입차시간);
    carList.push_back(c);
  }
  void CarOut(int carNum) { // 출차
    time_t distTime; // 시간차 받을 변수
    time_t tempTime = time(0); // 현재시간 받을 변수
    string strTime = timeToString(tempTime); // 현재시간 string으로 표현
    int index; // 해당 차의 인덱스 받을 변수
    int fee; // 요금
    index = findCar(carNum); // 차번호로 차량 찾기
    if(index < 0) { // 해당 차량이 없을 경우
      cout << "그런 차량 없음!" << endl << endl;
      return;
    }
    distTime = calcTime(tempTime, index); // 시간차 계산
    fee = calcFee(distTime); // 시간에 따른 요금 계산
    totalFee += fee; // 총 요금 합산
    cout << strTime << " [" << carNum << "] 출차, 요금 : " << fee << "원" << endl << endl; // 출처 정보 출력
  }
  time_t calcTime(time_t tempTime, int index) { // 시간차 계산하는 함수
    time_t distTime; // 시간차 받을 변수
    distTime = tempTime - carList[index].getTime(); // 시간차 계산
    return distTime; // 시간차 return
  }
  int calcFee(time_t distTime) {
    int fee = 1000; // 요금. 기본요금 1000원
    int additionalFee = 500; // 추가요금 500원
    int count = 0; // 추가횟수
    time_t tempTime = distTime - 30; // 30초가 넘는지 확인하기 위해 사용
    if(tempTime < 0) { // 추가횟수 구하기
      count = tempTime / 10;
      if(tempTime % 10 == 0) count++;
    }
    fee += (additionalFee * count); // 최종 요금 구하기
    return fee; // 요금 return
  }
  int findCar() { // 차량번호로 해당 차량 찾기

    return index;
  }
  void showCars() { //주차차량 보여주기
    vector를 돌려서 모든 차량 보여주기
    getCar가 이용됨
  }
  void showTotalFee() { // 총수입계산
    totalFee 보여주기
  }
};

int main() {
  주차장 생성
  while(1) {
   주차장에서 할 일 선택
  }
}

