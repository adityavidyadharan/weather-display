#!/usr/bin/python

import sys
import os

from PIL import Image
from PIL import ImageDraw
import numpy as np
import struct

isSWAP = False
# isSWAP = True

def main():

    len_argument = len(sys.argv)
    filesize = 0
    if (len_argument != 3):
      print ("")
      print ("Correct Usage:")
      print ("\tpython png2rgb565.py <png_file> <output_file>")
      print ("")
      sys.exit(0)

    try:
        im=Image.open(sys.argv[1])
        #print ("/* Image Width:%d Height:%d */" % (im.size[0], im.size[1]))
    except:
        print ("Fail to open png file ", sys.argv[1])
        sys.exit(0)

    image_height = im.size[1]
    image_width = im.size[0]


    background = Image.new('RGBA', im.size, (181, 176, 176))
    alpha_composite = Image.alpha_composite(background, im)
    im = alpha_composite.convert("RGB")
    im.quantize(colors=256, method=2)

    try:
        outfile = open(sys.argv[2],"w")
        name = sys.argv[1].split("/")[-1].split(".")[0]
        # outfile = open("icons/headers/" + name + ".h", "w")
    except:
        print ("Can't write the file %s" % sys.argv[2])
        sys.exit(0)

    # try:
    #     binoutfile = open(sys.argv[3],"wb")
    # except:
    #     print ("Can't write the binary file %s" % sys.argv[3])
    #     sys.exit(0)


    print("/* Image Width:%d Height:%d */" % (im.size[0], im.size[1]), file=outfile)
    print("const static uint16_t %s [] = {" % (name), file=outfile)

    pix = im.load()  #load pixel array

    for h in range(image_height):
        for w in range(image_width):
            if ((w) % 50 == 0):
                print (" ", file=outfile)
                print ("\t\t", file=outfile, end = '')

            if w < im.size[0]:
                R=pix[w,h][0]>>3
                G=pix[w,h][1]>>2
                B=pix[w,h][2]>>3

                rgb = (R<<11) | (G<<5) | B

                if (isSWAP == True):
                    swap_string_low = rgb >> 8
                    swap_string_high = (rgb & 0x00FF) << 8
                    swap_string = swap_string_low | swap_string_high
                    print ("0x%04x," %(swap_string), file=outfile, end = '')
                    # binoutfile.write(struct.pack('H', swap_string))
                else:
                    print ("0x%04x," %(rgb), file=outfile, end = '')
                    # binoutfile.write(struct.pack('H', rgb))
            else:
                rgb = 0
        #
    print ("", file=outfile)
    print ("};", file=outfile)

    outfile.close()
    # binoutfile.close()

    print ("PNG file \"%s\"" % sys.argv[1], "converted to \"%s\"" % name)

if __name__=="__main__":
  main()