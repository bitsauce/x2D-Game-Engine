#ifndef CGF_INPUT_CONTEXT_H
#define CGF_INPUT_CONTEXT_H

#include <CGF/Config.h>
#include <CGF/Input/InputManager.h>

BEGIN_CGF_NAMESPACE

/*********************************************************************
**	Input context													**
**********************************************************************/

class Game;

class CGF_API InputContext
{
	friend class InputManager;
public:
	InputContext(InputManager*);

	/**
	 * \fn	void InputContext::addKeybind(KeybindPtr keybind);
	 *
	 * \brief	Bind a function to an action for this input context.
	 *
	 * \param	keybind	The keybind.
	 *
	 * ### param	name	The name.
	 */

	void addKeybind(KeybindPtr keybind);

	/**
	 * \fn	void InputContext::removeKeybind(KeybindPtr keybind);
	 *
	 * \brief	Removes the keybind described by keybind.
	 *
	 * \param	keybind	The keybind.
	 *
	 * ### param	name	The name.
	 */

	void removeKeybind(KeybindPtr keybind);

	bool getKeyState(string name) const;

private:

	/**
	 * \fn	void InputContext::updateKeybinds(KeyEvent *e);
	 *
	 * \brief	Updates the keybinds with event e.
	 *
	 * \param [in,out]	e	If non-null, the KeyEvent to process.
	 */

	void updateKeybinds(KeyEvent *e);

	// Key binds
	map<string, KeybindPtr> m_keybinds;

	// Input manager
	InputManager *m_inputManager;
};

END_CGF_NAMESPACE

#endif // CGF_INPUT_CONTEXT_H