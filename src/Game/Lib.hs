{-# LANGUAGE TemplateHaskell #-}

module Game.Lib where

import Control.Lens
import Control.Monad.State
import Game.SdlUtils.Events
import GHC.Word
import Control.Monad
import SDL hiding (get, set)

newtype GameState = GameState {
  _gamei :: Word8
}
makeLenses ''GameState

gameLoop :: Renderer -> StateT GameState IO ()
gameLoop renderer = do
  events <- pollEvents
  i <- gets _gamei
  rendererDrawColor renderer $= V4 i 64 (255 - i) 255
  clear renderer
  present renderer
  delay 5
  gamei %= \x -> (x + 1) `rem` 255
  unless (any isQuitEvent events) $ gameLoop renderer
