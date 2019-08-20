#include "stdafx.h"
#include "StateManager.h"

using namespace std;

typedef pair<State*, bool> StatePair;

#pragma region getInstance, Constructor, Finalizer
StateManager* StateManager::Instance = NULL;

StateManager* StateManager::getInstance() {
	if (StateManager::Instance == NULL) {
		StateManager::Instance = new StateManager();
	}
	return StateManager::Instance;
}

StateManager::StateManager() {
	// vector 공간 예약 할당
	this->stateStack.reserve(sizeof(State*) * 4);
}

StateManager::~StateManager() {
	this->Clear();
}
#pragma endregion

#pragma region Clear, Empty
StateManager* StateManager::Clear() {
	// 장면 스택 해제
	while (this->stateStack.size() > 0) {
		auto back = this->stateStack.back();
		this->stateStack.pop_back();
		if (back.first != NULL)
			delete back.first;
	}
	return this;
}

bool StateManager::Empty() {
	return this->stateStack.empty();
}
#pragma endregion

#pragma region Push, Pop, PopUntil
StateManager* StateManager::Push(State* state, bool pararell) {
	if (!this->Empty()) // 스택이 비어있지 않다면 기존 최상위 장면에 onDeactivated 호출
		this->stateStack.back().first->onDeactivated();

	this->stateStack.push_back(pair<State*, bool>(state, pararell));
	state->onEnter();
	state->onActivated();
	return this;
}

State* StateManager::Pop() {
	auto back = this->stateStack.back();
	this->stateStack.pop_back();

	back.first->onDeactivated();
	back.first->onLeave();
	if (!this->Empty()) // 스택이 비어있지 않다면 최상위 장면에 onActivated 호출
		this->stateStack.back().first->onActivated();

	return back.first;
}

StateManager* StateManager::PopUntil(State* state) {
	while (!this->Empty() && this->Pop() != state)
		;
	return this;
}

#pragma endregion

StateManager* StateManager::Update() {
	auto stackSize = this->stateStack.size();
	for (vector<pair<State*, bool>>::size_type i = 0; i < stackSize; i++) {
		auto item = this->stateStack[i];
		if (item.second || i + 1 == stackSize) { // 병렬 갱신이 설정된 장면이라면
			item.first->update();				 // 장면을 갱신
			item.first->render();				 // 장면을 그리기
		}
	}
	return this;
}