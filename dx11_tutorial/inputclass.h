#pragma once


class InputClass
{
public:
	InputClass();
	InputClass(const InputClass &);
	~InputClass();

	void initialize();

	void keyDown(unsigned int);
	void keyUp(unsigned int);

	bool isKeyDown(unsigned int);

private:
	bool m_keys[256];
};