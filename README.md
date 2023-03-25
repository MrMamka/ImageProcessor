# ImageProcessor
Console application that can apply filters to bmp format images

You can write path for file to read and path for file to write as arguments.__
Then you may use filters on image. List of available filter:__
Crop (-crop) with 2 arguments - width and height of new cropped image.__
Grayscale (-gs) without arguments - converts the image to shades of gray.__
Negative (-neg) without arguments - converts the image to negative.__
Sharpening (-sharp) without arguments - increases sharpness of the image.__
EdgeDetection (-edge) with 1 argument (between 0 and 1) - highlights borders of the image.__
GaussianBlur (-blur) with 1 argument (degree of blur) - blurring the image.__
Censorship (-censor) with 1 argument (size of new pixels) - censoring the image.
