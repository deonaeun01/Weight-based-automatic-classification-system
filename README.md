# ⚖️ 무게 기반 자동 분류 시스템 (Weight-Based Automatic Classification System)

STM32 FreeRTOS를 활용한 로드셀 + 컨베이어 벨트 + 5축 로봇팔 통합 자동화 프로젝트

---

## 📌 시스템 아키텍처

로드셀 (AD002 변환 모듈)
└─── 아날로그 신호 ───▶ STM32 F411RE (Nucleo)
                               │
                     ┌─────────┼─────────┐
                     │         │         │
                 이동 평균    컨베이어    5축 로봇팔
                 필터 처리    벨트 모터      피킹
                (노이즈 제거)  (이송 제어)  (분류 동작)


---

## 🛠 사용 하드웨어

| 장치 | 역할 | 비고 |
|---|---|---|
| STM32 F411RE (Nucleo) | 메인 MCU — 센서 처리 및 모터 제어 | ARM Cortex-M4 |
| 로드셀 + AD002 모듈 | 무게 측정 및 아날로그→디지털 변환 | 24-bit ADC 내장 모듈 |
| 컨베이어 벨트 + 모터드라이버 | DC 모터를 통한 물체 이송 제어 | PWM 속도 제어 |
| 5축 로봇팔 (서보모터) | 물체 피킹 및 목적지별 분류 동작 | 다축 서보 제어 |

---

## 🔌 STM32 주요 인터페이스 설정

| 기능 | Peripheral | 연결 및 역할 |
|---|---|---|
| **로드셀 신호 입력** | ADC / GPIO | AD002 모듈과의 인터페이스 및 디지털 변환 데이터 수집 |
| **컨베이어 벨트 제어** | TIM PWM / GPIO | 모터 드라이버 방향 제어 및 PWM을 통한 속도 제어 |
| **5축 로봇팔 제어** | TIM PWM (Multi-Ch) | 각 관절 서보모터 제어를 위한 다채널 PWM 펄스 출력 |

> 💡 상세 핀맵 및 레지스터 설정은 각 프로젝트 폴더 내 `Core/Inc/` 헤더 파일들을 참고해 주세요.

---

## ⚙️ 주요 기능 및 기술적 특징

### ⚖️ 정밀 무게 측정 & 이동 평균 필터 (Moving Average Filter)
- 로드셀 센서 특성상 발생하는 진동 및 전기적 노이즈를 제거하기 위해 **이동 평균 필터 알고리즘**을 소프트웨어적으로 구현했습니다.
- 실시간으로 수집되는 무게 데이터의 변동 폭을 최소화하여 분류 판단의 정확도와 시스템 신뢰성을 높였습니다.

### 🔄 FreeRTOS 기반 멀티태스킹 아키텍처
시스템의 실시간성(Real-time)을 보장하기 위해 기능별로 독립된 Task를 부여하고 우선순위를 최적화했습니다.
- **SensorTask (High)**: 로드셀 주기적 샘플링 및 필터링 연산 수행
- **ControlTask (Normal)**: 무게 임계값 판별 및 전체 시퀀스(이송/동작) 상태 관리
- **ActTask (Normal)**: 컨베이어 벨트 드라이버 및 로봇팔 서보모터 제어 

---

## 📂 파일 구조

Weight-based-automatic-classification-system/
├── Koe/                        # STM32 프로젝트 (팀원 A - 메인 제어 로직)
│   ├── Core/
│   │   ├── Inc/                # 모듈화된 레이어별 헤더 파일
│   │   └── Src/
│   │       └── main.c          # FreeRTOS 커널 및 태스크 초기화
│   └── ...
└── stm32f411_cli/              # STM32 프로젝트 (팀원 B - 주변장치 인터페이스)
├── Core/
│   ├── Inc/
│   └── Src/
│       └── main.c
└── ...

> 🛠 **설계 특징**: 하드웨어 의존적인 헤더(.h) 파일과 비즈니스 로직 소스(.c) 파일을 명확히 분리·모듈화하여, 6인 팀원이 Git Conflict를 최소화하며 병렬 개발을 진행할 수 있도록 설계했습니다.

---

## 🚀 빌드 및 실행

### 개발 환경 준비
- STM32CubeIDE 1.x 설치
- STM32 F411RE (Nucleo) 보드 및 ST-LINK 드라이버 확인

### 프로젝트 로드 및 실행
1. `STM32CubeIDE` 실행 ➡️ `File` ➡️ `Import` ➡️ `Existing Projects into Workspace` 선택
2. `Koe/` 또는 `stm32f411_cli/` 폴더를 루트로 지정하여 가져오기
3. `Project` ➡️ `Build All (Ctrl+B)` 로 빌드 후 `Run` ➡️ `Run As` ➡️ `STM32 C/C++ Application`을 통해 타겟 보드에 플래시 및 실행

---

## 👥 팀 협업 및 형상 관리

| 항목 | 내용 |
|---|---|
| **인원** | 6명 (학부 팀 프로젝트) |
| **역할 분담** | 시스템 시퀀스 아키텍처 설계 / 센서 신호처리 알고리즘 구현 / 하드웨어 인터페이스 제어 |
| **형상 관리** | GitHub 브랜치 전략 기반 협업, 주기적인 코드 리뷰를 통한 안정적인 코드 Merge |
| **문서화** | Notion 공유 페이지를 활용하여 요구사항 명세서, 회의록 및 하드웨어 회로도 관리 |

📎 **프로젝트 Notion 공간**: [팀 노션 링크 이동](https://www.notion.so/Team-b97304a11b72836aa188015b787c27f1)

---

## 🛠 기술 스택

![C](https://img.shields.io/badge/C-A8B9CC?style=flat-square&logo=c&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![STM32](https://img.shields.io/badge/STM32-03234B?style=flat-square&logo=stmicroelectronics&logoColor=white)
![FreeRTOS](https://img.shields.io/badge/FreeRTOS-8CC84B?style=flat-square)
![Git](https://img.shields.io/badge/Git-F05032?style=flat-square&logo=git&logoColor=white)
![GitHub](https://img.shields.io/badge/GitHub-181717?style=flat-square&logo=github&logoColor=white)

---

## 👨‍💻 개발 환경

- STM32CubeIDE 1.x
- STM32 HAL Library
- FreeRTOS (CMSIS-RTOS v2)
- Git / GitHub
