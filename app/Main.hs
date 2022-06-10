{-# LANGUAGE OverloadedStrings #-}

module Main where

import SDL
import Control.Monad (unless)
import GHC.Word (Word8)
import Game.SdlUtils.Events

main :: IO ()
main = do
  initializeAll
  window <- createWindow "Haskell SDL2 stuffs" defaultWindow
  renderer <- createRenderer window (-1) defaultRenderer
  gameLoop renderer 1
  destroyWindow window

gameLoop :: Renderer -> Word8 -> IO()
gameLoop renderer i = do
  events <- pollEvents
  rendererDrawColor renderer $= V4 i 64 (255 - i) 255
  clear renderer
  present renderer
  delay 5
  unless (any isQuitEvent events) $ gameLoop renderer $ (i + 1) `rem` 255
