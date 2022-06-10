module Game.SdlUtils.Events where

import SDL.Input.Keyboard
import SDL.Event

isQuitEvent :: Event -> Bool
isQuitEvent event = 
  case eventPayload event of
       QuitEvent -> True
       _ -> False

keyPressed :: Keycode -> Event -> Bool
keyPressed keycode event =
  case eventPayload event of
       KeyboardEvent kbev ->
         keyboardEventKeyMotion kbev == Pressed &&
           keysymKeycode (keyboardEventKeysym kbev) == keycode
       _ -> False

