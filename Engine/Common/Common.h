#pragma once

#pragma warning(disable: 4172) // 지역 변수의 주소를 반환하면 안된다고 warning. 위험성 인지한채로 사용
#pragma warning(disable: 4251) // dll 뽑을 때 stl 넘겨주면 안된다고 warning. 미봉책 (방법 없음)

#define DLLEXPORT __declspec( dllexport )
#define DLLIMPORT __declspec( dllimport )

#if ENGINE_BUILD_DLL
#define JD_API DLLEXPORT
#else
#define JD_API DLLIMPORT
#endif

#define DEBUG_BREAK(cause) __debugbreak()