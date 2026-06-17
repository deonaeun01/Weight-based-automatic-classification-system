# ⚖️ 무게 기반 자동 분류 시스템 (Weight-Based Automatic Classification System)

STM32 FreeRTOS를 활용한 로드셀 + 컨베이어 벨트 + 6축 로봇팔 통합 자동화 프로젝트

---

## 📌 시스템 아키텍처

```
로드셀 (AD002 변환 모듈)
    └─── 아날로그 신호 ───▶ STM32 F411RE (Nucleo)
                                    │
                          ┌─────────┼─────────┐
                          │         │         │
                    이동 평균    컨베이어    6축 로봇팔
                    필터 처리    벨트 모터      피킹
                   (노이즈 제거)  (이송 제어)  (분류 동작)
```

---

## 🛠 사용 하드웨어

| 장치 | 역할 |
|---|---|
| STM32 F411RE (Nucleo) | 메인 MCU — 센서 처리 및 모터 제어 |
| 로드셀 + AD002 모듈 | 무게 측정 및 아날로그→디지털 변환 |
| 컨베이어 벨트 + 모터드라이버 | 물체 이송 |
| 6축 로봇팔 (서보모터) | 물체 피킹 및 분류 |

---

## 🔌 STM32 핀 설정

| 핀 | 기능 | 연결 |
|---|---|---|
| — | ADC / Timer PWM | 로드셀 신호, 서보 제어, 모터드라이버 |

> 상세 핀맵은 `stm31411_cli/Core/Inc/` 헤더 파일 참고

---

## ⚙️ 주요 기능

### ⚖️ 정밀 무게 측정
- 로드셀 + AD002 변환 모듈로 아날로그 무게 신호 수집
- STM32 ADC를 통한 디지털 변환

### 📊 이동 평균 필터 (Moving Average Filter)
- 센서 노이즈를 최소화하는 신호 처리 알고리즘 적용
- 측정값 안정화로 분류 정확도 향상

### 🏭 실시간 통합 제어 시퀀스
- 무게 데이터 수집 → 필터링 → 분류 기준 판별
- 컨베이어 벨트 구동으로 물체 이송
- 6축 로봇팔 피킹(Picking) 동작으로 목적지 분류

### 🔄 FreeRTOS 멀티태스킹
- 센서 수집 / 필터링 / 모터 제어를 독립 태스크로 분리
- 실시간 스케줄링으로 안정적인 동작 보장

---

## 📂 시스템 처리 흐름

```
1. Sensing   : 로드셀 아날로그 신호 수집 (AD002 → ADC)
       ↓
2. Filtering : 이동 평균 필터로 노이즈 제거
       ↓
3. Decision  : 무게 임계값 기준으로 분류 판별
       ↓
4. Acting    : 컨베이어 벨트 이송 + 로봇팔 피킹 동작 실행
```

---

## 📁 파일 구조

```
Weight-based-automatic-classification-system/
├── Koe/                        # STM32 프로젝트 (팀원 A)
│   ├── Core/
│   │   ├── Inc/                # 헤더 파일 (모듈화)
│   │   └── Src/
│   │       └── main.c          # FreeRTOS 메인 코드
│   └── ...
├── stm31411_cli/               # STM32 프로젝트 (팀원 B)
│   ├── Core/
│   │   ├── Inc/
│   │   └── Src/
│   │       └── main.c
│   └── ...
├── stm31411_cli.zip            # 백업 압축 파일
└── README.md
```

> 헤더(.h)와 소스(.c) 파일 분리로 모듈화하여 6인 팀 병렬 개발 및 Git Merge 최적화

---

## 🚀 빌드 및 실행

### 개발 환경 준비
```
STM32CubeIDE 1.x 설치
STM32 F411RE (Nucleo) 보드 연결 (USB)
```

### 프로젝트 열기
```
STM32CubeIDE → File → Import → Existing Projects into Workspace
→ Koe/ 또는 stm31411_cli/ 폴더 선택
```

### 빌드 및 플래시
```
Project → Build All (Ctrl+B)
Run → Debug (F11) 또는 Run As → STM32 C/C++ Application
```

---

## 👥 팀 협업

| 항목 | 내용 |
|---|---|
| 인원 | 6명 |
| 역할 분담 | 시스템 로직 설계 / 하드웨어 인터페이스 / 데이터 필터링 구현 |
| 형상 관리 | GitHub 브랜치 전략 + 주기적 코드 리뷰 + Merge 중심 협업 |
| 문서화 | Notion을 통한 회의록 및 설계 문서 관리 |

📎 **Notion**: https://www.notion.so/Team-b97304a11b72836aa188015b787c27f1

---

## 🛠 기술 스택

![C](https://img.shields.io/badge/C-A8B9CC?style=flat-square&logo=c&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![STM32](https://img.shields.io/badge/STM32-03234B?style=flat-square&logo=stmicroelectronics&logoColor=white)
![FreeRTOS](https://img.shields.io/badge/FreeRTOS-8CC84B?style=flat-square&logo=freertos&logoColor=white)
![Git](https://img.shields.io/badge/Git-F05032?style=flat-square&logo=git&logoColor=white)
![GitHub](https://img.shields.io/badge/GitHub-181717?style=flat-square&logo=github&logoColor=white)

---

## 👨‍💻 개발 환경

- STM32CubeIDE 1.x
- STM32 HAL Library
- FreeRTOS (CMSIS-RTOS v2)
- Git / GitHub
