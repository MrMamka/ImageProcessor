# ImageProcessor
Console application that can apply filters to bmp format images

You can write path for file to read and path for file to write as arguments.  
Then you may use filters on image. List of available filter:  
Crop (-crop) with 2 arguments - width and height of new cropped image.  
Grayscale (-gs) without arguments - converts the image to shades of gray.  
Negative (-neg) without arguments - converts the image to negative.  
Sharpening (-sharp) without arguments - increases sharpness of the image.  
EdgeDetection (-edge) with 1 argument (between 0 and 1) - highlights borders of the image.  
GaussianBlur (-blur) with 1 argument (degree of blur) - blurring the image.  
Censorship (-censor) with 1 argument (size of new pixels) - censoring the image.  
