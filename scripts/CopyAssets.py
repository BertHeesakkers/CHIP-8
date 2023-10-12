import sys
import os
from distutils.dir_util import copy_tree

# parse script parameters
srcPath = sys.argv[1]
destPath = sys.argv[2]
print(f"Copy assets from {srcPath} to {destPath}.")

# make path for asset destination folder
if not os.path.isdir(destPath):
    os.makedirs(destPath)

# copy assets recursively
copy_tree(srcPath, destPath)
