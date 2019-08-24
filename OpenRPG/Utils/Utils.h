#pragma once

// 스마트 포인터
using std::shared_ptr;

/// <summary>단축 타입과 함수들을 정의한 네임스페이스입니다.</summary>
namespace g {

/// <summary><c>shared_ptr&lt;T&gt;</c>로 해석되는 타입입니다.</summary>
template <typename T> using safe = shared_ptr<T>;

/// <summary><c>std::map&lt;std::string, T&gt;</c>로 해석되는 타입입니다.</summary>
template <typename T> using map = std::map<std::string, T>;

/// <summary><c>std::map&lt;std::string, safe&lt;T&gt;&gt;</c>로 해석되는 타입입니다.</summary>
template <typename T> using safemap = std::map<std::string, safe<T>>;

/// <summary><c>std::vector&lt;safe&lt;T&gt;&gt;</c>로 해석되는 타입입니다.</summary>
template <typename T> using safevector = std::vector<safe<T>>;

/// <summary>"#"을 포함하는 Hex 색상 코드를 <see cref="sf::Color"/>로 변환합니다.</summary>
sf::Color Color(std::string rgba);

/// <summary>"#"을 포함하는 Hex 색상 코드와 투명도를 <see cref="sf::Color"/>로 변환합니다.</summary>
sf::Color Color(std::string rgb, int alpha);

} // namespace g

/// <summary>
/// <c>g::safe&lt;State&gt;</c> 유형의 <see cref="State"/>를
/// 간단하게 생성할 수 있는 매크로입니다.
/// </summary>
#define SafeState(X, ...) g::safe<State>(new X(__VA_ARGS__))
