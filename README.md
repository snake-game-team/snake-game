# Snake Game

C++과 ncurses 라이브러리를 사용한 콘솔 기반 스네이크 게임입니다.  
맵, 스코어 보드, 미션 보드를 포함하며, 아이템, 게이트, 동적 장애물, 스테이지 미션 등을 구현했습니다.

## 기능
- **맵/스코어/미션 보드**: 실시간 점수와 목표 달성 여부 표시
- **아이템**  
  - Growth(`+`): 길이 증가  
  - Poison(`-`): 길이 감소 (길이 3 미만 시 게임 종료)  
  - Speed Up(`S`): 이동 속도 증가
- **게이트**: 쌍으로 생성되며 한쪽 진입 시 다른 쪽으로 이동
- **동적 장애물**: 게임 중 무작위로 생성·제거
- **스테이지 미션**: 각 스테이지별 목표 달성 시 다음 스테이지 진행

## 개발 환경
- Language: C++
- Library: ncurses, STL(queue, chrono)
- OS: Ubuntu (WSL 환경)

## 설치 및 실행
```bash
sudo apt update
sudo apt install g++ gdb make git
sudo apt install libncurses5-dev libncursesw5-dev

git clone https://github.com/MinJuTur/snake-game.git
cd snake-game
make clean
make
./main
```

## 조작
- `w`, `a`, `s`, `d`로 이동
- 진행 방향의 반대 키 입력 시 게임 종료

## 팀원
- 장민주: 3·4단계 구현, 구조 설계, 리팩토링
- 장운영: 1·2단계 구현
- 최비성: 5단계 및 추가 기능(Speed Up, 동적 장애물, UI 개선)
