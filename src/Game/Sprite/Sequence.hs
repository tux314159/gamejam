module Game.Sprite.Sequence where

import Codec.BMP
import Control.Monad
import qualified Data.Text as T
import System.IO.Strict
import Data.Either

newtype SpriteSequence = SpriteSequence {seqFiles :: [BMP]}

loadSpriteSequence :: T.Text -> T.Text -> Int -> IO SpriteSequence
loadSpriteSequence name action n = do
  let bmps = map (Right . (\i -> readBMP $ T.unpack name ++ "-" ++ T.unpack action ++ show i)) [1..n]
      in return SpriteSequence {seqFiles = bmps}
