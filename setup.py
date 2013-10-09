from distutils.core import setup, Extension

import pyzbase32

setup(
  name = 'pyzbase32',
  version = '0.0.1',
  ext_modules = [pyzbase32.ffi.verifier.get_extension()],
  requires = ['cffi'],
)
