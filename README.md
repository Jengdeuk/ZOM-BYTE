# ZOM-BYTE
🧟 2D ASCII zombie survival shooter<br>
콘솔 앱 기반의 2D 탑다운 슈팅 게임입니다.

| 게임 명 | ZOM-BYTE |
| --- | --- |
| 게임 장르 | 탑다운 슈팅, 핵 앤 슬래시, 서바이벌 액션 |
| 플랫폼 | PC (Windows, Console Application) |
| 개발 인원 | 1인 |
| 사용 엔진 | C++ 기반 자체 개발 |
| 프로젝트 기간 | 2026.02.05 ~ 2026.02.11 (7일) |
| 배포 | https://drive.google.com/file/d/1KkdMCq3R0-Sj7OtLahHtk1_BRq-I7pWw/view?usp=sharing |
| 노션 링크 | https://jengdeuk.notion.site/ZOM-BYTE-2f75d8590d1180739638ed8ebbb06df2 |

## 게임 소개

<aside>
💡 `원티드 포텐업`에서 진행하는 `게임 개발자 양성과정 4th`프로그램에서 제작한 게임입니다.<br>
C++ 콘솔 텍스트 출력 기반의 탑다운 슈팅 게임을 제작했습니다.
</aside>

## 게임 영상

[https://youtu.be/HdAMU0mTXPE?si=og5ZlKALmBonKptq](https://youtu.be/HdAMU0mTXPE?si=og5ZlKALmBonKptq)

## 개발 내용

[노션 링크](https://jengdeuk.notion.site/ZOM-BYTE-2f75d8590d1180739638ed8ebbb06df2)
1. 화면 스크롤 및 이동 시스템
2. 물리 및 충돌 처리 시스템
3. 적 AI 시스템 - FSM
4. 무기 시스템
5. 캐릭터 스탯 시스템

## 보완할 점

- 현재는 좀비 생성/삭제 시 동적 할당이 발생하므로, 오브젝트 풀링을 도입해 메모리 할당 비용과 단편화를 줄이고 다수의 좀비가 등장하는 상황에서도 프레임 드랍을 최소화할 수 있도록 개선할 계획입니다.
- 기존 상태 머신 기반 AI를 행동 트리(Behavior Tree) 구조로 확장하여, 조건 기반 의사결정과 병렬 행동을 지원하는 것 보다 확장성 있는 AI 구조로 개선할 수 있습니다.

## 프로젝트 성과

- 7일이라는 제한된 기간 내에 기획, 설계, 구현, 회고 및 발표까지 전 과정을 완주하며 빠른 실행력과 일정 관리 역량을 검증했습니다.
- 그래픽스 API 없이 콘솔 환경에서 2D 게임을 구현하여 렌더링 파이프라인의 기본 원리를 이해하고 응용했습니다.
- 콘솔 스크린 버퍼를 활용한 더블 버퍼링을 구현하여 화면 깜빡임을 제거하고 렌더링 구조를 개선했습니다.
- C++ 기반으로 RTTI(Runtime Type Information)를 직접 구현하여 타입 식별 구조에 대한 이해를 심화했습니다.
- 스마트 포인터를 적용하여 객체 생명주기 및 메모리 관리를 안정적으로 설계했습니다.
