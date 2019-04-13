# HW3 Sorting

Sorting 알고리즘들을 class 형식으로 구현하는 문제입니다.

작동방식은 다음과 같아야 합니다.



1. Sorting 클래스를 만들어서 멤버함수인 run()을 호출하면 클래스 내부에 저장된 배열이 정렬

2. 각 클래스마다 friend 함수가 있어서 정렬이 제대로 되었는지 확인하여 제대로 되었으면 true를 리턴

3. Sorting 클래스의 destructor는 반드시 할당된 메모리를 반환



자세한 구현사항은 PPT를 참조해주시고, 첨부된 skeleton code에서 알맞은 부분에 구현해주시면 됩니다. 추가로 필요한 함수가 있다면 각 클래스의 멤버 함수로 구현하시면 됩니다.



제출 기한은 4월 17일 수 11:00까지이고 딜레이는 4월 19일 금 11:00 까지 받으며 50%의 페널티가 있습니다.


--추가 설명--

1. 함수 comment

구현하도록 주어진 constructor, destructor, set 등의 함수도 comment를 해주셔야 합니다.

Report에 적어주실 내용은 Quicksort와 관련해서 구현한 함수 전부 + 본인이 추가한 함수 전부입니다.



2. 시간 출력 및 Stoogesort 실행

time_t로 되어있는 member variable을 전부 double로 바꿔주세요. 소수점 아래 4번째 자리까지 출력되도록 구현해주시면 됩니다.

또한, 각 알고리즘의 소요되는 시간이 10초 이상일 경우

"Terminated due to the time limit"

문자열을 출력하고 종료하도록 구현해주세요.



3. Random number generation

각 class에서 double로 된 배열을 갖고 있게 했는데, random number는 double이든 int든 상관없이 생성하고 double로 변환해서 넣어주시면 됩니다.

예를 들어 0에서 99 사이 값을 만들었다면

double d = (double)(rand() % 100);

를 입력해주면 d에 0~99 값 중 하나가 double로 변환되어 들어갑니다.


----4/9 추기----

배열을 생성할 때 수의 범위는 0에서 적어도 999 이상이 되도록 만들어 주세요.



----4/12 추기----

1. Quick sort 의 구현은 수업시간에 배운 것처럼 QuickSort(Alternative) 슬라이드에 나온 파티션 방법으로 구현해주세요.

2. ppt에서 constructor에서 array = {1,2,3,4,5,6,7,8,9,10}으로 할당하라는 말이 있어서 혼란이 좀 있었습니다만, 이는 객체를 새로 만들 때 default array를 하나 만든다고 생각하시면 됩니다.

실제로 sort를 할 배열은 set 함수를 통해 새로 할당합니다. set 함수의 설명에서 you should avoid memory leak는 잘 생각하면 무슨 뜻인지 알 수 있으실겁니다.

3. sorting에 필요한 함수는 멤버 함수로 추가하시면 됩니다.
