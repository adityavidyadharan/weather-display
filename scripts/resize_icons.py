#resize png images in png/* to argument size

import os
from PIL import Image
import argparse

parser = argparse.ArgumentParser(description='Resize png images in png/* to argument size')
parser.add_argument('weather_size', metavar='N', type=int, help='size of weather icons')
parser.add_argument('svg_size', metavar='N', type=int, help='size of svg icons')
args = parser.parse_args()

for file in os.listdir("png"):
    if file.endswith(".png"):
        print("resizing " + file)
        im = Image.open("png/" + file)
        imResize = im.resize((args.weather_size,args.weather_size), Image.LANCZOS)
        imResize.save("png/resized/" + file, 'PNG', quality=90)

for file in os.listdir("png/svg"):
    if file.endswith(".svg"):
        # convert to png
        print("converting " + file)
        file_name = file.split(".")[0].replace("-", "_")
        os.system("/Applications/Inkscape.app/Contents/MacOS/inkscape -w %d -h %d %s -o %s --export-background='#ffffff'" % (args.svg_size, args.svg_size, "png/svg/" + file, "png/resized/" + file_name + ".png"))