{-# LANGUAGE OverloadedStrings #-}

module Main where

import SDL
import Control.Monad (unless)
import Control.Monad.State
import GHC.Word (Word8)
import Game.SdlUtils.Events
import Game.Lib
import Game.PixelRender

main :: IO ()
main = do
  initializeAll
  window <- createWindow "Haskell SDL2 stuffs" defaultWindow
  renderer <- createRenderer window (-1) defaultRenderer
  runStateT (gameLoop renderer) $ GameState { _gamei = 0, _globalFrame = emptyFrame (64, 64) }
  destroyWindow window
