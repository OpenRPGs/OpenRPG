#pragma once

/// <summary><c>Dispose</c> 가능한 인터페이스입니다.</summary>
class IDisposable {
  protected:
	bool disposed = false;

  public:
	virtual void Dispose() = 0;
};
