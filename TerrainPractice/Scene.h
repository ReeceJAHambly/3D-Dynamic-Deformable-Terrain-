#pragma once

class Scene {
public:
	virtual void Initialize() = 0;
	virtual void Update(float delta) = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
};