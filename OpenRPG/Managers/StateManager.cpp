﻿#include "stdafx.h"
#include "StateManager.h"

#pragma region getInstance, Constructor, Finalizer, Dispose
StateManager* StateManager::Instance = NULL;

StateManager* StateManager::getInstance() {
	if (StateManager::Instance == NULL) {
		StateManager::Instance = new StateManager();
	}
	return StateManager::Instance;
}

StateManager::StateManager() {
}

StateManager::~StateManager() {
	this->Dispose();
}

void StateManager::Dispose() {
	if (this->disposed)
		throw "ERROR::StateManager::Already Disposed";

	this->Clear();

	this->disposed = true;
}
#pragma endregion

#pragma region Clear, Empty
StateManager* StateManager::Clear() {
	if (this->disposed)
		throw "ERROR::StateManager::Already Disposed";

	using std::vector;

	// 장면 스택 해제
	while (this->stateStack.size() > 0) {
		auto back = this->stateStack.back();
		this->stateStack.pop_back();

		back->onDeactivated();
	}
	return this;
}

bool StateManager::Empty() {
	if (this->disposed)
		throw "ERROR::StateManager::Already Disposed";

	return this->stateStack.empty();
}
#pragma endregion

#pragma region GoTo, Push, Pop, PopUntil
StateManager* StateManager::GoTo(g::safe<State> state) {
	if (this->disposed)
		throw "ERROR::StateManager::Already Disposed";

	this->Pop();
	this->Push(state);
	return this;
}

StateManager* StateManager::Push(g::safe<State> state) {
	if (this->disposed)
		throw "ERROR::StateManager::Already Disposed";

	if (!this->Empty()) // 스택이 비어있지 않다면 기존 최상위 장면에 onDeactivated 호출
		this->stateStack.back()->onDeactivated();

	this->stateStack.push_back(g::safe<State>(state));
	state->onActivated();
	return this;
}

g::safe<State> StateManager::Pop() {
	using std::find;

	if (this->disposed)
		throw "ERROR::StateManager::Already Disposed";

	auto back = this->stateStack.back();
	this->stateStack.pop_back();

	back->onDeactivated();
	if (!this->Empty()) // 스택이 비어있지 않다면 최상위 장면에 onActivated 호출
		this->stateStack.back()->onActivated();

	return back;
}

StateManager* StateManager::PopUntil(State* state) {
	if (this->disposed)
		throw "ERROR::StateManager::Already Disposed";

	while (!this->Empty()) {
		auto back = this->Pop();
		if (back.get() == state)
			break;
	}
	return this;
}
#pragma endregion

StateManager* StateManager::Update() {
	if (this->disposed)
		throw "ERROR::StateManager::Already Disposed";

	bool update = true, render = true;

	auto stackSize = this->stateStack.size();
	for (g::safevector<State>::size_type i = stackSize - 1; i >= 0; i--) { // 최상위부터 순서대로 갱신
		auto item = this->stateStack[i];

		if (update)
			item->update(); // 장면을 갱신
		if (render)
			item->render(); // 장면을 그리기

		// 갱신 또는 그리기가 흐를 수 있는지를 확인
		update = update && (item->flow() & StateFlow::FLOW_UPDATE);
		render = render && (item->flow() & StateFlow::FLOW_RENDER);

		// 둘 다 할 수 없을 때
		if (!update && !render)
			break;
	}
	return this;
}