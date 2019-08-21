#pragma once

#include "Interfaces/IDisposable.h"
#include "States/State.h"

typedef void (*StateDeleter)(State*);

class StateManager : public IDisposable {
  public:
	/// <summary>
	/// 싱글톤 인스턴스를 가져옵니다.
	/// 기존에 인스턴스가 없었다면 새로 생성합니다.
	/// </summary>
	/// <returns><see cref="StateManager"/>의 싱글톤 객체입니다.</returns>
	static StateManager* getInstance();

	/// <summary>모든 자원을 해제하고 사용을 중지시킵니다.</summary>
	void Dispose();

	/// <summary>모든 장면을 정리하고 삭제합니다.</summary>
	StateManager* Clear();

	/// <summary>장면 스택에 장면이 존재하지 않는지 검사합니다.</summary>
	bool Empty();

	/// <summary>
	/// 새 장면으로 이동합니다.
	/// <see cref="State"/> 스택에 추가되지 않고 현재 장면을 교체합니다.
	/// </summary>
	/// <param name="state">추가할 장면입니다.</param>
	/// <param name="callback">
	/// <c>Pop</c>되는 <see cref="State"/>를 전달받는 콜백 메서드입니다.
	/// </param>
	StateManager* GoTo(State* state, StateDeleter callback = NULL);

	/// <summary>
	/// 새 장면을 추가합니다.
	/// 추가된 장면은 <see cref="State"/> 스택에 추가됩니다.
	/// </summary>
	/// <param name="state">추가할 장면입니다.</param>
	StateManager* Push(State* state);

	/// <summary>현재 장면을 제거하고 반환합니다.</summary>
	State* Pop();

	/// <summary>
	/// 전달된 <see cref="State"/>를 찾을 때 까지 <see cref="Pop"/>합니다.
	/// 만약 찾지 못했다면, 모든 <see cref="State"/>가 <see cref="Pop"/>됩니다.
	/// </summary>
	/// <param name="state">찾을 <see cref="State"/>입니다.</param>
	/// <param name="callback">
	/// <c>Pop</c>되는 <see cref="State"/>를 전달받는 콜백 메서드입니다.
	/// </param>
	StateManager* PopUntil(State* state, StateDeleter callback = NULL);

	/// <summary>
	///장면 스택의 front부터 back까지 갱신 가능한 모든 장면을 갱신하고 화면에 그립니다.
	///</summary>
	StateManager* Update();

  private:
	/// <summary>
	/// 싱글톤 인스턴스입니다.
	/// 프로세스 내에 한번만 할당되는 것이 보장됩니다.
	/// </summary>
	static StateManager* Instance;

	/// <summary>
	/// 장면을 관리하는 스택입니다.
	/// <c>stateStack.back().first</c>는 항상 현재 장면을 가리킵니다.
	/// </summary>
	std::vector<State*> stateStack;

	/// <summary>생성자입니다. private로 지정하여 일반적인 할당을 금지합니다.</summary>
	StateManager();
	~StateManager();
};
