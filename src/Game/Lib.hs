{-# LANGUAGE TemplateHaskell #-}

module Game.Lib where

import Control.Lens
import Control.Monad
import Control.Monad.State
import GHC.Word
import Game.SdlUtils.Events
import SDL hiding (get, set)

data GameState = GameState
  { _gamei :: Int
  }

makeLenses ''GameState

gameLoop :: Renderer -> StateT GameState IO ()
gameLoop renderer = do
  events <- pollEvents
  i <- gets _gamei
  frame <- gets _globalFrame
  rendererDrawColor renderer $= V4 (fromIntegral i) 64 (255 - fromIntegral i) 255
  clear renderer

  present renderer
  delay 15 -- should give <= 60 fps
  gamei %= \x -> (x + 1) `rem` 255
  unless (any isQuitEvent events) $ gameLoop renderer
