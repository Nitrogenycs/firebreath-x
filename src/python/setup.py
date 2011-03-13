#!/usr/bin/env python

"""
setup.py file for firebreath py wrapper module.
"""

from distutils.core import setup, Extension

setup (name = 'fbx',
       version = '0.1',
       author      = "",
       description = """Python wrapper for firebreath""",
		package_dir={'fbx': 'fbx'},
		packages=['fbx'],		
		data_files=[('Lib/site-packages/fbx', ['fbx/_FireBreath.pyd'])],
       )
