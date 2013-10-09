from distutils.core import setup, Extension

ext = Extension('pyzbase32.ext',
  sources = [
    'src/pyzbase32.c',
    'src/zbase32.c',
  ],
  depends = ['include/zbase32.h'],
  include_dirs = ['include'],
)

setup(
  name = 'pyzbase32',
  version = '0.0.1',
  ext_modules = [ext],
  packages = ['pyzbase32'],
)
