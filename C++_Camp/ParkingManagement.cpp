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
    strftime(str, sizeof(str), "[%Y-%m-%d] %X", tstruct);                         // YYYY-MM-DD.HH:mm:ss 형태의 스트링
    return str;
}

/* 클래스 Car (차) */
class Car {
    int carNumber;                                                                // 차량번호
    //  string carType;                                                             // 차종
    time_t enterTime;                                                             // 입차시간
    
public:
    Car(int num, time_t tempTime){}                                               // 정보 초기화
    int getCarNumber(){}                                                          // 차량번호 반환
    time_t getTime(){}                                                            // 입차시간 반환
    
    // 정보 초기화
    Car(int num, time_t tempTime) {
        //  Car(int num, string type, time_t time) {                                    // 정보 초기화
        carNumber = num;                                                            // 차량번호 초기화
        //    carType = type;                                                           // 차종 초기화
        enterTime = tempTime;                                                       // 입차시간 초기화
    }
    
    // 차량번호 반환
    int getCarNumber() {
        return carNumber;                                                           // 차량번호 return
    }
    
    // 입차시간 반환
    time_t getTime() {
        return enterTime;                                                           // 입차시간 return
    }
};

/* 클래스 ParkingLot (주차장) */
class ParkingLot {
    int MAX_COUNT;                                                                // 주차장의 주차 최대 차량
    int carCount;                                                                 // 현재 차량 수
    vector<Car> carList;                                                          // 주차된 차량의 목록을 받을 vector
    int totalFee;                                                                 // 총 요금
    
public:
    ParkingLot(){}                                                                // 주차장 생성자 (default)
    ParkingLot(int count){}                                                       // 주차장 생성자 (최대차량대수 설정 가능)
    void run(){}                                                                  // 주차장 관리 프로그램 작동
    void CarIn(int carNum){}                                                      // 입차
    void CarOut(int carNum){}                                                     // 출차
    time_t calcTime(time_t tempTime, int index){}                                 // 시간차 계산하는 함수
    int calcFee(time_t distTime){}                                                // 요금 계산
    int findCar(int carNum){}                                                     // 차량번호로 해당 차량 찾기
    void showCars(){}                                                             // 주차차량 보여주기
    void showTotalFee(){}                                                         // 총수입계산
    
    // 주차장 생성자 (default)
    ParkingLot() {
        MAX_COUNT = 100;                                                            // 최대 차량 default 100대
        carCount = 0;                                                               // 현재 차량 수 초기화
        totalFee = 0;                                                               // 총 요금 초기화
    }
    
    // 주차장 생성자 (최대차량대수 설정 가능)
    ParkingLot(int count) {
        MAX_COUNT = count;                                                          // 최대 차량 설정
        carCount = 0;                                                               // 현재 차량 수 초기화
        totalFee = 0;                                                               // 총 요금 초기화
    }
    
    // 주차장 관리 프로그램 작동
    void run() {
        int num;                                                                    // 선택된 번호
        int carNum;                                                                 // 선택된 차량번호
        while(1) {                                                                  // 종료를 선택할 때까지 무한 반복
            cout << "작업 : 1. 입차 2. 출차 3. 주차 차량 정보 4. 총 수입 0. 종료 >> ";          // 선택사항 안내
            cin >> num;                                                               // 번호 입력
            switch (num) {                                                            // 번호 선택
                case 1:                                                                   // 1. 입차
                    cout << "[입차] 차량번호는? >> ";
                    cin >> carNum;
                    CarIn(carNum);
                    break;
                case 2:                                                                   // 2. 출차
                    cout << "[출차] 차량번호는? >> ";
                    cin >> carNum;
                    CarOut(carNum);
                    break;
                case 3:                                                                   // 3. 주차 차량 정보
                    showCars();
                    break;
                case 4:                                                                   // 4. 총 수입
                    showTotalFee();
                    break;
                case 0:                                                                   // 0. 종료
                    return;
                default:                                                                  // 잘못된 번호 선택
                    cout << "다시 입력해주세요." << endl << endl;
                    break;
            }
        }
    }
    
    // 입차
    void CarIn(int carNum) {
        if(carCount + 1 > MAX_COUNT) {                                              // 주차장에 자리가 없을 경우
            cout << "주차장에 자리가 없습니다." << endl << endl;
            return;
        }
        carCount++;                                                                 // 주차장의 현재 차량 수 증가
        time_t tempTime = time(0);                                                  // 현재시간 받을 변수
        string strTime = timeToString(tempTime);                                    // 현재시간 string으로 표현
        Car carA(carNum, tempTime);                                                 // 차 생성
        carList.push_back(carA);                                                    // 생성한 차를 vector에 추가
        cout << strTime << " [" << carNum << "] 입차" << endl << endl;               // 입차 정보 출력
    }
    
    // 출차
    void CarOut(int carNum) {
        time_t distTime;                                                            // 시간차 받을 변수
        time_t tempTime = time(0);                                                  // 현재시간 받을 변수
        string strTime = timeToString(tempTime);                                    // 현재시간 string으로 표현
        int index;                                                                  // 해당 차의 인덱스 받을 변수
        int fee;                                                                    // 요금
        index = findCar(carNum);                                                    // 차번호로 차량 찾기
        if(index < 0) {                                                             // 해당 차량이 없을 경우
            cout << "주차장에 존재하지 않는 차량입니다." << endl << endl;
            return;
        }
        distTime = calcTime(tempTime, index);                                       // 시간차 계산
        fee = calcFee(distTime);                                                    // 시간에 따른 요금 계산
        totalFee += fee;                                                            // 총 요금 합산
        carList.erase(carList.begin() + index);                                     // vector에서 해당 차량 삭제
        carCount--;                                                                 // 주차장의 현재 차량 수 감소
        cout << strTime << " [" << carNum << "] 출차, 요금 : " << fee << "원" << endl << endl; // 출차 정보 출력
    }
    
    // 시간차 계산하는 함수
    time_t calcTime(time_t tempTime, int index) {
        time_t distTime;                                                            // 시간차 받을 변수
        distTime = tempTime - carList[index].getTime();                             // 시간차 계산
        return distTime;                                                            // 시간차 return
    }
    
    // 요금 계산
    int calcFee(time_t distTime) {
        int fee = 1000;                                                             // 요금. 기본요금 1000원
        int additionalFee = 500;                                                    // 추가요금 500원
        int count = 0;                                                              // 추가횟수
        time_t tempTime = distTime - 30;                                            // 30초가 넘는지 확인하기 위해 사용
        if(tempTime > 0) {                                                          // 추가횟수 구하기
            count = tempTime / 10;
            if(tempTime % 10 == 0) count++;
        }
        fee += (additionalFee * count);                                             // 최종 요금 구하기
        return fee;                                                                 // 요금 return
    }
    
    // 차량번호로 해당 차량 찾기
    int findCar(int carNum) {
        int index = -1;                                                             // 찾는 차량번호가 있는 인덱스
        for(int i = 0; i < carList.size(); i++) {                                   // 전체 vector 확인
            if(carList[i].getCarNumber() == carNum) {                                 // 찾는 차량번호와 일치할 경우
                index = i;                                                              // 현재 위치를 인덱스로 저장
            }
        }
        return index;                                                               // 찾는 차량번호에 해당하는 인덱스 return. 없는 차인 경우 -1 return.
    }
    
    // 주차차량 보여주기
    void showCars() {
        string strTime;                                                             // 시간을 string으로 표현하기 위한 변수
        for(int i = 0; i < carList.size(); i++) {
            strTime = timeToString(carList[i].getTime());                             // 시간을 string으로 표현
            cout << strTime << " [" << carList[i].getCarNumber() << "]" << endl;      // 차량 각각의 정보 출력
        }
        cout << endl;
    }
    
    // 총수입계산
    void showTotalFee() {
        for(int i = 0; i < carList.size(); i++) {
            cout << carList[i].getCarNumber() << "-";                                 // 차량번호 목록 출력
        }
        cout << endl;
        cout << "총 수입 : " << totalFee << "원" << endl << endl;                     // 총 수입 출력
    }
};

int main() {
    ParkingLot manager(50);                                                       // 주차장 생성, 최대 차량 수 : 50대
    manager.run();                                                                // 주차장 관리 프로그램 작동
    return 0;
}
