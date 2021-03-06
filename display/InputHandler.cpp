#include "InputHandler.h"
#include "LcdDisplay.h"
#include "KeypadInput.h"

InputState InputHandler::curState;
uint8_t InputHandler::cmdDataSize;
CommandByte InputHandler::curCmd;
uint8_t InputHandler::cmdData[2];

void InputHandler::init() {
  cmdDataSize = 0;
  curState = PRINTING;
}

void InputHandler::recvByte(uint8_t c) {
  // See if this is a control character
  if (c == COMMAND_CHAR) {
    curState = READING_COMMAND;
  }
  // If a control character has just been sent, get the command
  else if (curState == READING_COMMAND) {
    curCmd = (CommandByte)c;

    // Setting the cursor position requires two more bytes
    // So just set the state and return
    if (curCmd == SET_CURSOR_POS) {
      curState = READING_COMMAND_DATA;
      return;
    }
    // The rest of the commands don't require data so
    // just do the action then return to the printing state
    else if (curCmd == AUTO_SCROLL_ON)    LcdDisplay::autoScroll = true;
    else if (curCmd == AUTO_SCROLL_OFF)   LcdDisplay::autoScroll = false;
    else if (curCmd == CLEAR_SCREEN)      LcdDisplay::clear();
    else if (curCmd == GO_HOME)           LcdDisplay::goHome();
    else if (curCmd == UNDERLINE_ON)      LcdDisplay::setUnderline(true);
    else if (curCmd == UNDERLINE_OFF)     LcdDisplay::setUnderline(false);
    else if (curCmd == BLINK_ON)          LcdDisplay::setBlink(true);
    else if (curCmd == BLINK_OFF)         LcdDisplay::setBlink(false);
    else if (curCmd == CLEAR_KEY_BUFFER)  KeypadInput::keyPressBuffer.flush();

    // All commands other than SET_CURSOR_POS (handled above) don't require data
    curState = PRINTING;
    curCmd = NONE;
  }
  else if (curState == READING_COMMAND_DATA) {
    cmdData[cmdDataSize] = c;
    cmdDataSize++;

    // Currently setCursorPosition is the only command supported that requires data
    if ((curCmd == SET_CURSOR_POS) && (cmdDataSize == 2)) {
      LcdDisplay::moveCursor(cmdData[0], cmdData[1]);

      curState = PRINTING;
      cmdDataSize = 0;
    }
  }
  else if (curState == PRINTING) {
    LcdDisplay::write(c);
  }
}
