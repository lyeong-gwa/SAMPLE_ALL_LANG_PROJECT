# DeliveryHub

중견기업 고객사 환경에 맞춰 다중 언어 버전으로 제공되는 **배달 플랫폼 솔루션**입니다.
배달의민족을 벤치마킹하여, 고객사의 인프라 환경(Java, Python, .NET 등)에 따라 선택적으로 배포할 수 있도록 설계되었습니다.

## 솔루션 개요

DeliveryHub는 단일 솔루션이 아닌, **고객사 환경별 다중 언어 버전**을 제공하는 배달 플랫폼입니다.

- Java 환경 고객사 → Java 백엔드
- Java 불가 환경 → Python 백엔드
- .NET 환경 고객사 → C# 백엔드
- 웹 프론트엔드는 JavaScript 기반으로 공통 제공

## 기술 스택

| 언어 | 모듈 | 설명 |
|------|------|------|
| Java | `backend-java/` | 백엔드 API 서버 (메인 버전) |
| Python | `backend-python/` | 백엔드 API 서버 (Python 환경 대체 버전) |
| C# | `backend-csharp/` | 백엔드 API 서버 (.NET 환경 대체 버전) |
| JavaScript | `frontend-web/` | 웹 프론트엔드 (공통) |
| C++ | `engine-core/` | 주문 매칭 및 경로 최적화 엔진 |
| C (C99) | `device-module/` | POS 단말기 / 키오스크 연동 모듈 |
| SQL | `database/` | DB 스키마, 프로시저, 마이그레이션 스크립트 |

## 주요 기능

- **주문 관리**: 주문 접수, 상태 추적, 주문 이력 조회
- **가맹점 관리**: 가맹점 등록, 메뉴 관리, 영업시간 설정
- **배달 매칭**: 주문-라이더 매칭 알고리즘 (C++ 엔진)
- **경로 최적화**: 실시간 배달 경로 계산 (C++ 엔진)
- **결제 연동**: 결제 처리 및 정산
- **POS 연동**: 가맹점 POS 단말기 통신 (C99 모듈)
- **관리자 대시보드**: 통계, 모니터링, 운영 관리

## 프로젝트 구조

```
DeliveryHub/
├── backend-java/          # Java 백엔드 (Spring Boot)
├── backend-python/        # Python 백엔드 (FastAPI)
├── backend-csharp/        # C# 백엔드 (ASP.NET Core)
├── frontend-web/          # JavaScript 프론트엔드 (React)
├── engine-core/           # C++ 매칭/경로 엔진
├── device-module/         # C99 POS/단말기 모듈
├── database/              # SQL 스키마 및 마이그레이션
│   ├── schema/
│   ├── procedures/
│   └── migrations/
└── docs/                  # 프로젝트 문서
```

## 환경별 배포 가이드

| 고객사 환경 | 백엔드 | 프론트엔드 | 엔진 | 단말기 |
|-------------|--------|-----------|------|--------|
| Java (JDK 11+) | backend-java | frontend-web | engine-core | device-module |
| Python (3.9+) | backend-python | frontend-web | engine-core | device-module |
| .NET (6.0+) | backend-csharp | frontend-web | engine-core | device-module |

## 브랜치 전략

- `main` : 운영 배포 브랜치
- `develop` : 개발 통합 브랜치
- `YYMM/JIRA-{번호}-{기능명}` : 기능 개발 브랜치
- 개인 작업 브랜치는 기능 브랜치 하위에서 자유롭게 생성

## 팀 구성

| 역할 | 인원 | 담당 |
|------|------|------|
| 총괄 PM | 1명 | 프로젝트 관리, 배포 관리 |
| 백엔드 시니어 | 2명 | 코드 리뷰, 아키텍처 설계 |
| 백엔드 주니어 | 3명 | Java / Python / C# 백엔드 개발 |
| 프론트엔드 시니어 | 1명 | 코드 리뷰, UI 아키텍처 |
| 프론트엔드 주니어 | 3명 | 웹 프론트엔드 개발 |
