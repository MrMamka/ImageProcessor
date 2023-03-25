# ImageProcessor
Console application that can apply filters to bmp format images

You can write path for file to read and path for file to write as arguments.\n
Then you may use filters on image. List of available filter:\n
Crop (-crop) with 2 arguments - width and height of new cropped image.\n
Grayscale (-gs) without arguments - converts the image to shades of gray.\n
Negative (-neg) without arguments - converts the image to negative.\n
Sharpening (-sharp) without arguments - increases sharpness of the image.\n
EdgeDetection (-edge) with 1 argument (between 0 and 1) - highlights borders of the image.\n
GaussianBlur (-blur) with 1 argument (degree of blur) - blurring the image.\n
Censorship (-censor) with 1 argument (size of new pixels) - censoring the image.\n
