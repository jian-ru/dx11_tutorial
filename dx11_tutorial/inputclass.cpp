#include "inputclass.h"


InputClass::InputClass() {}

InputClass::InputClass(const InputClass& other) {}

InputClass::~InputClass() {}

void InputClass::initialize()
{
	int i;

	// Initialize all the keys to being released and not pressed.
	for (i = 0; i < 256; i++)
	{
		m_keys[i] = false;
	}
}

void InputClass::keyDown(unsigned int input)
{
	// If a key is pressed then save that state in the key array.
	m_keys[input] = true;
}

void InputClass::keyUp(unsigned int input)
{
	// If a key is released then clear that state in the key array.
	m_keys[input] = false;
}

bool InputClass::isKeyDown(unsigned int key)
{
	// Return what state the key is in (pressed/not pressed).
	return m_keys[key];
}