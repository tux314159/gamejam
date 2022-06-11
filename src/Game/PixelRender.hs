module Game.PixelRender where

import Control.Monad.Trans
import Data.Int
import qualified Data.Vector.Unboxed as V
import Foreign.C.Types
import SDL

type Pixel = (Int, Int, Int)

data Frame = Frame {fBuffer :: V.Vector Pixel, fDimensions :: (Int, Int)}

pixelSize :: Int
pixelSize = 8

emptyFrame :: (Int, Int) -> Frame
emptyFrame fdim@(w, h) =
  Frame
    { fBuffer = V.replicate (w * h) (255, 255, 255),
      fDimensions = fdim
    }

framePutPixel :: (Int, Int) -> Pixel -> Frame -> Frame
framePutPixel (x, y) pixel frame =
  let (fw, fh) = fDimensions frame
      idx = fw * x + y
      fbuf = fBuffer frame
   in frame {fBuffer = V.update fbuf $ V.fromList [(idx, pixel)]}

framePutPixels :: V.Vector ((Int, Int), Pixel) -> Frame -> Frame
framePutPixels pixels frame =
  V.foldl' (\f (c, p) -> framePutPixel c p f) frame pixels

renderFrame :: MonadIO m => Frame -> Renderer -> m ()
renderFrame frame renderer = do
  col <- get $ rendererDrawColor renderer

  let (fw, fh) = fDimensions frame
      coordConv n = (n `rem` fw, n `div` fw)
      fbuf = fBuffer frame
   in mapM_
        (\n -> renderPixel (coordConv n) (fbuf V.! n) renderer)
        [0 .. (fw * fh - 1)]

  -- reset colour
  rendererDrawColor renderer $= col
  where
    renderPixel (x, y) pixel@(r, g, b) renderer =
      let int2CInt = CInt . fromIntegral
          fi = fromIntegral
       in do
            rendererDrawColor renderer $= V4 (fi r) (fi g) (fi b) 255
            fillRect
              renderer
              ( Just $
                  Rectangle
                    (P (V2 (int2CInt $ x * pixelSize) (int2CInt $ y * pixelSize)))
                    (V2 (int2CInt pixelSize) (int2CInt pixelSize))
              )
