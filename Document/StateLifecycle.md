# State Lifecycle

### 1. 개요
State의 라이프 사이클을 정리한 문서입니다.

OpenRPG 프로젝트 내의 State는 다음과 같은 Lifecycle로 작동할 것이고, 이는 보장되어야합니다.

### 2. Lifecycle
1. *[constructor]*
	- 장면을 생성할 때 전달받는 정보가 있다면 이곳에서 받아서 멤버에 값을 전달합니다.
2. `onInitialize`
	- 장면이 생성될 때 호출됩니다.
	- 멤버 초기화 등의 작업을 합니다.
	- 장면이 시작되는 트랜지션 연출의 준비 또한 이 메서드에서 이루어집니다.
3. `onActivated`
	- 장면이 초기화된 후 또는 다른 장면에서 돌아온 경우에 호출됩니다.
	- 장면이 백그라운드에서 일부만 갱신되어야 할 때 등에 사용할 수 있습니다.
4. `update`
	- 실제로 장면이 갱신되는 메서드입니다.
	- 매 프레임 갱신되어야 하는 내용을 처리합니다.
5. `render`
	- `update`에서 갱신된 최신 정보를 기반으로 화면에 그려내는 부분입니다.
	- 장면이 **파괴되지 않았다면**, 이후에 `3. update`로 되돌아갑니다.
6. `onDeactivated`
	- 스택의 최상위 장면이 아니게 되었을 때 호출됩니다.
	- 장면이 백그라운드에서 일부만 갱신되어야 할 때 등에 사용할 수 있습니다.
7. `onLeave`
	- 장면이 게임에서 제거될 때 발생합니다.
	- State에서 할당하여 사용하던 **자원들을 해제**해야 합니다.
8. *finalizer*
	- 장면이 메모리에서 완전히 제거될 때 발생합니다.
	- State 내부적으로 사용하는 자원들이 해제됩니다.

### 3. Flow
각 State는 `Flow`를 속성으로 가질 수 있습니다.
`Flow`는 스택의 아래쪽으로 장면의 `update` 또는 `render`가 흐를 수 있는지를 결정합니다.

다음 표를 통해서 `Flow`가 어떻게 동작하는지 알 수 있습니다.

`Top 장면`의 `Flow`는 `all`이라고 가정하고, `Top-2 장면`은 `none`이라고 가정합니다.

| Top-1의 `Flow` | Top 장면 | Top-1 장면 | Top-2 장면 |
|----------------|----------|-----------|------------|
| `none`         | `both`   | `both`    |            |
| `update`       | `both`   | `both`    | `update`   |
| `render`       | `both`   | `both`    | `render`   |
| `all`          | `both`   | `both`    | `both`     |

`Top-1 장면`에서 `Top-2 장면`으로 `update` 또는 `render`의 처리 가능 여부가 흐르는 것을 볼 수 있습니다.

### 4. 슈퍼클래스
모든 장면은 `State`를 상속받아 구현되어야 합니다.

만약 상속받는 메서드를 구현한다면, 반드시 다음과 같이 슈퍼클래스의 메서드를 호출해야 합니다.
```c++
void SubState::update() {
	State::update();
	// ...
}
```

만약 상속되어 구현된 `State`를 상속하여 **이중 상속된 장면**을 구현한다면, 가장 마지막으로 상속받은 장면의 메서드를 호출해야합니다.
```c++
class SubState : public State {
	// ...
}
class SubSubState : public SubState {
	// ...
}

void SubSubState::update() {
	SubState::update();
	// ...
}
```

만약 생성자에서 전달받는 인자가 없다면, 다음과 같이 생성자를 간단하게 구현합니다.
```c++
class SubState : public State {
  public:
	SubState() : State() {}
}
```

### 5. 개발시 주의사항
State를 작성할 때에는 `8.finalizer`는 구현하지 않도록 합니다.

`1. constructor`는 `initialize`를 비롯한 Lifecycle의 메서드들을 호출하지 않습니다.
